//
//  vec3.hpp
//  raytracer 1
//
//  Created by Admin on 22/12/23.
//

#ifndef vec3_hpp
#define vec3_hpp

#include <stdio.h>
#include <cstdint>
#include <math.h>
#include <iostream>
#include <stdlib.h>

#define myhalfrandMinusOne ((double)rand() / (1073741823.5)) - 1.0
#define myrand ((double)rand() / (RAND_MAX))

typedef std::uint_fast8_t i8t;
typedef std::uint_fast16_t i16t;
typedef std::uint_fast32_t i32t;
typedef std::uint_fast64_t imaxt;

const double halfRandMax_Inverted = 2.0 / RAND_MAX;


class vec3
{

public:
    inline vec3(){};
    inline vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}
    inline vec3(double a) : e{a, a, a} {}
    inline double x() const { return e[0]; }
    inline double y() const { return e[1]; }
    inline double z() const { return e[2]; }
    inline double r() const { return e[0]; }
    inline double g() const { return e[1]; }
    inline double b() const { return e[2]; }

    inline const vec3 &operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    inline double operator[](const std::uint_fast8_t i) const { return e[i]; }
    inline double &operator[](const std::uint_fast8_t i) { return e[i]; }

    inline vec3 &operator+=(const vec3 &v2)
    {
        e[0] += v2.e[0];
        e[1] += v2.e[1];
        e[2] += v2.e[2];
        return *this;
    };
    inline vec3 &operator-=(const vec3 &v2)
    {
        e[0] -= v2.e[0];
        e[1] -= v2.e[1];
        e[2] -= v2.e[2];
        return *this;
    };
    inline vec3 &operator/=(const vec3 &v2)
    {
        e[0] /= v2.e[0];
        e[1] /= v2.e[1];
        e[2] /= v2.e[2];
        return *this;
    };
    inline vec3 &operator*=(const vec3 &v2)
    {
        e[0] *= v2.e[0];
        e[1] *= v2.e[1];
        e[2] *= v2.e[2];
        return *this;
    };
    inline vec3 &operator/=(const double t)
    {
        e[0] /= t;
        e[1] /= t;
        e[2] /= t;
        return *this;
    };
    inline vec3 &operator*=(const double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    };

    inline bool operator==(const vec3 &v2) const
    {
        const bool check = (e[0] == v2.e[0] && e[1] == v2.e[1] && e[2] == v2.e[2]);
        return check;
    };

    inline double length() const
    {
        return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    };

    inline double squared_length()
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    };

    inline void make_unit_vector()
    {
        const double vlength = (1 / this->length());
        e[0] *= vlength;
        e[1] *= vlength;
        e[2] *= vlength;
    }

    double e[3];
};

inline std::istream &operator>>(std::istream &is, vec3 &t)
{
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream &operator<<(std::ostream &os, const vec3 &t)
{
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(const double t, const vec3 &v)
{
    return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}
inline vec3 operator-(const double t, const vec3 &v)
{
    return vec3(v.e[0] - t, v.e[1] - t, v.e[2] - t);
}
inline vec3 operator+(const double t, const vec3 &v)
{
    return vec3(v.e[0] + t, v.e[1] + t, v.e[2] + t);
}
inline vec3 operator/(const double t, const vec3 &v)
{
    return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline vec3 operator*(const vec3 &v, const double t)
{
    return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}
inline vec3 operator-(const vec3 &v, const double t)
{
    return vec3(v.e[0] - t, v.e[1] - t, v.e[2] - t);
}
inline vec3 operator+(const vec3 &v, const double t)
{
    return vec3(v.e[0] + t, v.e[1] + t, v.e[2] + t);
}
inline vec3 operator/(const vec3 &v, const double t)
{
    return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}
inline double dot(const vec3 &v1, const vec3 &v2)
{
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
                -v1.e[0] * v2.e[2] + v1.e[2] * v2.e[0],
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

inline vec3 unit_vector(const vec3 &v)
{
    return v / v.length();
}

inline vec3 reflect(const vec3 &v, const vec3 &n)
{
    return v - 2 * dot(v, n) * n;
}

inline bool refract(const vec3 &v, const vec3 &n, const double &ni_over_nt, vec3 &refracted)
{
    const vec3 uv = unit_vector(v);
    const double dt = dot(uv, n);
    const double discriminant = 1 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0)
    {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    }
    return false;
}

inline vec3 random_in_unit_sphere()
{
    static vec3 p_random_in_unit_sphere;
    do
    {
        p_random_in_unit_sphere = vec3(myhalfrandMinusOne, myhalfrandMinusOne, myhalfrandMinusOne);
        // p_random_in_unit_sphere = vec3(((double) rand() / (RAND_MAX))-0.5,((double) rand() / (RAND_MAX))-0.5,((double) rand() / (RAND_MAX))-0.5) ;
    } while (p_random_in_unit_sphere.squared_length() >= 1.0);
    return unit_vector(p_random_in_unit_sphere);
}

inline vec3 random_in_unit_disk()
{
    static vec3 p_random_in_unit_disk;
    do
    {
        p_random_in_unit_disk = vec3(myhalfrandMinusOne, myhalfrandMinusOne, 0);
    } while (p_random_in_unit_disk.squared_length() >= 1.0);
    return unit_vector(p_random_in_unit_disk);
}

#endif /* vec3_hpp */
