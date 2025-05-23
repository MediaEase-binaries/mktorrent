/*
This file is part of mktorrent
Copyright (C) 2007, 2009 Emil Renner Berthing

mktorrent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

mktorrent is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*/


#include <stdlib.h>      /* exit(), srandom() */
#include <errno.h>       /* errno */
#include <string.h>      /* strerror() */
#include <stdio.h>       /* printf() etc. */
#include <sys/stat.h>    /* S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH */
#include <fcntl.h>       /* open() */
#include <unistd.h>      /* close(), read() */
#include <time.h>        /* clock_gettime() */
#include <signal.h>      /* signal handling */
#include <inttypes.h>    /* PRIuMAX etc. */
#include <pthread.h>

/* Define constants that may be missing */
#ifndef MAX_OPENFD
#define MAX_OPENFD 100
#endif

#ifndef PROGRESS_PERIOD
#define PROGRESS_PERIOD 200000
#endif

/* Define clock types if not already defined */
#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#endif

#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif

#include "export.h"
#include "mktorrent.h"
#include "init.h"
#include "hash.h"
#include "output.h"
#include "msg.h"
#include "ll.h"

#ifdef ALLINONE
/* include all .c files in alphabetical order */

#include "ftw.c"

#ifdef USE_PTHREADS
#include "hash_pthreads.c"
#else
#include "hash.c"
#endif

#include "init.c"
#include "ll.c"
#include "msg.c"
#include "output.c"

#ifndef USE_OPENSSL
#include "sha1.c"
#endif

#endif /* ALLINONE */

#ifndef O_BINARY
#define O_BINARY 0
#endif

#ifndef S_IRGRP
#define S_IRGRP 0
#endif

#ifndef S_IROTH
#define S_IROTH 0
#endif

#ifndef VERSION
#define VERSION "unspecified_version"
#endif

#ifndef BUILD_CFG
#define BUILD_CFG "unspecified_build_type"
#endif

/* global variables */
EXPORT volatile int force_exit = 0;

/* Signal handler for graceful exit */
static void handle_signal(int signum)
{
	if (signum == SIGINT || signum == SIGTERM) {
		fprintf(stderr, "\nReceived signal %d, cleaning up...\n", signum);
		force_exit = 1;
	}
}

/*
 * create and open the metainfo file for writing and create a stream for it
 * we don't want to overwrite anything, so abort if the file is already there
 * and force is false
 */
static FILE *open_file(const char *path, int force)
{
	int fd;  /* file descriptor */
	FILE *f; /* file stream */

	if (!path || !*path) {
		fprintf(stderr, "Error: Invalid path specified\n");
		return NULL;
	}

	int flags = O_WRONLY | O_BINARY | O_CREAT;
	if (!force)
		flags |= O_EXCL;

	/* open and create the file if it doesn't exist already */
	fd = open(path, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0) {
		fprintf(stderr, "Error: Cannot create '%s': %s\n", path, strerror(errno));
		return NULL;
	}

	/* create the stream from this filedescriptor */
	f = fdopen(fd, "wb");
	if (f == NULL) {
		close(fd);  /* Don't leak file descriptor if fdopen fails */
		fprintf(stderr, "Error: Cannot create stream for '%s': %s\n", 
            path, strerror(errno));
		return NULL;
	}

	return f;
}

/*
 * close the metainfo file
 */
static int close_file(FILE *f)
{
	if (!f) return 0;  /* Accept NULL pointers */

	/* close the metainfo file */
	if (fclose(f) != 0) {
		fprintf(stderr, "Error: Cannot close stream: %s\n", strerror(errno));
		return -1;
	}
	return 0;
}

/*
 * Count the number of nodes in a linked list
 */
static unsigned int count_ll_nodes(struct ll *list)
{
	unsigned int count = 0;
	
	if (!list) return 0;
	
	LL_FOR(node, list) {
		count++;
	}
	
	return count;
}

/*
 * main().. it starts
 */
int main(int argc, char *argv[])
{
	/* Check for --version first */
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-V") == 0) {
			printf("mktorrent %s (c) 2007, 2009 Emil Renner Berthing\n", VERSION);
			return EXIT_SUCCESS;
		}
	}

	FILE *file = NULL;	/* stream for writing to the metainfo file */
	unsigned char *hash = NULL; /* hash string */
	int exit_code = EXIT_SUCCESS;
	struct metafile m = {
		/* options */
		0,    /* piece_length, 0 by default indicates length should be calculated automatically */
		NULL, /* announce_list */
		NULL, /* torrent_name */
		NULL, /* metainfo_file_path */
		NULL, /* web_seed_url */
		NULL, /* comment */
		0,    /* target_is_directory  */
		0,    /* no_creation_date */
		0,	  /* no_created_by */
		0,    /* private */
		NULL, /* source string */
		0,    /* cross_seed */
		0,    /* verbose */
		0,    /* force_overwrite */
		NULL, /* exclude_list */
#ifdef USE_PTHREADS
		0,    /* threads, initialised by init() */
#endif

		/* information calculated by read_dir() */
		0,    /* size */
		NULL, /* file_list */
		0     /* pieces */
	};

	/* Set up signal handling */
	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);

	/* Seed PRNG with current time */
	struct timespec ts;
	if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
		fprintf(stderr, "Failed to get time: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	srandom(ts.tv_nsec ^ ts.tv_sec);

	/* Process command line options */
	int init_result = init(&m, argc, argv);
	if (init_result != 0) {
		if (init_result == EXIT_SUCCESS) {
			/* This is a normal exit (e.g. --version or --help) */
			return EXIT_SUCCESS;
		}
		fprintf(stderr, "Failed to initialize from command line arguments\n");
		cleanup_metafile(&m);
		/* Return EXIT_FAILURE on error from init */
		return EXIT_FAILURE;
	}

	/* Check for interrupt */
	if (force_exit) {
		fprintf(stderr, "Operation cancelled by user\n");
		cleanup_metafile(&m);
		return EXIT_FAILURE;
	}

	/* open the file stream now, so we don't have to abort
	   _after_ we did all the hashing in case we fail */
	file = open_file(m.metainfo_file_path, m.force_overwrite);
	if (!file) {
		cleanup_metafile(&m);
		return EXIT_FAILURE;
	}

	/* Start measuring time */
	struct timespec start_time;
	if (clock_gettime(CLOCK_MONOTONIC, &start_time) == -1) {
		fprintf(stderr, "Failed to get start time: %s\n", strerror(errno));
	}

	/* Calculate hash string... */
	hash = make_hash(&m);
	if (!hash || force_exit) {
		if (force_exit) {
			fprintf(stderr, "Hashing cancelled by user\n");
		} else {
			fprintf(stderr, "Failed to create hashes\n");
		}
		exit_code = EXIT_FAILURE;
		goto cleanup;
	}

	/* Stop measuring time */
	struct timespec end_time;
	if (clock_gettime(CLOCK_MONOTONIC, &end_time) == -1) {
		fprintf(stderr, "Failed to get end time: %s\n", strerror(errno));
	} else {
		/* Calculate elapsed time */
		double elapsed = (end_time.tv_sec - start_time.tv_sec) + 
						(end_time.tv_nsec - start_time.tv_nsec) / 1e9;

		if (m.verbose) {
			printf("Hashing completed in %.2f seconds (%.2f MB/s)\n", 
				elapsed, (m.size / (1024.0 * 1024.0)) / elapsed);
		}
	}

	/* Write the metainfo to file */
	if (write_metainfo(file, &m, hash) != 0) {
		fprintf(stderr, "Failed to write metainfo file\n");
		exit_code = EXIT_FAILURE;
		goto cleanup;
	}

cleanup:
	/* Clean up resources */
	if (file && close_file(file) != 0) {
		/* close_file already printed an error message */
		exit_code = EXIT_FAILURE;
	}
	
	cleanup_metafile(&m);
	free(hash);

	if (exit_code == EXIT_SUCCESS && m.verbose) {
		printf("Torrent created successfully: %s\n", m.metainfo_file_path);
		if (m.target_is_directory) {
			printf("Files: %u, Total size: %" PRIuMAX " bytes\n", 
				count_ll_nodes(m.file_list), m.size);
		}
	}

	/* Return success or failure */
	return exit_code;
}
