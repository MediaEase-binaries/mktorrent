# MKTorrent

[![Current Version](https://img.shields.io/github/v/release/tomcdj71/mktorrent?label=current%20version)](https://github.com/tomcdj71/mktorrent/releases)
![Github Actions CI CD](https://github.com/tomcdj71/mktorrent/workflows/Build%20Mktorrent/badge.svg)

A simple command-line utility to create BitTorrent metainfo files.

## Features

- Fast, multi-threaded hashing with OpenSSL support
- Support for large files (>2GB)
- Configurable piece length
- Multiple tracker URLs
- Private flag support
- Web seed URLs support
- Source string support
- Comment field support
- Linux only

## Quick Start

1. [Install MKTorrent](docs/Installation-Guide.md)
2. Create a torrent:
   ```bash
   mktorrent -a http://tracker.example.com/announce -o output.torrent input_file
   ```

## Documentation

For detailed documentation, please visit our [documentation](docs/Home.md) which includes:

- [Installation Guide](docs/Installation-Guide.md)
- [Command Line Options](docs/Command-Line-Options.md)
- [Release Packages](docs/Release-Packages.md)
- [FAQ](docs/FAQ.md)

## Support

If you encounter any issues:
1. Check the [FAQ](docs/FAQ.md)
2. Search [existing issues](https://github.com/tomcdj71/mktorrent/issues)
3. Open a new issue with detailed information

## License

MKTorrent is released under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file for details.

## Building a Debian Package

### Using FPM (Recommended)

[FPM](https://github.com/jordansissel/fpm) provides a simplified way to build Debian packages without needing to create a complete Debian packaging structure.

#### Prerequisites

Install FPM and required dependencies:

```bash
sudo apt-get update
sudo apt-get install ruby ruby-dev build-essential
sudo gem install fpm
```

#### Build and Package

1. First, compile mktorrent:

```bash
# Clone the repository
git clone https://github.com/tomcdj71/mktorrent.git
cd mktorrent

# Build with your desired options
cmake -B build \
  -DMKTORRENT_LONG_OPTIONS=ON \
  -DMKTORRENT_PTHREADS=ON \
  -DMKTORRENT_OPENSSL=ON \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build
```

2. Create staging directory structure:

```bash
# Create necessary directories
mkdir -p staging/usr/bin
mkdir -p staging/usr/share/man/man1

# Copy binary to staging
cp build/mktorrent staging/usr/bin/

# Copy man page
cp man/mktorrent.1 staging/usr/share/man/man1/

# Make executable
chmod +x staging/usr/bin/mktorrent
```

3. Build the .deb package with FPM:

```bash
# Extract version from CMakeLists.txt
VERSION=$(awk '/project\(mktorrent/,/\)/ { if ($1 ~ /VERSION/) print $2 }' CMakeLists.txt | tr -d ')')

# Create the package
fpm -s dir -t deb -C staging \
  --name mktorrent \
  --version $VERSION \
  --architecture amd64 \
  --description "Simple command-line torrent file creator" \
  --url "https://github.com/tomcdj71/mktorrent" \
  --maintainer "Your Name <your.email@example.com>" \
  --license "Public Domain" \
  --depends "libc6" \
  --depends "libssl3" \
  --deb-compression xz \
  --deb-priority optional \
  --category net \
  usr/bin usr/share/man
```

This will create a file named `mktorrent_$VERSION_amd64.deb` in your current directory.

4. Install and test the package:

```bash
sudo dpkg -i mktorrent_*.deb
mktorrent --version
```

#### Advanced Options

For smaller packages, you can strip debug symbols:

```bash
# Strip debug symbols
strip --strip-unneeded staging/usr/bin/mktorrent

# Optionally compress with UPX for even smaller binaries
sudo apt-get install upx
upx --best --lzma staging/usr/bin/mktorrent
```

You can add additional metadata to better describe the build configuration:

```bash
# Add build options to the description
fpm -s dir -t deb -C staging \
  --name mktorrent \
  --version $VERSION \
  --architecture amd64 \
  --description "Simple command-line torrent file creator with OpenSSL=$OPENSSL and pthreads=$PTHREADS support" \
  # ... rest of options
```

This approach mirrors the build process used in the project's GitHub Actions workflow.
