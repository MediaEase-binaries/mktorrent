# Command Line Options

## Basic Syntax

```bash
mktorrent [options] <target>
```

Where `<target>` is the file or directory to create a torrent from.

## Common Options

| Short | Long Option | Description | Example |
|-------|------------|-------------|----------|
| `-a` | `--announce` | Tracker's announce URL (required) | `-a http://tracker.example.com/announce` |
| `-o` | `--output` | Output file name | `-o my.torrent` |
| `-l` | `--piece-length` | Set piece length (default: auto) | `-l 20` (1MB pieces) |
| `-p` | `--private` | Make torrent private | `-p` |
| `-c` | `--comment` | Add comment | `-c "My torrent"` |
| `-n` | `--name` | Set torrent name (default: basename) | `-n "Custom Name"` |
| `-s` | `--source` | Set source flag for private trackers | `-s "MY-GROUP"` |
| `-t` | `--threads` | Set number of threads for hashing | `-t 4` |
| `-v` | `--verbose` | Be verbose | `-v` |
| `-h` | `--help` | Show help | `-h` |

## Advanced Options

| Short | Long Option | Description | Example |
|-------|------------|-------------|----------|
| `-w` | `--web-seed` | Add web seed URLs | `-w http://direct.example.com/file` |
| `-x` | `--exclude` | Exclude files matching pattern | `-x "*.txt"` |
| `-f` | `--force` | Overwrite output file | `-f` |
| | `--no-creation-date` | Don't write creation date | `--no-creation-date` |
| | `--no-created-by` | Don't write created by | `--no-created-by` |
| | `--cross-seed` | Ensure unique info hash | `--cross-seed` |

## Piece Length

The piece length is automatically chosen based on the total size:

| Total Size | Piece Length |
|------------|-------------|
| ≤ 50MB | 15 (32KB) |
| ≤ 100MB | 16 (64KB) |
| ≤ 200MB | 17 (128KB) |
| ≤ 400MB | 18 (256KB) |
| ≤ 800MB | 19 (512KB) |
| ≤ 1.6GB | 20 (1MB) |
| ≤ 3.2GB | 21 (2MB) |
| ≤ 6.4GB | 22 (4MB) |
| > 6.4GB | 23 (8MB) |

You can override this with the `-l` option.

## Examples

1. Create a basic torrent:
```bash
mktorrent -a http://tracker.example.com/announce path/to/files/
```

2. Create a private torrent with custom piece length:
```bash
mktorrent -a http://tracker.example.com/announce -p -l 21 -o release.torrent path/to/files/
```

3. Create a torrent with multiple trackers and web seeds:
```bash
mktorrent -a http://tracker1.example.com/announce \
          -a http://tracker2.example.com/announce \
          -w http://direct1.example.com/file \
          -w http://direct2.example.com/file \
          path/to/files/
```

4. Create a torrent for a private tracker with source flag:
```bash
mktorrent -a http://private-tracker.example.com/announce \
          -p \
          -s "MY-GROUP" \
          -c "Release Info" \
          -n "Release.Name.1080p" \
          path/to/files/
```

5. Create a torrent with multiple threads and verbose output:
```bash
mktorrent -a http://tracker.example.com/announce \
          -t 4 \
          -v \
          path/to/files/
``` 
