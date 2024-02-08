//
//  image_texture.hpp
//  raytracer 1
//
//  Created by Admin on 12/01/24.
//

#ifndef image_texture_hpp
#define image_texture_hpp

#include <stdio.h>
#include "texture.hpp"

class image_texture : public texture {
    public:
        inline image_texture() {}
        inline image_texture(unsigned char *pixels, int A, int B) : data(pixels), nx(A), ny(B) {}
                inline virtual vec3 value(const double& u,const double& v, const vec3& p) const {
                    int i = u*nx;
                    int j = (1-v)*ny-0.001;
                    if (i < 0) i = 0;
                    if (j < 0) j = 0;
                    if (i > nx-1) i = nx-1;
                    if (j > ny-1) j = ny-1;
                    int _i_nx_j = 3*i + 3*nx*j;
                    const double r = int(data[_i_nx_j]  ) / 255.0;
                    const double g = int(data[_i_nx_j+1]) / 255.0;
                    const double b = int(data[_i_nx_j+2]) / 255.0;
                    return vec3(r, g, b);
               }

        unsigned char *data;
        int nx, ny;
};



#endif /* image_texture_hpp */
