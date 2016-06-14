#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED
#include "myvector.h"

class Matrix : public MyVector {
public:
    //! \brief Allocates @p n vectors with @p m elements on the heap.
    //!
    //! \param[in] n number of vectors
    //! \param[in] m vector length
    //!
    Matrix(const long long int n = 0,const long long int m = 0);

    //! \brief Allocates @p n vectors with @p m elements on the heap and initializes them with the vectors in @p ilist
    //!
    //! \param[in] n number of vectors
    //! \param[in] m vector length
    //! \param[in] ilist initializer_list with n vectors vector length
    //!
    Matrix(const long long int n,const long long int m,initializer_list<MyVector> ilist);


    //! \brief Allocates a matrix with the same elements as matrix @p orig and copies its elements.
    //!
    //! \param[in] orig original matrix
    //! \warning Throws an exception in case of insufficient memory.
    //!
    Matrix(const Matrix& orig);

   //! \brief Deallocates the heap memory.
    //!
    virtual ~Matrix();

    //! \brief Allocates a matrix with the same elements as matrix @p other and copies its elements.
    //!
    //! \param[in] other original matrix
    //! \warning Throws an exception in case of insufficient memory.
    //!
    Matrix& operator=(const Matrix& other );

    //! \brief adds another matrix to a matrix
    //!
    //! \param[in]  rhs matrix that is added to the current instance
    //!
    Matrix operator+=(const Matrix& rhs  );

    //! \brief subtracts another matrix from a matrix
    //!
    //! \param[in]  rhs matrix that is subtracted from the current instance
    //!
    Matrix operator-=(const Matrix& rhs  );

    //! \brief addition of two matrices
    //!
    //! \param[in]  rhs matrix that is added to the other one
    //!
    const Matrix operator+(const Matrix& rhs  ) const;

    //! \brief subtracts a matrix from another matrix
    //!
    //! \param[in]  rhs matrix that is subtracted from the current instance
    //!
    const Matrix operator-(const Matrix& rhs  ) const;


    //! \brief Output of the matrix @p orig.
    //!
    //! \param[in] s     output stream
    //! \param[in] orig  matrix
    //! \warning Throws an exception in case of insufficient memory.
    //!
    friend std::ostream & operator<<(std::ostream & s, const Matrix& orig);

    //! \brief matrix-vector multiplication
    //!
    //! \param[in] lhs  matrix
    //! \param[in] rhs  vector with which @lhs is multiplied
    //! \return y lhs*rhs
    //!
    friend MyVector operator*(const Matrix& lhs, const MyVector& rhs);

    //! \brief matrix-multiplication
    //!
    //! \param[in] rhs matrix with which the current instance is multiplied (from the right side)
    //! \return y matrix product
    //!
    Matrix operator*(const Matrix& rhs);

    //! \brief Returns the value of element @p i.
    //!
    //! \param[in] i     index
    //! \return          value
    //!
    const MyVector& operator[](const long long int i) const {
        return mval_[i];
    }

    //! \brief solves a system of linear equations @p A * x = @p b until either an accuracy of @p tol is reached or the number of iterations exceeds @p max_iter
    //!
    //! \param[in] A matrix
    //! \param[in] b vector
    //! \param[in] tol desired accuracy
    //! \param[in] max_iter maximal number of iterations allowed
    //! \return x solution vector
    //!
    friend MyVector jacobi(const Matrix& A, const MyVector& b, const double& tol, const long long int max_iter=1000);

protected:
    long long int      rows_;     //!< number of elements
    long long int      columns_;     //!< number of elements
    MyVector * mval_;                  //!< pointer to allocated memory
};

#endif // MATRIX_HPP_INCLUDED

//MyVector jacobi(const Matrix& A, const MyVector& b, const double& tol, const long long int max_iter = 1000);
