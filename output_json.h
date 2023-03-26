#pragma once

#include <QObject>

#include <QJsonObject>
#include <QJsonArray>

#include <vector>

#include "my_comparison.h"

class Output_JSON : public QObject
{
    Q_OBJECT
public:
    explicit Output_JSON(QObject *parent = nullptr);

    void output(Output_struct* output_struct);
signals:
    void output_finished();
};

