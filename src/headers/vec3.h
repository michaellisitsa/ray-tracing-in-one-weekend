// VEC3_H gets given to the whole if block
// Any imports of vec3.h will be replaced with the contents of this file
// This is a header guard so this only occurs once
#ifndef VEC3_H
#define VEC3_H

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

    // This is a const member function, so it can't modify the object it's called on
    // i.e. any members of this class.
    vec3 operator-() const
    {
        return vec3(-e[0], -e[1], -e[2]);
    }

    // This is a read-only version of the function.
    // You get a copy of the element at index i.
    // You can't assign to it.
    double operator[](int i) const
    {
        return e[i];
    }

    // This one you can write to
    double &operator[](int i)
    {
        return e[i];
    }

    // const because its taking another vector as an argument
    // and that vector is not being modified in this function
    vec3 &operator+=(const vec3 &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        // Dereference the pointer so you can return the object itself
        return *this;
    }

    vec3 &operator*=(double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    // Division assignment operator.
    vec3 &operator/=(double t)
    {
        return *this *= 1 / t;
    }

    double length() const
    {
        return sqrt(length_squared());
    }

    double length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    // Create a random vector
    static vec3 random()
    {
        return vec3(random_double(), random_double(), random_double());
    }

    static vec3 random(double min, double max)
    {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;

// This version can accept temporary objects, const objects, and non-const objects as its arguments, making it more flexible,
// than having this overload inside the class
inline vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v)
{
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t)
{
    return t * v;
}

inline vec3 operator/(const vec3 &v, double t)
{
    return (1 / t) * v;
}

inline double dot(const vec3 &u, const vec3 &v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3 &v)
{
    return v / v.length();
}

// Generate a random vector within a unit sphere
// which we can use to sample a random direction
// that a diffuse surface bounces the ray.
inline vec3 random_in_unit_sphere()
{
    while (true)
    {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() < 1)
            return p;
    }
}

inline vec3 random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}

inline vec3 random_on_hemisphere(const vec3 &normal)
{
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

// We want to overload ostream so we can print out vec3 objects
// without looping over each parameter
// But does the << do. Is it an append operator the lvalue?
// and does it need a return value just so you can chain it?
// Because this is non-member method, we need 2 params, for self and other
// lvalue: a std::ostream object which is probably the base class of std::cout? A reference to that object
// rvalue: a vec3 object. A const reference because we're not modifying it.
inline void operator<<(std::ostream &out, const vec3 vector)
{
    // << is already overloaded for std::ostream and char* so we can just use it
    out << vector.x() << ' ' << vector.y() << ' ' << vector.z();
}

#endif