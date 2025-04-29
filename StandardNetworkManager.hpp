//
//  StandardNetworkManager.hpp
//  BackendlessQt
//
//  Created by Roman Podymov on 27/10/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#ifndef STANDARD_NETWORK_MANAGER_H
#define STANDARD_NETWORK_MANAGER_H

#include "BasicAPI.hpp"
#include <QString>
#include <QByteArray>
#include <QNetworkAccessManager>

class StandardNetworkManager: public AnyNetworkAccessManager {
public:
<<<<<<< HEAD
    StandardNetworkManager(QObject* parent): manager(parent) { }

    void get(QString, const QObject*, std::function<void(QByteArray)> const&) override;
    void post(QString, PostParams, const QObject*, std::function<void(QByteArray)> const&) override;
    void put(QString, PostParams, const QObject* context, std::function<void(QByteArray)> const&) override;
    void deleteResource(QString, const QObject* context, std::function<void(QByteArray)> const&) override;
=======
    void get(QString, QMap<QString, QString>, const QObject*, std::function<void(QByteArray)> const&) override;
    void post(QString, QMap<QString, QString>, PostParams, const QObject*, std::function<void(QByteArray)> const&) override;
    void put(QString, QMap<QString, QString>, PostParams, const QObject* context, std::function<void(QByteArray)> const&) override;
    void deleteResource(QString, QMap<QString, QString>, const QObject* context, std::function<void(QByteArray)> const&) override;
>>>>>>> main

    QFuture<QByteArray> get(QString);

private:
    QNetworkAccessManager manager;
};

#endif
