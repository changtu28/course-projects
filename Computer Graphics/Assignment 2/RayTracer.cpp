/*____________________________________________________________
* COSC 363 Ray Tracer
* Date: 31/05/2019
* Author: Chang Tu
* ID: 57224976
* Build Command: g++ -Wall -o "%e" RayTracer.cpp Ray.cpp SceneObject.cpp Cone.cpp Cylinder.cpp Plane.cpp Sphere.cpp TextureBMP.cpp -lm -lGL -lGLU -lglut
*____________________________________________________________
*/


#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <cmath>
#include "SceneObject.h"
#include "Ray.h"
#include "Plane.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Cone.h"
#include <GL/glut.h>
#include "TextureBMP.h"

using namespace std;
const float WIDTH = 20.0, HEIGHT = 20.0, EDIST = 40.0, NUMDIV = 500;
const int MAX_STEPS = 5;
const float XMIN = -WIDTH * .5, XMAX =  WIDTH * .5;
const float YMIN = -HEIGHT * .5, YMAX =  HEIGHT * .5;
//const float _eta_ = 2.5;
const float _eta_ = 1.003;
TextureBMP texture1, texture2;
vector<SceneObject*> sceneObjects;


// _______________________ Ray tracer ____________________________________________________________
glm::vec3 tracer(Ray ray, int step)
{
    glm::vec3 background_color(0);
    glm::vec3 light_1(-10.0, 15, -5.0), light_2(16.0, 16, 0);
    glm::vec3 white(1);
    glm::vec3 specular_1(0),specular_2(0);
    glm::vec3 color_sum(0),anbient_color(0.2);

    float light1_intensity = 0.5,f = 100.0,transparency = 0.2;

    ray.closestPt(sceneObjects);

    if(ray.xindex == -1) return background_color;

    glm::vec3 color = sceneObjects[ray.xindex]->getColor();
    glm::vec3 normal_vec = sceneObjects[ray.xindex]->normal(ray.xpt);
    glm::vec3 light_vec_1 = light_1 - ray.xpt, light_vec_2 = light_2 - ray.xpt;

    float light_dist_1 = glm::length(light_vec_1), light_dist_2 = glm::length(light_vec_2);

    light_vec_1=glm::normalize(light_vec_1), light_vec_2=glm::normalize(light_vec_2);

    float lDotn_1 = glm::dot(light_vec_1,normal_vec), lDotn_2 = glm::dot(light_vec_2,normal_vec);

    glm::vec3 reflect_vector_1 = glm::reflect(-light_vec_1, normal_vec);  
    glm::vec3 reflect_vector_2 = glm::reflect(-light_vec_2, normal_vec);


    float rDotv_1 = glm::dot(reflect_vector_1,-ray.dir), rDotv_2 = glm::dot(reflect_vector_2,-ray.dir);
    rDotv_1 = max(rDotv_1, 0.0f), rDotv_2 = max(rDotv_1, 0.0f);

//__________________floor texture____________________________________________________________________
    if(ray.xindex == 0) {
        int modulo_x = (int)((ray.xpt.x + 50) /2) % 2, modulo_z = (int)((ray.xpt.z + 200) /2) % 2;

        if((modulo_x && modulo_z) || (!modulo_x && !modulo_z)) {
            color = glm::vec3(0.2,0.2,0.2);
        }
        else {
            color = glm::vec3(1,1,1);
        }
    }

//____________background texture__________________________________________________________________________
    if(ray.xindex == 1)
    {
        float s = (ray.xpt.x+50)/100, t = (ray.xpt.y+20)/70;
        color = texture1.getColorAt(s,t);
    }

//_____________Cone texture_________________________________________________________________________
    if(ray.xindex == 3)
    {
        if ((int(ray.xpt.x+ray.xpt.y-13) % 2 == 0)) {
            color = glm::vec3(1.00,0.25,0.35);
            
        } else {
            color = glm::vec3(0.95,1.00,0.66);
            //color = mix(glm::vec3(0.80,0.07,0.19), glm::vec3(0.,0.,0.),glm::vec3(0,0.00,0.0));
            
        }
    }

//_________________Sun texture_____________________________________________________________________

    if (ray.xindex == 5)
    {
        glm::vec3 center(2.5, 5., -70.0), d=glm::normalize(ray.xpt-center);
        float u=(0.5-atan2(d.z,d.x)+M_PI)/(2*M_PI), v=0.5+asin(d.y)/M_PI;
        color = texture2.getColorAt(u, v);
    }

//_________________ Shadow _____________________________________________________________________

    Ray shadow_1(ray.xpt,light_vec_1);
    Ray shadow_2(ray.xpt,light_vec_2);
    
    shadow_1.closestPt(sceneObjects);
    shadow_2.closestPt(sceneObjects);

    if (rDotv_1>=0) {
        specular_1 = pow(rDotv_1,f)*white;
    }

    if (((shadow_1.xindex>-1)&&(shadow_1.xdist < light_dist_1))||(lDotn_1<=0 )) {
        color_sum = anbient_color*color;
        if(shadow_1.xindex == 6) {
            color_sum += (lDotn_1*color + specular_1)*glm::vec3(0.2)+sceneObjects[6]->getColor()*glm::vec3(0.0251);
        } 
    } else {
        color_sum=anbient_color*color + (lDotn_1*color + specular_1)*light1_intensity;

    }

    if (rDotv_2>=0) {
        specular_2 = pow(rDotv_2,f)*white;
    }

    if ((lDotn_2<=0 )||((shadow_2.xindex>-1)&&(shadow_2.xdist < light_dist_2))) {
        color_sum += color*anbient_color;
        if(shadow_2.xindex == 6) {
            color_sum +=(lDotn_2*color + specular_2)*glm::vec3(0.15) + sceneObjects[6]->getColor()*glm::vec3(0.0135); 
        }
    } else {
        color_sum+=anbient_color*color + (lDotn_2*color + specular_2)*(1-light1_intensity);

    }


//____________________Reflection__________________________________________________________________

    if((ray.xindex == 6) && (step < MAX_STEPS)) {
        glm::vec3 refraction_direction_1 = glm::refract(ray.dir,normal_vec,1.f/_eta_);
        Ray refraction_ray_1(ray.xpt,refraction_direction_1);
        refraction_ray_1.closestPt(sceneObjects);
        if(refraction_ray_1.xindex==-1) {
            return background_color;
        }
        glm::vec3 normal_vector_2 = sceneObjects[refraction_ray_1.xindex]->normal(refraction_ray_1.xpt);
        glm::vec3 refraction_direction_2 = glm::refract(refraction_direction_1, -normal_vector_2, _eta_);
        Ray refraction_ray_2(refraction_ray_1.xpt,refraction_direction_2);
        refraction_ray_2.closestPt(sceneObjects);
        if(refraction_ray_2.xindex==-1) {
            return background_color;
        }
        glm::vec3 refraction_color_2 = tracer(refraction_ray_2, step+1);
        color_sum = color_sum * transparency + refraction_color_2*(1-transparency);  

        return color_sum;
    }
    
    if((ray.xindex == 0||ray.xindex ==4) &&(step < MAX_STEPS)) {   
        glm::vec3 Dir_reflection = glm::reflect(ray.dir, normal_vec);
        Ray ray_ref(ray.xpt, Dir_reflection);
        glm::vec3 refraction_color_1 = tracer(ray_ref, step+1);  
        color_sum = color_sum + (0.6f*refraction_color_1);
    }

    return color_sum;
}


//________________Anti Aliasing______________________________________________________________________
glm::vec3 antiAliasing(glm::vec3 eye_pos, float pixel_size, float x_pos, float y_pos) {
    float one_over_four = pixel_size * 0.25, three_over_four = pixel_size * 0.75;

    glm::vec3 color_sum(0), average(0.25);

    Ray ray = Ray(eye_pos, glm::vec3(x_pos + one_over_four, y_pos + one_over_four, -EDIST));
    ray.normalize();
    color_sum= color_sum+tracer(ray,1);

    ray = Ray(eye_pos, glm::vec3(x_pos + one_over_four, y_pos + three_over_four, -EDIST));
    ray.normalize();
    color_sum= color_sum+tracer(ray,1);

    ray = Ray(eye_pos, glm::vec3(x_pos + three_over_four, y_pos + one_over_four, -EDIST));
    ray.normalize();
    color_sum= color_sum+tracer(ray,1);

    ray = Ray(eye_pos, glm::vec3(x_pos + three_over_four, y_pos + three_over_four, -EDIST));
    ray.normalize();
    color_sum= color_sum+tracer(ray,1);
    
    
    
    //// Anti Aliasing not being used testing 
    //float one_over_two =  pixel_size * 0.5;
    //Ray ray = Ray(eye_pos, glm::vec3(x_pos + one_over_two, y_pos + one_over_two, -EDIST));
    //ray.normalize();
    //color_sum= color_sum+tracer(ray,1);    
    
    //ray = Ray(eye_pos, glm::vec3(x_pos + one_over_two, y_pos + one_over_two, -EDIST));
    //ray.normalize();
    //color_sum= color_sum+tracer(ray,1);    
    
    //ray = Ray(eye_pos, glm::vec3(x_pos + one_over_two, y_pos + one_over_two, -EDIST));
    //ray.normalize();
    //color_sum= color_sum+tracer(ray,1);    
    
    //ray = Ray(eye_pos, glm::vec3(x_pos + one_over_two, y_pos + one_over_two, -EDIST));
    //ray.normalize();
    //color_sum= color_sum+tracer(ray,1);    
    
    
    
    
    
    
    
    
    color_sum= color_sum*average;

    return color_sum;

}

//______________________________________________________________________________________

//_____The display module displays the ray traced image by drawing________
//______________________________________________________________________________________
void display()
{
    float x_pos, y_pos;
    float cell_x = (XMAX-XMIN)/NUMDIV, cell_y = (YMAX-YMIN)/NUMDIV;

    glm::vec3 eye_pos(0., 0., 0.);  //The eye_pos 

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glFogi(GL_FOG_MODE,GL_LINEAR);
    glFogf(GL_FOG_START, -2000);
    glFogf(GL_FOG_END, 2000);
    
    float color[]={.5, .5, .5,1};
    glFogfv(GL_FOG_COLOR, color);
    

    glBegin(GL_QUADS);

    for(int i = 0; i < NUMDIV; i++)
    {
        x_pos = XMIN + i*cell_x;
        for(int j = 0; j < NUMDIV; j++)
        {
            y_pos = YMIN + j*cell_y;

            glm::vec3 dir(x_pos+0.5*cell_x, y_pos+0.5*cell_y, -EDIST);

            Ray ray = Ray(eye_pos, dir);
            ray.normalize();  

            glm::vec3 color = antiAliasing(eye_pos,cell_x,x_pos,y_pos); 

            glColor3f(color.r, color.g, color.b);
            glVertex2f(x_pos, y_pos);
            glVertex2f(x_pos+cell_x, y_pos);
            glVertex2f(x_pos+cell_x, y_pos+cell_y);
            glVertex2f(x_pos, y_pos+cell_y);
        }
    }

    glEnd();
    glFlush();
}


void initialize()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(XMIN, XMAX, YMIN, YMAX);
    

    glClearColor(0, 0, 0, 1);
    texture1 = TextureBMP((char*)"bkground.bmp"), texture2 = TextureBMP((char*)"sun.bmp");

//____________________Create Fog______________________________________________________________________________________

    //glEnable(GL_FOG);
    glClearColor(0.5f, 0.5f, 0.5f, 1);

    glm::vec3 point_A = glm::vec3(-50., -20, -40), point_B = glm::vec3(50., -20, -40);
    glm::vec3 point_C = glm::vec3(50., -20, -200), point_D = glm::vec3(-50., -20, -200);
    glm::vec3 point_E = glm::vec3(50., 50, -200), point_F = glm::vec3(-50., 50, -200);
    
//____________________Create Objects______________________________________________________________________________________
    Plane *floor = new Plane (point_A, point_B, point_C, point_D, glm::vec3(0.8));
    sceneObjects.push_back(floor);   //      0
    
    Plane *wall = new Plane(point_D, point_C, point_E, point_F, glm::vec3(1,1,1));
    sceneObjects.push_back(wall);     //      1
    
    Cylinder *cylinder = new Cylinder(glm::vec3(-12, -10, -70), 3, 3.0, glm::vec3(1.,1.,.4));
    sceneObjects.push_back(cylinder); //      2
    
    Cone *cone = new Cone(glm::vec3(12.5, -10., -80.0), 5, 10., glm::vec3(1, 0.7529, 0.7961));
    sceneObjects.push_back(cone);     //      3
    
    Sphere *blue_sphere = new Sphere(glm::vec3(-5., -8., -105.0), 10., glm::vec3(.4,.6,1.));//blue
    sceneObjects.push_back(blue_sphere);   //      4
    
    Sphere *sun = new Sphere(glm::vec3(2.5, 5., -70.0), 3, glm::vec3(0.9, 1.0, .98));//sun
    sceneObjects.push_back(sun);  //      5
    
    Sphere *sph_3 = new Sphere(glm::vec3(0, -10., -68.0), 6, glm::vec3(0.9, 1.0, .98));
    sceneObjects.push_back(sph_3);  //      6


//____________________Create Cube______________________________________________________________________________________
    float x_axis=7, y_axis=-13., z_axis=-60., length=5, width=5, height=5;
    glm::vec3 color = glm::vec3(1, 0.73545, 0.205485);
    glm::vec3 point_a = glm::vec3(x_axis,y_axis,z_axis), point_b = glm::vec3(x_axis+length,y_axis,z_axis);
    glm::vec3 point_c = glm::vec3(x_axis+length,y_axis+height,z_axis), point_d = glm::vec3(x_axis,y_axis+height,z_axis);
    glm::vec3 point_e = glm::vec3(x_axis+length,y_axis,z_axis-width), point_f = glm::vec3(x_axis+length,y_axis+height,z_axis-width);
    glm::vec3 point_g = glm::vec3(x_axis,y_axis+height,z_axis-width), point_h = glm::vec3(x_axis,y_axis,z_axis-width);

    Plane *face_1 = new Plane(point_a,point_b,point_c,point_d,color); 
    sceneObjects.push_back(face_1);
    
    Plane *face_2 = new Plane(point_b,point_e,point_f,point_c,color);
    sceneObjects.push_back(face_2);
    
    Plane *face_3 = new Plane(point_e,point_h,point_g,point_f,color); 
    sceneObjects.push_back(face_3); 
    
    Plane *face_4 = new Plane(point_d,point_g,point_h,point_a,color);
    sceneObjects.push_back(face_4);
    
    Plane *face_5 = new Plane(point_d,point_c,point_f,point_g,color); 
    sceneObjects.push_back(face_5); 
    
    Plane *face_6 = new Plane(point_h,point_e,point_b,point_a,color);
    sceneObjects.push_back(face_6);

    
//____________________Create Tetrahedron______________________________________________________________________________________
    float x_axis_=-14,  y_axis_=-14,  z_axis_=-68,  l=7;
    glm::vec3 color_=glm::vec3(.605145, 1.0529, 0.60061);

    glm::vec3 point_a_ = glm::vec3(x_axis_+l/2, y_axis_, z_axis_ + sqrt(3.0f) * l/2 );
    glm::vec3 point_b_ = glm::vec3(x_axis_+l/2, y_axis_+sqrt(6.0f)/3.0f * l, z_axis_ + sqrt(3.0f) * l/4);
    glm::vec3 point_c_ = glm::vec3(x_axis_,y_axis_,z_axis_), point_d_ = glm::vec3(x_axis_+l,y_axis_,z_axis_);

    glm::vec3 line_cd = glm::vec3(x_axis_+l/2,y_axis_,z_axis_);
    glm::vec3 line_ab = glm::vec3((point_a_.x+point_b_.x)/2,(point_a_.y+point_b_.y)/2,(point_a_.z+point_b_.z)/2);

    Plane *face_1_ = new Plane(point_d_,point_b_,line_ab,point_a_,color_);
    sceneObjects.push_back(face_1_);
    Plane *face_2_ = new Plane(point_c_,point_b_,point_d_,line_cd,color_);
    sceneObjects.push_back(face_2_);
    Plane *face_3_ = new Plane(point_b_,point_c_,point_a_,line_ab,color_);
    sceneObjects.push_back(face_3_);
    Plane *face_4_ = new Plane(line_cd,point_d_,point_a_,point_c_,color_);
    sceneObjects.push_back(face_4_);
                                                      
}


int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("ray tracer application");
    glutDisplayFunc(display);
    initialize();
    glutMainLoop();
    return 0;
}
