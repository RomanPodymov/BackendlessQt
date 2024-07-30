//
//  API.hpp
//  BackendlessQt
//
//  Created by Roman Podymov on 30/07/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#include <QString>
#include <QMap>

struct BackendlessUser {
    QString email;
    QString name;
    QString password;
};

class API {
public:
    void registerUser(QString, QString, BackendlessUser);

private:
    void request(QString, QMap<QString, QString>);
};
