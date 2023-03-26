#pragma once

#include <QObject>

#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include <QString>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QVariantList>
#include <QArrayData>

#include <map>
#include <vector>

class My_Reply : public QObject {
    Q_OBJECT
    QNetworkAccessManager *manager;
    QNetworkRequest request;
public:
    QNetworkReply *reply;
    //QJsonDocument json_document;
    QJsonArray json_array;
    std::vector<QString> names;
    std::vector<QString> versions;

    explicit My_Reply(QString Url, QObject *parent = nullptr);
    void get_reply();
    //void ready_read();


signals:
    void finished();
    //void data_ready();
};

