#pragma once

#include <QObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>

#include "my_comparison.h"
#include "Struct_source.h"

class Reply_Comparison : public QObject{
    Q_OBJECT

    QThread *comparison_thread;
    My_Comparison *comparison;      //в этом классе будет выполняться вся сложная яработа, которую мы разобьём на потоки
public:
    explicit Reply_Comparison(Reply_struct* first_json, Reply_struct* second_json, QObject *parent = nullptr);

    My_Comparison* get_My_Comparison();     //передаём данные для дальнейшей работы

signals:
    void comparison_finished();             //даём остальному коду знать, что закончили
};

