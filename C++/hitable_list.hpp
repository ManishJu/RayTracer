//
//  hitable_list.hpp
//  raytracer 1
//
//  Created by Admin on 22/12/23.
//

#ifndef hitable_list_hpp
#define hitable_list_hpp

#include <stdio.h>
#include "hitable.hpp"

class hitable_list : public hitable
{

public:
    inline hitable_list(){};
    inline hitable_list(hitable **l, int n) : list(l), list_size(n){};
    inline virtual bool hit(const ray &r, const double &t_min, const double &t_max, hit_record &rec) const;
    inline virtual bool bounding_box(const double &t0, const double &t1, aabb &box) const;
    hitable **list;
    int list_size;
};

inline bool hitable_list::hit(const ray &r, const double &t_min, const double &t_max, hit_record &rec) const
{
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (unsigned int i = 0; i < list_size; i++)
    {
        if (list[i]->hit(r, t_min, closest_so_far, rec))
        {
            hit_anything = true;
            closest_so_far = rec.t;
        }
    }
    return hit_anything;
}
inline bool hitable_list::bounding_box(const double &t0, const double &t1, aabb &box) const
{

    if (list_size < 1)
        return false;

    aabb temp_box;

    if (!(list[0]->bounding_box(t0, t1, temp_box)))
        return false;

    box = temp_box;

    for (unsigned int i = 0; i < list_size; i++)
    {
        if (list[0]->bounding_box(t0, t1, temp_box))
        {
            box = surrounding_box(box, temp_box);
        }
        else
            return false;
    }
    return true;
}

#endif /* hitable_list_hpp */
