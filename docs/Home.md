# MKTorrent

MKTorrent is a command-line utility for creating BitTorrent metainfo files, designed for efficiency and ease of use.

## Features

- Fast, multi-threaded hashing with OpenSSL support
- Support for large files (>2GB)
- Configurable piece length
- Multiple tracker URLs
- Private flag support
- Web seed URLs support
- Source string support
- Comment field support
- Cross-platform compatibility (Linux, macOS, Windows)

## Quick Start

1. [Install MKTorrent](Installation-Guide)
2. Create a torrent:
   ```bash
   mktorrent -a http://tracker.example.com/announce -o output.torrent input_file
   ```

## Documentation

- [Installation Guide](Installation-Guide) - Detailed installation instructions
- [Command Line Options](Command-Line-Options) - Complete list of available options
- [Release Packages](Release-Packages) - Available packages and build variants
- [FAQ](FAQ) - Frequently Asked Questions
- [Contributing](Contributing) - Guidelines for contributing to the project

## Support

If you encounter any issues:
1. Check the [FAQ](FAQ)
2. Search [existing issues](https://github.com/tomcdj71/mktorrent/issues)
3. Open a new issue with detailed information

## License

MKTorrent is released under the GNU General Public License v3.0. See the [LICENSE](https://github.com/tomcdj71/mktorrent/blob/main/LICENSE) file for details. 
