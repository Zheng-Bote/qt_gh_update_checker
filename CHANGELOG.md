# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- Future features and improvements will be documented here

### Changed

- Ongoing improvements and refactoring

### Fixed

- Bug fixes will be documented here

### Deprecated

- Deprecations will be documented here

### Removed

- Removals will be documented here

### Security

- Security-related fixes will be documented here

## [0.1.0] - 2026-02-09

### Added

- Initial release of qt_gh-update-checker
- Header-only C++ library for checking GitHub repository updates
- Semantic versioning (SemVer) support with parsing and comparison
- `SemVer` struct for version handling
  - `parse()` static method for string parsing
  - Three-way comparison operator (`<=>`) support
- `toGithubApiUrl()` function to convert GitHub web URLs to API endpoints
- `http_get()` inline function for synchronous HTTP GET requests
  - Built-in error handling
  - User-Agent header configuration
- `UpdateInfo` struct containing version information and update status
- `check_github_update()` main API function
  - Repository URL validation
  - GitHub API integration
  - Automatic update detection
  - Exception-based error handling
- CLI tool (`qt_gh-update-checker`)
  - Plain text output format
  - JSON output format (`--json` flag)
  - Configurable exit codes for CI/CD integration
- Comprehensive test suite
  - `test_basic` executable for sanity checks
  - Tests for SemVer parsing
  - Tests for GitHub API URL conversion
  - Tests for update detection logic
- CMake build system
  - C++23 support
  - Qt6 integration (Core and Network modules)
  - CMake package config for easy integration
  - Support for `find_package()` discovery
  - Support for `FetchContent` integration
- Installation targets
  - Header installation
  - CMake export targets
  - CLI executable installation
- Complete documentation
  - README.md with build, installation, and usage instructions
  - Doxygen-compatible inline code documentation
  - API reference for all public functions and structures
  - CLI usage examples
  - Troubleshooting guide
- SPDX license headers in all source files
  - MIT license identification
  - Copyright attribution

### Dependencies

- Qt6 6.9+
  - Core module for QString and containers
  - Network module for HTTP requests
- CMake 3.23+
- C++23 compatible compiler

### Project Metadata

- Repository: https://github.com/Zheng-Bote/qt_gh_update_checker
- License: MIT
- Author: Zheng-Bote
- Version: 0.1.0
- Last Updated: 2026-02-09

[Unreleased]: https://github.com/Zheng-Bote/qt_gh_update_checker/compare/v0.1.0...HEAD
[0.1.0]: https://github.com/Zheng-Bote/qt_gh_update_checker/releases/tag/v0.1.0
