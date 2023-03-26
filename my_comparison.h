#pragma once

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <vector>

#include "Struct_source.h"


class My_Comparison : public QObject{
    Q_OBJECT
    Recurring recurring;                                //структура для хранения номеров повторяющихся пакетов
    QJsonArray first_json;
    QJsonArray second_json;
    std::vector<QString> first_json_names;              //сравнение чистых строк позволяет оптимизировать код
    std::vector<QString> second_json_names;             //постоянный перевод JSON в строку был слишком затратен
    std::vector<QString> first_json_versions;
    std::vector<QString> second_json_versions;
    std::vector<int> unique_first;                      //хранить JSON, как и строку затратно, поэтому сохраняем порядковые номера
    std::vector<int> unique_second;
    std::vector<int> newer_version;

public:
    explicit My_Comparison(Reply_struct* first_struct, Reply_struct* second_struct, QObject *parent = nullptr);
    void recurring_search();                            //находим повторяющиеся пакеты
    void comparison_unique();                           //находим уникальные пакеты
    void comparison_versions();                         //находим новейшие версии
    Output_struct* get_output_struct();                 //передаём структуру для вывода результатов

signals:
    void recurring_search_finished();
    void comparison_unique_finished();
    void comparison_versions_finished();
};


