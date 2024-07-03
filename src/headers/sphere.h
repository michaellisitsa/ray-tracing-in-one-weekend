#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable
{
public:
    sphere() {}
    sphere(point3 cen, double r) : center(cen), radius(r) {}

    virtual bool hit(const ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const
    {
        // We want to find if something has been hit.
        // We want to find the roots of the equation.
        // Unlike hit_sphere method, we want to update the hit_record rather than return the root t value
        // We also store the radius and center so don't have to pass it in.

        // ray = 𝐐+𝑡𝐝
        // Equation of sphere
        // C is the center of the sphere
        // (𝐂−𝐏)⋅(𝐂−𝐏)=𝑟2
        // Expands to
        // (𝐂−(𝐐+𝑡𝐝))⋅(𝐂−(𝐐+𝑡𝐝))=𝑟2
        // and distribute dot product
        // 𝑡2𝐝⋅𝐝−2𝑡𝐝⋅(𝐂−𝐐)+(𝐂−𝐐)⋅(𝐂−𝐐)=𝑟2
        // Solving the roots:
        // (−𝑏±𝑏2−4𝑎𝑐)/(√2𝑎)
        // a = d⋅d
        // b = -2𝐝⋅(𝐂−𝐐)
        // c = (𝐂−𝐐)⋅(𝐂−𝐐)−𝑟2
        //
        // This function must calculate the roots
        // If the roots are real and positive, then the ray intersects the sphere
        // If the roots are real and negative, then the ray does not intersect the sphere
        // If the roots are complex, then the ray intersects the sphere at a tangent
        double a = dot(r.direction(), r.direction());
        vec3 oc = center - r.origin();            // (𝐂−𝐐)
        double b = -2.0 * dot(r.direction(), oc); // -2𝐝⋅(𝐂−𝐐)
        double c = dot(oc, oc) - radius * radius; // (𝐂−𝐐)⋅(𝐂−𝐐)−𝑟2
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
            return false;

        auto root = (-b - sqrt(discriminant)) / (2.0 * a);

        if (root < ray_tmin || root > ray_tmax)
        {
            // switch the sign of the sqrt discriminant
            root = (-b + sqrt(discriminant)) / (2.0 * a);
            if (root < ray_tmin || root > ray_tmax)
                return false;
        }
        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 normal = unit_vector(rec.p - center);
        // Check which direction was hit
        // If the dot product of the normal and the ray direction is negative, then the ray hit the front of the sphere
        rec.front_face = dot(r.direction(), normal) < 0;
        rec.normal = rec.front_face ? normal : -normal;
        return true;
    };

private:
    point3 center;
    double radius;
};

#endif