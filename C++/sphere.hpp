//
//  sphere.hpp
//  raytracer 1
//
//  Created by Admin on 22/12/23.
//

#ifndef sphere_hpp
#define sphere_hpp

#include <stdio.h>
#include "hitable.hpp"

class sphere: public hitable {
    public:
    inline sphere(): center{0,0,0}, radius(0.0) {};
    inline sphere(vec3 cen, double r, material* m) : center(cen), radius(r), mat(m) {};
    inline virtual bool hit(const ray& r,const double& t_min, const double& t_max, hit_record& rec) const;
    vec3 center;
    double radius;
    material* mat;
};

bool sphere::hit(const ray& r,const double& t_min,const double& t_max, hit_record& rec) const {
    const vec3 oc = r.origin() - center;
    const double a = dot(r.direction(),r.direction());
    const double b = dot(oc,r.direction());
    const double c = dot(oc,oc) - radius*radius;
    const double discriminant  =  b*b - a*c;
    if(discriminant > 0) {
        const double temp = (-b - sqrt(discriminant))/a;
        if(temp < t_max && temp > t_min){
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center )/radius;
            rec.mat_ptr = mat;
            return true;
        }
        const double temp2 = (-b + sqrt(discriminant))/a;
        if(temp2 < t_max && temp2 > t_min){
            rec.t = temp2;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center )/radius;
            rec.mat_ptr = mat;
            return true;
        }
    }
    return false;
}

#endif /* sphere_hpp */

