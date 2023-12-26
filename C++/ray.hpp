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

class ray {
public:
    inline ray() {};
    inline ray(const vec3& a, const vec3& b): A(a), B(b) {};
    inline const vec3& origin() const { return A; };
    inline const vec3& direction()  const { return B; };
    inline vec3 point_at_parameter(double t) const { return A + t*B; };
    inline void updateRay(const vec3& a, const vec3 &b)  {
        A = a;
        B = b;
    };
    
    vec3 A;
    vec3 B;
};
#endif /* ray_hpp */
