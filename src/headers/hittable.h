#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

// Since we're going to recursively shoot rays when calculating the shade of a pixel
// we need to record when a hit has occurred
struct hit_record
{
    // The point where the ray hits the object
    // Normal vector at the point it hit
    point3 p;
    vec3 normal;
    double t;
};

class hittable
{
    // An abstract class that represents a hittable object
    // Must implement a hit method that takes a ray and a t_min and t_max value
    // That hit function takes a hit_record and updates it with the hit information
public:
    // Virtual as it can be overridden in sub-classes. = 0 means it's a pure virtual function
    virtual bool hit(const ray &r, hit_record &rec) const = 0;

    // We need a virtual destructor to ensure that the destructor of the derived class is called
    ~hittable() = default;
};

#endif