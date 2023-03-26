#include "my_comparison.h"

My_Comparison::My_Comparison(Reply_struct* first_struct, Reply_struct* second_struct, QObject *parent)
    : QObject(parent), first_json(first_struct->json_array), second_json(second_struct->json_array),
    first_json_names(first_struct->names), second_json_names(second_struct->names),
    first_json_versions(first_struct->versions), second_json_versions(second_struct->versions){

}

void recurr(std::vector<QString>& names_first, std::vector<QString> names_second, std::vector<int>& recurring_num) {
    for (int a = 0; a < names_first.size(); ++a) {
        for (int b = 0; b < names_second.size(); ++b) {
            if (names_first[a] == names_second[b]){
                recurring_num.push_back(a);
                break;
            }
        }
        if(!(a % 10000)) qDebug() << "recurring process " << a << " of " << names_first.size();
    }
}

void My_Comparison::recurring_search() {
    qDebug() << "recurring started";

    //создаём по потоку на каждый запрос
    //можно было создать вектор потоков или QThreadPool, но два потока того не стоят
    //передаём первый параметр ссылкой для экономии, а второй копируем, чтобы избежать ошибок доступа
    QThread *first_thread = QThread::create(recurr, std::ref(first_json_names), second_json_names, std::ref(recurring.recurring_first_num));
    QThread *second_thread = QThread::create(recurr, std::ref(second_json_names), first_json_names, std::ref(recurring.recurring_second_num));

    first_thread->start();
    second_thread->start();

    while(!first_thread->isFinished() || !second_thread->isFinished())
        this->thread()->sleep(1);

    first_thread->deleteLater();
    second_thread->deleteLater();


    qDebug() << "recurring finished";
    qDebug() << "recurring size: " << recurring.recurring_first_num.size() << " " << recurring.recurring_second_num.size();

    emit recurring_search_finished();
}

void unique(QJsonArray& json_array, std::vector<int>& recurring_nums,std::vector<int>& unique) {
    for (int a = 0; a < json_array.size(); ++a) {
        bool flag = false;
        for (int b = 0; b < recurring_nums.size(); ++b) {
            if (a == recurring_nums[b]) {
                flag = true;
                break;
            }
        }
        if (!flag) unique.push_back(a);
        if(!(a % 10000)) qDebug() << "unique process " << a << " of " << json_array.size();
    }
}

void My_Comparison::comparison_unique() {
    qDebug() << "unique started";
    //та же ситуация, что и с копиями, но здесь вся память разная, поэтому всё можно передавать по ссылкам
    QThread* first_thread = QThread::create(unique, std::ref(first_json), std::ref(recurring.recurring_first_num), std::ref(unique_first));
    QThread* second_thread = QThread::create(unique, std::ref(second_json), std::ref(recurring.recurring_second_num), std::ref(unique_second));

    first_thread->start();
    second_thread->start();

    while(!first_thread->isFinished() || !second_thread->isFinished())
        this->thread()->sleep(1);

    first_thread->deleteLater();
    second_thread->deleteLater();

    qDebug() << "unique finished";
    //qDebug() << "first json size: " << first_json.size();
    qDebug() << "unique first size: " << unique_first.size();
    //qDebug() << "second json size: " << second_json.size();
    qDebug() << "unique second size: " << unique_second.size();

    emit comparison_unique_finished();
}

void My_Comparison::comparison_versions() {
    qDebug() << "versions starteded";
    //нутро подсказывает мне, что оно работает не совсем правильно, но заставить это работать абсолютно корректно невозможно или слишком трудозатратно
    for(int a = 0; a < recurring.recurring_first_num.size(); ++a) {
        if (first_json[recurring.recurring_first_num[a]].toObject()["version"].toString() > second_json[recurring.recurring_second_num[a]].toObject()["version"].toString())
            newer_version.push_back(recurring.recurring_first_num[a]);
    }

    qDebug() << "versions finished";
    qDebug() << "versions newer size: " << newer_version.size();

    emit comparison_versions_finished();
}

Output_struct* My_Comparison::get_output_struct() {
    return new Output_struct(first_json, second_json, unique_first, unique_second, newer_version);
}
