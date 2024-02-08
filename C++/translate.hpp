//
//  translate.hpp
//  raytracer 1
//
//  Created by Admin on 25/01/24.
//

#ifndef translate_h
#define translate_h
#include "hitable.hpp"
class translate : public hitable
{
public:
    translate(hitable *p, const vec3 &displacement) : ptr(p), offset(displacement) {}
    virtual bool hit(const ray &r, const double &t_min, const double &t_max, hit_record &rec) const;
    virtual bool bounding_box(const double &t0, const double &t1, aabb &box) const;
    hitable *ptr;
    vec3 offset;
};
bool translate::hit(const ray &r, const double &t_min, const double &t_max, hit_record &rec) const
{
    ray moved_r(r.origin - offset, r.direction, r.time);
    if (ptr->hit(moved_r, t_min, t_max, rec))
    {
        rec.p += offset;
        return true;
    }
    return false;
}
bool translate::bounding_box(const double &t0, const double &t1, aabb &box) const
{
    if (ptr->bounding_box(t0, t1, box))
    {
        box = aabb(box._min + offset, box._max + offset);
        return true;
    }
    return false;
}

#endif /* translate_h */
