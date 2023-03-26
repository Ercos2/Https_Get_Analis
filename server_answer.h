#pragma once

#include <QObject>

#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include <QString>
#include <QDebug>
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>

#include "my_reply.h"
#include "Struct_source.h"

class Server_answer : public QObject {
    Q_OBJECT
    QThread *reply_thread;
    My_Reply *reply;            //этот класс будет выполнять всю сложную работу

public:
    bool ready_flag = false;    //флаг даст знать остальному коду, что мы зкончили

    explicit Server_answer(QString Url, QObject *parent = nullptr);
    ~Server_answer() override;
    Reply_struct* get_reply_struct();       //передаём данные для дальнейшей работы
};
