#pragma once

#include <QObject>

#include <QThread>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QArrayData>

#include <vector>


struct Recurring {
    std::vector<int> recurring_first_num;
    std::vector<int> recurring_second_num;
};

struct Output_struct {
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

class My_Comparison : public QObject
{
    Q_OBJECT
    Recurring recurring;
    //std::vector<QString> names_first;
    //std::vector<QString> names_second;
    //std::vector<QString> versions_first;
    //std::vector<QString> versions_second;
    QJsonArray first_json;
    QJsonArray second_json;
    std::vector<int> unique_first;
    std::vector<int> unique_second;
    std::vector<int> newer_version;
public:


    explicit My_Comparison(QJsonArray first_json, QJsonArray second_json, QObject *parent = nullptr);
    void recurring_search();
    void comparison_unique();
    void comparison_versions();
    Output_struct* get_output_struct();
    //void recurring_search(std::vector<QString>& names_first, std::vector<QString>& names_second, Recurring& recurring);
    //void comparison_unique(std::vector<QString>& names_vec, std::vector<int>& recurring_nums, std::vector<QString>&  unique);
    //void comparison_versions(std::vector<QString>& versions_first, std::vector<QString>& versions_second, Recurring& recurring, std::vector<QString>& newer);

signals:
    void recurring_search_finished();
    void comparison_unique_finished();
    void comparison_versions_finished();
};


