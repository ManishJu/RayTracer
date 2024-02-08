//
//  yz_rect.hpp
//  raytracer 1
//
//  Created by Admin on 20/01/24.
//

#ifndef yz_rect_h
#define yz_rect_h

class yz_rect : public hitable
{
public:
    inline yz_rect() {}
    inline yz_rect(double _y0, double _y1, double _z0, double _z1, double _k, material *mat) : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat), invert_diffY(1 / (y1 - y0)), invert_diffZ(1 / (z1 - z0)), y0_invert_diffY(y0 * invert_diffY), z0_invert_diffZ(z0 * invert_diffZ){};
    inline virtual bool hit(const ray &r, const double &t0, const double &t1, hit_record &rec) const;
    inline virtual bool bounding_box(const double &t0, const double &t1, aabb &box) const
    {
        box = aabb(vec3(k - 0.001, y0, z0), vec3(k + 0.001, y1, z1));
        return true;
    }

    material *mp;
    double y0, y1, z0, z1, k;
    double invert_diffY, invert_diffZ;
    double y0_invert_diffY, z0_invert_diffZ;
};

inline bool yz_rect::hit(const ray &r, const double &t0, const double &t1, hit_record &rec) const
{

    const double t = (k - r.origin.e[0]) / r.direction.e[0];
    if (t < t0 || t > t1)
        return false;
    const double y = r.origin.e[1] + t * r.direction.e[1];
    const double z = r.origin.e[2] + t * r.direction.e[2];

    if (y < y0 || y > y1 || z < z0 || z > z1)
        return false;

    rec.u = y * invert_diffY - y0_invert_diffY;
    rec.v = z * invert_diffZ - z0_invert_diffZ;
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(1, 0, 0);
    return true;
}

#endif /* yz_rect_h */
