#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;

class hittable_list : public hittable
{
public:
    hittable_list() {}
    void add(shared_ptr<hittable> object)
    {
        hittables.push_back(object);
    }

    virtual bool hit(const ray &r, hit_record &rec) const
    {
        // If I call each object's hit method, do I overwrite the same hit_record?
        // Or should I store an array of hit records as well?
        // In the end, the ray_color function will have to iterate over the hit records to find the closest hit
        // and then calculate the color of that hit.
        // So we could reduce down all the hit records to a single hit record based on the smallest t.

        for (const auto &object : hittables)
        {
            auto current_rec = hit_record();
            if (object->hit(r, current_rec))
            {
                // We can replace the hit record if the current hit record is closer
                // What happens if none of the objects are hit, I guess it'll return nothing
                if (!rec.t || current_rec.t < rec.t)
                {
                    rec = current_rec;
                }
            }
        }
        return rec.t;
    }

private:
    // The hitable list should store a list of hittable objects as private
    std::vector<shared_ptr<hittable>> hittables;
};

#endif