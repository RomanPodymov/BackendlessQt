//
//  StandardNetworkManager.cpp
//  BackendlessQt
//
//  Created by Roman Podymov on 27/10/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#include "StandardNetworkManager.hpp"
#include <QNetworkRequest>
#include <QNetworkReply>

void StandardNetworkManager::get(QString urlString, const QObject* context, std::function<void(QByteArray)> const& handleRequest) {
    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QObject::connect(&manager, &QNetworkAccessManager::finished, context, [handleRequest](auto reply) {
        handleRequest(reply->readAll());
    }, Qt::SingleShotConnection);
    manager.get(request);
}

void StandardNetworkManager::post(QString urlString, PostParams customParams, const QObject* context, std::function<void(QByteArray)> const& handleRequest) {
    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString params = "{";

    for (auto [key, value] : customParams.asKeyValueRange()) {
        params += "\"";
        params += key;
        params += "\"";
        params += ":";
        params += value->asParam();
        params += ",";
    }

    params.removeLast();
    params += "}";

    QObject::connect(&manager, &QNetworkAccessManager::finished, context, [handleRequest](auto reply) {
        handleRequest(reply->readAll());
    }, Qt::SingleShotConnection);
    manager.get(request);
}

void StandardNetworkManager::put(QString, QString, const QObject* context, std::function<void(QByteArray)> const&) {

}

void StandardNetworkManager::deleteResource(QString, const QObject* context, std::function<void(QByteArray)> const&) {

}
