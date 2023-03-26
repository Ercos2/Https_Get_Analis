#include "server_answer.h"

//#include <QTcpSocket>
//#include <thread>
//#include <QThread>
//#include <mutex>

Server_answer::Server_answer(QString Url, QObject *parent)
    : QObject(parent) {
    //connect(reply, &QIODevice::readyRead, this, &Server_answer::ready_read);
    //connect(manager, &QNetworkAccessManager::finished, this, &Server_answer::ready_read);

    reply = new My_Reply(Url);
    reply_thread = new QThread(this);
    //reply->moveToThread(reply_thread);
    //reply_thread = QThread::create(std::bind(&My_Reply::get_reply, reply));
    //QThread *reply_thread = QThread::create(std::bind(&My_Reply::get_reply, reply));
    reply->moveToThread(reply_thread);


    //connect(reply, &My_Reply::finished, this, &Server_answer::ready_read);
    connect(reply_thread, &QThread::started, reply, &My_Reply::get_reply);
    //connect(reply, &My_Reply::finished, reply, &My_Reply::ready_read);
    //connect(reply, &My_Reply::data_ready, [this]{ready_flag = true;});
    connect(reply, &My_Reply::finished, [this]{ready_flag = true;});
    //connect(reply, &My_Reply::data_ready, reply_thread, &QThread::deleteLater);

    //reply->get_reply();
    reply_thread->start();
}

Server_answer::~Server_answer() = default;

QJsonArray Server_answer::get_json() {
    return reply->json_array;
}
/*
void Server_answer::ready_read() {
    //while (reply->canReadLine())
        //qDebug() << QJsonDocument::fromJson(reply->readLine()).object();
        //qDebug() << reply->readLine();
    //flag = true;
    //*/
    //qDebug() << "reply " << reply->size();
    //qDebug() << "Someshit";
    //*
    /*
    auto jsonObject = QJsonDocument::fromJson(reply->reply->readAll());

    for (auto pack : jsonObject["packages"].toArray()) {
        reply->names.push_back(pack.toObject()["name"].toString());
        reply->versions.push_back(pack.toObject()["version"].toString());
        //qDebug() << pack.toString();
    }
    qDebug() << "json size: " << jsonObject["packages"].toArray().size();
    qDebug() << "names size: " << reply->names.size();
    qDebug() << "versions size: " << reply->versions.size();
//
}


std::vector<QString>& Server_answer::get_names() {
    return reply->names;
}
std::vector<QString>& Server_answer::get_versions() {
    return reply->versions;
}
*/
