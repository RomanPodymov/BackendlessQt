//
//  API.cpp
//  BackendlessQt
//
//  Created by Roman Podymov on 30/07/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#include "API.hpp"
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPromise>
#include <QScopedPointer>
#include <QThread>

QFuture<QString> API::registerUser(QString appId, QString key, BackendlessUser user) {
    return request(
        "https://eu-api.backendless.com/" + appId + "/" + key + "/users/register",
        {
            {"email", user.email},
            {"name", user.name},
            {"password", user.password}
        }
    );
}

QFuture<QString> API::request(QString urlString, QMap<QString, QString> customParams) {
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

    QPromise<QString> promise;
    QFuture<QString> future = promise.future();

    QScopedPointer<QThread> thread(QThread::create([] (QPromise<QString> promise) {
        promise.start();
        QObject::connect(&networkAccessManager, &QNetworkAccessManager::finished, [=](QNetworkReply* reply){
            auto replyValue = reply->readAll();
            qDebug() << replyValue;
            promise.addResult(replyValue);
            promise.finish();
        });
    }, std::move(promise)));
    thread->start();

    networkAccessManager.post(request, params.toUtf8());

    return future;
}
