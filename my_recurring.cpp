#include "my_recurring.h"



My_Recurring::My_Recurring(QJsonArray first_json, QJsonArray second_json, Recurring* recurring, int start, int end, int& first_size, int& second_size, bool& flag, QObject *parent)
    : QObject{parent}, first_json(first_json), second_json(second_json), recurring(recurring), start(start), end(end), first_size(first_size), second_size(second_size), flag(flag)
{

}

void My_Recurring::run() {
    //qDebug() << "entered the cycle " << a;
    //if (end == -1) end =
    for (int a = start; a < end; ++a) {
        for(int b = 0; b < second_size; ++b) {
            //mute_name.try_lock();
            if (first_json[a].toObject()["name"] == second_json[b].toObject()["name"]) {
                recurring->recurring_first_num.push_back(a);
                recurring->recurring_second_num.push_back(b);
                break;
            }
            //mute_name.unlock();
        }
        if(!(a % 1000)) qDebug() << "recurring alive " << a;
        //++a;

    }
    if (end >= first_size) flag = true;
}
