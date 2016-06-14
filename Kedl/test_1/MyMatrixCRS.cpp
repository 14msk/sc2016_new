/** @file MyMatrixCRS.cpp
*   @author Simon Pieber
*   @date SoSe 2016
*/

#include <iostream>
#include <string>
#include <cassert>
#include <map>
#include <cmath>
#include <fstream>

using namespace std;

#include "MyVector.h"
#include "MyMatrix.h"
#include "MyMatrixCRS.h"

class MyVector;
class MyMatrix;

// ==================================================
// ======= Konstruktoren, Destruktor ================
// ==================================================

MyMatrixCRS::MyMatrixCRS()
   : _A(nullptr), _IA(nullptr), _JA(nullptr), _n(0), _m(0), _nnz(0)
{
   _IA    = new uint32_t [1];
   _IA[0] = 0;
}

MyMatrixCRS::MyMatrixCRS(uint32_t n, uint32_t m)
    : MyMatrixCRS()
{
   _n = n;
   _m = m;
   delete [] _IA;
   _IA = new uint32_t [_n+1];
   for (uint32_t i=0; i<=_n; ++i)
      _IA[i] = 0;
}

MyMatrixCRS::MyMatrixCRS(MyMatrixCRS const & orig)
    : _A(nullptr), _IA(nullptr), _JA(nullptr), _n(orig._n), _m(orig._m), _nnz(orig._nnz)
{
   _A  = new double [_nnz];
   _IA = new uint32_t [_n+1];
   _JA = new uint32_t [_nnz];
   for (uint32_t i=0; i<_nnz; ++i)
   {
      _A [i] = orig._A [i];
      _JA[i] = orig._JA[i];
   }
   for (uint32_t i=0; i<=_n; ++i)
      _IA[i] = orig._IA[i];
}

MyMatrixCRS::MyMatrixCRS(MyMatrix const & mat)
    : MyMatrixCRS(mat.NrOfRows(), mat.NrOfCols())
{
   for (uint32_t i=0; i<mat.NrOfRows(); ++i)
   {
      for (uint32_t j=0; j<mat.NrOfCols(); ++j)
         Set(i,j, mat(i,j));
   }
}

MyMatrixCRS::~MyMatrixCRS()
{
   delete [] _A;
   delete [] _IA;
   delete [] _JA;
}


// ==================================================
// ======= Zuweisungsoperator =======================
// ==================================================

MyMatrixCRS& MyMatrixCRS::operator=(const MyMatrixCRS& rhs)
{
   if (&rhs != this)
   {
      MyMatrixCRS newCRS(rhs);
      swap(_A, newCRS._A);
      swap(_IA, newCRS._IA);
      swap(_JA, newCRS._JA);
      swap(_n, newCRS._n);
      swap(_m, newCRS._m);
      swap(_nnz, newCRS._nnz);
   }
   return *this;
}

// ==================================================
// ======= Zugriffsoperatoren =======================
// ==================================================

double MyMatrixCRS::operator()(uint32_t i, uint32_t j) const
{
   double Mij(0.0);
   assert(i<_n && j<_m);
   uint32_t pos = FindIndexA(i,j);
   if (pos != static_cast<uint32_t>(-1))
   {
      Mij = _A[pos];
   }
   return Mij;
}

// warnung: keine Eintraege werden geloescht, wenn auf 0 gesetzt
void   MyMatrixCRS::Set(uint32_t i, uint32_t j, double x)
{
   assert(i<_n && j<_m);
   if (abs(x) > 1e-17)
   {
      uint32_t pos = FindIndexA(i, j);
      if (pos != static_cast<uint32_t>(-1))
      {
         _A[pos] = x;
      }
      else
      {
         uint32_t nz_posj(0); // Anzahl !=0 Elemente in Zeile i VOR Position (i,j)

         if (_nnz > 0)
         {
            while ((_JA[ _IA[i] + nz_posj] < j)          // SpaltenNr in Zeile i ist < j
            && (nz_posj < (_IA[i+1] - _IA[i])))   // Wir sind noch in Zeile i
            {
               ++nz_posj;
            }
         }
         ++_nnz;

         double*   new_A  = new double [_nnz];
         uint32_t* new_JA = new uint32_t [_nnz];
         pos = _IA[i] + nz_posj; // dort muss in _A und _JA jeweiliges Element eingefuegt werden
         for (uint32_t k=0; k<pos; ++k)
         {
            new_A[k]  =  _A[k];
            new_JA[k] = _JA[k];
         }
         new_A[pos]  = x;
         new_JA[pos] = j;
         for (uint32_t k=pos+1; k<_nnz; ++k)
         {
            new_A[k]  =  _A[k-1];
            new_JA[k] = _JA[k-1];
         }

         for (uint32_t k=i+1; k<=_n; ++k)
         {
            _IA[k] += 1;
         }
         swap( _A, new_A );
         swap(_JA, new_JA);
         delete [] new_A;
         delete [] new_JA;
      }
   }
}


uint32_t MyMatrixCRS::FindIndexA(uint32_t const& i, uint32_t const& j) const
{
   uint32_t pos(static_cast<uint32_t>(-1));
   if (_nnz > 0 && i<_n)
   {
      uint32_t nnzi = _IA[i+1] - _IA[i]; // non-zeros in zeile i
      if (nnzi > 0)
      {
         uint32_t posj(0);
         while (((_JA[_IA[i] + posj] < j) && (posj < nnzi-1)))
         {
            ++posj;
         }
         if (_JA[_IA[i] + posj] == j) // gefunden
         {
            pos = _IA[i] + posj;
         }
      }
   }
   return pos;
}


// ==================================================
// ======= Arithmetik ===============================
// ==================================================

MyVector MyMatrixCRS::operator*(MyVector const & v) const
{
    assert(_m == v.Size());
    MyVector res(_n, 0.0);
    for (uint32_t i = 0; i<_n; ++i)
    {
        for (uint32_t k = _IA[i]; k<_IA[i+1]; ++k)
        {
            res[i] += _A[k] * v[_JA[k]];
        }
    }
    return res;
}

MyMatrixCRS MyMatrixCRS::operator+(MyMatrixCRS const & rhs) const
{
    assert(_n == rhs._n && _m == rhs._m);

    MyMatrixCRS newCRS;
    for (uint32_t i=0; i<_n; ++i)
    {
        for (uint32_t j=0; j<_m; ++j)
        {
            newCRS.Set(i,j, operator()(i,j) + rhs(i,j));
        }
    }
    return newCRS;
}

MyMatrixCRS MyMatrixCRS::operator-(MyMatrixCRS const & rhs) const
{
   assert(_n == rhs.NrOfRows());

   MyMatrixCRS newCRS;
   for (uint32_t i=0; i<_n; ++i)
   {
      for (uint32_t j=0; j<_m; ++j)
      {
         newCRS.Set(i,j, operator()(i,j) - rhs(i,j));
      }
   }
   return newCRS;
}

MyMatrixCRS MyMatrixCRS::operator*(double alpha) const
{
   MyMatrixCRS newCRS;
   if (abs(alpha) > 1.0e-30)
   {
      newCRS = *this;
      for (uint32_t k=0; k<_nnz; ++k)
         newCRS._A[k] *= alpha;
   }
   return newCRS;
}


// ==================================================
// ======= Sonstige Methoden ========================
// ==================================================

void MyMatrixCRS::CheckStructure() const
{
    cout << "(_n, _m, _nnz) = " << _n << ", " << _m << ", " << _nnz << endl;
    cout << " _A:   ";
    for (uint32_t i=0; i<_nnz; ++i) cout << _A[i] << " ";
    cout << endl;
    cout << " _IA:  ";
    for (uint32_t i=0; i<=_n; ++i)  cout << _IA[i] << " ";
    cout << endl;
    cout << " _JA:  ";
    for (uint32_t i=0; i<_nnz; ++i) cout << _JA[i] << " ";
    cout << endl;
}

void MyMatrixCRS::ShowFullMatrix() const
{
   for (uint32_t i=0; i<_n; ++i)
   {
      cout << "Zeile " << i << ":   ";
      for (uint32_t j=0; j<_m; ++j)
      {
         cout << operator()(i,j) << "  ";
      }
      cout << endl;
   }
}


void MyMatrixCRS::WriteToAscii(string const & OutFileName) const
{
   ofstream outFile(OutFileName);
   if (outFile.is_open())
   {
      outFile << _n << " " << _m << " " << _nnz << endl;
      for (uint32_t i=0; i<_nnz; i++)
      {
         outFile << _A[i] << " ";
      }
      outFile << endl;
      for (uint32_t i=0; i<=_n; ++i)
      {
         outFile << _IA[i] << " ";
      }
      outFile << endl;
      for (uint32_t i=0; i<_nnz; ++i)
      {
         outFile << _JA[i] << " ";
      }
      outFile.close();
      cout << "MyMatrixCRS::WriteToAscii: " << _n << " x " << _m
       << " Matrix --> " << OutFileName << endl;
   }
   else
   {
      cout << "MyMatrixCRS::WriteToAscii: Konnte file "
           << OutFileName << " nicht oeffnen." << endl;
   }
}

void MyMatrixCRS::ReadFromAscii(string const & InFileName)
{
    ifstream inFile(InFileName);
    if (inFile.is_open())
    {
        (*this).~MyMatrixCRS();
        inFile >> _n >> _m >> _nnz;
        _A  = new double [_nnz];
        _IA = new uint32_t [_n+1];
        _JA = new uint32_t [_nnz];
        for (uint32_t i=0; i<_nnz; ++i)  inFile >>  _A[i];
        for (uint32_t i=0; i<=_n ; ++i)  inFile >> _IA[i];
        for (uint32_t i=0; i<_nnz; ++i)  inFile >> _JA[i];
        cout << "CRS-Matrix eingelesen. " << _n << " x " << _m << "  -->  " << InFileName << endl;
    }
    else
    {
        cout << "ACHTUNG: Konnte " << InFileName << " nicht oeffnen." << endl;
    }
}

void MyMatrixCRS::WriteToBinary(string const & OutFileName) const
{
    ofstream outFile(OutFileName, ofstream::binary);

    uint16_t const SizeInt(4), SizeDouble(8);

    outFile.write(reinterpret_cast<char const*>(&_n),   SizeInt);
    outFile.write(reinterpret_cast<char const*>(&_m),   SizeInt);
    outFile.write(reinterpret_cast<char const*>(&_nnz), SizeInt);
    outFile.write(reinterpret_cast<char const*>( _A),   _nnz*SizeDouble);
    outFile.write(reinterpret_cast<char const*>(_IA), (_n+1)*SizeInt);
    outFile.write(reinterpret_cast<char const*>(_JA),   _nnz*SizeInt);

    outFile.close();

    cout << "MyMatrixCRS::WriteToBinary:  "
         << _n << " x " << _m << " --> " << OutFileName << endl;
}

void MyMatrixCRS::ReadFromBinary(string const & InFileName)
{
    ifstream inFile(InFileName, ifstream::binary);

    if (!inFile.is_open())
    {
        cout << "MyMatrixCRS::ReadFromBinary: FEHLER. Konnte Datei \"" << InFileName
             << "\" nicht oeffnen." << endl;
    }
    else
    {
        uint16_t const SizeInt(4), SizeDouble(8);

        inFile.read(reinterpret_cast<char*>(&_n),   SizeInt);
        inFile.read(reinterpret_cast<char*>(&_m),   SizeInt);
        inFile.read(reinterpret_cast<char*>(&_nnz), SizeInt);

        this -> ~MyMatrixCRS();

        _A  = new double [_nnz];
        _IA = new uint32_t [_n+1];
        _JA = new uint32_t [_nnz];

        inFile.read(reinterpret_cast<char*>( _A),   _nnz*SizeDouble);
        inFile.read(reinterpret_cast<char*>(_IA), (_n+1)*SizeInt);
        inFile.read(reinterpret_cast<char*>(_JA),   _nnz*SizeInt);

        cout << "MyMatrixCRS::ReadFromBinary:  "
             << _n << " x " << _m << " <-- " << InFileName << endl;
    }
}














