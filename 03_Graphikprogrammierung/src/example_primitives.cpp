//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "example_primitives.h"

void example_primitives::render()
{
	// Disable lighting and depth testing
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	// Clear the screen to white
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Clear the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Clear the modelview matrix and set a scale
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScaled(0.5, 0.5, 0.5);

	// Set the point size to 3 pixels
	glPointSize(3);

	// Set the drawing color to red
	glColor3d(1, 0, 0);

	// Move to the lower left corner
	glTranslated(-1, -1, 0);


	// An example for points. Every vertex is represented as a point
	glBegin(GL_POINTS);
	glColor3d(0, 0, 0);
	glVertex3d(0, 0, 0);
	glColor3d(1, 0, 0);
	glVertex3d(-0.5, 0, 0);
	glColor3d(0, 1, 0);
	glVertex3d(0.7, 0, 0);
	glColor3d(0, 0, 1);
	glVertex3d(0.5, 0.7, 0);
	glColor3d(0.3, 0.1, 0.7);
	glVertex3d(0.2, -0.3, 0);
	glEnd();


	// Move to the lower right corner
	glTranslated(2, 0, 0);
	// An example for triangles. Each 3 vertices are connected
	// to one triangle. For every vertex a color can be defined which
	// is then interpolated in between
	glBegin(GL_TRIANGLES);
	glColor3d(1, 0, 0);
	glVertex3d(-0.5, 0, 0);
	glVertex3d(0.1, -0.2, 0);
	glVertex3d(0.3, 0.5, 0);

	glColor3d(1, 0, 0);
	glVertex3d(0.4, 0.3, 0);
	glColor3d(0, 1, 0);
	glVertex3d(0.8, 0.9, 0);
	glColor3d(0, 0, 1);
	glVertex3d(0.9, -0.2, 0);
	glEnd();



	// Move to the upper right
	glTranslated(0, 2, 0);
	// An example for rectangles. Each 4 vertices are connected
	// to one quad.
	glBegin(GL_QUADS);
	glColor3d(0, 1, 0);
	glVertex3d(-0.5, -0.6, 0);
	glVertex3d(0.2, -0.5, 0);
	glColor3d(1, 1, 0);
	glVertex3d(0.3, 0.5, 0);
	glVertex3d(-0.5, 0.6, 0);
	glEnd();


	// Move to the upper left
	glTranslated(-2, 0, 0);
	// And example for lines. Each 2 vertices are connected
	// to one line.
	glBegin(GL_LINES);
	glColor3d(0, 0, 0);
	glVertex3d(-0.5, 0.3, 0);
	glVertex3d(0.4, -0.7, 0);

	glColor3d(1, 0, 1);
	glVertex3d(0.4, -0.4, 0);
	glColor3d(0, 1, 0);
	glVertex3d(1.0, -0.2, 0);
	glEnd();


}



void example_primitives::set_text(std::stringstream &stream)
{
	stream<<"Basic colored primitives  (from example_primitives.cpp)";
}