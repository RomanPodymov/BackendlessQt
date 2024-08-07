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
#include "BackendlessQt/BackendlessUser.hpp"

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
    void userTokenValidated(bool);

private:
    void request(QString, QMap<QString, QString>, bool, std::function<void(QNetworkReply*)> const&);

private:
    QString appId;
    QString apiKey;
    QString endpoint;
    QString userToken;
    QNetworkAccessManager& networkAccessManager;
};
