//
//  dielectric.hpp
//  raytracer 1
//
//  Created by Admin on 25/12/23.
//

#ifndef dielectric_hpp
#define dielectric_hpp

#include <stdio.h>
#include "material.hpp"
#define myrand1 ((double)rand() / (RAND_MAX))
#define myrand2 ((double)rand() / (RAND_MAX))
#define myrand3 ((double)rand() / (RAND_MAX))


class dielectric : public material
{
public:
    inline dielectric(double ri) : ref_idx(ri), inverse_ref_idx(1.0 / ri) {}
    inline virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        vec3 outward_normal;
        const vec3 reflected = reflect(r_in.direction, rec.normal);
        double ni_over_nt = ref_idx;
        attenuation = vec3(1.0);
        vec3 refracted;
        double reflect_prob = 1.0;
        double cosine;
        if (dot(r_in.direction, rec.normal) > 0)
        {
            outward_normal = -rec.normal;
            cosine = ni_over_nt * dot(r_in.direction, rec.normal) / r_in.direction.length();
        }
        else
        {
            outward_normal = rec.normal;
            ni_over_nt = inverse_ref_idx;
            cosine = -dot(r_in.direction, rec.normal) / r_in.direction.length();
        }
        if (refract(r_in.direction, outward_normal, ni_over_nt, refracted))
        {
            reflect_prob = schlick(cosine, ref_idx);
        }
        //        else {
        //            //scattered = ray(rec.p,reflected);
        //            reflect_prob =1.0;
        //        }
        if (myrand < reflect_prob)
        {
            scattered = ray(rec.p, reflected, r_in.time);
        }
        else
        {
            scattered = ray(rec.p, refracted, r_in.time);
        }
        return true;
    }
    const double ref_idx, inverse_ref_idx;
};

#endif /* dielectric_hpp */
