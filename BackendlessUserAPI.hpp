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
#include "BackendlessUser.hpp"

enum class BackendlessErrorCode {
    noError = 0,
    invalidLoginOrPassword = 3003
};

struct BackendlessError {
    BackendlessErrorCode code;

    BackendlessError(
        BackendlessErrorCode _code
    ): code(_code) { }
};

class BackendlessUserAPI: public QObject {
    Q_OBJECT

public:
    BackendlessUserAPI(QNetworkAccessManager*, QString _appId, QString _apiKey, QString _endpoint = "https://eu-api.backendless.com/");

    void registerUser(BackendlessRegisterUser);
    void signInUser(QString, QString);
    void validateUserToken();

signals:
    void userRegistered();
    void signInUserResult(std::variant<BackendlessSignInUser, BackendlessError>);
    void userTokenValidated(bool);

private:
    BackendlessErrorCode extractError(QByteArray replyValue);
    QString extractToken(QByteArray);
    void request(QString, QMap<QString, QString>, bool, std::function<void(QNetworkReply*)> const&);

private:
    QNetworkAccessManager* networkAccessManager;
    QString appId;
    QString apiKey;
    QString endpoint;
    QString userToken;
};
