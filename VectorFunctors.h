/**
 * @file: VectorFunctors.h
 * @author Ethan Raymond
 * @Description: This file implements the functors used in the Vector class
 * @Honor Code: I pledge my honor that I have neither given nor received
    unauthorized aid on this work.
*/

/*
* @brief functor that can multiply a given value by a scalar or
    the product of 2 given values
*/
struct multiply_x {
    multiply_x(double num) : scalar(num) {}
    multiply_x() : scalar(1) {}
    double operator()(double x, double y) {return x * y;}
    void operator()(double &x) {x = x * scalar;}
private:
    double scalar;
};

/*
* @brief negates the given value, passed by reference
*/
struct negate_x {
    void operator()(double &x) {x = -x;}
};

/*
* @brief returns the difference between 2 given values
*/
struct subtract_x {
    double operator()(double x, double y) {return x-y;}
};

/*
* @brief returns the sum of two given values or adds the given
    value to a sum
*/
struct add_x {
    add_x() : sum(0) {}
    double operator()(double x, double y) {return x + y;}
    void operator()(double x) {sum += x;}
    double get() {return sum;}
private:
    double sum;
};

/*
* @brief finds the square of the norm of a Vector,
    can return the square of the norm and the norm
*/
struct norm_x {
    norm_x() : sum(0) {}
    void operator()(double num) {sum += num * num;}
    double getNorm() {return sqrt(sum);}
    double getNormSq() {return sum;}
private:
    double sum;
};