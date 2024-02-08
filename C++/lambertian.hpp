//
//  lambertian.hpp
//  raytracer 1
//
//  Created by Admin on 23/12/23.
//

#ifndef lambertian_hpp
#define lambertian_hpp

#include <stdio.h>
#include "material.hpp"
#include "texture.hpp"

class lambertian : public material {
    public :
    inline lambertian (texture *a) : albedo(a) {}
    inline virtual bool scatter (const ray& r_in,const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target-rec.p,r_in.time);
        attenuation = albedo->value(rec.u,rec.v,rec.p);
        return true;
    }
    //const vec3 albedo;
    texture *albedo;
};
#endif /* lambertian_hpp */
