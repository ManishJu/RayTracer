//
//  bvh_node.hpp
//  raytracer 1
//
//  Created by Admin on 05/01/24.
//

#ifndef bvh_node_hpp
#define bvh_node_hpp

#include <stdio.h>
#include "hitable.hpp"

class bvh_node : public hitable
{
public:
    inline bvh_node() {}
    inline bvh_node(hitable **l, const int &n, const double &time0, const double &time1);
    inline virtual bool hit(const ray &r, const double &t_min, const double &t_max, hit_record &rec) const;
    inline virtual bool bounding_box(const double &t0, const double &t1, aabb &b) const;
    hitable *left;
    hitable *right;
    aabb box;
};

inline bool bvh_node::bounding_box(const double &t0, const double &t1, aabb &b) const
{
    b = box;
    return true;
}

inline bool bvh_node::hit(const ray &r, const double &t_min, const double &t_max, hit_record &rec) const
{
    if (box.hit(r, t_min, t_max))
    {
        hit_record left_rec, right_rec;
        bool hit_left = left->hit(r, t_min, t_max, left_rec);
        bool hit_right = right->hit(r, t_min, t_max, right_rec);
        if (hit_left && hit_right)
        {
            if (left_rec.t < right_rec.t)
                rec = left_rec;
            else
                rec = right_rec;
            return true;
        }
        else if (hit_left)
        {
            rec = left_rec;
            return true;
        }
        else if (hit_right)
        {
            rec = right_rec;
            return true;
        }
        else
            return false;
    }
    else
        return false;
}
inline int box_x_compare(const void *a, const void *b)
{
    aabb box_left, box_right;
    hitable *ah = *(hitable **)a;
    hitable *bh = *(hitable **)b;
    if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
        std::cerr << "no bounding box in bvh_node constructor\n";
    if (box_left._min.e[0] - box_right._min.e[0] < 0.0)
        return -1;
    else
        return 1;
}

inline int box_y_compare(const void *a, const void *b)
{
    aabb box_left, box_right;
    hitable *ah = *(hitable **)a;
    hitable *bh = *(hitable **)b;
    if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
        std::cerr << "no bounding box in bvh_node constructor\n";
    if (box_left._min.e[1] - box_right._min.e[1] < 0.0)
        return -1;
    else
        return 1;
}

inline int box_z_compare(const void *a, const void *b)
{
    aabb box_left, box_right;
    hitable *ah = *(hitable **)a;
    hitable *bh = *(hitable **)b;
    if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
        std::cerr << "no bounding box in bvh_node constructor\n";
    if (box_left._min.e[2] - box_right._min.e[2] < 0.0)
        return -1;
    else
        return 1;
}
inline bvh_node::bvh_node(hitable **l, const int &n, const double &time0, const double &time1)
{
    int axis = rand() % 3;
    if (axis == 0)
        qsort(l, n, sizeof(hitable *), box_x_compare);
    else if (axis == 1)
        qsort(l, n, sizeof(hitable *), box_y_compare);
    else
        qsort(l, n, sizeof(hitable *), box_z_compare);

    if (n == 1)
    {
        left = right = l[0];
    }
    else if (n == 2)
    {
        left = l[0];
        right = l[1];
    }
    else
    {
        left = new bvh_node(l, n / 2, time0, time1);
        right = new bvh_node(l + n / 2, n - n / 2, time0, time1);
    }
    aabb box_left, box_right;
    if (!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right))
        std::cerr << "no bounding box in bvh_node constructor\n";
    box = surrounding_box(box_left, box_right);
}

#endif /* bvh_node_hpp */
