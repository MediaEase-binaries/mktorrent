# Testing Guide

This document provides information about the test suite for MKTorrent.

## Test Suite Overview

The test suite is designed to verify MKTorrent's functionality and prevent regressions. It consists of a core framework and individual test files covering different aspects of the application.

### Core Components

- `test_framework.sh`: Core framework providing common testing functions
- `run_tests.sh`: Main script that runs all test cases
- `torrent_parser.py`: Python script to parse and validate torrent files
- Individual test files for different test categories

## Test Categories

1. **Single File Tests** (`test_single_file.sh`)
   - Basic torrent creation with default settings
   - Custom piece length
   - Custom announce URL
   - Private flag

2. **Directory Tests** (`test_directory.sh`)
   - Directory torrent creation with default settings
   - Custom name
   - Comments
   - Multiple announce URLs

3. **Error Cases** (`test_error_cases.sh`)
   - Non-existent files
   - Invalid piece length
   - Missing required parameters
   - Existing output file

4. **Interrupt Handling** (`test_interrupt.sh`)
   - SIGINT handling
   - SIGTERM handling
   - Cleanup of partial files

5. **Performance Tests** (`test_performance.sh`)
   - Tests with different file sizes (small, medium, large)
   - Different thread counts
   - Different piece length settings
   - _Note: These tests are disabled by default_

## Running Tests

### Basic Usage

```bash
# Run all tests
cd tests
./run_tests.sh

# Run specific test file
cd tests
source test_framework.sh
./test_single_file.sh  # Or any other specific test file
print_summary
```

### Configuration

Tests can be configured with environment variables:

| Variable | Description |
|----------|-------------|
| `PERFORMANCE_TESTS=1` | Enable performance tests |
| `PERFORMANCE_LARGE_TESTS=1` | Enable large file tests (200MB+) |

## Test Framework Functions

The framework provides several utility functions:

- `init_test_env`: Initialize test environment
- `cleanup_test_env`: Clean up test environment
- `create_test_file`: Create a test file of specified size
- `create_test_dir`: Create a directory with multiple test files
- `run_test`: Run a test command and check result
- `validate_torrent`: Validate a torrent file
- `print_summary`: Print test summary

## Adding New Tests

To add a new test:

1. Create a new test file named `test_<description>.sh`
2. Source the framework at the top of your file
3. Create test fixtures with `create_test_file` or `create_test_dir`
4. Run tests with `run_test` function
5. Validate results with `validate_torrent` function

Example:
```bash
#!/bin/bash
# Test a new feature

# Create test files
create_test_file "test.dat" 1024

# Run test
run_test "New feature test" \
    "$MKTORRENT -v -o $TEST_RESULTS_DIR/new_feature.torrent $TEST_DATA_DIR/test.dat"

# Validate results
validate_torrent "$TEST_RESULTS_DIR/new_feature.torrent"
```

## Test Validation

The test suite uses `torrent_parser.py` to validate generated torrent files. This script:

- Parses torrent metadata
- Verifies file inclusion
- Checks piece size and count
- Validates hash values
- Ensures correct structure

## Continuous Integration

Tests are automatically run in the CI pipeline for:

- Each pull request
- Main branch updates
- Release candidates

### CI Configuration

The CI pipeline:
1. Builds MKTorrent with test support
2. Runs all test categories
3. Reports test results
4. Fails on any test failure

## Troubleshooting

### Common Issues

1. **Test Framework Not Found**
   ```
   Error: test_framework.sh not found
   Solution: Ensure you're in the tests directory
   ```

2. **Permission Issues**
   ```
   Error: Cannot create test files
   Solution: Check directory permissions
   ```

3. **Performance Tests Failing**
   ```
   Error: Performance tests timeout
   Solution: Adjust system limits or disable with PERFORMANCE_TESTS=0
   ```

### Debugging

```bash
# Enable verbose output
MKTORRENT_DEBUG=1 ./run_tests.sh

# Run specific test with debug
source test_framework.sh
MKTORRENT_DEBUG=1 ./test_single_file.sh
```

## Test Data

The test suite includes various test files and directories:

- Small test files (1KB-1MB)
- Medium test files (10MB-100MB)
- Large test files (1GB+)
- Test directories with various structures

### Test Data Structure

```
tests/
├── data/              # Test data files
│   ├── small/        # Small test files
│   ├── medium/       # Medium test files
│   └── large/        # Large test files
├── results/          # Expected test results
└── scripts/          # Test utility scripts
```

## Test Results

Test results are stored in the `tests/results/` directory and include:

- Torrent files
- Hash values
- Performance metrics
- Error logs

### Result Verification

The test suite compares generated torrents with expected results to ensure:

- Correct file inclusion
- Accurate piece size calculation
- Proper hash generation
- Correct metadata structure

## Test Maintenance

Regular maintenance tasks:

1. Update test data as needed
2. Verify test results
3. Clean up old test artifacts
4. Review test coverage 
