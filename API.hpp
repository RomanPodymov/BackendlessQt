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
    void signInUser(QString, QString, QString, QString);

signals:
    void userRegistered();
    void userSignedIn(QString);

private:
    void request(QString, QMap<QString, QString>, std::function<void(QNetworkReply*)>);

private:
    QNetworkAccessManager networkAccessManager;
};
