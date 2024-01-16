//
//  main.cpp
//  raytracer 1
//
//  Created by Admin on 22/12/23.
//

#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "camera.hpp"
#include "hitable_list.hpp"
#include "bvh_node.hpp"
#include "sphere.hpp"
#include "metal_mat.hpp"
#include "lambertian.hpp"
#include "dielectric.hpp"
#include "checker_texture.hpp"
#include "noise_texture.hpp"

using namespace std;
typedef std::string str;

FILE *fptr;
ray scattered;
vec3 attenuation;
hit_record rec;
vec3 unit_direction;
double t;

const vec3 oneVector(1.0);
const vec3 zeroVector(0.0);
const vec3 fixedColor(0.5, 0.7, 1.0);

void printToFile(int r, int g, int b)
{

    fprintf(fptr, "%d", r);
    fprintf(fptr, "%s", " ");
    fprintf(fptr, "%d", g);
    fprintf(fptr, "%s", " ");
    fprintf(fptr, "%d", b);
    fprintf(fptr, "%s", " ");
    fprintf(fptr, "%s", "\n");
}

void printInitialPPMCodeToFile(int nx, int ny)
{

    fprintf(fptr, "%s", "P3\n");
    fprintf(fptr, "%d", nx);
    fprintf(fptr, "%s", " ");
    fprintf(fptr, "%d", ny);
    fprintf(fptr, "%s", "\n255\n");
}
double getLightColor()
{
    double channelColor;
    while (true)
    {
        channelColor = min(1.0, max(0.5, myrand));
        if (channelColor > 0.5)
            return channelColor;
    }
}

vec3 getMyRandomColor()
{
    // rgb(255, 68, 51)
    double r = floor(myrand * 15);
    // double rand = floor(((double) rand() / (RAND_MAX))*15);
    // cout<<(r)<<endl;
    switch ((int)r)
    {
    case 0:
        cout << endl
             << "r" << r << " " << (double)210 / 255 << (double)105 / 255 << (double)30 / 255;
        return vec3((double)210 / 255, (double)105 / 255, (double)30 / 255);
        break;
    case 1:
        cout << endl
             << "r" << r << " " << (double)255 / 255 << (double)105 / 255 << (double)180 / 255;
        return vec3((double)255 / 255, (double)105 / 255, (double)180 / 255);
        break;
    case 2:
        cout << endl
             << "r" << r << " " << (double)255 / 255 << (double)20 / 255 << (double)147 / 255;
        return vec3((double)255 / 255, (double)20 / 255, (double)147 / 255);
        break;
    case 3:
        cout << endl
             << "r" << r << " " << (double)255 / 255 << (double)0 / 255 << (double)0 / 255;
        return vec3((double)255 / 255, (double)0 / 255, (double)0 / 255);
        break;
    case 4:
        cout << endl
             << "r" << r << " " << (double)255 / 255 << (double)69 / 255 << (double)0 / 255;
        return vec3((double)255 / 255, (double)69 / 255, (double)0 / 255);
        break;
    case 5:
        cout << endl
             << "r" << r << " " << (double)255 / 255 << (double)255 / 255 << (double)0 / 255;
        return vec3((double)255 / 255, (double)255 / 255, (double)0 / 255);
        break;
    case 6:
        cout << endl
             << "r" << r << " " << (double)0 / 255 << (double)0 / 255 << (double)255 / 255;
        return vec3((double)0 / 255, (double)0 / 255, (double)255 / 255);
        break;
    case 7:
        cout << endl
             << "r" << r << " " << (double)0 / 255 << (double)191 / 255 << (double)255 / 255;
        return vec3((double)0 / 255, (double)191 / 255, (double)255 / 255);
        break;
    case 8:
        cout << endl
             << "r" << r << " " << (double)0 / 255 << (double)0 / 255 << (double)128 / 255;
        return vec3((double)0 / 255, (double)0 / 255, (double)128 / 255);
        break;
    case 9:
        cout << endl
             << "r" << r << " " << (double)255 / 255 << (double)0 / 255 << (double)255 / 255;
        return vec3((double)255 / 255, (double)0 / 255, (double)255 / 255);
        break;
    case 10:
        cout << endl
             << "r" << r << " " << (double)148 / 255 << (double)0 / 255 << (double)211 / 255;
        return vec3((double)148 / 255, (double)0 / 255, (double)211 / 255);
        break;
    case 11:
        cout << endl
             << "r" << r << " " << (double)0 / 255 << (double)255 / 255 << (double)255 / 255;
        return vec3((double)0 / 255, (double)255 / 255, (double)255 / 255);
        break;
    case 12:
        cout << endl
             << "r" << r << " " << (double)73 / 255 << (double)255 / 255 << (double)47 / 255;
        return vec3((double)73 / 255, (double)255 / 255, (double)47 / 255);
        break;
    case 13:
        cout << endl
             << "r" << r << " " << (double)4 / 255 << (double)139 / 255 << (double)34 / 255;
        return vec3((double)4 / 255, (double)139 / 255, (double)34 / 255);
        break;
    case 14:
        cout << endl
             << "r" << r << " " << (double)238 / 255 << (double)130 / 255 << (double)238 / 255;
        return vec3((double)238 / 255, (double)130 / 255, (double)238 / 255);
        break;
    }
    return vec3(1, 0, 0);
}
texture *checker = new checker_texture(
    new constant_texture(vec3(0.2, 0.3, 0.1)),
    new constant_texture(vec3(0.9, 0.9, 0.9)));
hitable *ballscene()
{
    texture *pertext = new noise_texture(10);
    hitable **list = new hitable *[2];
    list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(pertext));
    list[1] = new sphere(vec3(0, 1, 0), 1, new lambertian(pertext));

    return new hitable_list(list, 2);
}
hitable *random_scene()
{

    const int n = 500;
    hitable **list = new hitable *[n + 1];
    list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(checker));
    int i = 1;
    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            const double choose_mat = myrand;
            const vec3 center(a + 5 * myrand, 0.2, b + 1.5 * myrand);
            if ((center - vec3(4, 0.2, 0)).length() > 0.9)
            {
                if (choose_mat < 0.62)
                {
                    list[i++] = new sphere(center, vec3(center.e[0], center.e[1] + 0.5 * myrand, center.e[2]), 0.0, 1.0, 0.2, new lambertian(new constant_texture(getMyRandomColor())));
                }
                else if (choose_mat < 0.88)
                {
                    list[i++] = new sphere(center, center + 0.5 * myrand, 0.0, 0.0, 0.2, new metal_mat(getMyRandomColor(), 0.2 * myrand));
                }
                else
                {
                    list[i++] = new sphere(center, center + 0.5 * myrand, 0.0, 0.0, 0.2, new dielectric(1.5));
                }
            }
        }
    }
    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(new constant_texture(vec3(0.4, 0.2, 0.1))));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal_mat(vec3(0.7, 0.6, 0.5), 0.0));
    // return new hitable_list(list,i);
    return new bvh_node(list, i, 0.0, 1.0);
}
vec3 colorF2(const ray &r, const hitable *const world, const std::uint_fast8_t depth)
{

    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec))
    {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * colorF2(scattered, world, depth + 1);
        }
        return zeroVector;
    }
    else
    {
        // unit_direction = unit_vector(r.direction);
        // t = 0.5*unit_vector(r.direction).e[1] + 0.5;
        // return (1.0-t)*oneVector + t*fixedColor;
        return oneVector;
    }
    // else return r.simpleReturnV;
}

int main(int argc, const char *argv[])
{

    // Open a file in writing mode
    fptr = fopen("image.ppm", "w");

    double u, v;
    ray r;

    hitable *world = ballscene();

    const int nx = 2000;
    const int ny = 1000;
    const int ns = 1;
    const double doubleNX = double(nx);
    const double doubleNY = double(ny);
    const double doubleNS = double(ns);
    const double aspect_ratio = doubleNX / doubleNY;
    const vec3 lookFrom(13, 2, 3);
    const vec3 lookAt(0, 0, 0);
    const vec3 vup(0, 1, 0);
    const double dist_to_focus = (lookFrom - lookAt).length();
    const double aperture = 0.0;

    // std::cout<<"P3\n" << nx <<" "<< ny << "\n255\n";
    printInitialPPMCodeToFile(nx, ny);

    std::int_fast16_t i = 0, j = ny - 1;
    int ir, ig, ib;
    vec3 col(0, 0, 0);

    camera cam(lookFrom, lookAt, vup, 20, aspect_ratio, aperture, dist_to_focus, 0, 1);
    ray r1;
    auto start = std::chrono::high_resolution_clock::now();
    while (j >= 0)
    {
        v = double(j) / doubleNY;
        std::clog << "\rScanlines remaining: " << v * 100.0 << '\%' << std::flush;
        while (i < nx)
        {
            col.e[0] = col.e[1] = col.e[2] = 0.0;

            for (int s = 0; s < ns; s++)
            {
                u = double(i + myrand) / doubleNX;
                v = double(j + myrand) / doubleNY;
                r1 = cam.get_ray(u, v);
                col += colorF2(r1, world, 0);
            }
            col /= doubleNS;
            ir = int(255.99 * sqrt(col[0]));
            ig = int(255.99 * sqrt(col[1]));
            ib = int(255.99 * sqrt(col[2]));

            printToFile(ir, ig, ib);
            i++;
        }
        j--;
        i = 0;
    }

    std::clog << "\rDone.                 \n";
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::clog << "Elapsed time: " << elapsed.count() << " s\n";
    fclose(fptr);
    return 0;
}
