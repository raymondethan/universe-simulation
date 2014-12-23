/**
 * @file: Vector.h
 * @author Ethan Raymond
 * @Description: This file declares the Vector class
 * @Honor Code: I pledge my honor that I have neither given nor received
    unauthorized aid on this work.
*/

#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib> // For size_t
#include <iterator>
#include <memory>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include "VectorFunctors.h"

template <size_t T>
class Vector {

public:

    /**
    * @brief Creates an Vector of size T.
    * @details Creates a Vector and initializes the private member
        variable to a double array of size T. The size must be greater
        than 0.
    * @param none
    * @pre integer template size given
    * @post creates a vector of size T
    * @throws exception if invalid size is given
    */
    Vector();

    /**
    * @brief Creates a Vector of Basis size and value.
    * @details creates a Vector and performs a deef copy of
        basis
    * @param double array
    * @pre valid double array given
    * @post a vector of basis size and with the same values is
        created
    * @throws error if invalid basis is given
    */
    Vector(const double basis[]);

    /**
    * @brief copy constructor.
    * @details creates a Vector of the same size and value
        as the given Vector
    * @param a Vector
    * @pre a valid Vector is given
    * @post creates an identical Vector
    * @throws exception if an invalid Vector is given
    */
    Vector(const Vector<T> &rhs) = default;

    /**
    * @brief destructor.
    * @details frees memory used to create the vector
    */
    ~Vector();

    /**
    * @brief assignment operator.
    * @details assigns a Vector to have the same values as the given vector
        by performing a deep copy.
    * @param a Vector
    * @return returns a reference to an identical Vector
    * @pre a valid Vector is given
    * @post an identical Vector is returned
    * @throws an exception in the Vectors have different size.
    */
    const Vector &operator =(const Vector &vec);

    /**
    * @brief prints out the Vector.
    * @details prints out the Vector in a specific format
    * @param none
    * @return a string representing the Vector
    * @post the vector is unchanged
    */
    std::string toString() const;

    /**
    * @brief vector cross product.
    * @details returns a Vector that is the cross product of the
        given Vector and this
    * @param a Vector
    * @return the Vector cross product
    * @pre a valid Vector is given
    * @post the cross product is returned
    * @throws a domain_error is the vectors are not of size 3.
    */
    Vector cross(const Vector &vec) const;

    /**
    * @brief vector dot product.
    * @details returns the dot product of 2 Vectors
    * @param a Vector
    * @return a double
    * @pre a valid Vector is given
    * @post both Vectors are unchanged
    * @throws an exception if the Vectors are of unequal length
    */
    double dot(const Vector &vec) const;

    /**
    * @brief returns the Norm of the Vector.
    * @details returns the size (magnitude/norm) of the Vector
    * @param none
    * @return a doulbe of the Norm
    */
    double norm() const;

    /**
    * @brief normSq function.
    * @details returns the square of the Norm (magnitude) of the Vector
    * @param none
    * @return a double of the norm squared
    */
    double normSq() const;

    /**
    * @brief normSq function.
    * @details returns the squared norm of the given Vector
    * @param a Vector
    * @return the double of the square of the Norm
    * @pre a valid Vector is given
    * @post the Vector remains unchanged
    */
    double normSq(Vector<T> vec) const;

    /**
    * @brief normalize function.
    * @details returns the Vector
        divided by the Norm of the Vector
    * @param none
    * @return a new Vector
    * @pre the Vector's norm is not 0
    * @post the orignal Vector's values are divided by the Norm
    * @throws an exception if the Norm is 0
    */
    Vector &normalize();

    /**
    * @brief non constant subscript operator.
    * @details returns the value of the Vector at the given index
    * @param a size_t index
    * @return the double value at the given index
    * @pre the Vector is valid
    * @post the value is returned
    */
    double &operator [](size_t index);

    /**
    * @brief constant subscript operator.
    * @details returns the value of the Vector at the given index
    * @param a size_t index
    * @return the double value at the given index
    * @pre the Vector is valid
    * @post the Vector is unchanged
    */
    const double &operator [](size_t index) const;

    /**
    * @brief equality operator.
    * @details returns true if two Vectors are equal,
        false if not
    * @param a Vector
    * @return boolean value
    * @pre the Vectors are of equal length
    * @post the Vectors are unchanged
    * @throws
    */
    bool operator ==(const Vector &vec) const;

    /**
    * @brief inequality operator.
    * @details returns false if two Vectors are unequal,
        true if not
    * @param a Vector
    * @return boolean value
    * @pre the Vectors are of equal length
    * @post the Vectors are unchanged
    */
    bool operator !=(const Vector &vec) const;

    /**
    * @brief Vector addition operator.
    * @details returns a Vector that is the sum of the given
        Vector and the *this Vector
    * @param a Vector
    * @return a Vector
    * @pre the Vectors have equal size
    * @post both Vectors are unchanged
    */
    const Vector operator +(const Vector vec) const;

    /**
    * @brief unary minus operator.
    * @details returns a Vector with all it's values negated
    * @param none
    * @return a Vector
    * @pre the Vectors have equal size
    * @post the original Vector is unchanged
    */
    Vector operator -() const;

    /**
    * @brief vector += operator.
    * @details returns a reference to the original Vector after
        it has been added with the given Vector
    * @param a Vector
    * @return a Vector
    * @pre the Vectors have equal size
    * @post this Vector's values are changed
    */
    const Vector &operator +=(const Vector &vec);

    /**
    * @brief Vector subtraction operator.
    * @details returns a Vector with its values equal to the
        difference between the values in the original and given Vectors
    * @param a Vector
    * @return a Vector
    * @pre the Vectors have equal size
    * @post both Vectors are unchanged
    */
    Vector operator -(const Vector vec) const;

    /**
    * @brief -= operator.
    * @details returns a reference to the original Vector with its values
        equal to the difference between the values in the original
        and given Vectors
    * @param a Vector
    * @return a Vector
    * @pre the Vectors have equal size
    * @post the given Vector is unchanged
    */
    Vector &operator -=(const Vector &vec);

    /**
    * @brief scalar multiplication operator.
    * @details multiplies each member of the Vector by the scalar
    * @param a double scalar
    * @return a Vector
    * @pre the Vector is valid
    * @post the original Vector is unchanged
    */
    const Vector operator *(double scalar) const;

    /**
    * @brief vector multiplication operator.
    * @details computs the dot product of the two Vectors
    * @param a Vector
    * @return a double
    * @pre the Vectors are the same size
    * @post both Vectors remain unchanged
    */
    double operator *(const Vector &vec) const;

    /**
    * @brief vector cross product operator.
    * @details computes the cross product of the two Vectors
    * @param a Vector
    * @return a double
    * @pre a valid Vector is given
    * @post both Vectors are unchanged
    * @throws an exception if the Vectors are of unequal length
    */
    Vector operator ^(const Vector &vec) const;

    /**
    * @brief *= operator.
    * @details multiplies the Vector by a scalar
        and updates its values
    * @param a double
    * @return a Vector
    * @pre the Vector is valid
    * @post the Vector's values have been multiplied
    */
    Vector &operator *=(double scalar);

    /**
    * @brief scalar division operator.
    * @details divides every value in the Vector by the scalar
    * @param a double
    * @return a Vector
    * @pre the Vector is valid
    * @post the Vector remains unchanged
    */
    Vector operator /(double scalar) const;

    /**
    * @brief /= operator.
    * @details updates the Vectors values by
        dividing every value in the Vector by the scalar
    * @param a double
    * @return a Vector
    * @pre the Vector is valid
    * @post the Vector remains unchanged
    */
    Vector &operator /=(double scalar);


private:

    /*
     *Private member variable ArrayList
     */
    double vector[T];

};

/**
* @brief commutative scalar multiplication operator.
* @details multiplies each member of the Vector by the scalar
* @param a double scalar
* @return a Vector
* @pre the Vector is valid
* @post the original Vector is unchanged
*/
template <size_t T>
Vector<T> operator *(double scalar, const Vector<T> &vec) {
    Vector<T> tmp(vec);
    tmp = vec * scalar;
    return tmp;
}

#include "Vector.tpp"

typedef Vector<2> vector2;

#endif