//
//  API.cpp
//  BackendlessQt
//
//  Created by Roman Podymov on 30/07/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#include "API.hpp"
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkRequest>

void API::registerUser(QString appId, QString key, BackendlessUser user) {
    request(
        "https://api.backendless.com/" + appId + "/" + key + "/users/register",
        {
         {"email", user.email},
         {"name", user.name},
         {"password", user.password}
        }
    );
}

void API::request(QString urlString, QMap<QString, QString> customParams) {
    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery params;

    for (auto [key, value] : customParams.asKeyValueRange()) {
        params.addQueryItem(key, value);
    }

    QObject::connect(networkAccessManager, &QNetworkAccessManager::finished, [=](QNetworkReply* reply){
        auto replyValue = reply->readAll();
        qDebug() << "Method called";
        qDebug() << replyValue;
    });

    networkAccessManager->post(request, params.query().toUtf8());
}
