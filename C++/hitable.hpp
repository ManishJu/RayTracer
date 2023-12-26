//
//  hitable.hpp
//  raytracer 1
//
//  Created by Admin on 22/12/23.
//

#ifndef hitable_hpp
#define hitable_hpp

#include <stdio.h>
#include "ray.hpp"

class material ;

struct hit_record {
    double t;
    vec3 p;
    vec3 normal;
    material* mat_ptr;
};

class hitable {
public:
    inline virtual bool hit(const ray& r,const double& t_min,const double& t_max, hit_record& rec) const = 0 ;
};
#endif /* hitable_hpp */
