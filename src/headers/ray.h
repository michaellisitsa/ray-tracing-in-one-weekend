#ifndef RAY_H
#define RAY_H

#include "vec3.h"

// The ray should be representing equation P(t) = A + tb
// where P is a 3D position along a line in 3D
// A is a 3d point, and b is a 3d vector
// A point is just an alias for a vec3 from the vec3.h file
// The ray's length is undetermined unless supplied with t.
// The ray should have a direction, which is a unit vector.
// The ray should have an origin, which points to its point, but that point should be private.
// The ray should have a method to get the point at a certain t value. ray::at(t)
// The ray may be constructed using an origin and a direction
class ray
{
public:
    // Since vec3 has a default constructor that sets it to the origin
    // we don't need to explicitly set these.
    ray() {}

    // We're passing these vectors in by reference, but then copying them in the initializer list
    // This means there's not an additional copy when the constructor is called
    // but that the ray class is easier to reason about that it's not modifying the original vectors
    // The ray object is self-constained and doesn't depend on the lifetime of the objects outside its scope.
    ray(const point3 &origin, const vec3 &direction) : orig(origin), dir(direction) {}

    // We return an immutable reference to the origin and direction
    // so that the user can't modify it directly
    const point3 &origin() const { return orig; }
    const vec3 &direction() const { return dir; }

    point3 at(double t) const
    {
        // Using operator overloads to make the vector math equations more readable
        return orig + t * dir;
    }

private:
    point3 orig;
    vec3 dir;
};
#endif