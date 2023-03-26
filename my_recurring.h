#pragma once

#include <QObject>
#include <QThreadPool>
#include <QRunnable>
#include <QJsonArray>
#include <QJsonValueRef>

//#include <mutex>
//std::mutex mute_name;

#include "my_comparison.h"


class My_Recurring : public QObject, public QRunnable
{
    Q_OBJECT
    int start;
    int end;
    int& first_size;
    int& second_size;
    bool& flag;
    QJsonArray first_json;
    QJsonArray second_json;
    Recurring* recurring;
public:
    explicit My_Recurring(QJsonArray first_json, QJsonArray second_json, Recurring* recurring, int start, int end, int& first_size, int& second_size, bool& flag, QObject *parent = nullptr);
    void run();
signals:
    void finished();
};


