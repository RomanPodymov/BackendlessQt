//
//  BackendlessUserAPI.cpp
//  BackendlessQt
//
//  Created by Roman Podymov on 07/08/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "BackendlessUserAPI.hpp"

BackendlessUserAPI::BackendlessUserAPI(QNetworkAccessManager* _networkAccessManager, QString _appId, QString _apiKey, QString _endpoint): QObject(),
    networkAccessManager(_networkAccessManager),
    appId(_appId),
    apiKey(_apiKey),
    endpoint(_endpoint) {

}

void BackendlessUserAPI::registerUser(BackendlessRegisterUser user) {
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

void BackendlessUserAPI::signInUser(QString login, QString password) {
    return request(
        endpoint + appId + "/" + apiKey + "/users/login",
        {
            {"login", login},
            {"password", password}
        }, true, [=](QNetworkReply* reply){
            auto replyValue = reply->readAll();
            qDebug() << replyValue;

            auto errorCode = extractError(replyValue);
            if (errorCode != 0) {
                emit signInUserResult(BackendlessError::invalidLoginOrPassword);
            } else {
                userToken = extractToken(replyValue);
                emit signInUserResult(BackendlessSignInUser(userToken));
            }
        }
    );
}

void BackendlessUserAPI::validateUserToken() {
    return request(
        endpoint + appId + "/" + apiKey + "/users/isvalidusertoken/" + userToken,
        {

        }, false, [=](QNetworkReply* reply){
            auto replyValue = reply->readAll();
            emit userTokenValidated(replyValue == "true");
        }
    );
}

int BackendlessUserAPI::extractError(QByteArray replyValue) {
    QJsonParseError jsonError;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(replyValue, &jsonError);
    QJsonObject jsonObject = jsonResponse.object();
    return jsonObject["code"].toInt();
}

QString BackendlessUserAPI::extractToken(QByteArray replyValue) {
    QJsonParseError jsonError;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(replyValue, &jsonError);
    QJsonObject jsonObject = jsonResponse.object();
    return jsonObject["user-token"].toString();
}

void BackendlessUserAPI::request(
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

    QObject::connect(networkAccessManager, &QNetworkAccessManager::finished, this, [handleRequest](QNetworkReply* reply) {
        handleRequest(reply);
    }, Qt::SingleShotConnection);
    if (isPost) {
        networkAccessManager->post(request, params.toUtf8());
    } else {
        networkAccessManager->get(request);
    }
}
