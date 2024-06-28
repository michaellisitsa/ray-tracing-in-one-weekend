// VEC3_H gets given to the whole if block
// Any imports of vec3.h will be replaced with the contents of this file
// This is a header guard so this only occurs once
#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3
{
    // This class needs to store 3 values for x y and z
    // It also needs to be able to do some basic math operations
    // Use an initializer list to set the values of x y and z
    // This initializer is public
    // Do I store the 3 values as an array, or as 3 separate variables?
public:
    double e[3];

    vec3() : e{0, 0, 0} {}

    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    // Operator overloads to make it easier to work with vec3 objects
    // Note: find parallels in other languages
    // What should + mean in the context of vectors.
    // I guess it adds the vectors elementwise to create a result vector
    // Do operator overloads define a type, or is that implied from the individual elements?
    // I think it's implied from the individual elements
};

inline vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
#endif