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
#include "lambertian.hpp"

class sphere : public hitable
{
public:
    inline sphere() : center0{0, 0, 0},
                      center1{0, 0, 0},
                      time0(0),
                      time1(0),
                      radius(0.0),
                      mat(new lambertian(new constant_texture(vec3(0.5, 0.5, 0.5)))),
                      timeDiff(0),
                      centerDiff(0),
                      isTimeSame(true),
                      isCenterSame(true),
                      isNotMoving(true),
                      radiusSquared(0.0),
                      center0Xtime0XcenterDivTime(0),
                      bb(surrounding_box(
                          aabb(center0 - vec3(radius), center0 + vec3(radius)),
                          aabb(center1 - vec3(radius), center1 + vec3(radius)))){};

    inline sphere(
        const vec3 &cen0,
        const vec3 &cen1,
        const double &t0,
        const double &t1,
        const double &r,
        const material *const m)
        : center0(cen0),
          center1(cen1),
          time0(t0),
          time1(t1),
          radius(r),
          mat(m),
          centerDiff(cen1 - cen0),
          timeDiff(t1 - t0),
          isTimeSame(t0 == t1),
          isCenterSame(cen0 == cen1),
          isNotMoving(isTimeSame || isCenterSame),
          centerDivTime(centerDiff / timeDiff),
          radiusSquared(r * r),
          center0Xtime0XcenterDivTime(center0 - time0 * centerDivTime),
          bb(surrounding_box(
              aabb(center0 - vec3(radius), center0 + vec3(radius)),
              aabb(center1 - vec3(radius), center1 + vec3(radius)))){};

    inline sphere(vec3 cen0,
                  double r,
                  const material *const m)
        : center0(cen0),
          center1(cen0),
          radius(r),
          mat(m),
          time0(0),
          time1(0),
          timeDiff(0),
          centerDiff(0),
          isTimeSame(true),
          isCenterSame(true),
          isNotMoving(true),
          radiusSquared(r * r),
          center0Xtime0XcenterDivTime(0),
          bb(surrounding_box(
              aabb(center0 - vec3(radius), center0 + vec3(radius)),
              aabb(center1 - vec3(radius), center1 + vec3(radius)))){};

    inline virtual bool hit(const ray &r,
                            const double &t_min,
                            const double &t_max,
                            hit_record &rec) const;

    inline vec3 center(const double &time) const;
    inline virtual bool bounding_box(const double &t0,
                                     const double &t1,
                                     aabb &box) const;

    const vec3 center0, center1, centerDiff;
    const double radius, time0, time1, timeDiff;
    const bool isTimeSame, isCenterSame;
    const bool isNotMoving;
    const vec3 centerDivTime;
    const double radiusSquared;
    const vec3 center0Xtime0XcenterDivTime;
    const material *const mat;
    const aabb bb;
};

inline bool sphere::bounding_box(const double &t0,
                                 const double &t1,
                                 aabb &box) const
{
    box = bb;
    return true;
}

inline vec3 sphere::center(const double &time) const
{
    if (isNotMoving)
        return center0;
    return center0Xtime0XcenterDivTime + time * centerDivTime;
}
inline bool sphere::hit(const ray &r, const double &t_min, const double &t_max, hit_record &rec) const
{
    const vec3 oc = r.origin - center(r.time);
    const double a = r.dotDD; // dot(r.direction(),r.direction());
    const double b = dot(oc, r.direction);
    const double c = dot(oc, oc) - radiusSquared;
    const double discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        const double temp0 = -b/a;
        const double temp1 = sqrt(discriminant) / a;
        const double temp = temp0 -temp1;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(temp);
            rec.normal = (rec.p - center(r.time)) / radius;
            rec.mat_ptr = mat;
            return true;
        }
        const double temp2 = temp0+temp1;
        if (temp2 < t_max && temp2 > t_min)
        {
            rec.t = temp2;
            rec.p = r.point_at_parameter(temp2);
            rec.normal = (rec.p - center(r.time)) / radius;
            rec.mat_ptr = mat;
            return true;
        }
    }
    return false;
}

#endif /* sphere_hpp */
