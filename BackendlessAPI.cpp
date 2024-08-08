//
//  BackendlessAPI.cpp
//  BackendlessQt
//
//  Created by Roman Podymov on 07/08/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "BackendlessAPI.hpp"

BackendlessAPI::BackendlessAPI(QString _appId, QString _apiKey, QString _endpoint): QObject(),
    userAPI(&networkAccessManager, _appId, _apiKey, _endpoint),
    appId(_appId),
    apiKey(_apiKey),
    endpoint(_endpoint) {

}

void BackendlessAPI::addItemToTable(QString tableName, QMap<QString, QString> params) {
    return request(
        endpoint + appId + "/" + apiKey + "/data/" + tableName,
        params, true, [=](QNetworkReply* reply){
            auto replyValue = reply->readAll();
            qDebug() << replyValue;
            emit itemAdded();
        }
    );
}

void BackendlessAPI::loadTableItems(QString tableName) {
    return request(
        endpoint + appId + "/" + apiKey + "/data/" + tableName,
        {

        }, false, [=](QNetworkReply* reply){
            auto replyValue = reply->readAll();
            qDebug() << replyValue;
            emit tableItemsLoaded(replyValue);
        }
    );
}

void BackendlessAPI::request(
    QString urlString,
    QMap<QString, QString> customParams,
    bool isPost,
    std::function<void(QNetworkReply*)> const& handleRequest
) {
    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString params = "{";

    for (auto [key, value] : customParams.asKeyValueRange()) {
        params += "\"";
        params += key;
        params += "\"";
        params += ":";
        params += "\"";
        params += value;
        params += "\"";
        params += ",";
    }

    params.removeLast();
    params += "}";

    QObject::connect(&networkAccessManager, &QNetworkAccessManager::finished, this, [handleRequest](QNetworkReply* reply) {
        handleRequest(reply);
    }, Qt::SingleShotConnection);
    if (isPost) {
        networkAccessManager.post(request, params.toUtf8());
    } else {
        networkAccessManager.get(request);
    }
}
