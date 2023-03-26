#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QThread>

#include "Struct_source.h"

class Output_JSON : public QObject
{
    Q_OBJECT
public:
    explicit Output_JSON(QObject *parent = nullptr);

    void output(Output_struct* output_struct);  //выводим JSON (шок)
signals:
    void output_finished();
};

