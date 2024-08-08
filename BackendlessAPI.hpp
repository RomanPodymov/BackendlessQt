//
//  BackendlessAPI.hpp
//  BackendlessQt
//
//  Created by Roman Podymov on 07/08/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#include <QString>
#include <QMap>
#include <QNetworkAccessManager>
#include <QSharedPointer>
#include "BackendlessUserAPI.hpp"

class BackendlessAPI: public QObject {
    Q_OBJECT

public:
    BackendlessAPI(QString _appId, QString _apiKey, QString _endpoint = "https://eu-api.backendless.com/");
    void addItemToTable(QString, QMap<QString, QString>);
    void loadTableItems(QString);

signals:
    void itemAdded();
    void tableItemsLoaded(QString);

private:
    void request(QString, QMap<QString, QString>, bool, std::function<void(QNetworkReply*)> const&);

private:
    //QNetworkAccessManager networkAccessManager;
    QString appId;
    QString apiKey;
    QString endpoint;

public:
    BackendlessUserAPI userAPI;
};
