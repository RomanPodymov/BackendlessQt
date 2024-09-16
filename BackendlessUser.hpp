//
//  BackendlessUser.hpp
//  BackendlessQt
//
//  Created by Roman Podymov on 07/08/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#ifndef BACKENDLESS_USER_H
#define BACKENDLESS_USER_H

#include <QMap>
#include <QString>

class BackendlessRegisterUserRepresentable {
public:
    virtual QMap<QString, QString> getAllParams() = 0;
};

struct BasicBackendlessRegisterUser: BackendlessRegisterUserRepresentable {
public:
    BasicBackendlessRegisterUser(
        QString _email,
        QString _password
    ): email(_email), password(_password) { }

    QMap<QString, QString> getAllParams() {
        return {
            {"email", email},
            {"password", password}
        };
    }

protected:
    QString email;
    QString password;
};

struct BackendlessRegisterUser: BasicBackendlessRegisterUser {
public:
    BackendlessRegisterUser(
        QString _email,
        QString _password,
        QString _name
    ): BasicBackendlessRegisterUser(_email, _password), name(_name) { }

    QMap<QString, QString> getAllParams() {
        QMap<QString, QString> result = {{"name", name}};
        result.insert(BasicBackendlessRegisterUser::getAllParams());
        return result;
    }

protected:
    QString name;
};

struct BackendlessSignInUser {
    QString userToken;

    BackendlessSignInUser(
        QString _userToken
    ): userToken(_userToken) { }
};

#endif
