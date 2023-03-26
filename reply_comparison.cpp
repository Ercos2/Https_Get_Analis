#include "reply_comparison.h"

Reply_Comparison::Reply_Comparison(QJsonArray first_json, QJsonArray second_json, QObject *parent)
    : QObject(parent) {
    comparison_thread = new QThread;
    comparison = new My_Comparison(first_json, second_json);
    comparison->moveToThread(comparison_thread);

    connect(comparison_thread, &QThread::started, comparison, &My_Comparison::recurring_search);
    connect(comparison, &My_Comparison::recurring_search_finished, comparison, &My_Comparison::comparison_unique);
    connect(comparison, &My_Comparison::comparison_unique_finished, comparison, &My_Comparison::comparison_versions);
    //connect(comparison, &My_Comparison::comparison_versions_finished, [this]{finish_flag = true;});
    connect(comparison, &My_Comparison::comparison_versions_finished, [this] {
        emit comparison_finished(comparison->get_output_struct());
    });
    //connect(reply, &My_Reply::finished, reply, &My_Reply::ready_read);

    comparison_thread->start();
}

My_Comparison* Reply_Comparison::get_My_Comparison() {
    return comparison;
}

/*
void Reply_Comparison::comparison_exist_first(std::vector<QString>& names_first, std::vector<QString>& names_second){
    //comparison_exist(names_first, names_second);

}
void Reply_Comparison::comparison_exist_second(std::vector<QString>& names_first, std::vector<QString>& names_second) {

}
void Reply_Comparison::comparison_versions(std::vector<QString>& versions_first, std::vector<QString>& versions_second) {

}
*/
