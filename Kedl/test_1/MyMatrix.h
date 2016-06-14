#pragma once

class MyVector;
class MyMatrixCRS;

class MyMatrix
{
public:
// Konstruktoren und Destruktor
   MyMatrix() : _n(0), _m(0), _mat(nullptr) {};
   MyMatrix(uint32_t n, uint32_t m) : _n(n), _m(m), _mat(nullptr)
   {
      _mat = new double [_n*_m];
   }
   MyMatrix(const MyMatrix& other);
   MyMatrix(const MyMatrixCRS & matCRS);

   ~MyMatrix() {delete [] _mat;}

// Zugriffsoperatoren
   double& operator()(uint32_t i, uint32_t j)
   { return _mat[_m*i + j]; }

   double  operator()(uint32_t i, uint32_t j) const
   { return _mat[_m*i + j]; }

   double& get(uint32_t i, uint32_t j);       // mit Index-Check
   double  get(uint32_t i, uint32_t j) const; // mit Index-Check
   uint32_t  NrOfRows() const {return _n;}
   uint32_t  NrOfCols() const {return _m;}

   void IndexCheck(uint32_t i, uint32_t j) const;

// Zuweisungsoperator
   MyMatrix& operator=(MyMatrix const & rhs);
   MyMatrix& operator=(MyMatrix&& rhs);

//  Arithmetik
   void operator+=(MyMatrix const& rhs);
   void operator-=(MyMatrix const& rhs);
   MyMatrix operator+(MyMatrix const& rhs) const;
   MyMatrix operator-(MyMatrix const& rhs) const;
   MyMatrix operator-(MyMatrix&& rhs)       const;
   MyMatrix operator*(double alpha)         const;
   MyVector operator*(const MyVector & x)   const;

//  Sonstige Methoden
   void WriteToAscii(string const& outFile) const;
   void WriteToBinary(string const& OutFileName) const;
   void ReadFromAscii(string const& inFileName);
   void ReadFromBinary(string const& InFileName);

private:
   uint32_t _n; // Zeilen
   uint32_t _m; // Spalten
   double* _mat;
};

MyMatrix operator-(MyMatrix const & m);
MyMatrix operator*(double alpha, MyMatrix const & m);

