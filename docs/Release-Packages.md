# Release Packages

Each release of MKTorrent includes several packages and files to accommodate different use cases and systems.

## Package Types

### Debian Packages (.deb)

For each release configuration, I provide a Debian package:

```
mktorrent_1.4.2_openssl-ON_pthreads-ON-ubuntu-latest_amd64.deb
mktorrent_1.4.2_openssl-ON_pthreads-OFF-ubuntu-latest_amd64.deb
mktorrent_1.4.2_openssl-OFF_pthreads-ON-ubuntu-latest_amd64.deb
mktorrent_1.4.2_openssl-OFF_pthreads-OFF-ubuntu-latest_amd64.deb
```

Package naming convention:
- `mktorrent`: Package name
- `1.4.2`: Version number
- `openssl-ON/OFF`: OpenSSL support
- `pthreads-ON/OFF`: POSIX threads support
- `ubuntu-latest`: Build platform
- `amd64`: Architecture

### Package Contents

Each .deb package contains:
- `/usr/bin/mktorrent`: Main executable
- Documentation and man pages
- Package metadata

## Build Configuration

All packages are built with the following common CMake options:

```cmake
-DMKTORRENT_LONG_OPTIONS=ON
-DMKTORRENT_USE_GITREV_VERSION=ON
-DCMAKE_BUILD_TYPE=RelWithDebInfo
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```

Additional options vary by package variant:
- OpenSSL support: `-DMKTORRENT_OPENSSL=ON/OFF`
- POSIX threads support: `-DMKTORRENT_PTHREADS=ON/OFF`

### Build Artifacts
Each build generates:
- `compile_commands.json`: Compilation database
- `target_graph.dot`: CMake dependency graph

## Build Variants

We provide different build configurations to suit various needs:

### Full Featured Build
- OpenSSL: ON
- POSIX Threads: ON
- Long Options: ON
```
mktorrent_1.4.2_openssl-ON_pthreads-ON-ubuntu-latest_amd64.deb
```
Best for: General use, maximum performance

### Minimal Build
- OpenSSL: OFF
- POSIX Threads: OFF
- Long Options: ON
```
mktorrent_1.4.2_openssl-OFF_pthreads-OFF-ubuntu-latest_amd64.deb
```
Best for: Systems with minimal dependencies

### Single-Threaded with OpenSSL
- OpenSSL: ON
- POSIX Threads: OFF
- Long Options: ON
```
mktorrent_1.4.2_openssl-ON_pthreads-OFF-ubuntu-latest_amd64.deb
```
Best for: Systems where threading is problematic

### Multi-Threaded without OpenSSL
- OpenSSL: OFF
- POSIX Threads: ON
- Long Options: ON
```
mktorrent_1.4.2_openssl-OFF_pthreads-ON-ubuntu-latest_amd64.deb
```
Best for: Systems without OpenSSL

## Additional Files

Each release also includes:

### Source Code
- `mktorrent-1.4.2.tar.gz`: Source code archive
- `mktorrent-1.4.2.zip`: Source code archive

### Build Artifacts
- `compile_commands.json`: Compilation database for each variant
- `target_graph.dot`: CMake dependency graph

## Legacy Releases

Mktorrent v1.1 assets are available in the [pobrn's repo](https://github.com/pobrn/mktorrent/releases), but I recommend using the latest version for:
- Better performance
- Bug fixes
- Security updates
- New features 
