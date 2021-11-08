//  ========================================================================
//  COSC363: Computer Graphics (2018);  University of Canterbury.
//
//  FILE NAME: Humanoid.cpp
//  See Lab02.pdf for details
//  ========================================================================

#include <iostream>
#include <fstream>
#include <cmath>
#include <GL/freeglut.h>
using namespace std;

//--Globals ---------------------------------------------------------------
int cam_hgt = 8; //Camera height
float angle = 10.0;  //Rotation angle for viewing
float theta = 20.0;
int movingForward = 0;

void myTimer(int value) {
    if (movingForward == 1) {
        theta++;
        if (theta == 20) {
            movingForward = 0;
        }
    } else {
        theta--;
        if(theta == -20) {
            movingForward = 1;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(50, myTimer, 0);
}

//--Draws a grid of lines on the floor plane -------------------------------
void drawFloor()
{
    glColor3f(0., 0.5, 0.);         //Floor colour
    for(float i = -50; i <= 50; i ++)
    {
        glBegin(GL_LINES);          //A set of grid lines on the xz-plane
            glVertex3f(-50, 0, i);
            glVertex3f(50, 0, i);
            glVertex3f(i, 0, -50);
            glVertex3f(i, 0, 50);
        glEnd();
    }
}

//--Draws a character model constructed using GLUT objects ------------------
void drawModel()
{
    glColor3f(1., 0.78, 0.06);      //Scanner Body
    glPushMatrix();
        glTranslatef(0, 7.7, 1.5);
        glScalef(1, 2, 1);
        glutSolidCube(1.4);
    glPopMatrix();

    glPushMatrix();                 //Scanner sphere/head
        glTranslatef(0, 8.7, 1.5);
        glutSolidSphere(1.4, 10, 10);
    glPopMatrix();

    glPushMatrix();                 //Tail
        glTranslatef(0, 7.5, -3.5);
        glRotatef(-45, 1, 0, 0);
        glTranslatef(0, -7.5, 3.5);
        glTranslatef(0, 7.5, -3.5);
        glScalef(0.8, 15, 0.8);
        glutSolidCube(0.2);
    glPopMatrix();

    glPushMatrix();                 //Tail end
        glTranslatef(0, 8.5, -4.5);
        glutSolidSphere(0.2, 10, 10);
    glPopMatrix();

    glColor3f(1., 0., 0.);          //Torso
    glPushMatrix();
        glTranslatef(0, 5.5, 0);
        glRotatef(90, 1, 0, 0);
        glScalef(3.75, 6.2, 2);
        glutSolidCube(1);
    glPopMatrix();

    glColor3f(0., 0., 1.);          //Front Right Leg
    glPushMatrix();
        glTranslatef(-1.05, 4.4, 2.3);
        glRotatef(-theta, 1, 0, 0);
        glTranslatef(1.05, -4.4, -2.3);
        glTranslatef(-1.05, 2.6, 2.3);
        //glTranslatef(-0.8, 2.2, 0);
        glScalef(1, 4.4, 1);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();                 //Front Right Leg Socket
        glTranslatef(-1.05, 4.6, 2.3);
        glutSolidSphere(0.8, 10, 10);
    glPopMatrix();

    glColor3f(0., 0., 1.);          //Front Left Leg
    glPushMatrix();
        glTranslatef(1.05, 4.4, 2.3);
        glRotatef(theta, 1, 0, 0);
        glTranslatef(-1.05, -4.4, -2.3);
        glTranslatef(1.05, 2.6, 2.3);
        glScalef(1, 4.4, 1);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();                 //Front Left Leg Socket
        glTranslatef(1.05, 4.6, 2.3);
        glutSolidSphere(0.8, 10, 10);
    glPopMatrix();

    glColor3f(0., 0., 1.);          //Back Right Leg
    glPushMatrix();
        glTranslatef(-1.05, 4.4, -2.3);
        glRotatef(-theta, 1, 0, 0);
        glTranslatef(1.05, -4.4, 2.3);
        glTranslatef(-1.05, 2.6, -2.3);
        glScalef(1, 4.4, 1);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();                 //Back Right Leg Socket
        glTranslatef(-1.05, 4.6, -2.3);
        glutSolidSphere(0.8, 10, 10);
    glPopMatrix();


    glColor3f(0., 0., 1.);          //Back Left Leg
    glPushMatrix();
        glTranslatef(1.05, 4.4, -2.3);
        glRotatef(theta, 1, 0, 0);
        glTranslatef(-1.05, -4.4, 2.3);
        glTranslatef(1.05, 2.6, -2.3);
        glScalef(1, 4.4, 1);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();                 //Back Left Leg Socket
        glTranslatef(1.05, 4.6, -2.3);
        glutSolidSphere(0.8, 10, 10);
    glPopMatrix();
}

void drawModel2()
{

    //Main Body
    glColor3f(0.1, 0.1, 0.1);
    glPushMatrix();
        glScalef(0.8, 2, 0.8);
        glutSolidSphere(2, 50, 50);
    glPopMatrix();

    //Eye - White
    glColor3f(1, 1, 1);
    glPushMatrix();
        glTranslatef(1.2, 1, 0);
        glScalef(0.5, 1, 1);
        glutSolidSphere(1, 20, 20);
    glPopMatrix();

    //Eye - Iris
    glColor3f(1, 0, 0);
    glPushMatrix();
        glTranslatef(1.5, 1, 0);
        glScalef(0.5, 1, 1);
        glutSolidSphere(0.5, 10, 10);
    glPopMatrix();

}

//--Display: ---------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display()
{
    float lpos[4] = {10., 10., 10., 1.0};  //light's position

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, cam_hgt, 10, 0, 4, 0, 0, 1, 0);
    glLightfv(GL_LIGHT0,GL_POSITION, lpos);   //Set light position

    glRotatef(angle, 0.0, 1.0, 0.0);  //Rotate the scene about the y-axis

    glDisable(GL_LIGHTING);         //Disable lighting when drawing floor.
    drawFloor();

    glEnable(GL_LIGHTING);         //Enable lighting when drawing the model
    drawModel2();

    glFlush();
}

//------- Initialize OpenGL parameters -----------------------------------
void initialize()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   //Background colour

    glEnable(GL_LIGHTING);                  //Enable OpenGL states
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 1000.0);   //Camera Frustum
}

//------------ Special key event callback ---------------------------------
// To enable the use of left and right arrow keys to rotate the scene
void special(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT) angle--;
    else if(key == GLUT_KEY_RIGHT) angle++;
    glutPostRedisplay();
}

//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH);
   glutInitWindowSize (600, 600);
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("Humanoid");
   initialize();

   glutDisplayFunc(display);
   glutSpecialFunc(special);
   glutTimerFunc(50, myTimer, 0);
   glutMainLoop();
   return 0;
}
