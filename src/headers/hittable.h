#ifndef HITTABLE_H
#define HITTABLE_H

// Since we're going to recursively shoot rays when calculating the shade of a pixel
// we need to record when a hit has occurred
struct hit_record
{
    // The point where the ray hits the object
    // Normal vector at the point it hit
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
    // We also want to know which side of the object we hit.
    // We know which direction the ray has come from, and we know the object's normal at that point.
    // But the normal could be in either direction, so we need to know if we hit the front or the back of the object.
    // I guess we can find the angle between the ray and the normal which ever direction it has
    // The dot product of vectors divided by their magnitudes gives the cosine of the angle between them
    // θ = cos-1 [ (a · b) / (|a| |b|) ]
    // Dot product is also useful to find the project of one vector on another
    // a.b = |a| |b| cos(θ)
    // a.b = |a| |b| cos(90) = 0 // because its perpendicular.
    // Nature of dot product is that two vectors are in parallel in the same direction of dot produt is positive
    // How do we store this information? can we store it as a unit vector?
    vec3 normal_face;
};

class hittable
{
    // An abstract class that represents a hittable object
    // Must implement a hit method that takes a ray and a t_min and t_max value
    // That hit function takes a hit_record and updates it with the hit information
public:
    // Virtual as it can be overridden in sub-classes. = 0 means it's a pure virtual function
    virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const = 0;

    // We need a virtual destructor to ensure that the destructor of the derived class is called
    ~hittable() = default;
};

#endif