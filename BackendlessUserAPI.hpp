//
//  BackendlessUserAPI.hpp
//  BackendlessQt
//
//  Created by Roman Podymov on 07/08/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#include <QString>
#include <QMap>
#include <QNetworkAccessManager>
#include <QJsonParseError>
#include "BackendlessUser.hpp"
#include "BasicAPI.hpp"

enum class BackendlessErrorCode {
    noError = 0,
    invalidLoginOrPassword = 3003
};

enum class BackendlessValidateUserTokenError {
    invalidResponse
};

struct BackendlessError {
    BackendlessErrorCode code;
    QString message;

    BackendlessError(
        BackendlessErrorCode _code,
        QString _message
    ): code(_code), message(_message) { }
};

class BackendlessUserAPI: public QObject, public BasicAPI {
    Q_OBJECT

public:
    BackendlessUserAPI(QNetworkAccessManager*, QString _appId, QString _apiKey, QString _endpoint = "https://eu-api.backendless.com/");

    void registerUser(BackendlessRegisterUser);
    void signInUser(QString, QString);
    void validateUserToken();

signals:
    void userRegistered();
    void signInUserResult(std::variant<BackendlessSignInUser, BackendlessError, QJsonParseError>);
    void validateUserTokenResult(std::variant<bool, BackendlessValidateUserTokenError>);

private:
    std::variant<BackendlessSignInUser, BackendlessError, QJsonParseError> extractResult(QByteArray replyValue);

private:
    QNetworkAccessManager* networkAccessManager;
    QString appId;
    QString apiKey;
    QString endpoint;
    QString userToken;
};
