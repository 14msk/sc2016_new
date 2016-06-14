#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <ratio>
#include <chrono>
#include "matrix.hpp"
#include "myvector.h"

using namespace std;


int main() {
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

    cout.precision(12);

    Matrix A = Matrix(3,3);
    Matrix B (3,3, {{1,2,3},{4,5,6},{7,8,9}});
    Matrix C(B);
    Matrix D = A;
    D = Matrix(3,3, {{9,8,7},{6,5,4},{3,2,1}});
    Matrix E = B + D;
    Matrix F = B - D;
    Matrix X (2,3, {{1,2,1},{1,0,2}});
    MyVector v({1,2,3});
    MyVector Y = X*v;
    Matrix Q (2,3, {{3,2,1},{1,0,2}});
    Matrix R (3,2, {{1,2},{0,1},{4,0}});
    Matrix G = R*Q;

    cout << "A: " << endl << A << endl;
    cout << "B: " << endl << B << endl;
    cout << "C: " << endl << C << endl;
    cout << "D: " << endl << D << endl;
    cout << "E: " << endl << E << endl;
    cout << "F: " << endl << F << endl;
    cout << "Y: " << endl << Y << endl << endl;
    cout << "Q: " << endl << Q << endl;
    cout << "R: " << endl << R << endl;
    cout << "G: " << endl << G << endl;

    ofstream myfile;
    myfile.open ("matrix.txt");
    myfile << G;
    myfile.close();

Matrix AA(4,4,{{10,-1,2,0},{-1,11,-1,3},{2,-1,10,-1},{0,3,-1,8}});
MyVector bb({6,25,-11,15});
MyVector xx = jacobi(AA,bb,1e-13);

chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  std::cout << "Die Ausfuehrung dieses Programms dauerte " << time_span.count() << " Sekunden.";
  std::cout << std::endl;

//Matrix CC(4,4,{{10,-2,-1,-1},{-2,10,-1,-1},{-1,-1,10,-2},{-1,-1,-2,10}});
//MyVector dd({3,15,27,-9});
//MyVector yy = jacobi(CC,dd,{0,0,0,0});
//cout << "x: " << endl << yy << endl << endl;
    return 0;
}
