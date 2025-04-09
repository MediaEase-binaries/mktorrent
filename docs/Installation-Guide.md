# Installation Guide

This guide provides detailed instructions for installing MKTorrent on your system.

## Table of Contents
- [Prerequisites](#prerequisites)
- [Quick Installation](#quick-installation)
- [Detailed Installation](#detailed-installation)
  - [Building from Source](#building-from-source)
  - [Package Installation](#package-installation)
- [Configuration Options](#configuration-options)
- [Verification](#verification)
- [Troubleshooting](#troubleshooting)

## Prerequisites

### Required Dependencies
| Dependency | Minimum Version | Purpose |
|------------|----------------|----------|
| CMake | 3.20 | Build system |
| GCC/Clang | Any recent | Compiler |
| POSIX threads | - | Multi-threading support |

### Optional Dependencies
| Dependency | Purpose | Benefit |
|------------|---------|----------|
| OpenSSL | SHA-1 implementation | Faster hashing |

### Installing Dependencies

**Ubuntu/Debian:**
```bash
# Required dependencies
sudo apt-get update
sudo apt-get install build-essential cmake

# Optional but recommended
sudo apt-get install libssl-dev
```

## Quick Installation

### Direct Package Download

| Build Type | OpenSSL | PTHREADS | Use Case | Download Command |
|------------|---------|----------|----------|------------------|
| Full Featured | ON | ON | Maximum performance | `wget "https://github.com/tomcdj71/mktorrent/releases/latest/download/mktorrent_1.4.2_openssl-ON_pthreads-ON-ubuntu-latest_amd64.deb"` |
| Minimal | OFF | OFF | Minimal dependencies | `wget "https://github.com/tomcdj71/mktorrent/releases/latest/download/mktorrent_1.4.2_openssl-OFF_pthreads-OFF-ubuntu-latest_amd64.deb"` |
| Single-Threaded | ON | OFF | Systems with threading issues | `wget "https://github.com/tomcdj71/mktorrent/releases/latest/download/mktorrent_1.4.2_openssl-ON_pthreads-OFF-ubuntu-latest_amd64.deb"` |
| Multi-Threaded | OFF | ON | Systems without OpenSSL | `wget "https://github.com/tomcdj71/mktorrent/releases/latest/download/mktorrent_1.4.2_openssl-OFF_pthreads-ON-ubuntu-latest_amd64.deb"` |

After downloading, install the package:
```bash
sudo dpkg -i mktorrent_*.deb
```

### From Source (Quick)
```bash
git clone https://github.com/tomcdj71/mktorrent.git
cd mktorrent
cmake -B build
cmake --build build
sudo cmake --install build
```

## Detailed Installation

### Building from Source

1. **Clone the Repository**
   ```bash
   git clone https://github.com/tomcdj71/mktorrent.git
   cd mktorrent
   ```

2. **Configure the Build**
   
   Basic configuration:
   ```bash
   cmake -B build
   ```

   Advanced configuration:
   ```bash
   cmake -B build \
     -DCMAKE_BUILD_TYPE=Release \
     -DMKTORRENT_OPENSSL=ON \
     -DMKTORRENT_PTHREADS=ON \
     -DMKTORRENT_LONG_OPTIONS=ON
   ```

3. **Build the Project**
   ```bash
   cmake --build build
   ```

4. **Install (Optional)**
   ```bash
   sudo cmake --install build
   ```

### Package Installation

#### Ubuntu/Debian
1. **Download Package**
   - From [releases page](https://github.com/tomcdj71/mktorrent/releases), or
   - Using wget:
     ```bash
     VERSION="1.4.2" \
     OPENSSL="ON" \
     PTHREADS="ON" 
     wget https://github.com/tomcdj71/mktorrent/releases/download/v${VERSION}/mktorrent_${VERSION}_openssl-${OPENSSL}_pthreads-${PTHREADS}-ubuntu-latest_amd64.deb
     ```

2. **Install Package**
   ```bash
   sudo dpkg -i mktorrent_*_amd64.deb
   ```

## Configuration Options

### CMake Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `MKTORRENT_OPENSSL` | ON | Use OpenSSL's SHA-1 implementation |
| `MKTORRENT_PTHREADS` | ON | Enable POSIX threads support |
| `MKTORRENT_LONG_OPTIONS` | ON | Enable GNU-style long options |
| `MKTORRENT_NO_HASH_CHECK` | OFF | Disable hash-size consistency check |
| `MKTORRENT_USE_GITREV_VERSION` | OFF | Include git commit in version |
| `CMAKE_BUILD_TYPE` | Release | Build type (Debug/Release/RelWithDebInfo) |

### Example Configurations

**Maximum Performance:**
```bash
cmake -B build \
  -DCMAKE_BUILD_TYPE=Release \
  -DMKTORRENT_OPENSSL=ON \
  -DMKTORRENT_PTHREADS=ON
```

**Minimal Build:**
```bash
cmake -B build \
  -DMKTORRENT_OPENSSL=OFF \
  -DMKTORRENT_PTHREADS=OFF \
  -DMKTORRENT_LONG_OPTIONS=OFF
```

## Verification

After installation, verify that mktorrent is working correctly:

```bash
# Check version
mktorrent --version

# Check help
mktorrent --help

# Create a test torrent
mktorrent -a http://example.com/announce -o test.torrent test_file
```

## Troubleshooting

### Common Issues and Solutions

#### 1. CMake Configuration Fails
```
Problem: CMake command not found
Solution: sudo apt-get install cmake
```

#### 2. Build Fails with OpenSSL Errors
```
Problem: OpenSSL development files missing
Solution: sudo apt-get install libssl-dev
```

#### 3. Threading Support Issues
```
Problem: POSIX threads not found
Solution: sudo apt-get install libc6-dev
```

### Getting Help

If you encounter problems:

1. **Check Prerequisites**
   - Verify all required dependencies are installed
   - Ensure minimum versions are met

2. **Gather Information**
   - System information
   - Complete error messages
   - Build logs

3. **Seek Help**
   1. Check the [FAQ](FAQ) page
   2. Search [existing issues](https://github.com/tomcdj71/mktorrent/issues)
   3. Open a new issue with:
      - Detailed system information
      - Complete error messages
      - Steps to reproduce
      - Build configuration used 
