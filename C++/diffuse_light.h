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
    diffuse_light(texture *a) : emit(a) {}
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 attenuation, ray &scattered) const { return false; }
    virtual vec3 emitted(double u, double v, const vec3 &p);
    texture *emit;
}

#endif /* diffuse_light_h */
