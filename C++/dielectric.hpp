//
//  dielectric.hpp
//  raytracer 1
//
//  Created by Admin on 25/12/23.
//

#ifndef dielectric_hpp
#define dielectric_hpp

#include <stdio.h>
#include "material.hpp"
#define myrand ((double) rand() / (RAND_MAX))

class dielectric: public material{
public:
    dielectric(double ri): ref_idx(ri){}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const{
        vec3 outward_normal;
        const vec3 reflected = reflect(r_in.direction(),rec.normal);
        double ni_over_nt;
        attenuation  = vec3(1.0);
        vec3 refracted;
        double reflect_prob;
        double cosine;
        if(dot(r_in.direction(),rec.normal)>0){
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx* dot(r_in.direction(),rec.normal)/r_in.direction().length();
        }
        else {
            outward_normal= rec.normal;
            ni_over_nt = 1.0/ref_idx;
            cosine = -dot(r_in.direction(),rec.normal) / r_in.direction().length();
        }
        if(refract(r_in.direction(),outward_normal, ni_over_nt,refracted)){
            reflect_prob = schlick(cosine,ref_idx);
        }
        else {
            //scattered = ray(rec.p,reflected);
            reflect_prob =1.0;
        }
        if(myrand < reflect_prob){
            scattered = ray(rec.p,reflected);
        }
        else {
            scattered = ray(rec.p,refracted);
        }
        return true;
        
    }
    double ref_idx;
};
        
#endif /* dielectric_hpp */
