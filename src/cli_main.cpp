#include <QCoreApplication>
#include <iostream>
#include "qt_gh-update-checker.hpp"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    const auto args = app.arguments();

    if (args.size() < 3) {
        std::cerr << "Usage: qt_gh-update-checker <repo-url> <local-version>\n";
        return 1;
    }

    QString repoUrl      = args.at(1);
    QString localVersion = args.at(2);

    try {
        auto info = qtgh::check_github_update(repoUrl, localVersion);

        std::cout << "Local version:  " << localVersion.toStdString() << "\n";
        std::cout << "Remote version: " << info.latestVersion.toStdString() << "\n";
        std::cout << "Update:         " << (info.hasUpdate ? "YES" : "NO") << "\n";

        return info.hasUpdate ? 2 : 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 3;
    }
}
