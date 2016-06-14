/** @file MyVector.cpp
*   @author Simon Pieber
*   @date SoSe 2016
*/

#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>

using namespace std;

#include "MyVector.h"


// =======================================
// ==== Konstruktoren, Destruktor ========

MyVector::MyVector()
    : _length(0), _capacity(50), _val(nullptr)
{ _val = new double [_capacity]; }

MyVector::MyVector(uint32_t n)
    : _length(n), _capacity(n), _val(nullptr)
{
    _val = new double[n];
}

MyVector::MyVector(uint32_t n, double init)
    : _length(n), _capacity(n), _val(nullptr)
{
    _val = new double [_capacity];
    for (uint32_t i=0; i<_length; ++i)
        _val[i] = init;
}

MyVector::MyVector(initializer_list<double> const & init)
    : _length(init.size()), _capacity(init.size()), _val(nullptr)
{
    _val = new double[_length];
    int i(0);
    for (double di : init)
        _val[i++] = di;
}

MyVector::MyVector(MyVector const& v)
    : _length(v.Size()), _capacity(v.Size()), _val(nullptr)
{
    _val = new double [_length];
    for (uint32_t i=0; i<_length; ++i)
        _val[i] = v[i];
}

MyVector::~MyVector()
{
    delete [] _val;
    _val = nullptr;
}

// =======================================
// ==== Zuweisungsoperatoren =============

MyVector& MyVector::operator=(MyVector const& rhs)
{
    if (&rhs != this)
    {
        delete [] _val;
        _length   = rhs._length;
        _capacity = rhs._length;
        _val = new double[_capacity];
        for (uint32_t i=0; i<_length; ++i)
            _val[i] = rhs[i];
    }

    return *this;
}


// =======================================
// ==== Arithmetik =======================
MyVector MyVector::operator*(double a) const
{
   MyVector sol(_length);
   for (uint32_t i=0; i<_length; ++i)
      sol[i] = a*_val[i];
   return sol;
}

MyVector operator*(double a, MyVector const& v)
{  return v*a;  }

MyVector MyVector::operator+(MyVector const& rhs) const
{
   MyVector sum(rhs);
   sum += *this;
   return sum;
}

MyVector MyVector::operator-(MyVector const& rhs) const
{
   MyVector res(rhs);
   res += *this;
   return res;
}

void MyVector::operator+=(MyVector const & rhs)
{
   assert(_length == rhs.Size());
   for (uint32_t i=0; i<_length; ++i)
      _val[i] += rhs.get(i);
}

void MyVector::operator-=(MyVector const & rhs)
{
   assert(_length == rhs.Size());
   for (uint32_t i=0; i<_length; ++i)
      _val[i] -= rhs.get(i);
}

// =======================================
// ==== Zugriffsoperatoren ===============

double& MyVector::get(uint32_t n)
{
    IndexCheck(n);
    return _val[n];
}

double  MyVector::get(uint32_t n) const
{
    IndexCheck(n);
    return _val[n];
}

void MyVector::IndexCheck(uint32_t i) const
{
    assert(i<_length);
    return;
}
// =======================================
// ==== Sonstige Vektor-Methoden =========

void MyVector::IncreaseCapacity(uint32_t n)
{
    if (n > _capacity)
    {
        double* tmp = new double [n];
        for (uint32_t i=0; i<_length; ++i)
            tmp[i] = _val[i];
        _capacity = n;
        swap(_val, tmp);
        delete [] tmp;
    }
}

void MyVector::PushBack(double x)
{
    if (_length == _capacity)
    {
        IncreaseCapacity(2*_capacity+1);
    }
    _val[_length] = x;
    ++_length;
}

// =======================================
// ==== Sonstige Fukntionen ==============

void MyVector::Clear()
{
   (*this).~MyVector();
   _length = 0;
   _capacity = 0;

}

ostream& operator<<(ostream& os, MyVector const& v)
{
    if (v.Size()>0)
    {
        os << "(";
        for (uint32_t i=0; i<v.Size()-1; ++i)
            os << v[i] << ", ";
        os << v[v.Size()-1] << ")";
    }
    else
        os << "( )";
    return os;
}

void MyVector::WriteToAscii(string const& OutFileName) const
{
   ofstream outFile(OutFileName);
   outFile << _length << endl;
   for (uint32_t i=0; i<_length; ++i)   outFile << *(_val+i) << " ";
}

void MyVector::ReadFromAscii(string const& InFileName)
{
   ifstream inFile(InFileName);
   if (inFile.is_open())
   {
      (*this).~MyVector();
      inFile >> _length;
      _capacity = _length;
      _val = new double [_capacity];
      for (uint32_t i=0; i<_capacity; ++i)
         inFile >> _val[i];
      cout << "Vektor der Laenge " << _length << " von \"" << InFileName << "\" eingelesen." << endl;
   }
   else
   {
      cout << "Konnte " << InFileName << " nicht oeffnen." << endl;
   }
}

void MyVector::WriteToBinary(string const& OutFileName) const
{
   ofstream outFile(OutFileName, ofstream::binary);

   outFile.write(reinterpret_cast<const char*>(&_length), 4);
   outFile.write(reinterpret_cast<const char*>(_val), _length*8);

   cout << "MyVector::WriteToBinary: " << _length << " --> " << OutFileName << endl;
}


void MyVector::ReadFromBinary(string const& InFileName, uint32_t offset)
{
   ifstream inFile(InFileName, ifstream::binary);

   if (inFile.is_open())
   {
      (*this).~MyVector();

      inFile.read(reinterpret_cast<char*>(&_length), 4);
      _capacity = _length;
      _val = new double [_capacity];
      inFile.seekg(offset);
      inFile.read(reinterpret_cast<char*>(_val), _length*8);

      cout << "MyVector::ReadFromBinary: " << _length << " <-- " << InFileName << endl;
   }
   else
   {
      cout << "MyVector::ReadFromBinary: Konnte " << InFileName << " nicht oeffnen." << endl;
   }

}


double dot(MyVector const & a, MyVector const & b)
{
   assert(a.Size() == b.Size());
   double d(0);
   for (uint32_t i=0; i<a.Size(); ++i)
      d += a[i]*b[i];
   return d;
}


double norm(MyVector const& a)
{
   double n(0.0);
   for (uint32_t i=0; i<a.Size(); ++i)
      n += a[i]*a[i];
   return sqrt(n);
}





