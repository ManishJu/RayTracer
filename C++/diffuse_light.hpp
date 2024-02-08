//
//  diffuse_light.h
//  raytracer 1
//
//  Created by Admin on 19/01/24.
//

#ifndef diffuse_light_h
#define diffuse_light_h
#include "material.hpp"
#include "texture.hpp"

class diffuse_light : public material
{
public:
    inline diffuse_light(texture *a) : emit(a) {}
    inline virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const { return false; }
    inline virtual vec3 emitted(const double& u,const double& v, const vec3& p) const {
        return emit->value(u, v, p);
    };
    texture *emit;
};

#endif /* diffuse_light_h */
