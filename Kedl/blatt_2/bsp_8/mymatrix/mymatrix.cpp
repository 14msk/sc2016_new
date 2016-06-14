#include "mymatrix.hpp"

using namespace std;

MyMatrix:: MyMatrix(const long long int n, const long long int m)
    : rows_( n>0 ? n : 0), columns_( m>0 ? m : 0), mval_(0) {
    mval_  = MyVector(m*n);
}

MyMatrix :: MyMatrix(const long long int n, const long long int m, const MyVector& v)
    : MyMatrix(n,m) {
    for (long long int i = 0; i < n*m; ++i) {
        mval_[i] = v[i];
    }
}

MyMatrix::MyMatrix(const MyMatrix& orig)
    : rows_(orig.rows_),columns_(orig.columns_), mval_(MyVector(orig.mval_)) {
}

MyMatrix& MyMatrix::operator=( const MyMatrix& other ) {
    if (this != &other) {
        mval_ =  MyVector(other.mval_);
        rows_ = other.rows_;
        columns_ = other.columns_;
    }
    return *this;
}

const MyMatrix MyMatrix::operator+(const MyMatrix& rhs  ) const {
    MyMatrix tmp = *this;
    if(rows_ == rhs.rows_ && columns_ == rhs.columns_) {
        tmp.mval_ = mval_ + rhs.mval_;
    } else {
        cout << "Dimensionen stimmen nicht überein!" << endl;
    }
    return tmp;
}

const MyMatrix MyMatrix::operator-(const MyMatrix& rhs  ) const {
    MyMatrix tmp = *this;

    if(rows_ == rhs.rows_ && columns_ == rhs.columns_) {
        tmp.mval_ = mval_ - rhs.mval_;
    } else {
        cout << "Dimensionen stimmen nicht überein!" << endl;
    }

    return tmp;
}

MyMatrix MyMatrix::operator+=(const MyMatrix& rhs  ) {

    MyMatrix tmp = *this;
    if(rows_ == rhs.rows_ && columns_ == rhs.columns_) {

        tmp.mval_ = mval_ + rhs.mval_;

    } else {
        cout << "Dimensionen stimmen nicht überein!" << endl;
    }
    return tmp;
}

MyMatrix MyMatrix::operator-=(const MyMatrix& rhs  ) {
    MyMatrix tmp = *this;
    if(rows_ == rhs.rows_ && columns_ == rhs.columns_) {

        mval_ = mval_ - rhs.mval_;
    } else {
        cout << "Dimensionen stimmen nicht überein!" << endl;
    }

    return tmp;
}

const double& MyMatrix::at(int r,int c) const {
    return mval_[ (r-1)*columns_ + (c-1) ];
}

MyVector operator*(const MyMatrix& lhs ,const MyVector& rhs) {
    MyVector y = MyVector(lhs.rows_);
    if (lhs.columns_ == rhs.size()) {
        for(long long int i = 1; i <= lhs.rows_; i++) {
            for(long long int j = 1; j <= lhs.columns_; j++) {
                y[i-1] +=  rhs[j-1] *lhs.at(i,j);
            }
        }
    } else {
        cout << "Matrix-Vektor-Multiplikation nicht möglich  Dimensionen stimmen nicht überein!" << endl;
    }
    return y;
}

ostream & operator<<(ostream & s, const MyMatrix& orig) {
    long long int i,j;
    for(i = 1; i <= orig.rows_; i++) {
        for(j = 1; j <= orig.columns_; j++) {
            s << orig.at(i,j) << "  ";

        }
        s << endl;
    }

    return s;
}

MyMatrix MyMatrix::operator*(const MyMatrix& rhs) {
    MyMatrix lhs = *this;
    auto n=lhs.rows_;
    auto m = lhs.columns_;
    auto p = rhs.columns_;
    MyMatrix y = MyMatrix(n,p);
    if (m == rhs.rows_) {
        for(long long int i = 1; i <= n; i++) {
            for(long long int j = 1; j <= p; j++) {
                y.mval_[(i-1)*(p) + (j-1)]=0;
                for(long long int k = 1; k <= m; k++) {
                    y.mval_[(i-1)*(p) + (j-1)] +=  lhs.at(i,k)*rhs.at(k,j) ;
                }
            }
        }
    }

    else {
        cout << "Dimensionen stimmen nicht überein!" << endl;
    }
    return y;
}

