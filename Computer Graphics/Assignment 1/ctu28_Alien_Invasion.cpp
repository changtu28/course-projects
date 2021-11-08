//  ====================================================================
//  COSC363: Assignment 1 Alien Invasion!
//  Date:04/07/2019
//  Author: Chang Tu
//  ID: 57224976 
//  ====================================================================
 //______________________________________________________

#include <iostream>
#include <GL/freeglut.h>
#include <fstream>
#include "loadTGA.h"
#include "stdio.h"
#include "loadBMP.h"
#include "math.h"
#include "stdlib.h"
#include <climits>
#include <cmath> 

//______________________________________________________

float robot_walking_time=0, walking_r=105, walking_angle = 20.0;   
float view_angle = 10.0, self_rotate_angle=0;    
float view_angle_theta = 35;   
int direc=1;


float light_pos[4] = {19.98,89.8,9.7,0.9};     
float camer_eye_x_position = 1.98,  camer_eye_y_position = 20,  camer_eye_z_position = 100;   
float look_at_x_position = 1.98, look_at_y_position = 20.19, look_at_z_position = 80;    
float cam_1 = 1,cam_2 = 2;
float spot_position[] = {-9.89, 13.89, 0.01, 1.0}, spot_direction[] = {-9.89,0,1,0};   
float camera_angle = 0;
int cam_adder = 0;       // camera increaser
//______________________________________________________


GLUquadric * quadr ;
GLuint txId[7];  

//______________________________________________________



// Camera mode
int camera_mode=0;  

// _______________________spaceship base________________________________
const int N = 50;  // Total number of vertices on the base curve
float v_x[N] = {20,19,18,17,16,15,14,13};
float v_y[N] = {0,2,3,4,8,16,16.3,16.8};
float v_z[N] = {0};

float angle = 25, camera_height = 50.0;  
//Rotation angle, camera height
 
//For energy
float energy_mov_speed=500.;         
float minimum_y_speed=2.;          
float minimum_fade_speed=1.;    

//--------------Structure For Particle---------------------------------
typedef struct                      
{
    float energy_lifespan;            
    float fade_speed;              
    float x_pos;                   
    float y_pos;                     
    float z_pos;                   
    float x_direction;                 
    float y_direction;                  
    float z_direction;                 
}Energy;                 



Energy energy[500];   

// _______________________Energy initialization _______________________
void init_energy(){
 for (int i=0;i<500;i++)              
    {
        energy[i].energy_lifespan=1.0;                   
        energy[i].fade_speed=float(rand()%100)/1000 + minimum_fade_speed;  
        energy[i].x_direction=float((rand()%50)-25.0);   
        energy[i].y_direction=float((rand()%80)-25.0)+ minimum_y_speed;       
        energy[i].z_direction=float((rand()%50)-25.0);
        
    }
}

// _______________________Energy location updates _______________________
void EnergyLoc(){   
    glColor3f(0, 0.354685, 1);
    for (int i = 0;i < 500; i++)      
    {
        if (energy[i].energy_lifespan > 0)
        {
            glTranslatef(energy[i].x_pos,energy[i].y_pos,energy[i].z_pos);
            gluSphere(quadr,0.02,4.,4.);             
            glTranslatef(-energy[i].x_pos,-energy[i].y_pos,-energy[i].z_pos);
            
            energy[i].x_pos += energy[i].x_direction/energy_mov_speed;   
            energy[i].y_pos += energy[i].y_direction/energy_mov_speed;   
            energy[i].z_pos += energy[i].z_direction/energy_mov_speed;   
            energy[i].energy_lifespan -= energy[i].fade_speed;      
            if (energy[i].energy_lifespan==0|| energy[i].y_pos>1||energy[i].y_pos<0  )  
            {
                energy[i].energy_lifespan=1.0;   
                energy[i].fade_speed=float(rand()%100)/1000.0 + minimum_fade_speed;
                energy[i].x_direction=float((rand()%60)-29.0);   
                energy[i].y_direction=float((rand()%100)-29.0) + minimum_y_speed; 
                energy[i].z_direction=float((rand()%60)-29.0);    
                               energy[i].x_pos=0.;   
                energy[i].y_pos=0.1;                  
                energy[i].z_pos=0.;                  
            
    
            }
        }
    }
}


void Normal(float x_1, float y_1, float z_1, 
            float x_2, float y_2, float z_2,
              float x_3, float y_3, float z_3 )
{
      float normal_x, normal_y, normal_z;
      normal_x = y_1*(z_2-z_3)+ y_2*(z_3-z_1)+ y_3*(z_1-z_2);
      normal_y = z_1*(x_2-x_3)+ z_2*(x_3-x_1)+ z_3*(x_1-x_2);
      normal_z = x_1*(y_2-y_3)+ x_2*(y_3-y_1)+ x_3*(y_1-y_2);

      glNormal3f(normal_x, normal_y, normal_z);
}


void DrawEnergySupplier(void)
{
    float w_x[N], w_y[N], w_z[N]; 
    float angle_step = -15. * 3.1415926 / 180.0;  //Rotate in 15 degrees steps (converted to radians)

    glColor4f (0.3,0.3,0.8, 0.);     
   
    for (int j =0;j< 36;j++){
        glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i < N; i++)
        {
            w_x[i] = v_x[i] * cos(angle_step) +  v_z[i] * sin(angle_step);
            w_y[i] = v_y[i];
            w_z[i] = -v_x[i] * sin(angle_step) + v_z[i] * cos(angle_step);
            if(i > 0) Normal(w_x[i - 1], w_y[i - 1], w_z[i - 1],  
                            v_x[i - 1], v_y[i - 1], v_z[i - 1],
                            v_x[i], v_y[i], v_z[i]);
            glTexCoord2f((float)j / 36.,(float)i/N); glVertex3f(v_x[i], v_y[i], v_z[i]);
            if(i > 0) Normal(w_x[i-1], w_y[i - 1], w_z[i - 1],
                            v_x[i], v_y[i], v_z[i],
                            w_x[i], w_y[i], w_z[i] );
            glTexCoord2f((float)(j+1) / 36.,(float)i/N);glVertex3f(w_x[i], w_y[i], w_z[i]);
        }
        glEnd();        
 
        for (int i = 0; i<N; i++){
            v_x[i] = w_x[i];
            v_y[i] = w_y[i];
            v_z[i] = w_z[i];
        }
    }
            
    glFlush();  
}







float light_gray = 0.82745;

// spaceship 
int spaceship_x = -500, spaceship_y = 700, spaceship_z = -500;
int ship_direction = 0;
int ship_angle=270;
int spaceship_latitude = 25;
int spaceship_e = 0;  //lift spaceship
int spaceship_rotate=1;


//_____________________globals_________________________________
float *x_pos, *y_pos, *z_pos;  
int num_of_vertices, num_of_triangles,*triangle_1, *triangle_2, *triangle_3;  


float bullet1_y = 14.81,bullet1_z = 115.6,bullet2_y = 14.81,bullet2_z = 115.6;
// if 'fire',bullets_e == 1 else == 0
int bullets_e = 0; 

 


//___________________________Load Textures___________________________
void loadTexture(void)              
{
    glGenTextures(7, txId);     
    
    glBindTexture(GL_TEXTURE_2D, txId[0]);   
    loadBMP("nuke_dn.bmp");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);  
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    
    glBindTexture(GL_TEXTURE_2D, txId[1]);  
    loadBMP("wall.bmp");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);  
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    
    glBindTexture(GL_TEXTURE_2D, txId[2]);   
    loadTGA("nuke_bk.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[3]);   
    loadTGA("nuke_rt.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);  
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[4]);  
    loadTGA("nuke_ft.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);  
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glBindTexture(GL_TEXTURE_2D, txId[5]);   
    loadTGA("nuke_lf.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);  
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glBindTexture(GL_TEXTURE_2D, txId[6]);   
    loadTGA("nuke_up.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);  
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    


    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}






//________________Load the mesh file ______________________________________
void loadMeshFile(const char* fname)  
{
    ifstream fp_in;int num;int ne;
    fp_in.open(fname, ios::in);
    if(!fp_in.is_open())
    {
        cout << "Error opening mesh file" << endl;
        exit(1);
    }

    fp_in.ignore(INT_MAX, '\n');               
    fp_in >> num_of_vertices >> num_of_triangles >> ne;               

    x_pos = new float[num_of_vertices];                     
    y_pos = new float[num_of_vertices];
    z_pos = new float[num_of_vertices];

    triangle_1 = new int[num_of_triangles];
    triangle_2 = new int[num_of_triangles];
    triangle_3 = new int[num_of_triangles];

    for(int i=0; i < num_of_vertices; i++)                        
        fp_in >> x_pos[i] >> y_pos[i] >> z_pos[i];

    for(int i=0; i < num_of_triangles; i++)                       
    {
        fp_in >> num >> triangle_1[i] >> triangle_2[i] >> triangle_3[i];
        if(num != 3)
        {
            cout << "ERROR: Polygon with index " << i  << " is not walking_r triangle." << endl;   
            exit(1);
        }
    }

    fp_in.close();
    cout << " File successfully read." << endl;
}

// ________________________ Normal Vector computation function __________________________________________
void NormalVector(int tindx)
{
    float x_1 = x_pos[triangle_1[tindx]], x_2 = x_pos[triangle_2[tindx]], x_3 = x_pos[triangle_3[tindx]];
    float y_1 = y_pos[triangle_1[tindx]], y_2 = y_pos[triangle_2[tindx]], y_3 = y_pos[triangle_3[tindx]];
    float z_1 = z_pos[triangle_1[tindx]], z_2 = z_pos[triangle_2[tindx]], z_3 = z_pos[triangle_3[tindx]];
    float normal_x, normal_y, normal_z;
    normal_x = y_1 * (z_2-z_3) + y_2 * (z_3-z_1) + y_3 * (z_1-z_2);
    normal_y = z_1 * (x_2-x_3) + z_2 * (x_3-x_1) + z_3 * (x_1-x_2);
    normal_z = x_1 * (y_2-y_3) + x_2 * (y_3-y_1) + x_3 * (y_1-y_2);
    glNormal3f(normal_x, normal_y, normal_z);
}

//________________________Create Cannon using mashfile______________________
void CannonCreater()
{
    glColor3f(0.4, 0.499, 0.4);
    

    //Construct the object model here using triangles read from OFF file
 
    
    glBegin(GL_TRIANGLES);
    
        for(int tindx = 0; tindx < num_of_triangles; tindx++)
        {
           NormalVector(tindx);
           glVertex3d(x_pos[triangle_1[tindx]], y_pos[triangle_1[tindx]], z_pos[triangle_1[tindx]]);
           glVertex3d(x_pos[triangle_2[tindx]], y_pos[triangle_2[tindx]], z_pos[triangle_2[tindx]]);
           glVertex3d(x_pos[triangle_3[tindx]], y_pos[triangle_3[tindx]], z_pos[triangle_3[tindx]]);
        }
        
    glEnd();

}
//________________________Create multiple Cannons ______________________

void CannonsCreater()  
{
    float light_pos[4] = {100., 100., 100., 1.0};  

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);     
    glMatrixMode(GL_MODELVIEW);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);   


//Cannon 1
    glPushMatrix();
        glTranslatef(-60,20,0);
        glRotatef(-28, 1, 0, 0);
        glTranslatef(20,-65,90);
        glRotatef(270, 0, 1, 0);

        glScalef(0.199, 0.199, 0.199);


        CannonCreater();
    glPopMatrix();



//Cannon 2 
    glPushMatrix();
        glTranslatef(10,20,0);
        glRotatef(-28, 1, 0, 0);
        glTranslatef(20,-65,90);
        glRotatef(270, 0, 1, 0);

        glScalef(0.199, 0.199, 0.199);


        CannonCreater();
    glPopMatrix();

    
//Cannon base block 1
    glPushMatrix();
        glColor3f(1.,0.65,0.);
        glTranslatef(-0,-0,-0);
        glScalef(1.5, 1.5, 20);
        glTranslatef(-25,-0,5.5);
        glutSolidCube(1);
    glPopMatrix();    
    
    glPushMatrix();
        glColor3f(1.,0.65,0.);
        glTranslatef(-0,-0,-0);
        glScalef(1.5, 10.5, 18);
        glTranslatef(-25,-0,5.5);
        glutSolidCube(1);
    glPopMatrix();    
    //Cannon base block  2
    glPushMatrix();
        glColor3f(1.,0.65,0.);
        glTranslatef(-0,-0,-0);
        glScalef(1.5, 1.5, 20);
        glTranslatef(-28,-0,5.5);
        glutSolidCube(1);
    glPopMatrix();    
    
    glPushMatrix();
        glColor3f(1.,0.65,0.);
        glTranslatef(-0,-0,-0);
        glScalef(1.5, 10.5, 18);
        glTranslatef(-28,-0,5.5);
        glutSolidCube(1);
    glPopMatrix();        
    // Cannon base block  3
        glPushMatrix();
        glColor3f(1.,0.65,0.);
        glTranslatef(-0,-0,-0);
        glScalef(1.5, 1.5, 20);
        glTranslatef(18,-0,5.5);
        glutSolidCube(1);
    glPopMatrix();    
    
    glPushMatrix();
        glColor3f(1.,0.65,0.);
        glTranslatef(-0,-0,-0);
        glScalef(1.5, 10.5, 18);
        glTranslatef(18,-0,5.5);
        glutSolidCube(1);
    glPopMatrix();    
    
    // Cannon base block  4
        glPushMatrix();
        glColor3f(1.,0.65,0.);
        glTranslatef(-0,-0,-0);
        glScalef(1.5, 1.5, 20);
        glTranslatef(21,-0,5.5);
        glutSolidCube(1);
    glPopMatrix();    
    
    glPushMatrix();
        glColor3f(1.,0.65,0.);
        glTranslatef(-0,-0,-0);
        glScalef(1.5, 10.5, 18);
        glTranslatef(21,-0,5.5);
        glutSolidCube(1);
    glPopMatrix();    
    
    
    //Bullet 1
     glPushMatrix();
        glTranslatef(0,0,0);
        glColor3f(0.,0.499,0.);
        glTranslatef(29.9,bullet1_y,bullet1_z);
        glutSolidSphere(1.3, 5, 5);
    glPopMatrix();
    
    //Bullet 2
     glPushMatrix();
        glTranslatef(0,0,0);
        glColor3f(0.,0.499,0.);
        glTranslatef(-40,bullet2_y,bullet2_z);
        glutSolidSphere(1.3, 5, 5);
    glPopMatrix();
    
    glFlush();
}
//_______________Spaceship draw circle  _______________________________________

GLvoid CircleCreater(float c_x, float c_y, float c_z, float radius, int number_of_segments)  
{  
    GLfloat vertex[4];   
  
    const GLfloat delta_angle = 2. * M_PI / number_of_segments;  
    glBegin(GL_TRIANGLE_FAN);  
  
        vertex[0] = c_x;  
        vertex[1] = c_y;  
        vertex[2] = c_z;  
        vertex[3] = 1.;          
        glVertex4fv(vertex);  
      
        for(int i = 0; i < number_of_segments ; i++)  
        {  
            vertex[0] = std::cos(delta_angle*i) * radius + c_x;  
            vertex[1] = std::sin(delta_angle*i) * radius + c_y;  
            vertex[2] = c_z;  
            vertex[3] = 1.;  
            glVertex4fv(vertex);  
        }  
      
        vertex[0] = 1. * radius + c_x;  
        vertex[1] = 0. * radius + c_y;  
        vertex[2] = c_z;  
        vertex[3] = 1.;  
        glVertex4fv(vertex);  
    glEnd();  
}

//_______________Space shipdraw cylinder _______________________________________

void CylinderCreater( GLUquadric* quad,  
                     GLdouble base,  
                     GLdouble top,  
                     GLdouble height,  
                     GLint slices,  
                     GLint stacks )  
{  
    gluCylinder(quad, base, top, height, slices, stacks);  
        //top   
    CircleCreater(0.0, 0.0, height, top, slices);   
       //base   
    CircleCreater(0.0, 0.0, 0.0, base, slices);  


}  

//________________spaceship drawer ______________________________________

void SpaceshipCreater()
{
    // the body of the space ship
    
    glPushMatrix();
        glRotatef(-90, 1, 0, 0);
        glPushMatrix();
          glColor3f(light_gray, light_gray, light_gray);            
          glutSolidSphere(20, 20, 20);
        glPopMatrix();
        
        
        glColor3f(0.499, 0.499, 0.499);
        glPushMatrix();
          GLUquadric *quadric1;quadric1 = gluNewQuadric();
          CylinderCreater(quadric1, 100, 100, 3, 20, 20);
          gluQuadricDrawStyle(quadric1, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, -2);
          GLUquadric *quadric3;quadric3 = gluNewQuadric();
          CylinderCreater(quadric3, 96, 100, 3, 20, 20);
          gluQuadricDrawStyle(quadric3, GLU_FILL);  
        glPopMatrix(); 
        
        
        
        glPushMatrix();
          glTranslatef(0, 0, 2);
          GLUquadric *quadric2;quadric2 = gluNewQuadric();
          CylinderCreater(quadric2, 100, 96, 3, 20, 20);
          gluQuadricDrawStyle(quadric2, GLU_FILL);  
        glPopMatrix();
        

        
        glPushMatrix();
          glTranslatef(0, 0, 4);
          GLUquadric *quadric4;quadric4 = gluNewQuadric();
          CylinderCreater(quadric4, 96, 92, 3, 20, 20);
          gluQuadricDrawStyle(quadric4, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, -4);
          GLUquadric *quadric5;quadric5 = gluNewQuadric();
          CylinderCreater(quadric5, 92, 96, 3, 20, 20);
          gluQuadricDrawStyle(quadric5, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, -6);
          GLUquadric *quadric7;quadric7 = gluNewQuadric();
          CylinderCreater(quadric7, 88, 92, 3, 20, 20);
          gluQuadricDrawStyle(quadric7, GLU_FILL);  
        glPopMatrix();    
            
        glPushMatrix();
          glTranslatef(0, 0, 6);
          GLUquadric *quadric6;quadric6 = gluNewQuadric();
          CylinderCreater(quadric6, 92, 88, 3, 20, 20);
          gluQuadricDrawStyle(quadric6, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, -8);
          GLUquadric *quadric9;quadric9 = gluNewQuadric();
          CylinderCreater(quadric9, 84, 88, 3, 20, 20);
          gluQuadricDrawStyle(quadric9, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, 8);
          GLUquadric *quadric8;quadric8 = gluNewQuadric();
          CylinderCreater(quadric8, 88, 84, 3, 20, 20);
          gluQuadricDrawStyle(quadric8, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, -10);
          GLUquadric *quadric11;quadric11 = gluNewQuadric();
          CylinderCreater(quadric11, 80, 84, 3, 20, 20);
          gluQuadricDrawStyle(quadric11, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, 10);
          GLUquadric *quadric10;quadric10 = gluNewQuadric();
          CylinderCreater(quadric10, 84, 80, 3, 20, 20);
          gluQuadricDrawStyle(quadric10, GLU_FILL);  
        glPopMatrix();        
        
    glPopMatrix();
    
    
    // the tail of the space ship
    glPushMatrix();
      glTranslatef(0, -15, 80);
          glPushMatrix();
              glScalef(5, 20, 5);
              glutSolidCube(1);
          glPopMatrix();
          
          
          glPushMatrix();
              glTranslatef(30, -10, 0);                       
              glRotatef(-90, 0, 1, 0); 
              GLUquadric *quadric12;
              quadric12 = gluNewQuadric();
              CylinderCreater(quadric12, 5, 5, 60, 20, 20);
              gluQuadricDrawStyle(quadric12, GLU_FILL); 
          glPopMatrix();
          
          glPushMatrix();
              glTranslatef(-30, -10, -10);
              GLUquadric *quadric14;
              quadric14 = gluNewQuadric();
              CylinderCreater(quadric14, 6, 6, 30, 20, 20);
              gluQuadricDrawStyle(quadric14, GLU_FILL); 
          glPopMatrix();          
          
          
          glPushMatrix();
              glTranslatef(30, -10, -10);
              GLUquadric *quadric13;
              quadric13 = gluNewQuadric();
              CylinderCreater(quadric13, 6, 6, 30, 20, 20);
              gluQuadricDrawStyle(quadric13, GLU_FILL); 
          glPopMatrix();
          
          
          glPushMatrix();
              glTranslatef(-30, -10, 20);
              GLUquadric *quadric16;
              quadric16 = gluNewQuadric();
              CylinderCreater(quadric16, 10, 10, 10, 20, 20);
              gluQuadricDrawStyle(quadric16, GLU_FILL); 
          glPopMatrix();
          
          glPushMatrix();
              glTranslatef(30, -10, 20);
              GLUquadric *quadric15;
              quadric15 = gluNewQuadric();
              CylinderCreater(quadric15, 10, 10, 10, 20, 20);
              gluQuadricDrawStyle(quadric15, GLU_FILL); 
          glPopMatrix();
          
          
          glPushMatrix();
              glTranslatef(-30, -10, 30);
              glutSolidTorus(2, 10, 20,20);
          glPopMatrix();
          
          
          glPushMatrix();
              glTranslatef(30, -10, 30);
              glutSolidTorus(2, 10, 20,20);
          glPopMatrix();
          
          

          
          float lgt_pos1[] = {0.0f, 0.0f, 2.0f, 1.0f};
          
          
          glColor3f(1, 0.499, 0); 
          
          glPushMatrix();
              glTranslatef(-30, -10, 31);
              glLightfv(GL_LIGHT1, GL_POSITION, lgt_pos1);   //light position            
                glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180);
                glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,0.01); 
              GLUquadric *quadric18;
              quadric18 = gluNewQuadric();
              gluDisk(quadric18, 0, 8, 10, 10);
              gluQuadricDrawStyle(quadric18, GLU_FILL);
          glPopMatrix(); 
                   
          glPushMatrix();
              glTranslatef(30, -10, 31);
              glLightfv(GL_LIGHT1, GL_POSITION, lgt_pos1);   //light position            
              glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180);
              glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,0.01); 
              GLUquadric *quadric17;
              quadric17 = gluNewQuadric();
              gluDisk(quadric17, 0, 8, 10, 10);
              gluQuadricDrawStyle(quadric17, GLU_FILL);
          glPopMatrix();
          

          
    glPopMatrix();
    
    
}






//__________________ Draw the floor ____________________________________
void FloorCreater()
{
    float black[4] = {0}, white[4] = {1., 1., 1., 1.};
    glEnable(GL_TEXTURE_2D);  glBindTexture(GL_TEXTURE_2D, txId[0]);
    glBegin(GL_QUADS);
        
        glMaterialfv(GL_FRONT, GL_SPECULAR, black);
        
        for(int i = -256; i < 256; i+=16)
        {
            for(int j = -256;  j < 256; j += 16)
            {
                glTexCoord2f(0.0,0.0);
                glVertex3f(i, -0.1, j);  
                glTexCoord2f(0.0,1.0);
                glVertex3f(i, -0.1, j+16);
                glTexCoord2f(1.0,1.0);
                glVertex3f(i+16, -0.1, j+16);
                glTexCoord2f(1.0,0.0);
                glVertex3f(i+16, -0.1, j);
            }
        }  
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
}

//________________________Draw robots_________________________________________
void RobotCreater(int colour)
{   

    if (colour == 0){                             //0 -->  colour of the shawdow
        glColor4f(0.2325,0.23512,0.23214,1.0);
    }
    else if (colour == 1){                            //1 --> colorful
        glColor3f(1., 0.7875 ,0.06357);               //Head
    }    
    
    if (colour == 1){
    glColor3f(0.7,0.7, 0.7);
    }       
    glPushMatrix();                                       //Head
      glTranslatef(0, 7.7, 0.199);
      glutSolidCube(3);
    glPopMatrix();
    
     if (colour == 1){
     glColor3f(0,0,0);
    }             
    glPushMatrix();                 //robot mouth
        glColor3f(0.,0.,0);
        glTranslatef(0, 7.0, 1.8);
        glScalef(3, 0.4, 1.8);
        glutSolidSphere(0.05,20,20);
    glPopMatrix();    
    

    glPushMatrix();                  //eye       
        glTranslatef(-0.6, 8, 1.8);
        glutSolidSphere(0.199,20,20);
    glPopMatrix();    
    
    
    
    glPushMatrix();                  //robot eye      
        glTranslatef(0.6, 8, 1.8);
        glutSolidSphere(0.199,20,20);
    glPopMatrix();        

    
    if (colour == 1){                
        glColor3f(1, 1, 0);
    }
    glPushMatrix();
      glTranslatef(0, 5.5, 0.75); 
      gluDisk(quadr, 0.0, 1.0, 20,2);
   glPopMatrix();    
    
      
    if (colour == 1){                
        glColor3f(0.8, 1, 1);
    }
                  
    glPushMatrix();                 //Torso
      glTranslatef(0, 5.5, 0);
      glScalef(3, 3, 1.4);
      glutSolidCube(1);
      
    glPopMatrix();;
    
    
    glPushMatrix();                 //Right leg
        glTranslatef(-0.8,4,0);
        glRotatef(-walking_angle, 1, 0, 0);
        glTranslatef(0.8, -4, 0); glTranslatef(-0.8, 2.2, 0);
        glScalef(1, 4.4, 1);
        glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();                 //Left leg  
        glTranslatef(-0.8, 4, 0);
        glRotatef(walking_angle, 1, 0, 0);
        glTranslatef(0.8, -4, 0); glTranslatef(0.8, 2.2, 0);
        glScalef(1, 4.4, 1);
        glutSolidCube(1);
    glPopMatrix();      

                                    
    glPushMatrix();                 //Right arm
        glTranslatef(-2, 6.5, 0);
        glRotatef(walking_angle, 1, 0, 0);
        glTranslatef(2, -6.5, 0); glTranslatef(-2, 5, 0);
        glScalef(1, 4, 1);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();                 //Left arm
        glTranslatef(2,6.5,0);
        glRotatef(-walking_angle, 1, 0, 0);
        glTranslatef(-2, -6.5, 0); glTranslatef(2, 5, 0);
        glScalef(1, 4, 1);
        glutSolidCube(1);
    glPopMatrix();
                         

}
//_________________ Draw the shadow of the robot_____________________________________
void RobotShadowCreater(){
    float shadowMat[16] = {light_pos[1],0,0,0,-light_pos[0],0,-light_pos[2],-1,0,0,light_pos[1],0,0,0,0,light_pos[1]};
   

    // Draw robot 1
    glEnable(GL_LIGHTING);
    glPushMatrix();
            glTranslatef(walking_r*cos(robot_walking_time)/(1+sin(robot_walking_time)*sin(robot_walking_time)),0,1);   
            glTranslatef(0,0,15);
            glRotatef(self_rotate_angle,0,1,0);
            glLightfv(GL_LIGHT1, GL_POSITION, spot_position);
            glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
            RobotCreater(1);
     glPopMatrix();           
       // Draw robot 2

       glEnable(GL_LIGHTING);
    glPushMatrix();
            glTranslatef(walking_r*cos(robot_walking_time)/(1+sin(robot_walking_time)*sin(robot_walking_time)),0,1);   
            glTranslatef(0,0,-215);
            glRotatef(self_rotate_angle,0,1,0);
            glLightfv(GL_LIGHT1, GL_POSITION, spot_position);
            glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
            RobotCreater(1);
     glPopMatrix();    
    
     //Draw shadow
    glDisable(GL_LIGHTING);
    
    
    
    // first robot shadow

    glPushMatrix();
        glMultMatrixf(shadowMat);
         glTranslatef(cos(robot_walking_time)*walking_r/(1+sin(robot_walking_time)*sin(robot_walking_time)),0,1);

            glTranslatef(0,0,15);
            glRotatef(self_rotate_angle,0,1,0);
        RobotCreater(0);
    glPopMatrix();
    
    // second robot shadow
    glPushMatrix();
        glMultMatrixf(shadowMat);
         glTranslatef(cos(robot_walking_time)*walking_r/(1+sin(robot_walking_time)*sin(robot_walking_time)),0,1);

            glTranslatef(0,0,-215);
            glRotatef(self_rotate_angle,0,1,0);
        RobotCreater(0);
    glPopMatrix();    
    
    
    
}
    




//_______________Draw the wall of the fortress_______________________________________

void FortressWallCreater(){
    
    glEnable(GL_TEXTURE_2D);glBindTexture(GL_TEXTURE_2D, txId[1]); 
    glColor3f(1, 1, 1);glBegin(GL_QUADS);
    
        glNormal3f(0, 0, 1);                  //front left  door
        
        glTexCoord2f(0, 0);glVertex3f(-50, 0, 80);
        glTexCoord2f(1, 0);glVertex3f(-5, 0, 80);
        glTexCoord2f(1, 1); glVertex3f(-5, 30, 80);
        glTexCoord2f(0, 1);glVertex3f(-50, 30, 80);
        
        
        glNormal3f(0, 0, 1);                 //above door
        
        glTexCoord2f(0, 0);glVertex3f(-5, 15, 80);
        glTexCoord2f(0.22, 0);glVertex3f(5, 15, 80);
        glTexCoord2f(0.22, 0.499);glVertex3f(5, 30, 80);
        glTexCoord2f(0, 0.499);glVertex3f(-5, 30, 80);
        
        
        glNormal3f(0, 0, 1);                  //right door
        
        glTexCoord2f(0, 0);glVertex3f(5, 0, 80);
        glTexCoord2f(1, 0);glVertex3f(50, 0, 80);
        glTexCoord2f(1, 1);glVertex3f(50, 30, 80);
        glTexCoord2f(0, 1);glVertex3f(5, 30, 80);
        
        
        glNormal3f(0, 0, -1);                  //backside left door
        
        glTexCoord2f(0, 0);glVertex3f(-50, 0, -80);
        glTexCoord2f(1, 0);glVertex3f(-5, 0, -80);
        glTexCoord2f(1, 1);glVertex3f(-5, 30, -80);
        glTexCoord2f(0, 1);glVertex3f(-50, 30, -80);
        
        
        
        glNormal3f(1, 0, 0);                   //right side
        glTexCoord2f(0, 0);glVertex3f(50, 0, 80);
        glTexCoord2f(1, 0);glVertex3f(50, 0, -80);
        glTexCoord2f(1, 1);glVertex3f(50, 30, -80);
        glTexCoord2f(0, 1);glVertex3f(50, 30, 80);
        
        
        glNormal3f(0, 0, -1);                  //right door
        glTexCoord2f(0, 0);glVertex3f(5, 0, -80);
        glTexCoord2f(1, 0);glVertex3f(50, 0, -80);
        glTexCoord2f(1, 1);glVertex3f(50, 30, -80);
        glTexCoord2f(0, 1);glVertex3f(5, 30, -80);
        
        
        glNormal3f(0, 0, -1);                 //above door
        glTexCoord2f(0, 0);glVertex3f(-5, 15, -80);
        glTexCoord2f(1, 0);glVertex3f(5, 15, -80);
        glTexCoord2f(1, 1);glVertex3f(5, 30, -80);
        glTexCoord2f(0, 1);glVertex3f(-5, 30, -80);
        
        

        
        glNormal3f(-1, 0, 0);
        glTexCoord2f(0, 0);glVertex3f(-50, 0, 80);
        glTexCoord2f(1, 0);glVertex3f(-50, 0, -80);
        glTexCoord2f(1, 1);glVertex3f(-50, 30, -80);
        glTexCoord2f(0, 1);glVertex3f(-50, 30, 80);
        
        
    glEnd();
    glDisable(GL_TEXTURE_2D);
}   
//______________Draw fortress________________________________________

void FortressCreater(){
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        FortressWallCreater();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}
//______________________________________________________

void SkyBoxCreater() {
    glEnable(GL_BLEND);
    glColor4f(1., 1., 1., 0.9);
    glPushMatrix();
        float black[4] = {0., 0., 0., 1.}, white[4] = {1., 1., 1., 1.};

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
        glMaterialfv(GL_FRONT, GL_SPECULAR, black);
        glEnable(GL_TEXTURE_2D);
            // SkyBox top
            glBindTexture(GL_TEXTURE_2D, txId[6]);
            glBegin(GL_QUADS);
                glTexCoord2f(0., 0.);     glVertex3f( 256.,  256., -256.);
                glTexCoord2f(1., 0.);     glVertex3f( 256.,  256.,  256.);
                glTexCoord2f(1., 1.);     glVertex3f(-256.,  256.,  256.);
                glTexCoord2f(0., 1.);     glVertex3f(-256.,  256., -256.);
            glEnd();
            //SkyBox  left
            glBindTexture(GL_TEXTURE_2D, txId[5]);
            glBegin(GL_QUADS);
                glTexCoord2f(0., 0.);     glVertex3f(-256., -256.,  256.);
                glTexCoord2f(1., 0.);     glVertex3f(-256., -256., -256.);
                glTexCoord2f(1., 1.);     glVertex3f(-256.,  256., -256.);
                glTexCoord2f(0., 1.);     glVertex3f(-256.,  256.,  256.);
            glEnd();       
            // SkyBox front
            glBindTexture(GL_TEXTURE_2D, txId[4]);
            glBegin(GL_QUADS);
                glTexCoord2f(0., 0.);     glVertex3f( 256., -256., 256.0);
                glTexCoord2f(1., 0.);     glVertex3f(-256., -256., 256.0);
                glTexCoord2f(1., 1.);     glVertex3f(-256.,  256., 256.0);
                glTexCoord2f(0., 1.);     glVertex3f( 256.,  256., 256.0);
            glEnd();
            // SkyBox right
            glBindTexture(GL_TEXTURE_2D, txId[3]);
            glBegin(GL_QUADS);
                glTexCoord2f(0., 0.);     glVertex3f(256., -256., -256.);
                glTexCoord2f(1., 0.);     glVertex3f(256., -256.,  256.);
                glTexCoord2f(1., 1.);     glVertex3f(256.,  256.,  256.);
                glTexCoord2f(0., 1.);     glVertex3f(256.,  256., -256.);
            glEnd();

            // SkyBox back
            glBindTexture(GL_TEXTURE_2D, txId[2]);
            glBegin(GL_QUADS);
                glTexCoord2f(0. , 0. );     glVertex3f(-256., -256., -256.);
                glTexCoord2f(1. , 0. );     glVertex3f( 256., -256., -256.);
                glTexCoord2f(1. , 1. );     glVertex3f( 256.,  256., -256.);
                glTexCoord2f(0. , 1. );     glVertex3f(-256.,  256., -256.);
            glEnd();

        glDisable(GL_TEXTURE_2D);
        glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glPopMatrix();
    
    glDisable(GL_BLEND);
    
}

//___________________________Displayer__________________________
void display()  
{   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    glMatrixMode(GL_MODELVIEW);                             
    glLoadIdentity();
    
    // space lift up mode view
    if (camera_mode==1){
            glTranslatef(10,-100,48); 
            glRotatef(20,100,10,0);
            glTranslatef(0,0,-15);
    } 
                
    else if(camera_mode == 0){
    // Camera
    float dir_x = -sin(camera_angle), dir_y = 0,  dir_z = -cos(camera_angle);

    camer_eye_x_position += cam_adder * cam_1 * dir_x;
    camer_eye_z_position += cam_adder * cam_1 * dir_z;
    cam_adder = 0;
     
    if (camer_eye_x_position >=230){
        camer_eye_x_position = 230;
    }   
    else if(camer_eye_x_position <=-230){
        camer_eye_x_position = -230;   
    }
    if (camer_eye_z_position >= 230){
        camer_eye_z_position = 230;
    }   
    else if (camer_eye_z_position <=-230){
        camer_eye_z_position = -230;
    }
                 
    look_at_x_position = camer_eye_x_position + cam_2 * dir_x;
    look_at_y_position = camer_eye_y_position + cam_2 * dir_y;
    look_at_z_position = camer_eye_z_position + cam_2 * dir_z; 

   
   
    gluLookAt(camer_eye_x_position, camer_eye_y_position, camer_eye_z_position,  look_at_x_position, look_at_y_position, look_at_z_position, 0, 1, 0);   
   }      
    

    
    glLightfv(GL_LIGHT0,GL_POSITION, light_pos);   


    glDisable(GL_LIGHTING);      
    FloorCreater();
    SkyBoxCreater();
    
    RobotShadowCreater();  
    
    glEnable(GL_LIGHTING);         

    glPushMatrix();            
      glTranslatef(0,0,-100);
      FortressCreater();
    glPopMatrix(); 
    
    
    
    glPushMatrix();
      glTranslatef(0,0,-100);
      CannonsCreater();
    glPopMatrix();
    
       // draw spaceship

    glPushMatrix();
      glTranslatef(0,0,-140);
      DrawEnergySupplier();
    glPopMatrix();
       
   glDisable(GL_LIGHTING);

    glEnable(GL_LIGHTING);
    
    
    glPushMatrix();
        glTranslatef(0,spaceship_latitude, -140);           
        glScalef(0.199, 0.199, 0.199);

        glRotatef(180, 0, 1, 0);
        glRotatef(spaceship_rotate, 0, 0, 1);
        SpaceshipCreater();
        
    glPopMatrix();
    
    
    glPushMatrix();
        glTranslatef(0,10, -140);           
        glScalef(20,10,20);
        EnergyLoc();
        init_energy();
    glPopMatrix();


    glutSwapBuffers();  
 

}

//+++++++++++++++++++++++++++ Special key event callback +++++++++++++++++++++++++++ 
void KeyEventsCallBack(int key, int x_pos, int y_pos)
{
    cam_adder = 0;
    if(key == GLUT_KEY_LEFT){
        camera_angle += 0.1;   
    }else if(key == GLUT_KEY_RIGHT){
         camera_angle -= 0.1;
    }else if(key == GLUT_KEY_UP){
        cam_adder = 2;
    }else if(key == GLUT_KEY_DOWN){
        cam_adder = -2;
    }else if (key == GLUT_KEY_HOME){
        if (camera_mode == 1) {
            camera_mode = 0;
        } else {
            camera_mode = 1;
        }
    
    }
    
    glutPostRedisplay();
}
//+++++++++++++++++++++++++++ keyboard event callback +++++++++++++++++++++++++++ 
void key(unsigned char key, int x_pos, int y_pos)
{
    if(key == 's'|| key == 'S'){
        spaceship_e = 1;
    }
      if(key == 'c'|| key == 'C'){
        bullets_e = 1;
    }  

 
    glutPostRedisplay();
}



//___________________timer for lifting spaceship___________________________________

void spaceship_timer(int value)
{
    
    
  if (spaceship_e == 1){ 
      if(spaceship_latitude < 80){
        camera_mode = 1;   

        spaceship_latitude += 1;    
      } 
  }
    glutTimerFunc(1,spaceship_timer, 0);
    glutPostRedisplay();
   
    
}   

//___________________timer for rotating spaceship___________________________________

void spaceship_rotate_timer(int value)
{
    
    if (spaceship_rotate == 1){
     spaceship_rotate = -1;
    } else {
     spaceship_rotate=1;
    }
   
    glutTimerFunc(50,spaceship_rotate_timer, 0);
    glutPostRedisplay();
   
    
}   

//______________________________________________________

void Robot_timer(int value)
{   
       
    if (walking_angle==-33){
        direc=1;
    }      
    if (walking_angle==33){
        direc=-1;
    }

    walking_angle+=direc;
    
    robot_walking_time+=0.01;
    self_rotate_angle-=3*(atan(sin(robot_walking_time-0.1))-atan(sin(robot_walking_time-0.4))); //self-rotating space ship view   
   
    glutTimerFunc(5,Robot_timer, 0);
    glutPostRedisplay();
    
}

//_______________ timer for the fire_______________________________________

void bullets_timer(int value)
{
    
    
  if (bullets_e == 1){ 
      if(bullet1_z < 500){
      bullet1_y += 0.8;
      bullet1_z += 2;
      bullet2_y += 0.8;
      bullet2_z += 2;     
      } else {
         bullets_e = 0;
         bullet1_y = 14.81;
         bullet1_z = 115.6;
         bullet2_y = 14.81;
         bullet2_z = 115.6;
          
    }

         
    

  }
    glutTimerFunc(1,bullets_timer, 0);
    glutPostRedisplay();
   
    
}   

//______________ initialize________________________________________
void initialization()
{
    float grey[4] = {0.199, 0.199, 0.199, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};

    quadr = gluNewQuadric();
    loadTexture();
    loadMeshFile("Cannon.off");             //Specify mesh file name here
    
    glEnable(GL_LIGHTING);                  
    glEnable(GL_LIGHT1); glEnable(GL_LIGHT0);  
    glLightfv(GL_LIGHT1, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,0.01);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);    
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    

    
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);  
    glMaterialf(GL_FRONT, GL_SHININESS, 50);

    gluQuadricDrawStyle(quadr, GLU_FILL);
    glClearColor (0.0, 0.0, 0.0, 0.0);  
    glMatrixMode(GL_PROJECTION);  glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 1000.0);    
    
    
    //cannon
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);                   
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_PROJECTION);
 
    
    

}


//__________________The main function for GLUT____________________________________
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
   glutInitWindowSize (600, 600); 
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("Alien Invasion");
   initialization();
   glutTimerFunc(20, Robot_timer, 0);
   glutTimerFunc(79.9,spaceship_rotate_timer, 0);
   glutTimerFunc(79.9,spaceship_timer, 0);
   glutTimerFunc(79.9,bullets_timer, 0);

   glutDisplayFunc(display);
   glutSpecialFunc(KeyEventsCallBack); 
   glutKeyboardFunc(key);
   glutMainLoop();
   return 0;
}
