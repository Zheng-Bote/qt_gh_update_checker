#pragma once
#include <QString>
#include <QRegularExpression>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <stdexcept>

namespace qtgh {

// ---------------------------------------------------------
// SemVer
// ---------------------------------------------------------
struct SemVer {
    int major = 0;
    int minor = 0;
    int patch = 0;

    static SemVer parse(const QString& v) {
        static QRegularExpression re(R"(v?(\d+)\.(\d+)(?:\.(\d+))?)");
        auto m = re.match(v);
        if (!m.hasMatch())
            throw std::runtime_error(("Invalid SemVer: " + v).toStdString());

        SemVer sv;
        sv.major = m.captured(1).toInt();
        sv.minor = m.captured(2).toInt();
        sv.patch = m.captured(3).isEmpty() ? 0 : m.captured(3).toInt();
        return sv;
    }

    auto operator<=>(const SemVer&) const = default;
};

// ---------------------------------------------------------
// GitHub URL → API URL
// ---------------------------------------------------------
inline QString toGithubApiUrl(const QString& url) {
    if (url.contains("api.github.com"))
        return url;

    static QRegularExpression re(R"(https://github\.com/([^/]+)/([^/]+))");
    auto m = re.match(url);
    if (!m.hasMatch())
        throw std::runtime_error(("Invalid GitHub URL: " + url).toStdString());

    QString owner = m.captured(1);
    QString repo  = m.captured(2);

    if (repo.endsWith(".git"))
        repo.chop(4);

    return QStringLiteral("https://api.github.com/repos/%1/%2/releases/latest")
        .arg(owner, repo);
}

// ---------------------------------------------------------
// HTTP GET (synchron, ohne QObject-Vererbung)
// ---------------------------------------------------------
inline QByteArray http_get(const QString& url) {
    QNetworkAccessManager mgr;
    QNetworkRequest req{QUrl(url)};
    req.setHeader(QNetworkRequest::UserAgentHeader, "Qt-gh-update-checker");

    QEventLoop loop;
    QObject::connect(&mgr, &QNetworkAccessManager::finished,
                     &loop, &QEventLoop::quit);

    QNetworkReply* reply = mgr.get(req);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        auto msg = reply->errorString();
        reply->deleteLater();
        throw std::runtime_error(("Network error: " + msg).toStdString());
    }

    QByteArray data = reply->readAll();
    reply->deleteLater();
    return data;
}

// ---------------------------------------------------------
// UpdateInfo
// ---------------------------------------------------------
struct UpdateInfo {
    bool hasUpdate;
    QString latestVersion;
};

// ---------------------------------------------------------
// Hauptfunktion
// ---------------------------------------------------------
inline UpdateInfo check_github_update(const QString& repoUrl,
                                      const QString& localVersion)
{
    QString apiUrl = toGithubApiUrl(repoUrl);

    QByteArray data = http_get(apiUrl);
    auto doc = QJsonDocument::fromJson(data);
    if (!doc.isObject())
        throw std::runtime_error("GitHub API returned non-object JSON");

    auto obj = doc.object();

    if (!obj.contains("tag_name") || !obj["tag_name"].isString()) {
        if (obj.contains("message") && obj["message"].isString()) {
            throw std::runtime_error(
                ("GitHub API error: " + obj["message"].toString()).toStdString()
            );
        }
        throw std::runtime_error("GitHub API returned no valid tag_name");
    }

    QString latest = obj["tag_name"].toString();

    SemVer local  = SemVer::parse(localVersion);
    SemVer remote = SemVer::parse(latest);

    return { remote > local, latest };
}

} // namespace qtgh
