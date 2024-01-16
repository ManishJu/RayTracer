//
//  hitable.hpp
//  raytracer 1
//
//  Created by Admin on 22/12/23.
//

#ifndef hitable_hpp
#define hitable_hpp

#include <stdio.h>
#include "ray.hpp"
#include "aabb.hpp"

class material;

struct hit_record
{
    double t;
    vec3 p;
    vec3 normal;
    const material *mat_ptr;
    double u,v;
};

class hitable
{
public:
    inline virtual bool hit(const ray &r, const double &t_min, const double &t_max, hit_record &rec) const = 0;
    inline virtual bool bounding_box(const double &t0, const double &t1, aabb &box) const = 0;
};
#endif /* hitable_hpp */
