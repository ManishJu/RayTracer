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
#include "sphere.hpp"
#include "metal_mat.hpp"
#include "lambertian.hpp"
#include "dielectric.hpp"


using namespace std;
typedef std::string str;

#define myrand ((double) rand() / (RAND_MAX))

FILE *fptr;
ray scattered;
vec3 attenuation;
hit_record rec;
vec3 unit_direction;
double t;

const vec3 oneVector(1.0);
const vec3 zeroVector(0.0);

void printToFile(int r, int g, int b){
    
    fprintf(fptr,"%d",r);
    fprintf(fptr,"%s"," ");
    fprintf(fptr,"%d",g);
    fprintf(fptr,"%s"," ");
    fprintf(fptr,"%d",b);
    fprintf(fptr,"%s"," ");
    fprintf(fptr,"%s","\n");

}

void printInitialPPMCodeToFile(int nx, int ny){
   
    fprintf(fptr,"%s","P3\n");
    fprintf(fptr,"%d",nx);
    fprintf(fptr,"%s"," ");
    fprintf(fptr,"%d",ny);
    fprintf(fptr,"%s","\n255\n");
}

hitable* random_scene(){
    const int n = 500;
    hitable **list = new hitable*[n+1];
    list[0] = new sphere(vec3(0,-1000,0),1000,new lambertian(vec3(0.5,0.5,0.5)));
    int i = 1;
    for(int a = -11; a<11; a++){
        for(int b = -11; b<11; b++){
            const double choose_mat = myrand;
            const vec3 center(a+1.5*myrand,0.2,b+1.5*myrand);
            if((center-vec3(4,0.2,0)).length()>0.9){
                if(choose_mat < 0.66){
                    list[i++] = new sphere(center,0.2,new lambertian(vec3(myrand*myrand,myrand*myrand,myrand*myrand)));
                }
                else if(choose_mat < 0.88){
                    list[i++] = new sphere(center,0.2,new metal_mat(vec3(0.5*(1+myrand),0.5*(1+myrand),0.5*(1+myrand)),0.5*myrand));
                }
                else {
                    list[i++] = new sphere(center,0.2,new dielectric(1.5));
                }
            }
        }
    }
    list[i++] = new sphere(vec3(0,1,0),1.0,new dielectric(1.5));
    list[i++] = new sphere(vec3(-4,1,0),1.0,new lambertian(vec3(0.4,0.2,0.1)));
    list[i++] = new sphere(vec3(4,1,0),1.0,new metal_mat(vec3(0.7,0.6,0.5),0.0));
    return new hitable_list(list,i);
}
vec3 colorF2(const ray& r,const hitable* const world,const std::uint_fast8_t depth){
    
    hit_record rec;
    if(world->hit(r,0.001,MAXFLOAT, rec)){
        ray scattered;
        vec3 attenuation;
        if(depth < 50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered)){
            return attenuation*colorF2(scattered,world,depth+1);
        }
        return zeroVector;
    }
    else {
         unit_direction = unit_vector(r.direction());
         t = 0.5*unit_direction.y() + 0.5;
        return (1.0-t)*oneVector + t*vec3(0.5,0.7,1.0);
    }
}

int main(int argc, const char * argv[]) {
    
    // Open a file in writing mode
    fptr = fopen("image.ppm", "w");
   
    vec3 col;
    double u,v;
    ray r;

    const vec3 sphereCenter(0,0,-1);
    const vec3 sphereCenter2(0,-100.5,-1);
    const vec3 sphereCenter3(1,0,-1);
    const vec3 sphereCenter4(-1,0,-1);
    const double R = cos(M_PI/4);
     const int list_size = 5;
     hitable *list[list_size];
     list[0] =  new sphere(sphereCenter,0.5, new lambertian(vec3(0.8,0.3,0.3)));
     list[1] = new  sphere(sphereCenter2,100,new lambertian(vec3(0.8,0.8,0.0)));
     list[2] = new sphere(sphereCenter3,0.5,new metal_mat(vec3(0.8,0.6,0.2),0.3));
     list[3] = new sphere(sphereCenter4,0.5,new dielectric(1.5));
     list[4] = new sphere(sphereCenter4,-0.48,new dielectric(1.5));

//    const int list_size = 2;
//    hitable *list[list_size];
//    list[0] =  new sphere(vec3(-R,0,-1),R, new lambertian(vec3(0,0,1)));
//    list[1] =  new sphere(vec3(R,0,-1),R, new lambertian(vec3(1,0,0)));
//    hitable *world = new hitable_list(list,list_size);
    hitable *world = random_scene();
    
    const int nx = 4000;
    const int ny = 2000;
    const int ns = 256;
    const double doubleNX = double(nx);
    const double doubleNY = double(ny);
    const double doubleNS = double(ns);
    const double aspect_ratio = doubleNX/doubleNY;
    const vec3 lookFrom(11,2,10);
    const vec3 lookAt(0,0,0);
    const vec3 vup(0,1,0);
    const double dist_to_focus = (lookFrom-lookAt).length();
    const double aperture = 0.05;
    //std::cout<<"P3\n" << nx <<" "<< ny << "\n255\n";
    
    printInitialPPMCodeToFile(nx,ny);

    std::int_fast16_t i = 0,j = ny-1;
    int ir, ig, ib;

    camera cam(lookFrom,lookAt,vup,20,aspect_ratio,aperture,dist_to_focus);
    ray r1;
    
    while(j >= 0){
        v = double(j)/doubleNY;
       std::clog << "\rScanlines remaining: " << v*100.0 << '\%' << std::flush;
        while(i < nx){
            
            vec3 col(0,0,0);
            for( int s= 0; s< ns; s++){
                u = double(i + ((double) rand() / (RAND_MAX)))/doubleNX;
                v = double(j + ((double) rand() / (RAND_MAX)))/doubleNY;
                r1 = cam.get_ray(u,v);
                //vec3 p = r.point_at_parameter(2.0);
                col += colorF2(r1,world,0);
            }
            col /= doubleNS;
             ir = int(255.99*sqrt(col[0]));
             ig = int(255.99*sqrt(col[1]));
             ib = int(255.99*sqrt(col[2]));
            
            //cout<<ir<<" "<<ig<<endl;
            printToFile(ir, ig, ib);
            i++;
        
        }
        j--;
        i = 0;
    }

    std::clog << "\rDone.                 \n";
    fclose(fptr);
    return 0;
}
