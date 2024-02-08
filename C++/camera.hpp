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
    inline camera(const vec3& lookFrom,
    const vec3& lookAt ,
    const vec3& vup,
    const double& vfov,
    const double& aspect, 
    const double& aperture, 
    const double& focus_distance,
    const double& t0,
    const double& t1
    )
     :      lens_radius(aperture/2),
            origin(lookFrom),
            time0(t0),
            time1(t1),
            w(unit_vector(lookFrom - lookAt)),
            u(unit_vector(cross(vup,w))),
            v(cross(w,u)),
            timeDiff(t1-t0),
            theta(vfov*M_PI/180),
            half_height(tan(theta/2)),
            half_width(aspect*half_height),
            lower_left_corner(origin - half_width*focus_distance*u - half_height*focus_distance*v - w*focus_distance),
            horizontal ( 2*half_width*focus_distance*u),
            vertical ( 2*half_height*focus_distance*v),
            lower_left_corner_minus_origin(lower_left_corner - origin)
       
        
     {}

    inline ray get_ray(const double& s,const double& t) const {
        const vec3 rd = lens_radius*random_in_unit_disk();
        const vec3 offset = u*rd.e[0] + v*rd.e[1];
        const double time = time0 + myrand*timeDiff;
        return ray(origin+offset,lower_left_corner_minus_origin + s*horizontal +t*vertical -offset,time);
    }
    
    const double lens_radius;
    const vec3 origin;
    const double time0, time1,timeDiff;
    const vec3 w,u,v;
    const double theta,half_height,half_width;
    const vec3 lower_left_corner;
    const vec3 horizontal;
    const vec3 vertical;
    const vec3 lower_left_corner_minus_origin;
};
#endif /* camera_hpp */
