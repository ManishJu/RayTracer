//
//  texture.hpp
//  raytracer 1
//
//  Created by Admin on 07/01/24.
//

#ifndef texture_hpp
#define texture_hpp

#include <stdio.h>
#include "vec3.hpp"

class texture {
public:
    virtual vec3 value(double u,double v,const vec3& p) const = 0;
};

class constant_texture : public texture {
    
    public :
    constant_texture() {}
    constant_texture(const vec3& c) :  color(c) {}
    virtual vec3 value(double u,double v,const vec3& p) const {
        return color;
    }
    vec3 color;
    
};
#endif /* texture_hpp */
