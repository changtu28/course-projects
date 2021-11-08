//  ========================================================================
//  COSC363: Computer Graphics (2018)  University of Canterbury.
//
//  FILE NAME: CylinderDraw.cpp
// 
//	See Lab10.pdf for details.
//  ========================================================================

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Cylinder.h"
#include "loadTGA.h"
using namespace std;

GLuint texID;
GLuint mvMatrixLoc, mvpMatrixLoc, norMatrixLoc;
float angle = 0.0;
glm::mat4 proj, view;  //Matrices
Cylinder *cylinder;

const float CDR = 3.14159265/180.0;   //Conversion from degrees to radians (required in GLM 0.9.6)

void loadTextures()
{
    glGenTextures(1, &texID);
   // Load dots texture
    glActiveTexture(GL_TEXTURE0);   //Texture unit 0
    glBindTexture(GL_TEXTURE_2D, texID);
	loadTGA("Dots.tga");

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void initialise()
{
	loadTextures();
	GLuint program = createShaderProg("Cylinder.vert", "Cylinder.frag");
	mvMatrixLoc = glGetUniformLocation(program, "mvMatrix");
	mvpMatrixLoc = glGetUniformLocation(program, "mvpMatrix");
	norMatrixLoc = glGetUniformLocation(program, "norMatrix");
	GLuint lgtLoc = glGetUniformLocation(program, "lightPos");

   //  Define a uniforrm variable "textureDots" in fragment shader and pass the value 0 <<<<<<<<<<<<<< 

	glm::vec4 light = glm::vec4(10.0, 10.0, 20.0, 1.0);
	proj = glm::perspective(10.0f*CDR, 1.0f, 100.0f, 1000.0f);  //perspective projection matrix
	view = glm::lookAt(glm::vec3(0.0, 30.0, 150.0), glm::vec3(0.0, 8.0, 0.0), glm::vec3(0.0, 1.0, 0.0)); //view matrix
	glm::vec4 lightEye = view*light;     //Light position in eye coordinates
	glUniform4fv(lgtLoc, 1, &lightEye[0]);

	cylinder = new Cylinder(6.0, 16.0, 36, 5);   //Radius, height, slices, stacks
	
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}


void update(int value)
{
	angle++;
	glutTimerFunc(50, update, 0);
	glutPostRedisplay();
}

void display()
{
	glm::mat4 mvMatrix = glm::rotate(view, angle*CDR, glm::vec3(0.0, 1.0, 0.0));  //Model-View matrix
	glm::mat4 mvpMatrix = proj * mvMatrix;      //Model-view-projection matrix
	glm::mat4 invMatrix = glm::inverse(mvMatrix);  //Inverse of model-view matrix for normal transformation
	glUniformMatrix4fv(mvMatrixLoc, 1, GL_FALSE, &mvMatrix[0][0]);
	glUniformMatrix4fv(mvpMatrixLoc, 1, GL_FALSE, &mvpMatrix[0][0]);
	glUniformMatrix4fv(norMatrixLoc, 1, GL_TRUE, &invMatrix[0][0]);  //Use transpose matrix here

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cylinder->render();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cylinder");
	glutInitContextVersion (4, 2);
	glutInitContextProfile ( GLUT_CORE_PROFILE );

	if(glewInit() != GLEW_OK)
	{
		cerr << "Unable to initialize GLEW  ...exiting" << endl;
		exit(EXIT_FAILURE);
	}

	initialise();
	glutDisplayFunc(display);
	glutTimerFunc(50, update, 0);
	glutMainLoop();
}

