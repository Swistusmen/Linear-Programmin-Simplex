#include <iostream>
#include <cmath>
#include <vector>

class Simplex {
private:
    int rows, cols;
    std::vector <std::vector<float> > A;
    std::vector<float> B;
    std::vector<float> C;

    float maximum;
    bool isUnbounded;

public:
    Simplex(std::vector <std::vector<float> > matrix, std::vector<float> b, std::vector<float> c);

    bool simplexAlgorithmCalculataion();
    bool checkOptimality();
    void doPivotting(int pivotRow, int pivotColumn);
    int findPivotColumn();
    int findPivotRow(int pivotColumn);
    void CalculateSimplex();
    void print();
};



/*
int main()
{

    int colSizeA = 6;  //should initialise columns size in A
    int rowSizeA = 3;  //should initialise columns row in A[][] vector

    float C[] = { -6,-5,-4,0,0,0 };  //should initialis the c arry here
    float B[] = { 180,300,240 };  // should initialis the b array here



    float a[3][6] = {    //should intialis the A[][] array here
                   { 2,  1,  1, 1, 0, 0},
                   { 1,  3,  2, 0, 1, 0},
                   { 2,  1,  2, 0, 0, 1}
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