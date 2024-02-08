//
//  xy_rect.hpp
//  raytracer 1
//
//  Created by Admin on 19/01/24.
//

#ifndef xy_rect_h
#define xy_rect_h

class xy_rect : public hitable
{
public:
    xy_rect() {}
    xy_rect(double _x0, double _x1, double _y0, double _y1, double _k, material *mat) : 
    x0(_x0), y0(_y0), x1(_x1), y1(_y1), k(_k), mp(mat), inv_diffx(1 / (x1 - x0)),
    inv_diffy(1 / (y1 - y0)),
    x0_inv_diffx(x0 * inv_diffx),
    y0_inv_diffy(y0 * inv_diffy) {}

    virtual bool hit(const ray &r, const double &t0, const double &t1, hit_record &rec) const;

    virtual bool bounding_box(const double &t0, const double &t1, aabb &box) const
    {
        box = aabb(vec3(x0, y0, k - 0.0001), vec3(x1, y1, k + 0.0001));
        return true;
    }

    material *mp;
    double x0, x1, y0, y1, k, inv_diffx, inv_diffy, x0_inv_diffx, y0_inv_diffy;
};

bool xy_rect::hit(const ray &r, const double &t0, const double &t1, hit_record &rec) const
{
    const double t = (k - r.origin.e[2]) / r.direction.e[2];
    if (t < t0 || t > t1)
        return false;
    const double x = r.origin.e[0] + t * r.direction.e[0];
    const double y = r.origin.e[1] + t * r.direction.e[1];

    if (x < x0 || x > x1 || y < y0 || y > y1)
        return false;

    rec.u = x * inv_diffx - x0_inv_diffx; // (x-x0)/(x1-x0)
    rec.v = y * inv_diffy - y0_inv_diffy;
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(0, 0, 1);
    return true;
}
#endif /* xy_rect_h */
