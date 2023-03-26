#include "server_answer.h"

Server_answer::Server_answer(QString Url, QObject *parent)
    : QObject(parent) {
    //подготавливаем класс к самостоятельной работе
    reply = new My_Reply(Url);
    reply_thread = new QThread(this);
    reply->moveToThread(reply_thread);
    //после запуска потока по цепочке запустятся две функции, а в конце поднимут флаг о завершении
    connect(reply_thread, &QThread::started, reply, &My_Reply::get_reply);
    connect(reply, &My_Reply::finished, reply, &My_Reply::ready_read);
    connect(reply, &My_Reply::data_ready, [this]{ready_flag = true;});

    reply_thread->start();
}

Server_answer::~Server_answer() = default;

Reply_struct* Server_answer::get_reply_struct() {
    return new Reply_struct(reply->json_array, reply->names, reply->versions);
}

