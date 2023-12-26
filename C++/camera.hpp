//
//  camera.hpp
//  raytracer 1
//
//  Created by Admin on 22/12/23.
//

#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>
#include "ray.hpp"
class camera {
    public : 
    camera(const vec3& lookFrom,
    const vec3& lookAt ,
    const vec3& vup,
    const double& vfov,
    const double& aspect, 
    const double& aperture, 
    const double& focus_distance
    ) {
        lens_radius = aperture/2;
        const double theta = vfov*M_PI/180;
        const double half_height = tan(theta/2);
        const double half_width = aspect*half_height;
        w = unit_vector(lookFrom - lookAt);
        u = unit_vector(cross(vup,w));
        v = cross(w,u);
        
        origin = lookFrom;
        //lower_left_corner = vec3(-half_width,-half_height,-1.0);
        lower_left_corner = origin - half_width*focus_distance*u - half_height*focus_distance*v - w*focus_distance;
        horizontal = 2*half_width*focus_distance*u;
        vertical = 2*half_height*focus_distance*v;
    }

    ray get_ray(const double& s,const double& t) {
        const vec3 rd = lens_radius*random_in_unit_disk();
        const vec3 offset = u*rd.x() + v*rd.y();
        return ray(origin+offset,lower_left_corner + s*horizontal +t*vertical  - origin -offset);
    }

    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 origin;
    vec3 u,v,w;
    vec3 lens_radius;
};
#endif /* camera_hpp */
