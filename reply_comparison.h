#pragma once

#include <QObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>

//#include <map>
//#include <unordered_map>
#include <vector>

#include "my_comparison.h"

class Reply_Comparison : public QObject
{
    Q_OBJECT
    //std::vector<QString> recurring;
    //std::map <int, int> recurring;
    //std::unordered_map<int, int> recurring;
    //Recurring recurring;
    //std::vector<QString> unique_first;
    //std::vector<QString> unique_second;
    //std::vector<QString> newer_version;
    QThread *comparison_thread;
    My_Comparison *comparison;
public:
    bool finish_flag = false;

    explicit Reply_Comparison(QJsonArray first_json, QJsonArray second_json, QObject *parent = nullptr);

    My_Comparison* get_My_Comparison();

    //void comparison_exist_first(std::vector<QString>& names_first, std::vector<QString>& names_second);
    //void comparison_exist_second(std::vector<QString>& names_first, std::vector<QString>& names_second);
    //void comparison_versions(std::vector<QString>& versions_first, std::vector<QString>& versions_second);
signals:
    void comparison_finished(Output_struct* output_struct);
    //void recurring_data(std::vector<QString>& first_data, std::vector<QString>& second_data, Recurring result_recurring);
    //void comparison_data(std::vector<QString>& first_data, std::vector<QString>& second_data, std::vector<int> recurring_vec, std::vector<QString>& result_vec);

};

