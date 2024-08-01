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
    void registerUser(QString, QString, BackendlessUser);

signals:
    void userRegistered();

private:
    void request(QString, QMap<QString, QString>);

private:
    QNetworkAccessManager networkAccessManager;
};
