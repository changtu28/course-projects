//  ============================================================================
//  COSC363  Computer Graphics (2014);  University of Canterbury.
//
//  FILE NAME: Cylinder.cpp
//
//  =============================================================================

#include <iostream>
#include "Cylinder.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
using namespace std;

const float Cylinder:: TWOPI = 6.2831853;

Cylinder:: Cylinder(float radius, float height, int nslices, int nstacks)
{	
    int nverts  = (nslices+1) * (nstacks + 1);    
	nelms = nslices * nstacks * 4;

    float *verts = new float[nverts * 3];		//3 coords per vertex
    float *normals = new float[nverts * 3];		//3 coords per normal
	float *texCoords = new float[nverts *2];    //2 texture coords per vertex
    unsigned int *elems = new unsigned int[nelms]; //elements

    float phiStep = TWOPI /(float) nslices;
	float hStep = height/(float) nstacks;
	float phi = 0.0, cph, sph, y = 0.0;
    int indx = 0, indxt = 0;

	//Generate vertex coordinates
	for(int slice = 0; slice <= nslices; slice++) 
	{
		phi = slice * phiStep;
        cph = cos(phi);
        sph = sin(phi);
		for(int stack = 0; stack <= nstacks; stack++)
		{
			y = stack * hStep;
            verts[indx] = cph * radius;
            verts[indx + 1] = y;
            verts[indx + 2] = - sph * radius;
            normals[indx] = cph;
            normals[indx + 1] = 0.0;
            normals[indx + 2] = -sph;
			texCoords[indxt] = phi/TWOPI;
			texCoords[indxt + 1] = y/height;
            indx += 3;
			indxt += 2;
        }
    }

    int ielndx = 0;
	int startindx;
	int currindx;
    for(int slice = 0; slice < nslices; slice++) 
	{
		startindx = (nstacks + 1)* slice;    //starting index on current slice
		for(int stack = 0; stack < nstacks; stack++)
		{
			currindx = startindx + stack;
            elems[ielndx] = currindx + 1;
            elems[ielndx + 1] = currindx;
			elems[ielndx + 2] = currindx + nstacks + 1;
			elems[ielndx + 3] = currindx + nstacks + 2;
			ielndx += 4;
        }
    }

    glGenVertexArrays( 1, &vaoID );
    glBindVertexArray(vaoID);

    GLuint vboID[4];
    glGenBuffers(4, vboID);

    glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
    glBufferData(GL_ARRAY_BUFFER, (indx) * sizeof(float), verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
    glBufferData(GL_ARRAY_BUFFER, (indx) * sizeof(float), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, vboID[2]);
    glBufferData(GL_ARRAY_BUFFER, (indx) * sizeof(float), texCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(2);  // texture coords


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (ielndx) * sizeof(unsigned int), elems, GL_STATIC_DRAW);

    delete [] verts;
    delete [] normals;
	delete [] texCoords;
    delete [] elems;

    glBindVertexArray(0);
}

void Cylinder::render() const
{
    glBindVertexArray(vaoID);
    glDrawElements(GL_QUADS, nelms, GL_UNSIGNED_INT, NULL);
}

