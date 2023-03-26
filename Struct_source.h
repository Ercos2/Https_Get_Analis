#pragma once

#include <vector>
#include <QJsonArray>

struct Recurring {                              //структура для хранения номеров повторяющихся пакетов у обоих запросов
    std::vector<int> recurring_first_num;
    std::vector<int> recurring_second_num;
};

struct Output_struct {          //структура для передачи данных на вывод
    QJsonArray first_json;
    QJsonArray second_json;
    std::vector<int> unique_first;
    std::vector<int> unique_second;
    std::vector<int> newer_version;

    Output_struct(QJsonArray new_first_json, QJsonArray new_second_json,
                  std::vector<int> new_unique_first, std::vector<int> new_unique_second,
                  std::vector<int> new_newer_version) :
        first_json(new_first_json), second_json(new_second_json),
        unique_first(new_unique_first), unique_second(new_unique_second),
        newer_version(new_newer_version) {};
};

struct Reply_struct {               //структура для передачи значений от запроса
    QJsonArray json_array;
    std::vector<QString> names;
    std::vector<QString> versions;

    Reply_struct(QJsonArray new_json_array, std::vector<QString> new_names, std::vector<QString> new_versions) :
        json_array(new_json_array), names(new_names), versions(new_versions) {}
};
