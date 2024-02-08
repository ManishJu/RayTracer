//
//  rotate_y.hpp
//  raytracer 1
//
//  Created by Admin on 25/01/24.
//

#ifndef rotate_y_h
#define rotate_y_h

#include "hitable.hpp"
class rotate_y : public hitable
{

public:
    rotate_y(hitable *p, double angle);
    virtual bool hit(const ray &r, const double &t_min, const double &t_max, hit_record &rec) const;
    virtual bool bounding_box(const double &t0, const double &t1, aabb &box) const
    {
        box = bbox;
        return hasbox;
    }
    hitable *ptr;
    double sin_theta;
    double cos_theta;
    bool hasbox;
    aabb bbox;
};

rotate_y::rotate_y(hitable *p, double angle) : ptr(p)
{
    double radians = (M_PI / 180) * angle;
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    hasbox = ptr->bounding_box(0, 1, bbox);
    vec3 min(__DBL_MAX__, __DBL_MAX__, __DBL_MAX__);
    vec3 max(-__DBL_MAX__, -__DBL_MAX__, -__DBL_MAX__);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                double x = i * bbox._max.e[0] + (1 - i) * bbox._min.e[0];
                double y = i * bbox._max.e[1] + (1 - j) * bbox._min.e[1];
                double z = i * bbox._max.e[2] + (1 - k) * bbox._min.e[2];
                double newx = cos_theta * x + sin_theta * z;
                double newz = -sin_theta * x + cos_theta * z;

                vec3 tester(newx, y, newz);
                for (int c = 0; c < 3; c++)
                {

                    max[c] = tester[c] > max[c] ? tester[c] : max[c];
                    min[c] = tester[c] < min[c] ? tester[c] : min[c];
                }
            }
        }
    }
    bbox = aabb(min, max);
}

bool rotate_y::hit(const ray &r, const double &t_min, const double &t_max, hit_record &rec) const
{
    vec3 origin = r.origin;
    vec3 direction = r.direction;
    origin[0] = cos_theta * r.origin.e[0] - sin_theta * r.origin.e[2];
    origin[2] = sin_theta * r.origin.e[0] + cos_theta * r.origin.e[2];
    direction[0] = cos_theta*r.direction.e[0] - sin_theta*r.direction.e[2];
    direction[2] = sin_theta*r.direction.e[0] + cos_theta*r.direction.e[2];
    ray rotated_r(origin, direction, r.time);
    if (ptr->hit(rotated_r, t_min, t_max, rec))
        
    {
        vec3 p = rec.p;
        vec3 normal = rec.normal;
        p[0] = cos_theta * rec.p[0] + sin_theta * rec.p[2];
        p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];

        normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
        normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];
        rec.p = p;
        rec.normal = normal;
        return true;
    }
    return false;
}
#endif /* rotate_y_h */
