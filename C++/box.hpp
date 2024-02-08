//
//  Header.h
//  raytracer 1
//
//  Created by Admin on 24/01/24.
//

#ifndef Box_h
#define Box_h
#include "flip_normals.hpp"

class box : public hitable
{
public:
    inline box() {}
    inline box(const vec3 &p0, const vec3 &p1, material *ptr);
    virtual bool hit(const ray &r, const double &t0, const double &t1, hit_record &rec) const;
    virtual bool bounding_box(const double &t0, const double &t1, aabb &b) const

    {
        b = b_b;
        return true;
    }

    vec3 pmin, pmax;
    aabb b_b;
    hitable *list_ptr;
};
inline box::box(const vec3 &p0, const vec3 &p1, material *ptr) : pmin(p0), pmax(p1),
                                                                 b_b(aabb(pmin, pmax))
{

    hitable **list = new hitable *[6];
    list[0] = new xy_rect(p0.e[0], p1.e[0], p0.e[1], p1.e[1], p1.e[2], ptr);
    list[1] = new flip_normals(new xy_rect(p0.e[0], p1.e[0], p0.e[1], p1.e[1], p0.e[2], ptr));
    list[2] = new xz_rect(p0.e[0], p1.e[0], p0.e[2], p1.e[2], p1.e[1], ptr);
    list[3] = new flip_normals(new xz_rect(p0.e[0], p1.e[0], p0.e[2], p1.e[2], p0.e[1], ptr));
    list[4] = new yz_rect(p0.e[1], p1.e[1], p0.e[2], p1.e[2], p1.e[0], ptr);
    list[5] = new flip_normals(new yz_rect(p0.e[1], p1.e[1], p0.e[2], p1.e[2], p0.e[0], ptr));

    list_ptr = new hitable_list(list, 6);
}

bool box::hit(const ray &r, const double &t0, const double &t1, hit_record &rec) const
{
    return list_ptr->hit(r, t0, t1, rec);
}
#endif /* Box_h */
