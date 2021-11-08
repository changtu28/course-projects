//  ========================================================================
//  COSC363: Computer Graphics (2019); CSSE  University of Canterbury.
//
//  FILE NAME: Skybox.cpp
//  See Lab03.pdf for details
//  ========================================================================

#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
#include "loadTGA.h"
using namespace std;

#define GL_CLAMP_TO_EDGE 0x812F   //To get rid of seams between textures
float lookAngle = 0.0;      //Camera rotation

GLuint texId[6];

void loadGLTextures()               // Load bitmaps And Convert To Textures
{
    glGenTextures(6, texId);        // Create texture ids
    // *** left ***
    glBindTexture(GL_TEXTURE_2D, texId[0]);
    loadTGA("left.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // *** front ***
    glBindTexture(GL_TEXTURE_2D, texId[1]);
    loadTGA("front.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // *** right ***
    glBindTexture(GL_TEXTURE_2D, texId[2]);
    loadTGA("right.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // *** back***
    glBindTexture(GL_TEXTURE_2D, texId[3]);
    loadTGA("back.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // *** top ***
    glBindTexture(GL_TEXTURE_2D, texId[4]);
    loadTGA("top.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // *** down ***
    glBindTexture(GL_TEXTURE_2D, texId[5]);
    loadTGA("down.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}

//========================================================================================

void skybox(){
    glEnable(GL_TEXTURE_2D);

  ////////////////////// LEFT WALL ///////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[0]);
  //glColor3f(1, 0, 0);    //<<<<<<<<<<<< Remove the statements that assign color to the sides of the cube
  glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0); glVertex3f(-1000,  0, 1000);
      glTexCoord2f(1.0, 0.0); glVertex3f(-1000, 0., -1000);
      glTexCoord2f(1.0, 1.0); glVertex3f(-1000, 1000., -1000);
      glTexCoord2f(0.0, 1.0); glVertex3f(-1000, 1000, 1000);
  glEnd();

  ////////////////////// FRONT WALL ///////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[1]);
  //glColor3f(0, 1, 0);
  glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0); glVertex3f(-1000,  0, -1000);
      glTexCoord2f(1.0, 0.0); glVertex3f(1000, 0., -1000);
      glTexCoord2f(1.0, 1.0); glVertex3f(1000, 1000, -1000);
      glTexCoord2f(0.0, 1.0); glVertex3f(-1000,  1000, -1000);
  glEnd();

 ////////////////////// RIGHT WALL ///////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[2]);
  //glColor3f(0, 0, 1);
  glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0); glVertex3f(1000,  0, -1000);
      glTexCoord2f(1.0, 0.0); glVertex3f(1000, 0, 1000);
      glTexCoord2f(1.0, 1.0); glVertex3f(1000, 1000,  1000);
      glTexCoord2f(0.0, 1.0); glVertex3f(1000,  1000,  -1000);
  glEnd();


  ////////////////////// REAR WALL ////////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[3]);
  //glColor3f(1, 1, 0);
  glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0); glVertex3f( 1000, 0, 1000);
      glTexCoord2f(1.0, 0.0); glVertex3f(-1000, 0,  1000);
      glTexCoord2f(1.0, 1.0); glVertex3f(-1000, 1000,  1000);
      glTexCoord2f(0.0, 1.0); glVertex3f( 1000, 1000, 1000);
  glEnd();

  /////////////////////// TOP //////////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[4]);
  //glColor3f(1, 0, 1);
  glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0); glVertex3f(-1000, 1000, -1000);
      glTexCoord2f(1.0, 0.0); glVertex3f(1000, 1000,  -1000);
      glTexCoord2f(1.0, 1.0); glVertex3f(1000, 1000,  1000);
      glTexCoord2f(0.0, 1.0); glVertex3f(-1000, 1000, 1000);
  glEnd();

  /////////////////////// FLOOR //////////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[5]);
  //glColor3f(0, 1, 1);
  glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0); glVertex3f(-1000, 0., 1000);
      glTexCoord2f(1.0, 0.0); glVertex3f(1000, 0.,  1000);
      glTexCoord2f(1.0, 1.0); glVertex3f(1000, 0., -1000);
      glTexCoord2f(0.0, 1.0); glVertex3f(-1000, 0., -1000);
  glEnd();

}

//---------------------------------------------------------------------
void initialise(void)
{
    loadGLTextures();   //<<<<<<<<< Uncomment this statement

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(80.0, 1.0, 100.0, 5000.0);   //Perspective projection
}

//---------------------------------------------------------------------
void display(void)
{
    float xlook, zlook;
    float cdr=3.14159265/180.0; //Conversion from degrees to radians
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    xlook = -100.0*sin(lookAngle*cdr);
    zlook = -100.0*cos(lookAngle*cdr);
    gluLookAt (0, 500, 0, xlook, 500, zlook, 0, 1, 0);  //camera rotation

    skybox();

    glFlush();
}

//--------------------------------------------------------------
 void special(int key, int x, int y)
 {
    if(key==GLUT_KEY_LEFT) lookAngle+=5;         //Turn left
    else if(key==GLUT_KEY_RIGHT) lookAngle-=5;   //Turn right

    glutPostRedisplay();
}
//-------------------------------------------------------------------

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH );
   glutInitWindowSize (700, 700);
   glutInitWindowPosition (50, 50);

   glutCreateWindow ("Sky Box");
   initialise();
   glutDisplayFunc(display);
   glutSpecialFunc(special);

   glutMainLoop();
   return 0;
}
