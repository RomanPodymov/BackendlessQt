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

            emit registerUserResult();
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

            #ifdef BACKENDLESS_VARIANT_RESPONSE
            extractResult(
                replyValue,
                [=](auto user) {
                    emit signInUserResult(user);
                },
                [=](auto beError) {
                    emit signInUserResult(beError);
                },
                [=](auto jsonError) {
                    emit signInUserResult(jsonError);
                }
            );
            #else
            extractResult(
                replyValue,
                [=](auto user) {
                    emit signInUserSuccess(user);
                },
                [=](auto beError) {
                    emit signInUserErrorBackendless(beError);
                },
                [=](auto jsonError) {
                    emit signInUserErrorJson(jsonError);
                }
            );
            #endif
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

            #ifdef BACKENDLESS_VARIANT_RESPONSE
            if (replyValue == "true") {
                emit validateUserTokenResult(true);
            } else if (replyValue == "false") {
                emit validateUserTokenResult(false);
            } else {
                emit validateUserTokenResult(BackendlessValidateUserTokenError::invalidResponse);
            }
            #else

            #endif
        }
    );
}

void BackendlessUserAPI::extractResult(
    QByteArray replyValue,
    std::function<void(BackendlessSignInUser)> const& onUser,
    std::function<void(BackendlessError)> const& onBEError,
    std::function<void(QJsonParseError)> const& onJSONError
) {
    QJsonParseError jsonError;
    auto jsonResponse = QJsonDocument::fromJson(replyValue, &jsonError);

    switch (jsonError.error) {
    case QJsonParseError::NoError:
        break;
    default:
        onJSONError(jsonError);
    }

    auto jsonObject = jsonResponse.object();
    auto code = static_cast<BackendlessErrorCode>(jsonObject["code"].toInt());
    switch (code) {
        case BackendlessErrorCode::noError:
            onUser(BackendlessSignInUser(
                jsonObject["user-token"].toString()
            ));
        default:
            onBEError(BackendlessError(
                code,
                jsonObject["message"].toString()
            ));
    }
}
