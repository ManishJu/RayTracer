//
//  constant_medium.hpp
//  raytracer 1
//
//  Created by Admin on 24/01/24.
//

#ifndef constant_medium_h
#define constant_medium_h
#include "hitable.hpp"
#include "texture.hpp"
#include "material.hpp"

class isotropic : public material
{
public:
    isotropic(texture *a) : albedo(a) {}
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        scattered = ray(rec.p, random_in_unit_sphere(), 0);
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    }
    virtual vec3 emitted(const double &u, const double &v, const vec3 &p) const
    {
        return vec3(0);
    }
    texture *albedo;
};

class constant_medium : public hitable
{
public:
    constant_medium(hitable *b, double d, texture *a) : boundary(b), density(d)

    {
        phase_function = new isotropic(a);
    }
    virtual bool hit(const ray &e, const double &t_min, const double &t_max, hit_record &rec) const;
    virtual bool bounding_box(const double &t0, const double &t1, aabb &box) const
    {
        return boundary->bounding_box(t0, t1, box);
    }
    hitable *boundary;
    double density;
    material *phase_function;
};
bool constant_medium::hit(const ray &r, const double &t_min, const double &t_max, hit_record &rec) const
{
    bool db = false; // myrand < 0.0001;
    //db  = false;
    hit_record rec1, rec2;
    if (boundary->hit(r, -__DBL_MAX__, __DBL_MAX__, rec1))
    {
        if (boundary->hit(r, rec1.t + 0.0001, __DBL_MAX__, rec2))
        {
            //if (db) std::cout << rec1.t << rec2.t;
            
            if (rec1.t < t_min)
                rec1.t = t_min;
            if (rec2.t > t_max)
                rec2.t = t_max;
            if (rec1.t >= rec2.t)
                return false;
            if (rec1.t < 0)
                rec1.t = 0;
            
            double distance_inside_boundary = (rec2.t - rec1.t) * r.direction.length();
            double hit_distance = -(1 / density) * log(myrand);
            if (hit_distance < distance_inside_boundary) {
                //std::cerr << "hit distance" << hit_distance;
                rec.t = rec1.t + hit_distance / r.direction.length();
                //if (db)
                   // std::cerr << "rec.t = " << rec.t << "\n";
                rec.p = r.point_at_parameter(rec.t);
                
                rec.normal = vec3(1, 0, 0);
                rec.mat_ptr = phase_function;
                return true;
            }
        }
    }
    return false;
}

#endif /* constant_medium_h */
