/*----------------------------------------------------------
* The Cylinder class
* This is a subclass of Object, and hence implements the
* methods intersect() and normal().
-------------------------------------------------------------*/

#include "Cylinder.h"
#include <math.h>

float Cylinder::intersect(glm::vec3 position, glm::vec3 dir)
{
    glm::vec3 d = position - center;
    float a = (dir.x * dir.x) + (dir.z * dir.z);
    float b = 2 * (dir.x * d.x + dir.z * d.z);
    float c = d.x * d.x + d.z * d.z - (radius * radius);
    
    float delta = (b*b - (4*a*c));
    
    if(delta < 0.0){
        return -1.0;
    }
    
    if((fabs(delta)) < 0.001)
    {
        return -1.0;
    }
         
    float small, big, t_1 = (-b - sqrt(delta))/(2 * a), t2 = (-b + sqrt(delta))/(2 * a);
 
    if(t_1<0.01){
        t_1=-1;
    }
    if(t2<0.01){
        t2=-1;
    }

 
    if (t_1>t2){
        small = t2;
        big=t_1;
    }else{
        small = t_1;
        big=t2;
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


glm::vec3 Cylinder::normal(glm::vec3 position)
{
    glm::vec3 d = position - center;
    glm::vec3 normalization = glm::vec3 (d.x,0,d.z);
    normalization = glm::normalize(normalization); //normalize
    return normalization;

}
