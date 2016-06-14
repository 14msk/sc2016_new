#include <iostream>
#include <fstream>
#include "mymatrix.hpp"

using namespace std;

int main() {

    MyMatrix A;
    A = MyMatrix(3,3);
    MyMatrix B = MyMatrix(3,3, {1,2,3,4,5,6,7,8,9});
    MyMatrix C(B);
    MyMatrix D = MyMatrix(3,3, {9,8,7,6,5,4,3,2,1});
    MyMatrix E= B + D;
    MyMatrix F = E - MyMatrix(3,3, {6,7,8,9,10,11,12,13,14,15});
    MyMatrix X = MyMatrix(2,3, {1,2,1,1,0,2});
    MyVector v = MyVector({1,2,3});
    MyVector Y = X*v;
    MyMatrix Q = MyMatrix(2,3, {3,2,1,1,0,2});
    MyMatrix R = MyMatrix(3,2, {1,2,0,1,4,0});

    cout << A << endl;
    cout << B << endl;
    cout << C << endl;
    cout << D << endl;
    cout << E << endl;
    cout << F << endl;
    cout << Y << endl;
    cout << Q << endl;
    cout << R << endl;
    cout << Q*R << endl;
    cout << R*Q << endl;
    cout <<MyMatrix(2,3, {4,2,1,0,-2,4})*MyMatrix(3,3, {1,2,3,0,4,6,2,-1,8}) << endl;


    ofstream myfile;
    myfile.open ("mymatrix.txt");
    myfile << B;
    myfile.close();

    return 0;
}
