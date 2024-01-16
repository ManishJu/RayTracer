//
//  fx.hpp
//  raytracer 1
//
//  Created by Admin on 24/12/23.
//

#ifndef fx_hpp
#define fx_hpp

#include <stdio.h>
double hit_sphere(const vec3& center, double radius, const ray& r){
    const vec3 oc = r.origin - center;
    const double a = dot(r.direction(),r.direction());
    const double b = 2.0 * dot(oc,r.direction());
    const double c = dot(oc,oc) - radius*radius;
    const double discriminant  =  b*b - 4*a*c;
    //return discriminant > 0 ;
    return discriminant <= 0  ? -1 : (-b - sqrt(discriminant))/(2.0*a);
}
vec3 colorItRed( const ray& r, const vec3& sphereCenter){
    const double t = hit_sphere(sphereCenter,0.5,r);
    if(t > 0) return vec3(1,0,0);
    //if(hit_sphere(sphereCenter,0.5,r)) return vec3(1,0,0);
    const vec3 unit_direction = r.direction_normalised;
    const double t2 = 0.5*(unit_direction.e[1]+ 1);
    return (1.0-t2)*vec3(1.0,1.0,1.0) + t2*vec3(0.5,0.7,1.0);
}
vec3 colorIt( const ray& r, const vec3& sphereCenter){
    const double t = hit_sphere(sphereCenter,0.5,r);
    if(t > 0.0){
        const vec3 N = unit_vector(r.point_at_parameter(t)-sphereCenter);
        return 0.5*(N+1);
    }
    const vec3 unit_direction = unit_vector(r.direction());
    const double t2 = 0.5*(unit_direction.e[1]+ 1);
    return (1.0-t2)*vec3(1.0,1.0,1.0) + t2*vec3(0.5,0.7,1.0);
}

vec3 colorF(const ray& r, hitable *world){
    hit_record rec;
    if(world->hit(r,0.001,MAXFLOAT,rec)){
        //return 0.5*vec3(rec.normal+1);
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5*colorF(ray(rec.p,target -rec.p),world);
    }
    else {
        const vec3 unit_direction = unit_vector(r.direction());
        const double t = 0.5*(unit_direction.e[1]+1);
        return (1.0-t)*vec3(1.0) + t*vec3(0.5,0.7,1.0);
    }
}
#endif /* fx_hpp */
