//
//  checker_texture.hpp
//  raytracer 1
//
//  Created by Admin on 07/01/24.
//

#ifndef checker_texture_hpp
#define checker_texture_hpp

#include <stdio.h>
#include "texture.hpp"

class checker_texture : public texture {
    public:
    checker_texture() {}
    checker_texture(texture* t0, texture* t1) : even(t0), odd(t1) {}
    virtual vec3 value(double u, double v, const vec3& p) const {
        return
        (sin(10*p.e[0])*sin(10*p.e[1])*sin(10*p.e[2]) < 0) ?
        vec3(1,1.0,0.8) : vec3(1,0.7,0.5);
    }
    
    texture *odd, *even ;
    
};
    

#endif /* checker_texture_hpp */
