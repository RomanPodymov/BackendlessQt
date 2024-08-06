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

API::API(QString _appId, QString _apiKey, QString _endpoint): QObject(), appId(_appId), apiKey(_apiKey), endpoint(_endpoint) {

}

void API::registerUser(BackendlessUser user) {
    return request(
        endpoint + appId + "/" + apiKey + "/users/register",
        {
            {"email", user.email},
            {"name", user.name},
            {"password", user.password}
        }, true, [=](QNetworkReply* reply){
            auto replyValue = reply->readAll();
            qDebug() << replyValue;
            emit userRegistered();
        }
    );
}

void API::signInUser(QString login, QString password) {
    return request(
        endpoint + appId + "/" + apiKey + "/users/login",
        {
            {"login", login},
            {"password", password}
        }, true, [=](QNetworkReply* reply){
            auto replyValue = reply->readAll();
            qDebug() << replyValue;
            QJsonParseError jsonError;
            QJsonDocument jsonResponse = QJsonDocument::fromJson(replyValue, &jsonError);
            QJsonObject jsonObject = jsonResponse.object();
            QString token = jsonObject["user-token"].toString();
            userToken = token;
            qDebug() << token;
            emit userSignedIn(token);
        }
    );
}

void API::loadTableItems(QString tableName) {
    return request(
        endpoint + appId + "/" + apiKey + "/data/" + tableName,
        {

        }, false, [=](QNetworkReply* reply){
            auto replyValue = reply->readAll();
            qDebug() << replyValue;
            emit tableItemsLoaded(replyValue);
        }
    );
}

void API::request(
    QString urlString,
    QMap<QString, QString> customParams,
    bool isPost,
    std::function<void(QNetworkReply*)> const& handleRequest
) {
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

    QObject::connect(&networkAccessManager, &QNetworkAccessManager::finished, this, [handleRequest](QNetworkReply* reply) {
        handleRequest(reply);
    }, Qt::SingleShotConnection);
    if (isPost) {
        networkAccessManager.post(request, params.toUtf8());
    } else {
        networkAccessManager.get(request);
    }
}
