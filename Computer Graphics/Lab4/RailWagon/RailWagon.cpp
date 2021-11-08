//  ========================================================================
//  COSC363: Computer Graphics (2019);  CSSE, University of Canterbury.
//
//  FILE NAME: RailWagon.cpp
//  See Lab04.pdf for details
//  ========================================================================

#include <iostream>
#include <cmath>
#include <GL/freeglut.h>
#include "loadBMP.h"
using namespace std;

GLuint txId;
GLUquadric *q;    //Required for creating cylindrical objects
float angle = 25, cam_hgt = 40.0;  //Rotation angle, camera height

//------Function to load a texture in bmp format  ------------------------
void loadTexture()
{
    glGenTextures(1, &txId);                // Create a Texture object
    glBindTexture(GL_TEXTURE_2D, txId);     //Use this texture
    loadBMP("WagonTexture.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//GL_MODULATE);
}

//-- Ground Plane --------------------------------------------------------
void floor()
{
    glDisable(GL_TEXTURE_2D);

    glDisable(GL_LIGHTING);
    glColor3f(0.7, 0.7,  0.7);          //Floor colour

    for(int i = -200; i <= 200; i +=5)
    {
        glBegin(GL_LINES);          //A set of grid lines on the xz-plane
            glVertex3f(-200, 0, i);
            glVertex3f(200, 0, i);
            glVertex3f(i, 0, -200);
            glVertex3f(i, 0, 200);
        glEnd();
    }
    glEnable(GL_LIGHTING);
}

//------Event handler for special key events -------------------------------------
void special(int key, int x, int y)
{
    if(key==GLUT_KEY_LEFT) angle --;        //Rotate wagon
    else if(key==GLUT_KEY_RIGHT) angle ++;
    else if(key==GLUT_KEY_UP) cam_hgt ++;   //Change camera height
    else if(key==GLUT_KEY_DOWN) cam_hgt --;

    if(cam_hgt < 10) cam_hgt = 10;
    else if(cam_hgt > 100) cam_hgt = 100;

    glutPostRedisplay();
}

//--------------------------------------------------------------------------------
void initialise()
{
    float grey[4] = {0.2, 0.2, 0.2, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};

    q = gluNewQuadric();
    loadTexture();     //<<<<<<<<<<<<<<<<<

    glClearColor(1., 1., 1., 1.);  //Background colour
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.,1.,70.,1000.);
}

//--------Base structure for the wagon including wheels----------------------------
void base()
{
    glDisable(GL_TEXTURE_2D);

    float xp[4] = {-27.0, -27.0, 27.0, 27.0};
    float zp[4] = {-5.0,    5.0, -5.0,  5.0};

    glColor4f(0.3, 0.3, 0.3, 1.0);

    //Base plate
    glPushMatrix();
      glTranslatef(0.0, 4.5, 0.0);
      glScalef(72.0, 1.0, 12.0);
      glutSolidCube(1.0);
    glPopMatrix();

    //Wheel assembly:  4 per wagon
    for(int i = 0; i < 4; i++)
    {
        glPushMatrix();
          glTranslatef(xp[i], 3., zp[i]);
          glScalef(16.0, 2.0, 2.0);
          glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
          glTranslatef(xp[i]-6.0, 2.0, zp[i]);
          gluDisk(q, 0.0, 2.0, 20, 2);
        glPopMatrix();
        glPushMatrix();
          glTranslatef(xp[i]+6.0, 2.0, zp[i]);
          gluDisk(q, 0.0, 2.0, 20, 2);
        glPopMatrix();
    }

}

//--------------------------------------------------------------------------------
void wagon()
{
    //base();

    glColor4f(1.0, 1.0, 1.0, 1.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId);



    //3 large polygons (front, back, top)


    glBegin(GL_TRIANGLES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(5.0, 5.0, 5.0);
        glVertex3f(10.0, 10.0, 10.0);
    glEnd();


    glDisable(GL_TEXTURE_2D);
    //2 small side polygons (left, right)

}

//--------------------------------------------------------------------------------
void display()
{
    float lgt_pos[] = {30.0f, 50.0f, 50.0f, 1.0f};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, cam_hgt, 150, 0, 0, 0,   0, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);

    floor();

    glPushMatrix();
        glRotated(angle, 0, 1, 0);
        wagon();
    glPopMatrix();

    glFlush();
}

//--------------------------------------------------------------------------------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH);
   glutInitWindowSize (700, 700);
   glutInitWindowPosition (50, 50);
   glutCreateWindow ("Railway Wagon");
   initialise();

   glutDisplayFunc(display);
   glutSpecialFunc(special);
   glutMainLoop();
   return 0;
}
