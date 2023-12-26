//
//  hitable_list.hpp
//  raytracer 1
//
//  Created by Admin on 22/12/23.
//

#ifndef hitable_list_hpp
#define hitable_list_hpp

#include <stdio.h>
#include "hitable.hpp"

class hitable_list : public hitable {
    
    public :
    inline hitable_list() {};
    inline hitable_list(hitable **l,int n): list(l), list_size(n) {};
    virtual inline bool hit(const ray& r,const double& t_min,const double& t_max, hit_record& rec) const;
    hitable **list;
    int list_size;
};

inline bool hitable_list::hit(const ray& r,const double& t_min,const double& t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for(int i = 0; i < list_size; i++){
        if(list[i]->hit(r,t_min,closest_so_far,temp_rec)){
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}
#endif /* hitable_list_hpp */
