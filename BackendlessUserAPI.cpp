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

            emit signInUserResult(extractResult(replyValue));
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

std::variant<BackendlessSignInUser, BackendlessError, QJsonParseError> BackendlessUserAPI::extractResult(QByteArray replyValue) {
    QJsonParseError jsonError;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(replyValue, &jsonError);

    switch (jsonError.error) {
    case QJsonParseError::NoError:
        break;
    default:
        return jsonError;
    }

    QJsonObject jsonObject = jsonResponse.object();
    auto code = static_cast<BackendlessErrorCode>(jsonObject["code"].toInt());
    switch (code) {
        case BackendlessErrorCode::noError:
            return BackendlessSignInUser(
                jsonObject["user-token"].toString()
            );
        default:
            return BackendlessError(
                code,
                jsonObject["message"].toString()
            );
    }
}
