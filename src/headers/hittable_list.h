#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <vector>

class hittable_list : public hittable
{
public:
    hittable_list() {}
    void add(shared_ptr<hittable> object)
    {
        hittables.push_back(object);
    }

    virtual bool hit(const ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const
    {
        // If I call each object's hit method, do I overwrite the same hit_record?
        // Or should I store an array of hit records as well?
        // In the end, the ray_color function will have to iterate over the hit records to find the closest hit
        // and then calculate the color of that hit.
        // So we could reduce down all the hit records to a single hit record based on the smallest t.

        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;

        for (const auto &object : hittables)
        {
            if (object->hit(r, ray_tmin, closest_so_far, temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }

private:
    // The hitable list should store a list of hittable objects as private
    std::vector<shared_ptr<hittable>> hittables;
};

#endif