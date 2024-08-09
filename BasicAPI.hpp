//
//  BasicAPI.hpp
//  BackendlessQt
//
//  Created by Roman Podymov on 09/08/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#include <QString>
#include <QMap>
#include <QNetworkAccessManager>

class BasicAPI {
protected:
    void request(QNetworkAccessManager*, const QObject*, QString, QMap<QString, QString>, bool, std::function<void(QNetworkReply*)> const&);
};
