//
//  API.hpp
//  BackendlessQt
//
//  Created by Roman Podymov on 30/07/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#include <QString>
#include <QMap>
#include <QNetworkAccessManager>

struct BackendlessUser {
    QString email;
    QString name;
    QString password;
};

class API: public QObject {
    Q_OBJECT

public:
    API(QString, QString, QString);
    void registerUser(BackendlessUser);
    void signInUser(QString, QString);

signals:
    void userRegistered();
    void userSignedIn(QString);

private:
    void request(QString, QMap<QString, QString>, std::function<void(QNetworkReply*)>);

private:
    QString appId;
    QString apiKey;
    QString endpoint;
    QNetworkAccessManager networkAccessManager;
};
