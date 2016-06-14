/** @file MyMatrix.cpp
*   @author Simon Pieber
*   @date SoSe 2016
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <map>

using namespace std;

#include "MyVector.h"
#include "MyMatrix.h"
#include "MyMatrixCRS.h"

//// ===============================
//// ===== Konstruktoren ===========

MyMatrix::MyMatrix(const MyMatrix& other)
    : _n(other._n), _m(other._m), _mat(nullptr)
{
    _mat = new double [_m*_n];
    for (uint32_t k = 0; k<_m*_n; ++k)
        _mat[k] = other._mat[k];
}

MyMatrix::MyMatrix(const MyMatrixCRS & matCRS)
    : _n(matCRS.NrOfRows()), _m(matCRS.NrOfCols()), _mat(nullptr)
{
    _mat = new double [_n*_m];
    for (uint32_t i=0; i<_n; ++i)
    {
        for (uint32_t j=0; j<_m; ++j)
        {
            _mat[_m*i + j] = matCRS(i,j);
        }
    }
}

//// ===============================
//// ===== Zugriffsoperatoren ======

double& MyMatrix::get(uint32_t i, uint32_t j)
{
    IndexCheck(i,j);
    return _mat[_m*i + j];;
}

double  MyMatrix::get(uint32_t i, uint32_t j) const
{
    IndexCheck(i,j);
    return _mat[_m*i + j];;
}

void MyMatrix::IndexCheck(uint32_t i, uint32_t j) const
{
    assert(i<_n && j<_m);
}

//// ===============================
//// ===== Zuweisungsoperatoren ====
MyMatrix& MyMatrix::operator=(MyMatrix const & rhs)
{
    if (this != &rhs)
    {
        (*this).~MyMatrix();
        _m = rhs._m;
        _n = rhs._n;
        _mat = new double [_m*_n];
        for (uint32_t i=0; i<_n*_m; ++i)
            _mat[i] = rhs._mat[i];
    }
    return *this;
}

MyMatrix& MyMatrix::operator=(MyMatrix&& rhs)
{
    swap(_m, rhs._m);
    swap(_n, rhs._n);
    swap(_mat, rhs._mat);
    delete [] rhs._mat; // notwendig ??
    return *this;
}

//// ===============================
//// ===== Arithmetik ==============
void MyMatrix::operator+=(MyMatrix const& rhs)
{
   assert(rhs._m == _m && rhs._n == _n);
   for (uint32_t i=0; i<_n*_m; ++i)
   {
      _mat[i] += rhs._mat[i];
   }
}


void MyMatrix::operator-=(MyMatrix const& rhs)
{
   assert(rhs._m == _m && rhs._n == _n);
   for (uint32_t i=0; i<_n*_m; ++i)
   {
      _mat[i] -= rhs._mat[i];
   }
}


MyMatrix MyMatrix::operator+(MyMatrix const & rhs) const
{
   MyMatrix res(*this);
   res += rhs;
   return res;
}

MyMatrix MyMatrix::operator-(MyMatrix const & rhs) const
{
   MyMatrix res(*this);
   res += rhs;
   return res;
}

MyMatrix operator-(MyMatrix const & m)
{
   return m*(-1.0);
}

MyMatrix MyMatrix::operator*(double alpha) const
{
   MyMatrix CopyOfThis(*this);
   for (uint32_t i=0; i<_m*_n; ++i)
      CopyOfThis._mat[i] = alpha*_mat[i];
   return CopyOfThis;
}

MyMatrix operator*(double alpha, MyMatrix const & m)
{
   return m*alpha;
}

MyVector MyMatrix::operator*(const MyVector& x) const
{
   assert(x.Size() == _m);
   MyVector result(_n, 0);
   for (uint32_t i=0; i<_n; ++i)
   {
      for (uint32_t j=0; j<_m; ++j)
         result[i] += _mat[i*_m+j]*x[j];
   }
   return result;
}


//// ===============================
//// ===== Sonstige Methoden =======
void MyMatrix::WriteToAscii(string const& outFileName) const
{
    ofstream outFile(outFileName);
    outFile << _n << " " << _m << endl << endl;
    for (uint32_t i=0; i<_n; ++i)
    {
        for (uint32_t j=0; j<_m; ++j)
        {
            outFile << this->get(i,j) << " ";
        }
        outFile << endl;
    }
    cout << "WriteToAscii:   " << _n << " x " << _m << " Matrix --> \""
         << outFileName << "\"" << endl;
}

void MyMatrix::ReadFromAscii(string const& inFileName)
{
    ifstream inFile(inFileName);
    if (!inFile.is_open())
        cout << "ReadFromAscii:  Konnte \"" << inFileName
             << "\" nicht finden." << endl;
    else
    {
        inFile >> _n >> _m;
        delete [] _mat;
        _mat = new double [_m*_n];
        for (uint32_t k=0; k<_m*_n; ++k)
            inFile >> _mat[k];
        cout << "ReadFromAscii:  " << _n << " x " << _m
            << " Matrix <-- \"" << inFileName << "\"" << endl;
    }
}

void MyMatrix::WriteToBinary(string const& OutFileName) const
{
   ofstream outFile(OutFileName, ofstream::binary);

   outFile.write(reinterpret_cast<char const*> (&_n), 4);
   outFile.write(reinterpret_cast<char const*> (&_m), 4);
   outFile.write(reinterpret_cast<char const*>(_mat), 8*_n*_m);
   cout << "WriteToBinary:  " << _n << " x " << _m
        << " --> \"" << OutFileName << "\"" << endl;
}

void MyMatrix::ReadFromBinary(string const& InFileName)
{
   ifstream inFile(InFileName, ifstream::binary);

   if (inFile.is_open())
   {
      (*this).~MyMatrix();

      inFile.read(reinterpret_cast<char*>(&_n), 4);
      inFile.read(reinterpret_cast<char*>(&_m), 4);

      _mat = new double [_n*_m];

      inFile.read(reinterpret_cast<char*>(_mat), 8*_n*_m);
      cout << "ReadFromBinary:  " << _n << " x " << _m
      << " <-- \"" << InFileName << "\"" << endl;
   }
   else
   {
      cout << "ReadFromBinary:  Konnte \"" << InFileName
           << "\" nicht oeffnen." << endl;
   }
}










