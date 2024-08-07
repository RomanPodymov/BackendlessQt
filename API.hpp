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

    BackendlessUser(
        QString _email,
        QString _name,
        QString _password
    ): email(_email), name(_name), password(_password) {

    }
};

class API: public QObject {
    Q_OBJECT

public:
    API(QString _appId, QString _apiKey, QString _endpoint = "https://eu-api.backendless.com/");
    void registerUser(BackendlessUser);
    void signInUser(QString, QString);
    void validateUserToken();
    void addItemToTable(QString, QMap<QString, QString>);
    void loadTableItems(QString);

signals:
    void userRegistered();
    void userSignedIn();
    void userTokenValidated(bool);
    void itemAdded();
    void tableItemsLoaded(QString);

private:
    void request(QString, QMap<QString, QString>, bool, std::function<void(QNetworkReply*)> const&);

private:
    QString appId;
    QString apiKey;
    QString endpoint;
    QString userToken;
    QNetworkAccessManager networkAccessManager;
};
