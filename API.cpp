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
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

void API::registerUser(QString appId, QString key, BackendlessUser user) {
    return request(
        "https://eu-api.backendless.com/" + appId + "/" + key + "/users/register",
        {
            {"email", user.email},
            {"name", user.name},
            {"password", user.password}
        }, [&](QNetworkReply*){
            emit userRegistered();
        }
    );
}

void API::signInUser(QString appId, QString key, QString login, QString password) {
    return request(
        "https://eu-api.backendless.com/" + appId + "/" + key + "/users/login",
        {
            {"login", login},
            {"password", password}
        }, [&](QNetworkReply* reply){
            QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
            QJsonObject jsonObject = jsonResponse.object();
            QString token = jsonObject["user-token"].toString();
            qDebug() << token;
            emit userSignedIn(token);
        }
    );
}

void API::request(QString urlString, QMap<QString, QString> customParams, std::function<void(QNetworkReply*)> handleRequest) {
    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString params = "{";

    for (auto [key, value] : customParams.asKeyValueRange()) {
        params += "\"";
        params += key;
        params += "\"";
        params += ":";
        params += "\"";
        params += value;
        params += "\"";
        params += ",";
    }

    params.removeLast();
    params += "}";

    QObject::connect(&networkAccessManager, &QNetworkAccessManager::finished, [handleRequest](QNetworkReply* reply) {
        auto replyValue = reply->readAll();
        qDebug() << replyValue;
        handleRequest(reply);
    });
    networkAccessManager.post(request, params.toUtf8());
}
