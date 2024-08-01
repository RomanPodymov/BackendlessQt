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
#include <QFuture>

struct BackendlessUser {
    QString email;
    QString name;
    QString password;
};

class API {
public:
    QFuture<QString> registerUser(QString, QString, BackendlessUser);

private:
    QFuture<QString> request(QString, QMap<QString, QString>);

private:
    QNetworkAccessManager networkAccessManager;
};
