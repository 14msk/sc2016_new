#pragma once

class MyVector;
class MyMatrix;

class MyMatrixCRS
{
public:
//  Konstruktoren, Destruktor
    MyMatrixCRS();
    MyMatrixCRS(uint32_t n, uint32_t m);
    MyMatrixCRS(MyMatrixCRS const& orig);
    MyMatrixCRS(MyMatrix const& mat);
    ~MyMatrixCRS();

//  Zuweisungsoperator
    MyMatrixCRS& operator=(const MyMatrixCRS & rhs);

//  Zugriffsoperatoren
    double operator()(uint32_t i, uint32_t j) const;
    void Set(uint32_t i, uint32_t j, double x);

    uint32_t NonZeroElements() const { return _nnz; };
    uint32_t NrOfCols() const {return _m;}
    uint32_t NrOfRows() const {return _n;}
    void SetNrOfCols(uint32_t m) {_m = m;}
    void SetNrOfRows(uint32_t n) {_n = n;}

//  Arithmetik
    MyVector operator*(MyVector const & v) const;
    MyMatrixCRS operator+(MyMatrixCRS const & rhs) const;
    MyMatrixCRS operator-(MyMatrixCRS const & rhs) const;
    MyMatrixCRS operator*(double alpha) const;


//  Sonstiges
    void CheckStructure() const;
    void ShowFullMatrix() const;

    void WriteToAscii(string const & OutFileName) const;
    void ReadFromAscii(string const & InFileName);
    void WriteToBinary(string const & OutFileName) const;
    void ReadFromBinary(string const & InFileName);

private:
    double* _A;
    uint32_t* _IA;
    uint32_t* _JA;
    uint32_t _n;   // NrOfRows
    uint32_t _m;   // NrOfCols
    uint32_t _nnz; // number of non-zero elements


    uint32_t FindIndexA(uint32_t const& i, uint32_t const& j) const;

};

inline MyMatrixCRS operator*(double alpha, MyMatrixCRS const & rhs)
{
    return rhs*alpha;
}



