#include "reply_comparison.h"

Reply_Comparison::Reply_Comparison(Reply_struct* first_json, Reply_struct* second_json, QObject *parent)
    : QObject(parent) {
    //подготавливаем класс к вольному полёту в обработке данных
    comparison_thread = new QThread;
    comparison = new My_Comparison(first_json, second_json);
    comparison->moveToThread(comparison_thread);
    //после запуска потока по цепочке начнут запускаться функции
    connect(comparison_thread, &QThread::started, comparison, &My_Comparison::recurring_search);
    connect(comparison, &My_Comparison::recurring_search_finished, comparison, &My_Comparison::comparison_unique);
    connect(comparison, &My_Comparison::comparison_unique_finished, comparison, &My_Comparison::comparison_versions);
    connect(comparison, &My_Comparison::comparison_versions_finished, this, &Reply_Comparison::comparison_finished);

    comparison_thread->start();
}

My_Comparison* Reply_Comparison::get_My_Comparison() {
    return comparison;
}

