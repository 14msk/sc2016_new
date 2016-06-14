#ifndef MYMATRIX_HPP_INCLUDED
#define MYMATRIX_HPP_INCLUDED

#include "myvector.h"

class MyMatrix : protected MyVector {
public:
    //! \brief Allocates a vector with n times m elements on the heap.
    //!
    //! \param[in] n number of rows
    //! \param[in] m vector columns
    //!
    MyMatrix(const long long int n = 0, const long long int m = 0);

    //! \brief Allocates a vector with n times m elements on the heap and initializes it with @p v
    //!
    //! \param[in] n number of rows
    //! \param[in] m vector columns
    //!
    MyMatrix(const long long int n, const long long int m, const MyVector& v);

    //! \brief Allocates a matrix with the same elements as matrix @p orig and copies its elements.
    //!
    //! \param[in] orig original matrix
    //! \warning Throws an exception in case of insufficient memory.
    //!
    MyMatrix(const MyMatrix& orig);

    //! \brief Allocates a matrix with the same elements as matrix @p other and copies its elements.
    //!
    //! \param[in] other original matrix
    //! \warning Throws an exception in case of insufficient memory.
    //!
    MyMatrix& operator=(const MyMatrix& other );

    //! \brief returns the value in the r-th row and nth column of the matrix (indices starting at 1 !!!)
    //!
    //! \param[in] r row index
    //! \param[in] c column index
    const double& at(int r,int c) const;

    //! \brief adds another matrix to a matrix
    //!
    //! \param[in]  rhs matrix that is added to the current instance
    //!
    MyMatrix operator+=(const MyMatrix& rhs  );

    //! \brief subtracts a matrix from another matrix
    //!
    //! \param[in]  rhs matrix that is subtracted from the current instance
    //!
    MyMatrix operator-=(const MyMatrix& rhs  );

    //! \brief addition of two matrices
    //!
    //! \param[in]  rhs matrix that is added to the other one
    //!
    const MyMatrix operator+(const MyMatrix& rhs  ) const;

    //! \brief subtracts a matrix from another matrix
    //!
    //! \param[in]  rhs matrix that is subtracted from the current instance
    //!
    const MyMatrix operator-(const MyMatrix& rhs  ) const;

    //! \brief Output of the matrix @p orig.
    //!
    //! \param[in] s     output stream
    //! \param[in] orig  matrix
    //!
    friend std::ostream & operator<<(std::ostream & s, const MyMatrix& orig);

    //! \brief matrix-vector multiplication
    //!
    //! \param[in] lhs  matrix
    //! \param[in] rhs  vector with which @lhs is multiplied
    //!
    friend MyVector operator*(const MyMatrix& lhs ,const MyVector& rhs);

    //! \brief matrix-multiplication
    //!
    //! \param[in] rhs  matrix with which the current instance is multiplied (from the right side)
    //! \return y matrix product
    //!
    MyMatrix operator*(const MyMatrix& rhs);

    //! \brief Returns the number of elements.
    //!
    //! \return Number of elements
    //!
    long long int size() const {
        return rows_*columns_;
    }

    const double& operator()(const long long int r,const long long int c) {
        return mval_[(r-1)*columns_ + (c-1)];
    }

protected:
    long long int      rows_;     //!< number of elements
    long long int      columns_;     //!< number of elements
    MyVector mval_;                  //!< pointer to allocated memory
};



#endif // MYMATRIX_HPP_INCLUDED
