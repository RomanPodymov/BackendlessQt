#include "API.hpp"
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkRequest>

void API::f(QString urlString) {
    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery params;
    params.addQueryItem("something", "something");

    QObject::connect(networkAccessManager, &QNetworkAccessManager::finished, [=](QNetworkReply* reply){

    });

    networkAccessManager->post(request, params.query().toUtf8());
}
