//
//  metal_mat.hpp
//  raytracer 1
//
//  Created by Admin on 24/12/23.
//

#ifndef metal_mat_hpp
#define metal_mat_hpp

#include <stdio.h>
#include "material.hpp"

class metal_mat : public material
{

public:
    inline metal_mat(const vec3 &a, const double f) : albedo(a), fuzz(fmin(1, f)) {}
    inline virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        const vec3 reflected = reflect(unit_vector(r_in.direction), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere(), r_in.time);
        attenuation = albedo;
        return (dot(scattered.direction, rec.normal) > 0);
    }

    const vec3 albedo;
    const double fuzz;
};
#endif /* metal_mat_hpp */
