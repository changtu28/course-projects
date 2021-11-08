//----------------------------------------------------------
//The file Cone.cpp
//
//implements the methods intersect() and normal().
//----------------------------------------------------------

#include "Cone.h"
#include <math.h>

float Cone::intersect(glm::vec3 position, glm::vec3 dir)
{   
    glm::vec3 distance = position - center;
    float yd = height - position.y + center.y;
    float stan = (radius / height) * (radius / height);
    float a = (dir.x * dir.x) + (dir.z * dir.z) - (stan*(dir.y * dir.y));
    float b = 2*(distance.x*dir.x + distance.z*dir.z + stan*yd*dir.y);
    float c = (distance.x*distance.x) + (distance.z*distance.z) - (stan*(yd*yd)), delta = b*b - 4*(a*c);
    
    if(fabs(delta) < 0.001){
        return -1.0;
    }    
    if(delta < 0.0){
         return -1.0;
    }
    
    float small, big, t_1 = (-b - sqrt(delta))/(2*a), t_2 = (-b + sqrt(delta))/(2*a);
  
    
    if(t_1<0.01){
        t_1=-1;
    }
    if(t_2<0.01){
        t_2=-1;
    }

 
    if (t_1>t_2){
        small = t_2;
        big=t_1;
    }else{
        small = t_1;
        big=t_2;
    }   

    float y_position = position.y + dir.y*small;
    if((y_position >= center.y) && (y_position <= center.y + height)){
        return small;
    }   
    else{
        float y_position = position.y + dir.y*big;
        if((y_position >= center.y) && (y_position <= center.y + height)){
            return big;
        }else{
            return -1.0;
    }
}

}


glm::vec3 Cone::normal(glm::vec3 position)
{
    glm::vec3 distance = position-center;
    float r = sqrt(distance.x * distance.x + distance.z * distance.z);
    glm::vec3 normalization= glm::vec3 (distance.x, r*(radius/height), distance.z);
    normalization=glm::normalize(normalization);
    return normalization;
}
