#pragma once

#include <QObject>

#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include <QString>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <vector>

class My_Reply : public QObject {
    Q_OBJECT
    QNetworkAccessManager *manager;                             //подготавливаемся к запросу
    QNetworkRequest request;

public:
    QNetworkReply *reply;
    QJsonArray json_array;
    std::vector<QString> names;                                 //сохраняем имена пакетов для оптимизации сравнения
    std::vector<QString> versions;                              //тоже самое, но с версиями

    explicit My_Reply(QString Url, QObject *parent = nullptr);
    void get_reply();                                           //совершаем запрос
    void ready_read();                                          //достаём имена и версии

signals:
    void finished();
    void data_ready();
};

