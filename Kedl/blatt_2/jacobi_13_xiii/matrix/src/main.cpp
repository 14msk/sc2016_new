#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <ratio>
#include <chrono>
#include "../inc/matrix.hpp"
#include "../inc/myvector.h"

using namespace std;

int main( int argc, char **argv ) {
  double tol = 1e-13;

  if ( argc >= 1 ) {
    tol = stod(argv [1]);
  }
  int unused;
  Matrix AA(4,4,{{10,-1,2,0},{-1,11,-1,3},{2,-1,10,-1},{0,3,-1,8}});
  MyVector bb({6,25,-11,15});
  MyVector xx = jacobi(AA,bb,tol);

  return 0;
}
