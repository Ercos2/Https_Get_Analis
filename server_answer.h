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
//#include <QVariantMap>
//#include <QVariantList>
//#include <QArrayData>

//#include <map>
#include <vector>

#include "my_reply.h"

class Server_answer : public QObject {
    Q_OBJECT
    //std::map<QString, QString> answers;
    //std::map<QString, std::vector<QString>> answers;
    //std::map<QString, std::map<QString, QString>> alt_answers;
    //QVariantMap variant_answers;
    //QVariantList list_answers;
    //QArrayData array_answers;
    //std::vector<QString> names;
    //std::vector<QString> versions;
    QThread *reply_thread;
    My_Reply *reply;

    //QNetworkAccessManager *manager;
    //QNetworkRequest request;
    //QNetworkReply *reply;

    //int number_again = 0;

    //void ready_read();

public:
    bool ready_flag = false;

    explicit Server_answer(QString Url, QObject *parent = nullptr);
    ~Server_answer() override;
    //std::vector<QString>& get_names();
    //std::vector<QString>& get_versions();
    QJsonArray get_json();

signals:

};
