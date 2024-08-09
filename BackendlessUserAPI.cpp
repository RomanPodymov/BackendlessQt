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
        networkAccessManager,
        this,
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
        networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/users/login",
        {
            {"login", login},
            {"password", password}
        }, true, [=](QNetworkReply* reply){
            auto replyValue = reply->readAll();
            qDebug() << replyValue;

            auto errorCode = extractError(replyValue);
            switch (errorCode) {
            case BackendlessErrorCode::noError:
                userToken = extractToken(replyValue);
                emit signInUserResult(BackendlessSignInUser(userToken));
                break;
            default:
                emit signInUserResult(BackendlessError(errorCode, ""));
                break;
            }
        }
    );
}

void BackendlessUserAPI::validateUserToken() {
    return request(
        networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/users/isvalidusertoken/" + userToken,
        {

        }, false, [=](QNetworkReply* reply){
            auto replyValue = reply->readAll();
            qDebug() << replyValue;

            if (replyValue == "true") {
                emit validateUserTokenResult(true);
            } else if (replyValue == "false") {
                emit validateUserTokenResult(false);
            } else {
                emit validateUserTokenResult(BackendlessValidateUserTokenError::invalidResponse);
            }
        }
    );
}

BackendlessErrorCode BackendlessUserAPI::extractError(QByteArray replyValue) {
    QJsonParseError jsonError;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(replyValue, &jsonError);
    QJsonObject jsonObject = jsonResponse.object();
    return static_cast<BackendlessErrorCode>(jsonObject["code"].toInt());
}

QString BackendlessUserAPI::extractToken(QByteArray replyValue) {
    QJsonParseError jsonError;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(replyValue, &jsonError);
    QJsonObject jsonObject = jsonResponse.object();
    return jsonObject["user-token"].toString();
}
