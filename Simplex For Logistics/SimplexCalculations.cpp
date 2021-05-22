#include "SimplexCalculations.h"

/*
The main method is in this program itself.
Instructions for compiling=>>
Run on any gcc compiler=>>
Special***** should compile in -std=c++11 or C++14 -std=gnu++11  *********  (mat be other versions syntacs can be different)
turorials point online compiler
==> go ti link   http://cpp.sh/ or  https://www.tutorialspoint.com/cplusplus/index.htm and click try it(scorel below) and after go to c++ editor copy code and paste.
after that click button execute.
if you have -std=c++11 you can run in command line;
g++ -o output Simplex.cpp
./output
How to give inputs to the program =>>>
   Example:
    colSizeA = 6 // input colmn size
    rowSizeA = 3  // input row size
    float C[N]={-6,-5,-4,0,0,0};  //Initialize the C array  with the coefficients of the constraints of the objective function
    float B[M]={240,360,300};//Initialize the B array constants of the constraints respectively
   //initialize the A array by giving all the coefficients of all the variables
   float A[M][N] =  {
                 { 2,  1,  1,   1,  0, 0},
                { 1,  3,  2,   0,  1, 0 },
                {   2,    1,  2,   0,  0,  1}
                };
*/



Simplex::Simplex(std::vector <std::vector<float> > matrix, std::vector<float> b, std::vector<float> c) {
        maximum = 0;
        isUnbounded = false;
        rows = matrix.size();
        cols = matrix[0].size();
        A.resize(rows, std::vector<float>(cols, 0));
        B.resize(b.size());
        C.resize(c.size());

        for (int i = 0; i < rows; i++) {             
            for (int j = 0; j < cols; j++) {
                A[i][j] = matrix[i][j];

            }
        }

        for (int i = 0; i < c.size(); i++) {      
            C[i] = c[i];
        }
        for (int i = 0; i < b.size(); i++) {      
            B[i] = b[i];
        }




    }

bool Simplex::simplexAlgorithmCalculataion() {
        if (checkOptimality() == true) {
            return true;
        }

        int pivotColumn = findPivotColumn();


        if (isUnbounded == true) {
            std::cout << "Error unbounded" << std::endl;
            return true;
        }

        int pivotRow = findPivotRow(pivotColumn);

        doPivotting(pivotRow, pivotColumn);

        return false;
    }

bool Simplex::checkOptimality() {
        bool isOptimal = false;
        int positveValueCount = 0;

        for (int i = 0; i < C.size(); i++) {
            float value = C[i];
            if (value >= 0) {
                positveValueCount++;
            }
        }
        if (positveValueCount == C.size()) {
            isOptimal = true;
            print();
        }
        return isOptimal;
    }

void Simplex::doPivotting(int pivotRow, int pivotColumn) {

        float pivetValue = A[pivotRow][pivotColumn];
       /*
        std::vector<float> pivotRowVals;
        pivotRowVals.resize(cols);
        std::vector<float> pivotColVals;
        pivotColVals.resize(rows);
        std::vector<float> rowNew;
        rowNew.resize(cols);
        */
        float* pivotRowVals = new float[cols];
        float* pivotColVals = new float[rows];
        float* rowNew = new float[cols];
        maximum = maximum - (C[pivotColumn] * (B[pivotRow] / pivetValue)); 
        for (int i = 0; i < cols; i++) {
            pivotRowVals[i] = A[pivotRow][i];
        }
        //get the column that has the pivot value
        for (int j = 0; j < rows; j++) {
            pivotColVals[j] = A[j][pivotColumn];
        }

        //set the row values that has the pivot value divided by the pivot value and put into new row
        for (int k = 0; k < cols; k++) {
            rowNew[k] = pivotRowVals[k] / pivetValue;
        }

        B[pivotRow] = B[pivotRow] / pivetValue;


        //process the other coefficients in the A array by subtracting
        for (int m = 0; m < rows; m++) {
            //ignore the pivot row as we already calculated that
            if (m != pivotRow) {
                for (int p = 0; p < cols; p++) {
                    float multiplyValue = pivotColVals[m];
                    A[m][p] = A[m][p] - (multiplyValue * rowNew[p]);
                    //C[p] = C[p] - (multiplyValue*C[pivotRow]);
                    //B[i] = B[i] - (multiplyValue*B[pivotRow]);
                }

            }
        }

        //process the values of the B array
        for (int i = 0; i < B.size(); i++) {
            if (i != pivotRow) {

                float multiplyValue = pivotColVals[i];
                B[i] = B[i] - (multiplyValue * B[pivotRow]);

            }
        }
        //the least coefficient of the constraints of the objective function
        float multiplyValue = C[pivotColumn];
        //process the C array
        for (int i = 0; i < C.size(); i++) {
            C[i] = C[i] - (multiplyValue * rowNew[i]);

        }


        //replacing the pivot row in the new calculated A array
        for (int i = 0; i < cols; i++) {
            A[pivotRow][i] = rowNew[i];
        }


    }


    //find the least coefficients of constraints in the objective function's position
int Simplex::findPivotColumn() {

        int location = 0;
        float minm = C[0];



        for (int i = 1; i < C.size(); i++) {
            if (C[i] < minm) {
                minm = C[i];
                location = i;
            }
        }

        return location;
}

int Simplex::findPivotRow(int pivotColumn) {
        float* positiveValues=new float[rows];
        std::vector<float> result(rows, 0);
        //float result[rows];
        int negativeValueCount = 0;

        for (int i = 0; i < rows; i++) {
            if (A[i][pivotColumn] > 0) {
                positiveValues[i] = A[i][pivotColumn];
            }
            else {
                positiveValues[i] = 0;
                negativeValueCount += 1;
            }
        }
        //checking the unbound condition if all the values are negative ones
        if (negativeValueCount == rows) {
            isUnbounded = true;
        }
        else {
            for (int i = 0; i < rows; i++) {
                float value = positiveValues[i];
                if (value > 0) {
                    result[i] = B[i] / value;

                }
                else {
                    result[i] = 0;
                }
            }
        }
        //find the minimum's location of the smallest item of the B array
        float minimum = 99999999;
        int location = 0;
        for (int i = 0; i < result.size(); i++) {
            if (result[i] > 0) {
                if (result[i] < minimum) {
                    minimum = result[i];

                    location = i;
                }
            }

        }

        return location;

    }

    void Simplex::CalculateSimplex() {
        bool end = false;

        std::cout << "initial array(Not optimal)" << std::endl;
        print();

        std::cout << "final array(Optimal solution)" << std::endl;


        while (!end) {

            bool result = simplexAlgorithmCalculataion();

            if (result == true) {

                end = true;


            }
        }
        std::cout << "Answers for the Constraints of variables" << std::endl;

        for (int i = 0; i < A.size(); i++) {  //every basic column has the values, get it form B array
            int count0 = 0;
            int index = 0;
            for (int j = 0; j < rows; j++) {
                if (A[j][i] == 0.0) {
                    count0 += 1;
                }
                else if (A[j][i] == 1) {
                    index = j;
                }


            }

            if (count0 == rows - 1) {

                std::cout << "variable" << index + 1 << ": " << B[index] << std::endl;  //every basic column has the values, get it form B array
            }
            else {
                std::cout << "variable" << index + 1 << ": " << 0 << std::endl;

            }

        }


        std::cout << "" << std::endl;
        std::cout << "maximum value: " << maximum << std::endl;  //print the maximum values




    } 

    void Simplex::print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << A[i][j] << " ";
            }
            std::cout << "" << std::endl;
        }
        std::cout << "" << std::endl;
    }


