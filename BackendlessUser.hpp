//
//  BackendlessUser.hpp
//  BackendlessQt
//
//  Created by Roman Podymov on 07/08/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#ifndef BACKENDLESS_USER_H
#define BACKENDLESS_USER_H

#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QJsonParseError>
#include "BasicAPI.hpp"

class BackendlessRegisterUserRepresentable {
public:
    virtual ~BackendlessRegisterUserRepresentable() = default;
    virtual PostParams getAllParams() = 0;
};

struct BasicBackendlessRegisterUser: BackendlessRegisterUserRepresentable {
public:
    BasicBackendlessRegisterUser(
        QString _email,
        QString _password
    );
    ~BasicBackendlessRegisterUser() override;

    PostParams getAllParams() override;

protected:
    StringPostParam* email;
    StringPostParam* password;
};

struct BackendlessSignInUser {
    QString name;
    QString email;
    QString userToken;

    BackendlessSignInUser(
        QJsonObject jsonObject
    ): name(jsonObject["name"].toString()),
       email(jsonObject["email"].toString()),
       userToken(jsonObject["user-token"].toString()) {

    }

    BackendlessSignInUser() {}
};

class SignInUserCoder {
public:
    virtual BackendlessSignInUser* decode(QJsonObject) = 0;
    virtual void write(QTextStream&, QSharedPointer<BackendlessSignInUser>, QString) = 0;
    virtual BackendlessSignInUser* read(QTextStream&) = 0;
};

template<typename T>
void extractResult(
    QByteArray replyValue,
    SignInUserCoder* decoder,
    std::function<void(T*)> const& onSuccess,
    std::function<void(BackendlessError)> const& onBEError,
    std::function<void(QJsonParseError)> const& onJSONError
    ) {
    QJsonParseError jsonError;
    auto jsonResponse = QJsonDocument::fromJson(replyValue, &jsonError);

    switch (jsonError.error) {
    case QJsonParseError::NoError:
        break;
    default:
        onJSONError(jsonError);
        return;
    }

    auto jsonObject = jsonResponse.object();
    auto code = static_cast<BackendlessErrorCode>(jsonObject["code"].toInt());
    switch (code) {
    case BackendlessErrorCode::noError:
    {
        auto decoded = decoder->decode(
            jsonObject
            );
        onSuccess(
            (T*)(decoded)
            );
    }
    break;
    default:
        onBEError(BackendlessError(
            code,
            jsonObject["message"].toString()
            ));
    }
}

#endif
