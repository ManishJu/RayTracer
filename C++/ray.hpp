//
//  ray.hpp
//  raytracer 1
//
//  Created by Admin on 22/12/23.
//

#ifndef ray_hpp
#define ray_hpp

#include <stdio.h>
#include "vec3.hpp"

class ray
{
public:
    inline ray(){};

    inline ray(const vec3 &a, const vec3 &b, const double &_t) : origin(a), direction(b), time(_t), dotDD(dot(b, b)), inverseDirection{1 / b.e[0], 1 / b.e[1], 1 / b.e[2]} {};
    inline vec3 point_at_parameter(double t) const { return origin + t * direction; };

    vec3 origin;
    vec3 direction;
    vec3 inverseDirection;
    double time, dotDD;
};
#endif /* ray_hpp */
