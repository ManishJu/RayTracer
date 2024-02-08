//
//  flip_normals.hpp
//  raytracer 1
//
//  Created by Admin on 21/01/24.
//

#ifndef flip_normals_h
#define flip_normals_h

#include "hitable.hpp"

class flip_normals : public hitable
{
public:
    inline flip_normals(hitable *p) : ptr(p) {}
    inline virtual bool hit(const ray &r, const double &t_min, const double &t_max, hit_record &rec) const
    {
        if (ptr->hit(r, t_min, t_max, rec))
        {
            rec.normal *= -1;
            return true;
        }
        return false;
    }
    inline virtual bool bounding_box(const double &t0, const double &t1, aabb &box) const {
        
        return true;
    };


    hitable *ptr;
};

#endif
