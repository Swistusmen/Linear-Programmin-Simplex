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

    QPixmap pix3("prize.jpg");
    ui.success_picture->setPixmap(pix3);

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
        if (productNames.size() == 0)
        {
            ReadTable();
            GenerateConditionals();
        }
        else {
            ReadConditionals();
            ui.stackedWidget->setCurrentIndex(2);
            auto tab=GenerateCalculationsInput();
            simplex(&tab);

            
            for (int i = 0; i < tab.m; i++)
            {
                for (int j = 0; j < tab.n; j++)
                {
                    std::cout << tab.mat[i][j] << " ";
                }
                std::cout << std::endl;
            }
            MapOutputToUI(&tab);
        }
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

void SimplexForLogistics::GenerateConditionals() 
{
    conditionals.clear();
    const int noProds = productNames.size();
    ui.conditionals->setRowCount(noProds + 1);
    ui.conditionals->setColumnCount(3);

    conditionalItems.push_back(new QLabel("Produkt"));
    ui.conditionals->setCellWidget(0, 0, conditionalItems.back());

    conditionalItems.push_back(new QLabel("<= / >="));
    ui.conditionals->setCellWidget(0, 1, conditionalItems.back());

    conditionalItems.push_back(new QLabel("Liczba"));
    ui.conditionals->setCellWidget(0, 2, conditionalItems.back());

    for (int i = 0; i < noProds; i++)
    {
        conditionalItems.push_back(new QLabel(productNames[i]));
        ui.conditionals->setCellWidget(i+1, 0, conditionalItems.back());
        for (int j = 0; j < 2; j++)
        {
            conditionalItems.push_back(new QLineEdit(""));
            ui.conditionals->setCellWidget(i+1, j+1, conditionalItems.back());
        }
    }
}

bool SimplexForLogistics::ReadConditionals()
{
    const int noProds = productNames.size();

    for (int i = 0; i < noProds; i++)
    {
        try {
            conditionals.push_back(std::stoi(((QLineEdit*)conditionalItems[(i + 1) * 3 + 2])->text().toStdString()));
        }
        catch (std::exception e) {
            return false;
        }

        if (((QLineEdit*)conditionalItems[(i + 1) * 3 + 1])->text() == ">=")
            conditionals.back() *= -1;
        std::cout << conditionals.back() << std::endl;
    }
}

Tableau SimplexForLogistics::GenerateCalculationsInput()
{
    Tableau output;
    
    output.m = 1 + conditionals.size() + means;
    output.n = 1 + profits.size();

    output.mat[0][0] = 0.0;
    for (int i = 1; i < output.n; i++)
    {
        output.mat[0][i] = -1 * profits[i - 1];
    }
    for (int i = 0; i < means; i++)
    {
        output.mat[i + 1][0] = limits[i];
        for (int j = 0; j < products; j++)
        {
            output.mat[i + 1][j + 1] = meansPerProduct[i*products+j];
        }
    }
    for (int i = 0; i < conditionals.size(); i++)
    {
        int row = means + 1 + i;
        output.mat[row][0] = conditionals[i];
        for (int j = 0; j < conditionals.size(); j++)
        {
            output.mat[row][j+1] = 0.0;
        }
        output.mat[row][i + 1] = 1.0;
    }

    return output;
}



static const double epsilon = 1.0e-8;
int equal(double a, double b) { return fabs(a - b) < epsilon; }



void nl(int k) { int j; for (j = 0; j < k; j++) putchar('-'); putchar('\n'); }

void print_tableau(Tableau* tab, const char* mes) {
    static int counter = 0;
    int i, j;
    printf("\n%d. Tableau %s:\n", ++counter, mes);
    nl(70);

    printf("%-6s%5s", "col:", "b[i]");
    for (j = 1; j < tab->n; j++) { printf("    x%d,", j); } printf("\n");

    for (i = 0; i < tab->m; i++) {
        if (i == 0) printf("max:"); else
            printf("b%d: ", i);
        for (j = 0; j < tab->n; j++) {
            if (equal((int)tab->mat[i][j], tab->mat[i][j]))
                printf(" %6d", (int)tab->mat[i][j]);
            else
                printf(" %6.2lf", tab->mat[i][j]);
        }
        printf("\n");
    }
    nl(70);
}

void read_tableau(Tableau* tab, const char* filename) {
    int err, i, j;
    FILE* fp;

    fp = fopen(filename, "r");
    if (!fp) {
        printf("Cannot read %s\n", filename); exit(1);
    }
    memset(tab, 0, sizeof(*tab));
    err = fscanf(fp, "%d %d", &tab->m, &tab->n);
    if (err == 0 || err == EOF) {
        printf("Cannot read m or n\n"); exit(1);
    }
    for (i = 0; i < tab->m; i++) {
        for (j = 0; j < tab->n; j++) {
            err = fscanf(fp, "%lf", &tab->mat[i][j]);
            if (err == 0 || err == EOF) {
                printf("Cannot read A[%d][%d]\n", i, j); exit(1);
            }
        }
    }
    printf("Read tableau [%d rows x %d columns] from file '%s'.\n",
        tab->m, tab->n, filename);
    fclose(fp);
}

void pivot_on(Tableau* tab, int row, int col) {
    int i, j;
    double pivot;

    pivot = tab->mat[row][col];
    assert(pivot > 0);
    for (j = 0; j < tab->n; j++)
        tab->mat[row][j] /= pivot;
    assert(equal(tab->mat[row][col], 1.));

    for (i = 0; i < tab->m; i++) { // foreach remaining row i do
        double multiplier = tab->mat[i][col];
        if (i == row) continue;
        for (j = 0; j < tab->n; j++) { // r[i] = r[i] - z * r[row];
            tab->mat[i][j] -= multiplier * tab->mat[row][j];
        }
    }
}

// Find pivot_col = most negative column in mat[0][1..n]
int find_pivot_column(Tableau* tab) {
    int j, pivot_col = 1;
    double lowest = tab->mat[0][pivot_col];
    for (j = 1; j < tab->n; j++) {
        if (tab->mat[0][j] < lowest) {
            lowest = tab->mat[0][j];
            pivot_col = j;
        }
    }
    printf("Most negative column in row[0] is col %d = %g.\n", pivot_col, lowest);
    if (lowest >= 0) {
        return -1; // All positive columns in row[0], this is optimal.
    }
    return pivot_col;
}

// Find the pivot_row, with smallest positive ratio = col[0] / col[pivot]
int find_pivot_row(Tableau* tab, int pivot_col) {
    int i, pivot_row = 0;
    double min_ratio = -1;
    printf("Ratios A[row_i,0]/A[row_i,%d] = [", pivot_col);
    for (i = 1; i < tab->m; i++) {
        double ratio = tab->mat[i][0] / tab->mat[i][pivot_col];
        printf("%3.2lf, ", ratio);
        if ((ratio > 0 && ratio < min_ratio) || min_ratio < 0) {
            min_ratio = ratio;
            pivot_row = i;
        }
    }
    printf("].\n");
    if (min_ratio == -1)
        return -1; // Unbounded.
    printf("Found pivot A[%d,%d], min positive ratio=%g in row=%d.\n",
        pivot_row, pivot_col, min_ratio, pivot_row);
    return pivot_row;
}

void add_slack_variables(Tableau* tab) {
    int i, j;
    for (i = 1; i < tab->m; i++) {
        for (j = 1; j < tab->m; j++)
            tab->mat[i][j + tab->n - 1] = (i == j);
    }
    tab->n += tab->m - 1;
}

void check_b_positive(Tableau* tab) {
    int i;
    for (i = 1; i < tab->m; i++)
        assert(tab->mat[i][0] >= 0);
}

// Given a column of identity matrix, find the row containing 1.
// return -1, if the column as not from an identity matrix.
int find_basis_variable(Tableau* tab, int col) {
    int i, xi = -1;
    for (i = 1; i < tab->m; i++) {
        if (equal(tab->mat[i][col], 1)) {
            if (xi == -1)
                xi = i;   // found first '1', save this row number.
            else
                return -1; // found second '1', not an identity matrix.

        }
        else if (!equal(tab->mat[i][col], 0)) {
            return -1; // not an identity matrix column.
        }
    }
    return xi;
}

void print_optimal_vector(Tableau* tab, char* message) {
    int j, xi;
    printf("%s at ", message);
    for (j = 1; j < tab->n; j++) { // for each column.
        xi = find_basis_variable(tab, j);
        if (xi != -1)
            printf("x%d=%3.2lf, ", j, tab->mat[xi][0]);
        else
            printf("x%d=0, ", j);
    }
    printf("\n");
}

void simplex(Tableau* tab) {
    int loop = 0;
    add_slack_variables(tab);
    check_b_positive(tab);
    print_tableau(tab, "Padded with slack variables");
    while (++loop) {
        int pivot_col, pivot_row;

        pivot_col = find_pivot_column(tab);
        if (pivot_col < 0) {
            printf("Found optimal value=A[0,0]=%3.2lf (no negatives in row 0).\n",
                tab->mat[0][0]);
            print_optimal_vector(tab, "Optimal vector");
            break;
        }
        printf("Entering variable x%d to be made basic, so pivot_col=%d.\n",
            pivot_col, pivot_col);

        pivot_row = find_pivot_row(tab, pivot_col);
        if (pivot_row < 0) {
            printf("unbounded (no pivot_row).\n");
            break;
        }
        printf("Leaving variable x%d, so pivot_row=%d\n", pivot_row, pivot_row);

        pivot_on(tab, pivot_row, pivot_col);
        print_tableau(tab, "After pivoting");
        print_optimal_vector(tab, "Basic feasible solution");

        if (loop > 20) {
            printf("Too many iterations > %d.\n", loop);
            break;
        }
    }
}

void SimplexForLogistics::MapOutputToUI(Tableau* tab)
{
    goalFunction = tab->mat[0][0];
    for (int i = 0; i < conditionals.size(); i++)
    {
        int row = means + 1 + i;
        x.push_back(tab->mat[row][0]);
    }
    ui.f_celu->setText(QString::number(goalFunction));
    ui.output_table->setRowCount(2);
    ui.output_table->setColumnCount(x.size());
    for (int i = 0; i < x.size(); i++)
    {
        ui.output_table->setCellWidget(0, i, new QLabel("X" + QString::number(i + 1)));
        ui.output_table->setCellWidget(1, i, new QLabel(QString::number(x[i])));
    }
    
}