#include "output_json.h"

Output_JSON::Output_JSON(QObject *parent)
    : QObject{parent} {}

void construct_array(QJsonArray& new_json_array, QJsonArray& json_array, std::vector<int>& nums_to_insert) {
    for(int a = 0; a < nums_to_insert.size(); ++a) {
        new_json_array.push_back(json_array[nums_to_insert[a]]);
    }
}

void Output_JSON::output(Output_struct* output_struct) {
    QJsonObject json_object;
    QJsonArray first_temp_array;
    QJsonArray second_temp_array;
    QJsonArray versions_temp_array;

    //конструируем из массивов с пакетами и нужных номеров массивы с нужными пакетами
    QThread *first_thread = QThread::create(construct_array, std::ref(first_temp_array), std::ref(output_struct->first_json), std::ref(output_struct->unique_first));
    QThread *second_thread = QThread::create(construct_array, std::ref(second_temp_array), std::ref(output_struct->second_json), std::ref(output_struct->unique_second));
    QThread *versions_thread = QThread::create(construct_array, std::ref(versions_temp_array), std::ref(output_struct->first_json), std::ref(output_struct->newer_version));

    first_thread->start();
    second_thread->start();
    versions_thread->start();

    while (!first_thread->isFinished() || !second_thread->isFinished() || !versions_thread->isFinished()) {
        this->thread()->sleep(1);
    }

    first_thread->deleteLater();
    second_thread->deleteLater();
    versions_thread->deleteLater();
    //формируем цельный объект структуры типа
    //{uniuqe packag in first request [ array]
    //uniuqe packag in second request [array]
    //newer packag in first request [array]}
    json_object.insert("uniuqe packag in first request", first_temp_array);
    json_object.insert("uniuqe packag in second request", second_temp_array);
    json_object.insert("newer packag in first request", versions_temp_array);
    //выводим объект
    qDebug() << json_object;

    emit output_finished();
}
