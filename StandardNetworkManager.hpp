//
//  StandardNetworkManager.hpp
//  BackendlessQt
//
//  Created by Roman Podymov on 27/10/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#ifndef STANDARD_NETWORK_MANAGER_H
#define STANDARD_NETWORK_MANAGER_H

#include <QString>
#include <QByteArray>

class AnyNetworkAccessManager {
    virtual void get(QString, std::function<void(QByteArray)> const&) = 0;
    virtual void post(QString, QString, std::function<void(QByteArray)> const&) = 0;
    virtual void put(QString, QString, std::function<void(QByteArray)> const&) = 0;
    virtual void deleteResource(QString, std::function<void(QByteArray)> const&) = 0;
};

class StandardNetworkManager: public AnyNetworkAccessManager {
public:
    void get(QString, std::function<void(QByteArray)> const&);
    void post(QString, QString, std::function<void(QByteArray)> const&);
    void put(QString, QString, std::function<void(QByteArray)> const&);
    void deleteResource(QString, std::function<void(QByteArray)> const&);
};

#endif
