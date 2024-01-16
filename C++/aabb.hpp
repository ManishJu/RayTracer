//
//  aabb.hpp
//  raytracer 1
//
//  Created by Admin on 04/01/24.
//

#ifndef aabb_hpp
#define aabb_hpp

#include <stdio.h>

#define SWAP(a, b) (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)));

class aabb
{

public:
    inline aabb() {}
    inline aabb(const vec3 &a, const vec3 &b) : _min(a), _max(b) {}
    inline vec3 min() const { return _min; }
    inline vec3 max() const { return _max; }

    inline bool hit(const ray &r, const double &tmin, const double &tmax) const
    {
        if(tmin == tmax) return false;
        double tt = r.inverseDirection.e[0];
        double t0 = (_min.e[0] - r.origin.e[0]) * tt;
        double t1 = (_max.e[0] - r.origin.e[0]) * tt;
        if (tt < 0.0f)
        {
            double t2 = t1;
            t1 = t0;
            t0 = t2;
        }
       
        if ((t1 < tmax ? t1 : tmax) <= (t0 > tmin ? t0 : tmin)) return false;

        tt = r.inverseDirection.e[1];
        t0 = (_min.e[1] - r.origin.e[1]) * tt;
        t1 = (_max.e[1] - r.origin.e[1]) * tt;
        if (tt < 0.0f)
        {
            double t2 = t1;
            t1 = t0;
            t0 = t2;
        }
       
        if ((t1 < tmax ? t1 : tmax) <= (t0 > tmin ? t0 : tmin)) return false;

        tt = r.inverseDirection.e[2];
        t0 = (_min.e[2] - r.origin.e[2]) * tt;
        t1 = (_max.e[2] - r.origin.e[2]) * tt;
        if (tt < 0.0f)
        {
            double t2 = t1;
            t1 = t0;
            t0 = t2;
        }

        if ((t1 < tmax ? t1 : tmax) <= (t0 > tmin ? t0 : tmin)) return false;

        return true;
    }
    vec3 _min, _max;
};

inline aabb surrounding_box(aabb box0, aabb box1)
{

    return aabb(
        vec3(fmin(box0._min.e[0], box1._min.e[0]), // small
             fmin(box0._min.e[1], box1._min.e[1]),
             fmin(box0._min.e[2], box1._min.e[2])),
        vec3(fmax(box0._max.e[0], box1._max.e[0]), // large
             fmax(box0._max.e[1], box1._max.e[1]),
             fmax(box0._max.e[2], box1._max.e[2])));
}

#endif /* aabb_hpp */
