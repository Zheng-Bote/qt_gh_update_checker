# qt_gh-update-checker

A lightweight, header-only C++ library and CLI tool for checking GitHub repository updates. It provides semantic versioning (SemVer) comparison and integrates seamlessly with Qt6.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)]()
[![CMake](https://img.shields.io/badge/CMake-3.23+-blue.svg)]()

[![GitHub release (latest by date)](https://img.shields.io/github/v/release/Zheng-Bote/qt_gh_update_checker?logo=GitHub)](https://github.com/Zheng-Bote/qt_gh_update_checker/releases)

[Report Issue](https://github.com/Zheng-Bote/qt_gh_update_checker/issues) · [Request Feature](https://github.com/Zheng-Bote/qt_gh_update_checker/pulls)

---

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
<!-- END doctoc generated TOC please keep comment here to allow auto update -->

---

## Features

- **Header-only library** – Easy integration into Qt-based projects
- **Semantic versioning support** – Parse and compare SemVer tags
- **GitHub API integration** – Fetch latest release information from public repositories
- **CLI tool** – Check updates from the command line with JSON output support
- **Modern C++** – Built with C++23 features and Qt6
- **CMake integration** – Easily integrate into other CMake projects via `find_package()`

## Requirements

- **CMake** 3.23 or higher
- **C++23 compiler** (GCC, Clang, or MSVC with C++23 support)
- **Qt6** 6.9 or higher (Core and Network modules)

### Installation of Dependencies

#### Ubuntu/Debian:

```bash
apt-get install cmake build-essential qt6-base-dev qt6-tools-dev
```

#### macOS (Homebrew):

```bash
brew install cmake qt@6
```

#### Windows (vcpkg):

```bash
vcpkg install qt6:x64-windows cmake
```

## Build

### Clone and Setup

```bash
git clone https://github.com/Zheng-Bote/qt_gh_update_checker.git
cd qt_gh_update_checker
```

### Build with CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Build Options

- **Default**: Builds the header-only library and CLI tool
- **With tests**: Tests are built automatically by default

### Verify Build

Check that these targets were created:

- `qt_gh-update-checker` – CLI executable
- `test_basic` – Test executable

## Installation

Install the library and CLI tool to your system:

```bash
cd build
cmake --install .
```

This will install:

- Headers to `<prefix>/include/`
- CMake config files to `<prefix>/lib/cmake/qt_gh_update_checker/`
- CLI executable to `<prefix>/bin/qt_gh-update-checker`

### Using as a Dependency

#### Option 1: find_package() (after installation)

After installation, use it in your CMake project:

```cmake
find_package(qt_gh_update_checker REQUIRED)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE qt_gh_update_checker::qt_gh_update_checker)
```

#### Option 2: FetchContent (download at configure time)

Alternatively, use CMake's `FetchContent` to automatically download and build the library:

```cmake
cmake_minimum_required(VERSION 3.23)
project(my_project)

include(FetchContent)

FetchContent_Declare(
    qt_gh_update_checker
    GIT_REPOSITORY https://github.com/Zheng-Bote/qt_gh_update_checker.git
    GIT_TAG main  # or a specific version tag
)

FetchContent_MakeAvailable(qt_gh_update_checker)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE qt_gh_update_checker::qt_gh_update_checker)
```

FetchContent automatically handles downloading, configuring, and building the dependency.

## Usage

### CLI Tool

Check for updates to a GitHub repository:

```bash
qt_gh-update-checker <repo-url> <local-version>
```

#### Examples:

**Plain text output:**

```bash
qt_gh-update-checker https://github.com/nlohmann/json 3.0.0
```

Output:

```
Local version:  3.0.0
Remote version: 3.11.2
Update:         YES
```

**JSON output:**

```bash
qt_gh-update-checker --json https://github.com/nlohmann/json 3.0.0
```

Output:

```json
{
  "local": "3.0.0",
  "remote": "3.11.2",
  "update": true
}
```

**Exit codes:**

- `0` – No update available
- `2` – Update available
- `1` – Error occurred

### Library Usage

Include the header and use the API:

```cpp
#include "qt_gh-update-checker.hpp"
#include <iostream>

int main() {
    try {
        auto info = qtgh::check_github_update(
            "https://github.com/nlohmann/json",
            "3.0.0"
        );

        std::cout << "Latest version: " << info.latestVersion.toStdString() << "\n";
        std::cout << "Update available: " << (info.hasUpdate ? "yes" : "no") << "\n";

        return info.hasUpdate ? 2 : 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
```

## Testing

### Run Tests

```bash
cd build
ctest
```

Or run the test executable directly:

```bash
./test_basic
```

### Test Details

The `test_basic` executable runs sanity checks on:

- Semantic version parsing
- GitHub API URL conversion
- Update availability checks

## Project Structure

```
qt_gh-update-checker/
├── CMakeLists.txt              # Build configuration
├── README.md                   # This file
├── include/
│   └── qt_gh-update-checker.hpp    # Main header-only library
├── src/
│   └── cli_main.cpp            # CLI tool implementation
├── tests/
│   └── test_basic.cpp          # Basic functionality tests
├── cmake/
│   └── qt_gh_update_checkerConfig.cmake.in  # CMake package config
└── build/                      # Build directory (created during build)
```

## API Reference

### `qtgh::SemVer` Structure

Represents a semantic version (major.minor.patch).

```cpp
struct SemVer {
    int major, minor, patch;
    static SemVer parse(const QString& v);  // Parse from string
};
```

### `qtgh::check_github_update()`

Main function for checking updates.

```cpp
UpdateInfo check_github_update(
    const QString& repoUrl,
    const QString& localVersion
);
```

**Parameters:**

- `repoUrl`: GitHub repository URL (e.g., `https://github.com/owner/repo`)
- `localVersion`: Current version string (e.g., `"1.0.0"`)

**Returns:** `UpdateInfo` struct with:

- `latestVersion` – Latest tag/release version
- `hasUpdate` – Boolean indicating if an update is available

**Throws:** `std::runtime_error` on invalid input or network errors

## Troubleshooting

### CMake not finding Qt6

Ensure Qt6 is installed and its CMake config is in the search path:

```bash
cmake -DCMAKE_PREFIX_PATH=/path/to/qt6 ..
```

### Network errors when checking updates

- Verify internet connectivity
- Check if the GitHub repository URL is correct and public
- GitHub API rate limiting may apply (60 requests/hour for unauthenticated)

### C++ standard errors

Ensure your compiler supports C++23:

```bash
g++ --version  # GCC 11+
clang --version  # Clang 13+
```

## Version

Current version: **0.1.0**

## Support

For issues or questions, please open an issue in the repository.

# Contributing

Contributions are welcome! Please fork the repository and create a pull request.

1. Fork the Project
2. Create your Feature Branch (git checkout -b feature/AmazingFeature)
3. Commit your Changes (git commit -m 'Add some AmazingFeature')
4. Push to the Branch (git push origin feature/AmazingFeature)
5. Open a Pull Request

# License

Distributed under the MIT License. See LICENSE for more information.

Copyright (c) 2026 ZHENG Robert

# Author

[![Zheng Robert - Core Development](https://img.shields.io/badge/Github-Zheng_Robert-black?logo=github)](https://www.github.com/Zheng-Bote)

## Code Contributors

![Contributors](https://img.shields.io/github/contributors/Zheng-Bote/qt_gh_update_checker?color=dark-green)

---

**Happy checking! 🚀** :vulcan_salute:
