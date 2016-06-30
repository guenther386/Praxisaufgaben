//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "example_cons_primitives.h"



// define math constants such as M_PI in math.h
#define _USE_MATH_DEFINES
// needed for mathematical operations
#include <math.h>




void example_consecutive_primitives::render()
{
	glPushMatrix();

	// Make OpenGL render only the outline of polygons
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// No lighting
	glDisable(GL_LIGHTING);
	// No depth testing
	glDisable(GL_DEPTH_TEST);
	// No face culling (also draw polygones that are turned away from the eye point) 
	glDisable(GL_CULL_FACE);

	// Clear the screen
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Clear the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Clear the modelview matrix and set a scale
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScaled(0.5, 0.5, 0.5);

	// Move to the lower left corner
	glTranslated(-1, -1, 0);
	// An example of quad strips...
	glBegin(GL_QUAD_STRIP);
	for (int i=0; i<5; i++) {
		glVertex3d(i*0.3-0.8, -0.3, 0);
		glVertex3d(i*0.3-0.8, 0.3, 0);
	}
	glEnd();

	// Move to the lower right corner
	glTranslated(2, 0, 0);
	glBegin(GL_TRIANGLE_STRIP);
	// An example of triangle strips. Initially 2 vertices
	// must be defined. Then every further vertex creates a new
	// triangle which is connected to the last 2 vertices.
	glVertex3d(-0.5, -0.6, 0);
	glVertex3d(-0.9, 0.6, 0);
	for (int i=1; i<4; i++) {
		glVertex3d(-0.6+i*0.3, -0.6, 0);
		glVertex3d(-0.6+i*0.5, 0.6, 0);
	}
	glEnd();


	// Move to the upper right corner
	glTranslated(0, 2, 0);
	glBegin(GL_TRIANGLE_FAN);
	// An example of a triangle strip. Initially 1 vertex
	// must be defined. If 3 vertices are provided the first
	// triangle is drawn and with every new vertex a new triangle
	// from the actual point, the last point and the first point
	// is rendered.
	glVertex3d(0, 0, 0);
	for (int i=0; i<=360; i+=45) 
		glVertex3d(cos(i*M_PI/180.0), sin(i*M_PI/180), 0);
	glEnd();

	// Move to the upper left corner
	glTranslated(-2, 0, 0);
	glBegin(GL_LINE_STRIP);
	// An example of a line strip. A line is created between the
	// current vertex and the last.
	for (int i=0; i<4; i++) {
		glVertex3d(-0.6+i*0.3, -0.6, 0);
		glVertex3d(-0.6+i*0.5, 0.6, 0);
	}
	glEnd();


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPopMatrix();
}


void example_consecutive_primitives::set_text(std::stringstream &stream)
{
	stream<<"Basic consecutive primitives as wireframe (from example_cons_primitives.cpp)";
}