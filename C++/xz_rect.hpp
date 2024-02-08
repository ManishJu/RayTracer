//
//  xz_rect.hpp
//  raytracer 1
//
//  Created by Admin on 20/01/24.
//

#ifndef xz_rect_h
#define xz_rect_h
#include "hitable.hpp"

class xz_rect : public hitable
{

public:
    inline xz_rect() {}
    inline xz_rect(double _x0, double _x1, double _z0, double _z1, double _k, material *mat) : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat), invert_diffX(1 / (x1 - x0)), invert_diffZ(1 / (z1 - z0)), x0_invert_diffX(x0 * invert_diffX),
                                                                                        z0_invert_diffZ(z0 * invert_diffZ){};
    inline virtual bool hit(const ray &r, const double &t0, const double &t1, hit_record &rec) const;
    inline virtual bool bounding_box(const double &t0, const double &t1, aabb &box) const
    {
        box = aabb(vec3(x0, k - 0.0001, z0), vec3(x1, k + 0.0001, z1));
        return true;
    }

    material *mp;
    double x0, x1, z0, z1, k;
    double invert_diffX, invert_diffZ;
    double x0_invert_diffX, z0_invert_diffZ;
};

inline bool xz_rect::hit(const ray &r, const double &t0, const double &t1, hit_record &rec) const
{
    const double t = (k - r.origin.e[1]) / r.direction.e[1];
    if (t < t0 || t > t1)
        return false;
    const double x = r.origin.e[0] + t * r.direction.e[0];
    const double z = r.origin.e[2] + t * r.direction.e[2];

    if (x < x0 || x > x1 || z < z0 || z > z1)
        return false;
    rec.u = x * invert_diffX - x0_invert_diffX;
    rec.v = z * invert_diffZ - z0_invert_diffZ;
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(0, 1, 0);
    return true;
}
#endif /* xz_rect_h */
