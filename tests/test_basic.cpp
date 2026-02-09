#include <QCoreApplication>
#include <iostream>
#include "qt_gh-update-checker.hpp"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);

    try {
        auto info = qtgh::check_github_update(
            "https://github.com/nlohmann/json",
            "0.0.1"
        );

        std::cout << "Latest: " << info.latestVersion.toStdString() << "\n";
        return 0;
    }
    catch (...) {
        return 1;
    }
}
