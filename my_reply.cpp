#include "my_reply.h"

My_Reply::My_Reply(QString Url, QObject *parent)
    : QObject(parent) {
    manager = new QNetworkAccessManager(this);

    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);

    request.setSslConfiguration(config);
    request.setUrl(QUrl(Url));
}

void My_Reply::get_reply() {

    reply = manager->get(request);//Получаем данные с сервера

    //connect(manager, &QNetworkAccessManager::finished, this, &My_Reply::finished);
    connect(manager, &QNetworkAccessManager::finished, [this] {
        qDebug() << request.url() << " finished";
        json_array = QJsonDocument::fromJson(reply->readAll())["packages"].toArray();
        qDebug() << "json size: " << json_array.size();
        //qDebug() << "json size: " << json_document["packages"].toArray().size();
        emit finished();
    });
}
/*
void My_Reply::ready_read() {
    //auto jsonObject = QJsonDocument::fromJson(reply->readAll());
    json_document = QJsonDocument::fromJson(reply->readAll());
//*
    for (auto pack : json_document["packages"].toArray()) {
        names.push_back(pack.toObject()["name"].toString());
        versions.push_back(pack.toObject()["version"].toString());
        //qDebug() << pack.toString();
    }

    qDebug() << "json size: " << json_document["packages"].toArray().size();
    //qDebug() << "names size: " << names.size();
    //qDebug() << "versions size: " << versions.size();

    emit data_ready();
}
*/
