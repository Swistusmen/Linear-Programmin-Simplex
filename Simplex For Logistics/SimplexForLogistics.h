#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_SimplexForLogistics.h"
#include <qsignalmapper.h>
#include <iostream>
#include <vector>
#include <qtablewidget.h>
#include <qimage.h>
//#include "SimplexCalculations.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define M 20
#define N 20

typedef struct {
    int m, n; // m=rows, n=columns, mat[m x n]
    double mat[M][N];
} Tableau;

void simplex(Tableau* tab);

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
    std::vector<int> conditionals;
    std::vector<QString> productNames;
    std::vector<QString> meansNames;
    std::vector<QWidget*> tableItems;
    std::vector<QWidget*> conditionalItems;
    std::vector<int> x;
    int goalFunction;
private:
    void GenerateTable();
    bool ReadTable();
    void GenerateConditionals();
    bool ReadConditionals();

    Tableau GenerateCalculationsInput();
    void MapOutputToUI(Tableau* tab);
};
