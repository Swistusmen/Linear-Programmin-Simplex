#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SimplexForLogistics.h"
#include <qsignalmapper.h>
#include <iostream>
#include <vector>
#include <qtablewidget.h>
#include <qimage.h>


class SimplexForLogistics : public QMainWindow
{
    Q_OBJECT

public:
    SimplexForLogistics(QWidget *parent = Q_NULLPTR);

public slots:
    void ChangePage(int index);

private:
    Ui::SimplexForLogisticsClass ui;
    QSignalMapper* pageMapper;
    

    int products, means;
    std::vector<int> meansPerProduct;
    std::vector<int> profits;
    std::vector<int> limits;
    std::vector<QString> productNames;
    std::vector<QString> meansNames;
    std::vector<QWidget*> tableItems;

private:
    void GenerateTable();
    bool ReadTable();
};
