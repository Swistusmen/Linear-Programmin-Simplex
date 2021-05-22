/*
#include "SimplexForLogistics.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimplexForLogistics w;
    w.show();
    return a.exec();
}
*/


/*
#include "SimplexCalculations.h"

int main()
{

    int colSizeA = 2;  //should initialise columns size in A
    int rowSizeA = 2;  //should initialise columns row in A[][] vector

    float B[] = { 96000, 80000 };  //should initialis the c arry here
    float C[] = { 30,40 };  // should initialis the b array here



    float a[2][2] = {    //should intialis the A[][] array here
                   { 16,  24},
                   { 16,  10}

    };


    std::vector <std::vector<float> > vec2D(rowSizeA, std::vector<float>(colSizeA, 0));

    std::vector<float> b(rowSizeA, 0);
    std::vector<float> c(colSizeA, 0);




    for (int i = 0; i < rowSizeA; i++) {         //make a vector from given array
        for (int j = 0; j < colSizeA; j++) {
            vec2D[i][j] = a[i][j];
        }
    }





    for (int i = 0; i < rowSizeA; i++) {
        b[i] = B[i];
    }

    for (int i = 0; i < colSizeA; i++) {
        c[i] = C[i];
    }


    // hear the make the class parameters with A[m][n] vector b[] vector and c[] vector
    Simplex simplex(vec2D, b, c);
    simplex.CalculateSimplex();


    return 0;
}
*/
/*
  What: Simplex in C
  AUTHOR: GPL(C) moshahmed/at/gmail.

  What: Solves LP Problem with Simplex:
    { maximize cx : Ax <= b, x >= 0 }.
  Input: { m, n, Mat[m x n] }, where:
    b = mat[1..m,0] .. column 0 is b >= 0, so x=0 is a basic feasible solution.
    c = mat[0,1..n] .. row 0 is z to maximize, note c is negated in input.
    A = mat[1..m,1..n] .. constraints.
    x = [x1..xm] are the named variables in the problem.
    Slack variables are in columns [m+1..m+n]

  USAGE:
    1. Problem can be specified before main function in source code:
      c:\> vim mosplex.c
      Tableau tab  = { m, n, {   // tableau size, row x columns.
          {  0 , -c1, -c2,  },  // Max: z = c1 x1 + c2 x2,
          { b1 , a11, a12,  },  //  b1 >= a11 x1 + a12 x2
          { b2 , a21, a22,  },  //  b2 >= a21 x1 + a22 x2
        }
      };
      c:\> cl /W4 mosplex.c  ... compile this file.
      c:\> mosplex.exe problem.txt > solution.txt

    2. OR Read the problem data from a file:
      $ cat problem.txt
            m n
            0  -c1 -c2
            b1 a11 a12
            b2 a21 a11
      $ gcc -Wall -g mosplex.c  -o mosplex
      $ mosplex problem.txt > solution.txt
*/
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
