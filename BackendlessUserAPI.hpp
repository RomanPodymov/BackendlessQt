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

enum class BackendlessError {
    invalidLoginOrPassword = 3003
};

class BackendlessUserAPI: public QObject {
    Q_OBJECT

public:
    BackendlessUserAPI(QNetworkAccessManager&, QString _appId, QString _apiKey, QString _endpoint = "https://eu-api.backendless.com/");
    void registerUser(BackendlessUser);
    void signInUser(QString, QString);
    void validateUserToken();

signals:
    void userRegistered();
    void userSignedIn();
    void userSignInError(BackendlessError);
    void userTokenValidated(bool);

private:
    int extractError(QByteArray replyValue);
    QString extractToken(QByteArray);
    void request(QString, QMap<QString, QString>, bool, std::function<void(QNetworkReply*)> const&);

private:
    QNetworkAccessManager& networkAccessManager;
    QString appId;
    QString apiKey;
    QString endpoint;
    QString userToken;
};
