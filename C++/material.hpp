//
//  material.hpp
//  raytracer 1
//
//  Created by Admin on 23/12/23.
//

#ifndef material_hpp
#define material_hpp

#include <stdio.h>
#include "ray.hpp"
#include "hitable.hpp"

class material
{
public:
    inline virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
    inline virtual vec3 emitted(const double& u,const double& v, const vec3& p) const {
        return vec3(0);
    }
};

inline double schlick(const double cosine, const double ref_idx)
{
    double r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 *= r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}
#endif /* material_hpp */
