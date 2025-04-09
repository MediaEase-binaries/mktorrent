# Change Log
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/)
and this project adheres to [Semantic Versioning](https://semver.org/).

## [v1.4.2] - 2025-04-09
### Fixed
- Improves SHA-1 implementation security by using local buffers to prevent data modification
- Ensures proper handling of padding and final transformations in SHA-1 calculations

### Changed
- Refactors SHA-1 logic for better code readability and maintainability
- Adds detailed comments for better code documentation

## [v1.4.1] - 2025-04-09
### Fixed
- Adds compatibility macros for custom SHA1 implementation
- Fixes timeout handling in AIO operations
- Resolves buffer allocation failures in high-memory scenarios

### Added
- Introduces asynchronous I/O (AIO) for improved file processing performance
- Adds system resource limits and thread affinity support
- Implements CPU core detection for better scalability

### Changed
- Optimizes buffer allocation based on system memory and threads
- Improves progress tracking and cleanup mechanisms
- Enhances error handling and retry logic for I/O operations

## [v1.4.0] - 2025-04-09
### Added
- Introduces memory-mapped I/O for large files
- Adds prefetching for concurrent file processing
- Implements cache-aligned memory allocation

### Changed
- Refactors file reading logic for better modularity
- Optimizes I/O operations for better performance
- Updates build system for modern tooling support

## [v1.3.3] - 2025-04-09
### Fixed
- Improves URL validation and protocol checks
- Fixes memory allocation issues in path handling

### Changed
- Streamlines absolute file path construction
- Optimizes handling of comma-separated URL lists
- Removes outdated test data and result files

## [v1.3.2] - 2025-04-09
### Added
- Adds comprehensive URL validation for input lists
- Introduces new test data files for validation coverage

### Fixed
- Fixes potential memory leaks in path handling
- Resolves issues with invalid input handling

### Changed
- Enhances error handling in main function
- Adds fallback constants for better portability
- Improves maintainability with default version string

## [v1.3.1] - 2025-04-09
### Fixed
- Fixes conditional compilation issues
- Resolves header inclusion problems

### Changed
- Enforces USE_PTHREADS checks
- Removes redundant preprocessor directives
- Improves portability across platforms

## [v1.3.0] - 2025-04-09
### Added
- Introduces comprehensive test suite
- Adds scripts for test execution and validation
- Implements torrent parser for validation

### Changed
- Updates test framework for better coverage
- Improves test file and directory creation
- Enhances error reporting in tests

## [v1.2.8] - 2025-04-09
### Fixed
- Fixes signal handling export issues
- Resolves memory leaks in hashing operations

### Changed
- Refactors hashing implementation using OpenSSL's EVP API
- Improves progress logging with ETA and throughput metrics
- Enhances error handling and user interrupt support

## [v1.2.7] - 2025-04-09
### Added
- Adds signal handling for SIGINT and SIGTERM
- Introduces utility for counting linked list nodes

### Changed
- Improves error handling and messaging
- Enhances verbose output details
- Refines user interruption handling

## [v1.2.6] - 2025-04-09
### Fixed
- Fixes null pointer dereferences
- Resolves file writing issues

### Changed
- Enhances error reporting across functions
- Improves cross-seed data generation
- Updates file writing functions to return status codes

## [v1.2.5] - 2025-04-09
### Fixed
- Fixes file descriptor leaks
- Resolves memory management issues

### Added
- Adds version display function
- Introduces execution time measurement

### Changed
- Improves file handling error checks
- Enhances verbose output for user feedback

## [v1.2.4] - 2025-04-09
### Fixed
- Fixes potential memory leaks
- Resolves input validation issues

### Changed
- Improves error handling in write functions
- Enhances logging for file operations
- Updates metadata handling

## [v1.2.3] - 2025-04-09
### Added
- Adds version and build information display
- Introduces error handling for hashing operations

### Changed
- Improves file descriptor management
- Enhances code readability
- Updates resource cleanup procedures

## [v1.2.2] - 2025-04-09
### Fixed
- Fixes memory management issues
- Resolves buffer allocation problems

### Changed
- Simplifies buffer and file handling
- Streamlines progress reporting
- Removes redundant verbose mode

## [v1.2.1] - 2025-04-09
### Added
- Adds optimal block size calculation
- Introduces verbose mode for progress reporting

### Changed
- Improves buffer management logic
- Enhances memory allocation strategies
- Updates progress reporting metrics

## [v1.2.0] - 2025-04-09
### Added
- Adds support for cross-seeding
- Introduces file exclusion by pattern
- Implements improved thread management

### Changed
- Migrates build system to CMake
- Updates documentation structure
- Removes legacy build files

### Fixed
- Fixes memory leaks in hash calculation
- Resolves path handling issues
- Improves error handling mechanisms

## [1.1] - 2017-01-11
### Added
- Autodetect the number of CPUs available <esmil@mailme.dk>
- Option for source string added to torrent info (`-s`), included in infohash.
  Often used by private trackers to create a unique infohash to prevent
  peer-leak and the possibility to track the trackers that do use leaked
  torrents. Having this option in mktorrent make it possible to create a
  infohash accurate torrent to the tracker you want to upload it to
### Changed
- Make `-a` (announce list) optional
- Optional announce URL even for private torrents. No need to require announce
  for private torrents, they are added by most private trackers anyway and they
  modify the infohash so you'd have to redownload their modified torrent with
  injected unique announce URL anyway. (@mathieui, fix from @jrwren)
### Fixed
- DHT makes trackers optional, so remove the warning

## [1.0] - 2009-08-25
### Added
- Add an exception to the license to allow distributions to link mktorrent to the OpenSSL library

## [0.7] - 2009-05-31
### Fixed
- Proper support for large files on certain 32bit OS's.
  Finally mktorrent properly handles files larger than 2Gb on 32bit Linux.
  Fixes for use on Windows under MinGW/Cygwin.

## [0.6] - 2009-05-13
### Added
- Support for multiple web seeds
### Changed
- Raised allowable piece size
- Only add the announce-list entry if there are more than one tracker.
  Thanks to Vladimir Vučićević for reporting.
- Include public domain SHA1 implementation to make the OpenSSL dependency optional.
- Lots of portability improvements. Now compiles on Linux, MinGW, OpenBSD, OSX,
  SunOS and probably many more. A big thanks to Edwin Amsler for reporting and
  testing.
- Rewritten multi threaded hashing to optimise CPU usage on multi processor machines

## [0.5] - 2009-03-01
### Added
- Support for multiple trackers
- Support for web seed (thanks to Justin Camerer)
### Changed
- Better error messages

## [0.4] - 2009-02-22
### Added
- Support for the private flag

## [0.3] - 2009-02-22
### Fixed
- Bug concerning files longer than 2^32 bytes
- Command line parameters

## [0.2] - 2009-02-22
### Added
- Support for single file torrents
- Support for long options can now be disabled at compile time

## [0.1] - 2009-02-22
Initial release
