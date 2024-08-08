//
//  BackendlessUser.hpp
//  BackendlessQt
//
//  Created by Roman Podymov on 07/08/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#include <QString>

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
