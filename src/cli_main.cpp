// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2026 Zheng-Bote
//
// cli_main.cpp - GitHub Update Checker CLI Tool
//
// Command-line tool for checking GitHub repository updates.
// Supports both plain text and JSON output formats.
//
// Usage:
//   qt_gh-update-checker <repo-url> <local-version>
//   qt_gh-update-checker --json <repo-url> <local-version>
//
// Examples:
//   qt_gh-update-checker https://github.com/nlohmann/json 3.0.0
//   qt_gh-update-checker --json https://github.com/nlohmann/json 3.0.0
//
// Exit codes:
//   0 - No update available
//   1 - Invalid arguments
//   2 - Update available
//   3 - Error occurred

#include <QCoreApplication>
#include <iostream>
#include "qt_gh-update-checker.hpp"

/// @brief Main entry point for the update checker CLI
/// @param argc Argument count
/// @param argv Argument vector
/// @return Exit code: 0=no update, 1=error, 2=update available, 3=exception
int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    const auto args = app.arguments();

    bool jsonMode = false;
    QString repoUrl;
    QString localVersion;

    // Parse command-line arguments
    // Format: qt_gh-update-checker [--json] <repo-url> <local-version>
    if (args.size() >= 2 && args.at(1) == "--json") {
        jsonMode = true;

        if (args.size() < 4) {
            std::cerr << "Usage: qt_gh-update-checker [--json] <repo-url> <local-version>\n";
            return 1;
        }

        repoUrl      = args.at(2);
        localVersion = args.at(3);
    } else {
        if (args.size() < 3) {
            std::cerr << "Usage: qt_gh-update-checker [--json] <repo-url> <local-version>\n";
            return 1;
        }

        repoUrl      = args.at(1);
        localVersion = args.at(2);
    }

    try {
        // Fetch update information from GitHub
        auto info = qtgh::check_github_update(repoUrl, localVersion);

        // Output result in requested format
        if (jsonMode) {
            std::cout << "{\n";
            std::cout << "  \"local\": \"" << localVersion.toStdString() << "\",\n";
            std::cout << "  \"remote\": \"" << info.latestVersion.toStdString() << "\",\n";
            std::cout << "  \"update\": " << (info.hasUpdate ? "true" : "false") << "\n";
            std::cout << "}\n";
        } else {
            std::cout << "Local version:  " << localVersion.toStdString() << "\n";
            std::cout << "Remote version: " << info.latestVersion.toStdString() << "\n";
            std::cout << "Update:         " << (info.hasUpdate ? "YES" : "NO") << "\n";
        }

        return info.hasUpdate ? 2 : 0;
    }
    catch (const std::exception& e) {
        // Handle errors and output in requested format
        if (jsonMode) {
            std::cout << "{\n";
            std::cout << "  \"error\": \"" << e.what() << "\"\n";
            std::cout << "}\n";
        } else {
            std::cerr << "Error: " << e.what() << "\n";
        }
        return 3;
    }
}
