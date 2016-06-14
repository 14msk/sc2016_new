#ifndef FILE_MYVECTOR
#define FILE_MYVECTOR

#include <iostream>
#include <initializer_list>
#include "myexceptions.h"		// Exeption handlers and classes

using namespace std;
//! \brief My own vector class.
//!
//!   The macro DEBUG switches the range check on/off.
//!
class MyVector
{
public:
    //! \brief Allocates a vector with @p n elements on the heap.
    //!
    //! \param[in] n vector length
    //! \warning Throws an exception in case of insufficient memory on the heap.
    //!
    MyVector(const long long int n = 0);


    //! \brief Allocates a vector with the same elements as @p ilist
    //!
    //! \param[in] ilist initializer list with vector entries
    //! \warning Throws an exception in case of insufficient memory.
    //!
    MyVector( initializer_list<double> ilist);

    //! \brief Allocates a vector with the same elements as vector @p orig and copies its elements.
    //!
    //! \param[in] orig original vector
    //! \warning Throws an exception in case of insufficient memory.
    //!
    MyVector(const MyVector& orig);

    //! \brief Reallocates the vector with the same elements as vector @p other and copies its elements.
    //!
    //! \param[in] other original vector
    //! \warning Throws an exception in case of insufficient memory.
    //!
    MyVector& operator=(const MyVector& other );

    //! \brief each element in the vector is multiplied by @n
    //!
    //! \param[in] n value by which vector elements are multiplied
    //!
    MyVector operator*(const double &n);

    //const double& Get (long long int n) const;

    //! \brief adds another vector to a vector
    //!
    //! \param[in]  rhs vector that is added to the current instance
    //!
    MyVector operator+=(const MyVector& rhs  );

    //! \brief addition of two vectors
    //!
    //! \param[in]  rhs vector that is added to the other one
    //!
    const MyVector operator+(const MyVector& rhs  ) const;
    const MyVector operator-(const MyVector& rhs  ) const;

    //! \brief appends value @a to a vector, increasing its length by 1
    //!
    //! \param[in]  a value that is appended to the vector
    //!
    void push_back( const double& a ) ;

   //! \brief Deallocates the heap memory.
    //!
    virtual ~MyVector();



    //! \brief Output of the vector @p orig.
    //!
    //! \param[in] s     output stream
    //! \param[in] orig  vector
    //! \warning Throws an exception in case of insufficient memory.
    //!
    friend std::ostream & operator<<(std::ostream & s, const MyVector& orig);

    //! \brief Returns the number of elements.
    //!
    //! \return Number of elements
    //!
    const long long int& size() const
    {
        return length_;
    }

    //! \brief Returns the value of element @p i.
    //!
    //! \param[in] i     index
    //! \return          value
    //! \warning Throws an exception "OutOfRange" in case an invalid index @p i.
    //!
    double& operator[](const long long int i)
    {
#ifndef NDEBUG
#pragma message(" ##########  Debug mode  ###############")
        IndexCheck(i);
#endif
        return val_[i];
    }

    //! \brief Returns the value of element @p i.
    //!
    //! \param[in] i     index
    //! \return          value
    //! \warning Throws an exception "OutOfRange" in case an invalid index @p i.
    //!
 const double& operator[](const long long int i) const		// const notw. fuer const. Instanzen von MyVektor
    {
#ifndef NDEBUG
#pragma message(" ##########  Debug mode  ###############")
        IndexCheck(i);
#endif
        return val_[i];
    }


private:
    //! \brief Checks whether @p i is an valid index, i.e.,@f$ i \in [0, length_ -1]@f$ .
    //!
    //! \param[in] i     index
    //! \warning Throws an exception "OutOfRange" in case of an invalid index @p i.
    //!
    void IndexCheck(const long long int &i) const
    {
        if ( i<0 || i>=size() )
            throw OutOfRange(i,size()-1);
    }

protected:
    long long int      length_;     //!< number of elements
    double * val_;                  //!< pointer to allocated memory
};

#endif


