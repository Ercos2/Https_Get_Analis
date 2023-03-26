#include "my_comparison.h"
#include "my_recurring.h"

//#include <mutex>
#include <QThreadPool>
#include <QRunnable>

#include <QJsonValueRef>

//std::mutex mute_name;
/*
class Recurring_class : public QObject, public QRunnable {
    Q_OBJECT
    int a = 0;
    QJsonArray first_json;
    QJsonArray second_json;
    Recurring* recurring;
public:
    My_Recurring(QJsonArray& first_json, QJsonArray& second_json, Recurring* recurring, QObject *parent = 0) :
        QObject(parent), first_json(first_json), second_json(second_json), recurring(recurring) {}
    void run() {
        for(int b = 0; b < second_json.size(); ++b) {
            if (first_json[a] == second_json[b]) {
                recurring->recurring_first_num.push_back(a);
                recurring->recurring_second_num.push_back(b);
                break;
            }
        }
        if(!(a % 1000)) qDebug() << "recurring alive " << a;
        ++a;
    }
};
*/
My_Comparison::My_Comparison(QJsonArray first_json, QJsonArray second_json, QObject *parent)
    : QObject(parent), first_json(first_json), second_json(second_json) {

}

void My_Comparison::recurring_search() {
    qDebug() << "recurring started";
    bool flag = false;
    int first_size = first_json.size();
    int second_size = second_json.size();
    QThreadPool::globalInstance()->setExpiryTimeout(1000);
    for(int a = 0; a * 1000 < first_size; ++a) {
        if (a * 1000 < first_size) {
        My_Recurring *recurr = new My_Recurring(first_json, second_json, &recurring, (a * 1000), ((a + 1) * 1000), first_size, second_size, flag);
        QThreadPool::globalInstance()->start(recurr);

        }
        else {
            My_Recurring *recurr = new My_Recurring(first_json, second_json, &recurring, (a * 1000), first_size, first_size, second_size, flag);
            QThreadPool::globalInstance()->start(recurr);
        }
        //this->thread()->sleep(1);

        /*
        for(int b = 0; b < second_json.size(); ++b) {
            if (first_json[a] == second_json[b]) {
                recurring.recurring_first_num.push_back(a);
                recurring.recurring_second_num.push_back(b);
                    break;
            }
        }
        if(!(a % 1000)) qDebug() << "recurring alive " << a;
        */
    }
    qDebug() << "Wait cicle";
    while (!flag) {

        this->thread()->sleep(1);
    }
    /*
    int second_json_size = second_json.size();
    for (int a = 0; a < first_json.size(); ++a) {
        for (int b = 0; b < second_json_size; ++b) {
            //if (first_json[a].toObject()["name"] == second_json[b].toObject()["name"]) {
            if (first_json[a] == second_json[b]){
                recurring.recurring_first_num.push_back(a);
                recurring.recurring_second_num.push_back(b);
                break;
            }
            //}
        }
        if(!(a % 1000)) qDebug() << "recurring alive " << a;
    }
    */
    /*
    for (int a = 0; a < names_first.size(); ++a) {
        for (int b = 0; b < names_second.size(); ++b) {
            if (names_first[a] == names_second[b]){
                recurring.recurring_first_num.push_back(a);
                recurring.recurring_second_num.push_back(b);
                break;
            }
        }
        if(!(a % 1000)) qDebug() << "recurring alive " << a;
    }
    /*/
    qDebug() << "recurring finished";
    qDebug() << "recurring size: " << recurring.recurring_first_num.size() << " " << recurring.recurring_second_num.size();

    emit recurring_search_finished();
}
/*
void unique(std::vector<QString>& names_vec, std::vector<int>& recurring_nums, std::vector<QString>&  unique, bool& thread_flag) {
    for (int a = 0; a < names_vec.size(); ++a) {
        bool flag = false;
        for (int b = 0; b <= a; ++b) {
            if (a == recurring_nums[b]) {
                flag = true;
                break;
            }
        }
        if (!flag) unique.push_back(names_vec[a]);
        if(!(a % 1000)) qDebug() << "unique alive " << a;
    }
    thread_flag = true;
}
*/
void unique(QJsonArray& json_array, std::vector<int>& recurring_nums,std::vector<int>& unique, bool& thread_flag) {
    for (int a = 0; a < json_array.size(); ++a) {
        bool flag = false;
        for (int b = 0; b <= recurring_nums.size(); ++b) {
            if (a == recurring_nums[b]) {
                flag = true;
                break;
            }
        }
        if (!flag) unique.push_back(a);
        if(!(a % 1000)) qDebug() << "unique alive " << a;
    }
    thread_flag = true;
}

void My_Comparison::comparison_unique() {
    qDebug() << "unique started";
    bool first_thread_flag = false;
    bool second_thread_flag = false;

    QThread* first_thread = QThread::create(unique, std::ref(first_json), std::ref(recurring.recurring_first_num), std::ref(unique_first), std::ref(first_thread_flag));
    QThread* second_thread = QThread::create(unique, std::ref(second_json), std::ref(recurring.recurring_second_num), std::ref(unique_second), std::ref(second_thread_flag));
    //QThread* first_thread = QThread::create(unique, std::ref(names_first), std::ref(recurring.recurring_first_num), std::ref(unique_first), std::ref(first_thread_flag));
    //QThread* second_thread = QThread::create(unique, std::ref(names_second), std::ref(recurring.recurring_second_num), std::ref(unique_second), std::ref(second_thread_flag));

    first_thread->start();
    second_thread->start();

    while(!first_thread_flag || !second_thread_flag)
        this->thread()->sleep(1);

    //first_thread->quit();
    first_thread->deleteLater();
    //second_thread->quit();
    second_thread->deleteLater();

    qDebug() << "unique finished";
    qDebug() << "first json size: " << first_json.size();
    qDebug() << "unique first size: " << unique_first.size();
    qDebug() << "second json size: " << second_json.size();
    qDebug() << "unique second size: " << unique_second.size();

    emit comparison_unique_finished();
}
void My_Comparison::comparison_versions() {
    qDebug() << "versions starteded";

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
