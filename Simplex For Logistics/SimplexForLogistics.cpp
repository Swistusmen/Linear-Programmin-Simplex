#include "SimplexForLogistics.h"

SimplexForLogistics::SimplexForLogistics(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    pageMapper = new QSignalMapper(this);
    pageMapper->setMapping(ui.generate_input, 0);
    pageMapper->setMapping(ui.generate_output, 1);
    pageMapper->setMapping(ui.reset, 2);

    QPixmap pix("dog.jpg");
    ui.welcome_image->setPixmap(pix);

    QPixmap pix2("AGH.png");
    ui.agh->setPixmap(pix2);

    connect(ui.generate_input, SIGNAL(clicked()), pageMapper, SLOT(map()));
    connect(ui.generate_output, SIGNAL(clicked()), pageMapper, SLOT(map()));
    connect(ui.reset, SIGNAL(clicked()), pageMapper, SLOT(map()));
    connect(pageMapper, SIGNAL(mapped(int)), this, SLOT(ChangePage(int)));
}

void SimplexForLogistics::ChangePage(int index)
{
    if (index == 0)
    {
        QString noProducts = ui.no_products->text();
        QString noMeans = ui.no_means->text();
        try {
            products = std::stoi(noProducts.toStdString());
            means = std::stoi(noMeans.toStdString());
        }
        catch (std::exception e) {
            return;
        }
        GenerateTable();
    ui.stackedWidget->setCurrentIndex(1);
    }
    else if(index==1)
    {
        if (tableItems.size() == 0)
            return;
        ReadTable();
        ui.stackedWidget->setCurrentIndex(2);
    }
    else {
        meansPerProduct.clear();
        profits.clear();
        limits.clear();
        productNames.clear();
        meansNames.clear();
        tableItems.clear();
        ui.stackedWidget->setCurrentIndex(0);
    }
    
}

void SimplexForLogistics::GenerateTable()
{
    if (tableItems.size() != 0)
        return;
    int rows = means + 2;
    int columns = products + 2;
    ui.input_table->setRowCount(rows);
    ui.input_table->setColumnCount(columns);

    tableItems.push_back(new QLabel);
    ui.input_table->setCellWidget(0, 0, tableItems.back());

    for (int i = 1; i < columns-1; i++)
    {
        tableItems.push_back(new QLineEdit("Produkt"));
        ui.input_table->setCellWidget(0, i, tableItems.back());
    }
    tableItems.push_back(new QLabel("Limity"));
    ui.input_table->setCellWidget(0, columns-1, tableItems.back());

    for (int i = 1; i < rows - 1; i++)
    {
        tableItems.push_back(new QLineEdit("Srodek Produkcji"));
        ui.input_table->setCellWidget(i, 0, tableItems.back());
        for (int j = 1; j < columns; j++)
        {
            tableItems.push_back(new QLineEdit(""));
            ui.input_table->setCellWidget(i, j, tableItems.back());
        }
    }

    tableItems.push_back(new QLabel("Zysk jednostkowy"));
    ui.input_table->setCellWidget(rows-1, 0, tableItems.back());

    for (int i = 1; i < columns - 1; i++)
    {
        tableItems.push_back(new QLineEdit(""));
        ui.input_table->setCellWidget(rows-1, i, tableItems.back());
    }

    tableItems.push_back(new QLabel);
    ui.input_table->setCellWidget(rows-1, columns-1, tableItems.back());
}

bool SimplexForLogistics::ReadTable()
{
    productNames.clear();
    meansNames.clear();
    limits.clear();
    profits.clear();

    int rows = means + 2;
    int columns = products + 2;
    
    for (int i = 1; i < columns - 1; i++)
    {
        productNames.push_back(((QLineEdit*)tableItems[i])->text());
    }
    for (int i = 1; i < rows - 1; i++)
    {
        meansNames.push_back(((QLineEdit*)tableItems[i*columns])->text());
        for (int j = 1; j < columns - 1; j++)
        {
            try {
                meansPerProduct.push_back(std::stoi(((QLineEdit*)tableItems[i * columns + j])->text().toStdString()));
            }
            catch (std::exception e) {
                return false;
            }
        }
        try {
            limits.push_back(std::stoi(((QLineEdit*)tableItems[i * columns + columns+-1])->text().toStdString()));
        }
        catch (std::exception e) {
            return false;
        }
    }
    for (int i = 1; i < columns - 1; i++)
    {
        try {
            profits.push_back(std::stoi(((QLineEdit*)tableItems[(rows - 1) * columns + i])->text().toStdString()));
        }
        catch (std::exception e) {
            return false;
        }
    }
    
    return true;
}