/**
* @file: Vector.cpp
* @author Ethan Raymond
* @Description: This file imlements the Vector class
* @Honor Code: I pledge my honor that I have neither given nor received
unauthorized aid on this work.
*/

/**
* @brief Creates an Vector of size T.
*/
template <size_t T>
Vector<T>::Vector() {
    static_assert(T > 0, "Size must be greater than 0");
    std::fill(std::begin(vector), std::end(vector), 0);
}

/**
* @brief Creates a Vector of Basis size and value.
*/
template <size_t T>
Vector<T>::Vector(const double basis[]) {
    std::copy(basis, basis + T, std::begin(vector));
}

/**
* @brief destructor.
*/
template <size_t T>
Vector<T>::~Vector() {}

/**
* @brief assignment operator.
*/
template <size_t T>
const Vector<T> &Vector<T>::operator =(const Vector<T> &vec) {
    std::copy(std::begin(vec.vector), std::end(vec.vector), std::begin(vector));
    return *this;
}

/**
* @brief prints out the Vector.
*/
template <size_t T>
std::string Vector<T>::toString() const {
    std::stringstream ss;
    ss << "[" << vector[0];
    std::for_each(std::begin(vector) + 1, std::end(vector),
        [&](double num){ss << " " << num;});
    ss << "]";
    return ss.str();
}

/**
* @brief vector cross product.
*/
template <size_t T>
Vector<T> Vector<T>::cross(const Vector<T> &vec) const {
    throw std::domain_error("Operation not supported");
}

/**
* @brief vector cross product.
*/
template <>
inline Vector<3> Vector<3>::cross(const Vector<3> &vec) const {
    Vector<3> tmp(*this);
    tmp[0] = vector[1] * vec.vector[2] - vector[2]* vec.vector[1];
    tmp[1] = vector[2] * vec.vector[0] - vector[0] * vec.vector[2];
    tmp[2] = vector[0] * vec.vector[1] - vector[1] * vec.vector[0];
    return tmp;
}

/**
* @brief vector dot product.
*/
template <size_t T>
double Vector<T>::dot(const Vector<T> &vec) const {
    Vector<T> tmp;
    multiply_x mult;
    add_x add;
    std::transform(std::begin(vector), std::end(vector),
                    std::begin(vec.vector), std::begin(tmp.vector), mult);
    add = std::for_each(std::begin(tmp.vector), std::end(tmp.vector), add);
    return add.get();
}

/**
* @brief creates the Normal Vector.
*/
template <size_t T>
double Vector<T>::norm() const {
    norm_x norm;
    norm = std::for_each(std::begin(vector), std::end(vector), norm);
    return norm.getNorm();
}

/**
* @brief normSq function.
*/
template <size_t T>
double Vector<T>::normSq() const {
    norm_x norm;
    norm = std::for_each(std::begin(vector), std::end(vector), norm);
    return norm.getNormSq();
}

/**
* @brief normSq function.
*/
template <size_t T>
double Vector<T>::normSq(Vector<T> vec) const {
    return vec.normSq();
}

/**
* @brief normalize function.
*/
template <size_t T>
Vector<T> &Vector<T>::normalize() {
    *this = *this / norm();
    return *this;
}

/**
* @brief subscript operator.
*/
template <size_t T>
double &Vector<T>::operator [](size_t index) {
    return vector[index];
}

/**
* @brief constant subscript operator.
*/
template <size_t T>
const double &Vector<T>::operator [](size_t index) const {
    return vector[index];
}

/**
* @brief equality operator.
*/
template <size_t T>
bool Vector<T>::operator ==(const Vector<T> &vec) const {
    return std::equal(std::begin(vector), std::end(vector),
        std::begin(vec.vector));
}

/**
* @brief inequality operator.
*/
template <size_t T>
bool Vector<T>::operator !=(const Vector<T> &vec) const {
    return !(*this == vec);
}

/**
* @brief Vector addition operator.
*/
template <size_t T>
const Vector<T> Vector<T>::operator +(const Vector<T> vec) const {
    Vector<T> tmp(*this);
    add_x add;
    std::transform(std::begin(vector), std::end(vector),
                    std::begin(vec.vector), std::begin(tmp.vector), add);
    return tmp;
}

/**
* @brief unary minus operator.
*/
template <size_t T>
Vector<T> Vector<T>::operator -() const {
    Vector<T> tmp(*this);
    negate_x negate;
    std::for_each(std::begin(tmp.vector), std::end(tmp.vector), negate);
    return tmp;
}

/**
* @brief vector += operator.
*/
template <size_t T>
const Vector<T> &Vector<T>::operator +=(const Vector<T> &vec) {
    *this = *this + vec;
    return *this;
}

/**
* @brief vector subtraction operator.
*/
template <size_t T>
Vector<T> Vector<T>::operator -(const Vector<T> vec) const {
    Vector<T> tmp(*this);
    subtract_x sub;
    std::transform(std::begin(vector), std::end(vector),
        std::begin(vec.vector), std::begin(tmp.vector), sub);
    return tmp;
}

/**
* @brief -= operator.
*/
template <size_t T>
Vector<T> &Vector<T>::operator -=(const Vector<T> &vec) {
    *this = *this - vec;
    return *this;
}

/**
* @brief scalar multiplication operator.
*/
template <size_t T>
const Vector<T> Vector<T>::operator *(double scalar) const {
    Vector<T> tmp(*this);
    multiply_x mult(scalar);
    std::for_each(std::begin(tmp.vector), std::end(tmp.vector), mult);
    return tmp;
}

/**
* @brief vector multiplication operator.
*/
template <size_t T>
double Vector<T>::operator *(const Vector<T> &vec) const {
    return dot(vec);
}

/**
* @brief vector cross product operator.
*/
template <size_t T>
Vector<T> Vector<T>::operator ^(const Vector<T> &vec) const {
    return cross(vec);
}

/**
* @brief *= operator.
*/
template <size_t T>
Vector<T> &Vector<T>::operator *=(double scalar) {
    *this = *this * scalar;
    return *this;
}

/**
* @brief scalar division operator.
*/
template <size_t T>
Vector<T> Vector<T>::operator /(double scalar) const {
    Vector<T> tmp(*this);
    if (scalar != 0) {
        return tmp * (1 / scalar);
    }
    return tmp;
}

/**
* @brief /= operator.
*/
template <size_t T>
Vector<T> &Vector<T>::operator /=(double scalar) {
    *this = *this / scalar;
    return *this;
}
