//
//  BackendlessAPI.hpp
//  BackendlessQt
//
//  Created by Roman Podymov on 07/08/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#ifndef BACKENDLESS_API_H
#define BACKENDLESS_API_H

#include <QString>
#include <QMap>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include "BackendlessUserAPI.hpp"

struct DeletionResult: public Codable {
    long deletionTime;

    DeletionResult(QJsonObject jsonObject): deletionTime(jsonObject["deletionTime"].toInteger()) { }
};

class AnyNetworkAccessManager;

class BackendlessAPI: public QObject, public BasicAPI {
    Q_OBJECT

public:
    BackendlessAPI(
        AnyNetworkAccessManager*,
        QSharedPointer<BackendlessSignInUserCoder>,
        QString,
        QString,
        QString _endpoint = "https://eu-api.backendless.com/"
    );
    void addItemToTable(QString, PostParams);
    void editTableItem(QString, QString, PostParams);
    void deleteItemFromTable(QString, QString);
    void loadTableItems(QString tableName, int pageSize = 100, int offset = 0, QString whereClause = "");
    void getItemsCount(QString);

signals:
    void itemAdded();
    void itemEdited();
    void deleteItemFromTableSuccess(DeletionResult*);
    void deleteItemFromTableError(BackendlessError);
#ifdef BACKENDLESS_VARIANT_RESPONSE

#else
    void loadTableItemsSuccess(QString);
    void loadTableItemsError(BackendlessError);
#endif
    void getItemsCountSuccess(int);

public:
    BackendlessUserAPI userAPI;

private:
    AnyNetworkAccessManager* networkAccessManager;
    QString appId;
    QString apiKey;
    QString endpoint;
};

#endif
