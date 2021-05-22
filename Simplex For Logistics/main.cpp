
#include "SimplexForLogistics.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimplexForLogistics w;
    w.show();
    return a.exec();
}



/*

#include "SimplexCalculations.h"
#include <iostream>

Tableau tab = { 5, 3, {                     // Size of tableau [4 rows x 5 columns ]
    { 0.0, -30.0, -40.0 },
    { 96000.0, 16.0 , 24.0   },
    { 80000.0, 16.0 ,  10.0   },
    {3000.0, 1.0, 0.0},
    {4000, 0.0, 1.0}
  }
};
int main(int argc, char* argv[]) {
    if (argc > 1) { // usage: cmd datafile
        read_tableau(&tab, argv[1]);
    }
    print_tableau(&tab, "Initial");
    simplex(&tab);

    print_optimal_vector(&tab, "Hello");
    std::cout << tab.m << " " << tab.n << std::endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            std::cout << tab.mat[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
*/