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
