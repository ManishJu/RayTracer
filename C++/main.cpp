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
#include "image_texture.hpp"
#include "diffuse_light.hpp"
#include "xy_rect.hpp"
#include "yz_rect.hpp"
#include "xz_rect.hpp"
#include "box.hpp"
#include "flip_normals.hpp"
#include "texture.hpp"
#include "constant_medium.hpp"
#include "translate.hpp"
#include "rotate_y.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"

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

hitable *cornell_smoke() {
    hitable **list = new hitable*[8];
    int i = 0;
    material *red = new lambertian( new constant_texture(vec3(0.65, 0.05, 0.05)) );
    material *white = new lambertian( new constant_texture(vec3(0.73, 0.73, 0.73)) );
    material *green = new lambertian( new constant_texture(vec3(0.12, 0.45, 0.15)) );
    material *light = new diffuse_light( new constant_texture(vec3(4)) );
    list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
    list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
    list[i++] = new xz_rect(113, 443, 127, 432, 554, light);
    list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
    list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));
    hitable *b1 = new translate(new rotate_y(new box(vec3(0, 0, 0), vec3(165, 165, 165), white), -18), vec3(130,0,65));
    hitable *b2 = new translate(new rotate_y(new box(vec3(0, 0, 0), vec3(165, 330, 165), white),  15), vec3(265,0,295));
    list[i++] = new constant_medium(b1, 0.01, new constant_texture(vec3(1.0, 1.0, 1.0)));
    list[i++] = new constant_medium(b2, 0.01, new constant_texture(vec3(0.0, 0.0, 0.0)));
    return new hitable_list(list,i);
}

hitable *earth() {
    int nx, ny, nn;
    //unsigned char *tex_data = stbi_load("tiled.jpg", &nx, &ny, &nn, 0);
    unsigned char *tex_data = stbi_load("earthmap.jpg", &nx, &ny, &nn, 0);
    material *mat =  new lambertian(new image_texture(tex_data, nx, ny));
    return new sphere(vec3(0,0, 0), 2, mat);
}

hitable *two_spheres() {
    texture *checker = new checker_texture( new constant_texture(vec3(0.2,0.3, 0.1)), new constant_texture(vec3(0.9, 0.9, 0.9)));
    int n = 50;
    hitable **list = new hitable*[n+1];
    list[0] =  new sphere(vec3(0,-10, 0), 10, new lambertian( checker));
    list[1] =  new sphere(vec3(0, 10, 0), 10, new lambertian( checker));

    return new hitable_list(list,2);
}

hitable *final() {
    int nb = 20;
    hitable **list = new hitable*[30];
    hitable **boxlist = new hitable*[10000];
    hitable **boxlist2 = new hitable*[10000];
    material *white = new lambertian( new constant_texture(vec3(0.73, 0.73, 0.73)) );
    material *red = new lambertian( new constant_texture(vec3(0.99, 0.13, 0.13)) );

    material *ground = new lambertian( new constant_texture(vec3(0.48, 0.83, 0.53)) );
    int b = 0;
    for (int i = 0; i < nb; i++) {
        for (int j = 0; j < nb; j++) {
            float w = 100;
            float x0 = -1000 + i*w;
            float z0 = -1000 + j*w;
            float y0 = 0;
            float x1 = x0 + w;
            float y1 = 100*(drand48()+0.01);
            float z1 = z0 + w;
            boxlist[b++] =  new box(vec3(x0,y0,z0), vec3(x1,y1,z1), new lambertian( new constant_texture(getMyRandomColor()*0.5+0.5) ));
        }
    }
    int l = 0;
    list[l++] = new bvh_node(boxlist, b, 0, 1);
    material *light = new diffuse_light( new constant_texture(vec3(4)) );
    list[l++] = new xz_rect(23, 523, 47, 512, 554, light);
    //auto b2 =new sphere(vec3(265, 100, 295), 3000, red); // new translate(new rotate_y(new box(vec3(0, 0, 0), vec3(165, 330, 165), white),15),vec3(265,0,295));

    //list[l++] = new constant_medium(b2, 0.0001, new constant_texture(vec3(1, 0.0, 0.0)));

    vec3 center(400, 400, 200);
    list[l++] = new sphere(center, center+vec3(30, 0, 0), 0, 1, 50, new lambertian(new constant_texture(vec3(0.7, 0.3, 0.1))));
    list[l++] = new sphere(vec3(260, 150, 45), 50, new dielectric(1.5));
    list[l++] = new sphere(vec3(0, 150, 145), 50, new metal_mat(vec3(0.8, 0.8, 0.9), 10.0));
    hitable *boundary = new sphere(vec3(360, 150, 145), 70, new dielectric(1.5));
    list[l++] = boundary;
    list[l++] = new constant_medium(boundary, 0.2, new constant_texture(vec3(1.0, 0.35, 0.0)));
    boundary = new sphere(vec3(0, 0, 0), 5000, new dielectric(1.5));
    list[l++] = new constant_medium(boundary, 0.0001, new constant_texture(vec3(1.0, 1.0, 1.0)));
    int nx, ny, nn;
    unsigned char *tex_data = stbi_load("earthmap.jpg", &nx, &ny, &nn, 0);
    material *emat =  new lambertian(new image_texture(tex_data, nx, ny));
    list[l++] = new sphere(vec3(400,200, 400), 100, emat);
    texture *pertext = new noise_texture();
    list[l++] =  new sphere(vec3(220,280, 300), 80, new lambertian( pertext ));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxlist2[j] = new sphere(vec3(165*drand48(), 165*drand48(), 165*drand48()), 10, new lambertian( new constant_texture(getMyRandomColor()) ));
    }
    list[l++] =   new translate(new rotate_y(new bvh_node(boxlist2,ns, 0.0, 1.0), 15), vec3(-100,270,395));
    return new hitable_list(list,l);
}
hitable *ballscene()
{
    int i = 0;
    const int hit_amount = 8;
    
    //    unsigned char *tex_data = stbi_load("earthmap.jpg", &nx, &ny, &nn, 0);
    //    material *mat = new lambertian(new image_texture(tex_data, nx, ny));
    //    material *mat2 = new diffuse_light(new constant_texture(vec3(10)));
    //    texture *pertext = new noise_texture(10);

    material *red = new lambertian(new constant_texture(vec3(0.65, 0.05, 0.05)));
    material *light = new diffuse_light(new constant_texture(vec3(1)));
    material *green = new lambertian(new constant_texture(vec3(0.12, 0.45, 0.15)));
    material *white = new lambertian(new constant_texture(vec3(0.73)));
    hitable **list = new hitable *[hit_amount];
    // list[0] = new sphere(vec3(0, -1001, 0), 1000, new lambertian(pertext));
    // list[1] = new sphere(vec3(0, 0, 0), 1,  new lambertian(pertext));
    // list[2] = new xz_rect(-3,-1,0,2,1, mat2);

    list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
    list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
    list[i++] = new xz_rect(113, 443, 127, 432, 554, light);
    list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
    list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));

    auto b1 = new translate(new rotate_y(new box(vec3(0, 0, 0), vec3(165, 165, 165), white),-18),vec3(130,0,65));
    auto b2 = new translate(new rotate_y(new box(vec3(0, 0, 0), vec3(165, 330, 165), white),15),vec3(265,0,295));

    list[i++] = new constant_medium(b1, 0.01, new constant_texture(vec3(1.0)));
    list[i++] = new constant_medium(b2, 0.01, new constant_texture(vec3(1.0)));

    // list[0] = new yz_rect(0,555,0,555,0,red);
    // list[1] = new xz_rect(0,555,0,555,0,red);
    // list[2] = new xz_rect(213,343,227,332,554,light);

    // list[2] = new sphere(vec3(0, 2.5, 0), 1, mat2);

    return new hitable_list(list, hit_amount);
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
        vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return emitted + attenuation * colorF2(scattered, world, depth + 1);
        }
        return emitted;
    }
    else
    {
        // unit_direction = unit_vector(r.direction);
        // t = 0.5*unit_vector(r.direction).e[1] + 0.5;
        // return (1.0-t)*oneVector + t*fixedColor;
        return zeroVector;
    }
    // else return r.simpleReturnV;
}

int main(int argc, const char *argv[])
{

    // Open a file in writing mode
    fptr = fopen("image.ppm", "w");

    double u, v;
    ray r;

    hitable *world = final();

    const int nx = 1000;
    const int ny = 900;
    const int ns = 20;
    const double doubleNX = double(nx);
    const double doubleNY = double(ny);
    const double doubleNS = double(ns);
    const double inverseDoubleNX = 1 / double(nx);
    const double inverseDoubleNY = 1 / double(ny);
    const double aspect_ratio = doubleNX / doubleNY;
    const vec3 lookFrom(478, 278, -670);
    const vec3 lookAt(278, 278, 0);
    const vec3 vup(0, 1, 0);
    const double dist_to_focus = 10; //(lookFrom - lookAt).length();
    const double aperture = 0.0;
    const double vfov = 40.0;
    // std::cout<<"P3\n" << nx <<" "<< ny << "\n255\n";
    printInitialPPMCodeToFile(nx, ny);

    std::int_fast16_t i = 0, j = ny - 1;
    int ir, ig, ib;
    vec3 col(0, 0, 0);

    camera cam(lookFrom, lookAt, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0, 1);
    ray r1;
    auto start = std::chrono::high_resolution_clock::now();
    while (j >= 0)
    {
        v = double(j) / doubleNY;
        std::clog << "\rScanlines remaining: " << v * 100.0 << '\%' << std::flush;
        while (i < nx)
        {
            //            col.e[0] = col.e[1] = col.e[2] = 0.0;
            //            u = double(i)/doubleNX;
            //            //v = double(j)/doubleNY;
            //            for (int s = 0; s < ns; s++)
            //            {
            //
            //                r1 = cam.get_ray(u + myrand*inverseDoubleNX, v + myrand*inverseDoubleNY);
            //                col += colorF2(r1, world, 0);
            //            }
            //            col /= doubleNS;
            //            ir = int(255.99 * sqrt(col[0]));
            //            ig = int(255.99 * sqrt(col[1]));
            //            ib = int(255.99 * sqrt(col[2]));
            //
            //            printToFile(ir, ig, ib);
            //            i++;
            //            if(i >= nx) break;
            //
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
