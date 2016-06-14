#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <new>
#include <cassert>
#include <iomanip>

#include "../inc/myvector.h"

using namespace std;

MyVector :: MyVector(const long long int n )
    : length_( n>0 ? n : 0), val_(0) {
    if ( length_>0 ) {
        val_    = new double [length_];
        for (long long int i = 0; i < n; i++) {
            val_[i] = 0;
        }
    }
}

MyVector :: MyVector(initializer_list<double> ilist)	// Standard-, Parameterkonstruktor
    : MyVector(ilist.size()) {
    long long int i = 0;
    for ( auto it=begin(ilist); it!=end(ilist); ++it) {
        val_[i] = *it;
        i++;
    }
}

MyVector :: MyVector(const MyVector& orig)	// Copy constructor
    : length_(orig.length_), val_(new double[orig.length_]) {
    copy(orig.val_, orig.val_ + orig.length_, val_);

}

MyVector :: ~MyVector() {			// Destruktor
    delete [] val_;
}

MyVector& MyVector::operator=( const MyVector& other ) {
    if (this != &other) {
        delete [] val_;
        val_ =  new double[other.length_];
        copy(other.val_, other.val_ + other.length_, val_);
        length_ = other.length_;
    }
    return *this;
}


void MyVector::push_back( const double& a ) {
    MyVector tmp;
    tmp = MyVector(length_ + 1);
    copy(val_,val_+length_,tmp.val_);
    tmp.val_[length_] = a;

    delete [] val_;
    val_ =  new double[tmp.length_];
    copy(tmp.val_, tmp.val_ + tmp.length_, val_);
    length_ = tmp.length_;

    return;
}



MyVector MyVector::operator*(const double& n ) {


    for (long long int i=0; i<length_; i++)   val_[i] = n*val_[i];
    return *this;
}



MyVector MyVector::operator+=(const MyVector& rhs  ) {

    for (long long int i=0; i<length_; i++)   val_[i] = val_[i]+rhs.val_[i];
    return *this;
}

const MyVector MyVector::operator+(const MyVector& rhs  ) const {
    MyVector tmp(rhs.length_);
    for (long long int i=0; i<length_; i++)   tmp.val_[i] = val_[i] + rhs.val_[i];
    return tmp;
}

const MyVector MyVector::operator-(const MyVector& rhs  ) const {
    MyVector tmp(rhs.length_);
    for (long long int i=0; i<length_; i++)   tmp.val_[i] = val_[i] - rhs.val_[i];
    return tmp;
}

ostream & operator<<(ostream & s, const MyVector& orig) {
    long long int i;
    for (i=0; i<orig.size(); i++) {
        s << setw(5);
        s << orig[i]<< "  ";
    }

    return s;
}

