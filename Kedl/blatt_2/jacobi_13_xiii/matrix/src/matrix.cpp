#include "../inc/matrix.hpp"
#include <iomanip>
#include <math.h>


using namespace std;

Matrix:: Matrix(const long long int n,const long long int m)
    : rows_( n>0 ? n : 0), columns_( m>0 ? m : 0), mval_(0) {

    if ( rows_>0 ) {
        mval_   = new  MyVector [rows_];
        for (long long int i = 0; i<n; i++) {
            mval_[i] = MyVector(m);
        }
    }
}

Matrix ::Matrix(const long long int n,const long long int m,initializer_list<MyVector> ilist)
    : Matrix(n,m) {
    long long int i = 0;
    for ( auto it=begin(ilist); it!=end(ilist); ++it) {
        mval_[i] = *it;
        i++;
    }
}

Matrix :: Matrix(const Matrix& orig)
    : rows_(orig.rows_),columns_(orig.columns_), mval_(new MyVector[orig.columns_]) {
    for (long long int i = 0; i < orig.rows_; i++) {
        mval_[i] = orig.mval_[i];
    }
}

Matrix :: ~Matrix() {			// Destruktor
    delete [] mval_;
}

Matrix& Matrix::operator=( const Matrix& other ) {
    if (this != &other) {
        delete [] mval_;
        mval_ =  new MyVector[other.rows_];
        for (long long int i = 0; i < other.rows_; i++) {
            mval_[i] = other.mval_[i];
        }
        rows_ = other.rows_;
        columns_ = other.columns_;
    }
    return *this;
}

const Matrix Matrix::operator+(const Matrix& rhs  ) const {
    Matrix tmp(rhs.rows_);
    if(rows_ == rhs.rows_ && columns_ == rhs.columns_) {
        for (long long int i = 0; i<rows_; i++) {
            tmp.mval_[i] = mval_[i] + rhs.mval_[i];
        }
    } else {
        cout << "Dimensionen stimmen nicht überein!" << endl;
    }
    return tmp;
}

const Matrix Matrix::operator-(const Matrix& rhs  ) const {
    Matrix tmp(rhs.rows_);
    if(rows_ == rhs.rows_ && columns_ == rhs.columns_) {
        for (long long int i = 0; i<rows_; i++) {
            tmp.mval_[i] = mval_[i] - rhs.mval_[i];
        }
    } else {
        cout << "Dimensionen stimmen nicht überein!" << endl;
    }
    return tmp;
}


Matrix Matrix::operator+=(const Matrix& rhs  ) {
    Matrix tmp = *this;
    if(rows_ == rhs.rows_ && columns_ == rhs.columns_) {
        for (long long int i = 0; i<rows_; i++) {
            tmp.mval_[i] = mval_[i] + rhs.mval_[i];
        }
    } else {
        cout << "Dimensionen stimmen nicht überein!" << endl;
    }
    return tmp;
}

Matrix Matrix::operator-=(const Matrix& rhs  ) {

    Matrix tmp = *this;
    if(rows_ == rhs.rows_ && columns_ == rhs.columns_) {

        for (long long int i = 0; i<rows_; i++) {
            tmp.mval_[i] = mval_[i] - rhs.mval_[i];
        }

    } else {
        cout << "Dimensionen stimmen nicht überein!" << endl;
    }

    return tmp;
}

MyVector operator*(const Matrix& lhs ,const MyVector& rhs) {
    MyVector y = MyVector(lhs.rows_);
    if (lhs.columns_ == rhs.size()) {
        for(long long int i = 0; i < lhs.rows_; i++) {
            for(long long int j = 0; j < lhs.columns_; j++) {
                y[i] +=  rhs[j] *lhs[i][j];
            }
        }
    } else {
        cout << "Dimensionen stimmen nicht überein!" << endl;
    }
    return y;
}

ostream & operator<<(ostream & s, const Matrix& orig) {
    //cout << "ROWS: " << orig.rows_ << " COLUMNS: " << orig.columns_ << endl;
    for(long long int i = 0; i < orig.rows_; i++) {
        s << orig.mval_[i] << "  ";

        s << endl;
    }

    return s;
}

Matrix Matrix::operator*(const Matrix& rhs) {
    Matrix lhs = *this;
    auto n=rows_;
    auto m = columns_;
    auto p = rhs.columns_;
    Matrix y (n,p);
    if (m == rhs.rows_) {
        for(long long int i = 0; i < n; i++) {
            for(long long int j = 0; j < p; j++) {
                y.mval_[i][j]=0;
                for(long long int k = 0; k < m; k++) {
                    y.mval_[i][j] +=  mval_[i][k]*rhs.mval_[k][j] ;
                }
            }
        }
    } else {
        cout << "Matrix-Multiplikation nicht möglich - Dimensionen stimmen nicht überein!" << endl;
    }
    return y;
}

MyVector jacobi(const Matrix& A, const MyVector& b, const double& tol, const long long int max_iter) {
    double merr = 10;
    long long int n = b.size();
    double s = 0;
    int m = 0;
    MyVector x_old(n);
    MyVector x(n);
    MyVector err(n);

    for(int k=0; k < n; k++) {
        cout << A [k];
        cout << setw(5);
        cout << " | " << b[k] << endl;
    }

    do {
        for (long long int i = 0; i < n; i++) {
            s = 0;

            for(long long int j = 0; j<n; j++) {
                if(!(j == i)) {
                    s += A[i][j]*x_old[j];
                }
            }
            x[i] =  (b[i] - s)/(A[i][i]);
        }

        err = x_old - x;
        merr = err.max();
        x_old =  x;
        m++;
    }while(merr > tol && m < max_iter);
    cout <<"\nApproximierte Loesung: " << x << endl;
    cout <<"Anzahl der Iterationen:    " << m+1 << endl;
    cout <<"Abweichung:                " << merr << endl << endl;
    return x;
}
