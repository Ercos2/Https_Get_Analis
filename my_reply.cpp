#include "my_reply.h"

My_Reply::My_Reply(QString Url, QObject *parent)
    : QObject(parent) {
    //мы перенесли создание в этот класс, чтобы не было конфликтов наследования
    manager = new QNetworkAccessManager(this);

    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);

    request.setSslConfiguration(config);
    request.setUrl(QUrl(Url));
}

void My_Reply::get_reply() {
    //запрос достаточно требовательный, чтобы выделить под него отдельную функцию в отдельном потоке
    reply = manager->get(request);//Получаем данные с сервера

    connect(manager, &QNetworkAccessManager::finished, this, &My_Reply::finished);

}

void My_Reply::ready_read() {
    //нам не нужен весь Json, поэтому оставляет только массив с пакетами
    json_array = QJsonDocument::fromJson(reply->readAll())["packages"].toArray();
    //облегчаем себе работу на будущее и сохраняем имена и версии в отдельные вектора
    for (auto pack : json_array) {
        names.push_back(pack.toObject()["name"].toString());
        versions.push_back(pack.toObject()["version"].toString());
    }

    qDebug() << "json size: " << json_array.size();
    qDebug() << "names size: " << names.size();
    qDebug() << "versions size: " << versions.size();

    emit data_ready();
}
