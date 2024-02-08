//
//  noise_texture.hpp
//  raytracer 1
//
//  Created by Admin on 08/01/24.
//

#ifndef noise_texture_hpp
#define noise_texture_hpp

#include <stdio.h>
#include "perlin.hpp"
class noise_texture : public texture {
public:
    inline noise_texture(): scale(1){}
    inline noise_texture(double sc):scale(sc){}
    inline virtual vec3 value(const double& u,const double& v, const vec3& p ) const {
        //return vec3(0.5)*(1+noise.turb(scale*p));
        //return vec3(1.0)*noise.turb(scale*p);
        return vec3(0.5)*(1+sin(scale*p.e[2] + 10*noise.turb(p)));
    }
    
    perlin noise;
    const double scale;
};

#endif /* noise_texture_hpp */
