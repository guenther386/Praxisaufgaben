//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "example_3d_primitives.h"


// define math constants such as M_PI in math.h
#define _USE_MATH_DEFINES
// needed for mathematical operations
#include <math.h>



example_3d_primitives::example_3d_primitives()
{
	angle = 0;
}




void example_3d_primitives::render()
{
	glEnable(GL_DEPTH_TEST);

	// Clear the screen
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Setup a perspective projection and lighting
	setup_projection();
	setup_light();

	glScaled(0.4, 0.4, 0.4);

	// Move 5 units to the left, save the current transformation
	// and show a rotated tetrahedron
	glTranslated(-5, 0, 0);
	glPushMatrix();
	glRotated(angle, 0, 1, 0);
	glColor3d(1, 1, 0);
	render_tetrahedron();
	glPopMatrix();

	// Move 3 units to the right, save the current transformation
	// and show a rotated cylinder
	glTranslated(3, 0, 0);
	glPushMatrix();
	glRotated(angle, 1, 0, 0);
	glColor3d(0, 1, 0);
	render_cylinder();
	glPopMatrix();

	// Move 3 units to the right, save the current transformation
	// and show a rotated cube
	glTranslated(3, 0, 0);
	glPushMatrix();
	glRotated(angle, 0, 1, 1);
	glColor3d(1, 0, 0);
	render_cube();
	glPopMatrix();

	// Move 3 units to the right, save the current transformation
	// and show a rotated sphere
	glTranslated(3, 0, 0);
	glPushMatrix();
	glRotated(angle, 0, 1, 0);
	glColor3d(0, 0, 1);
	render_sphere();
	glPopMatrix();
}




void example_3d_primitives::render_tetrahedron()
{
	// The tetrahedron is rendered by explicitly providing all 4 sides

	// Activate rendering of triangles
	glBegin(GL_TRIANGLES);

	glNormal3d(-1, 2, 1);
	glVertex3d(0, 1, 1);
	glVertex3d(-1, 1, -1);
	glVertex3d(0, -1, 0);

	glNormal3d(1, 2, 1);
	glVertex3d(1, 1, -1);
	glVertex3d(0, 1, 1);
	glVertex3d(0, -1, 0);

	glNormal3d(0, 2, -1);
	glVertex3d(0, -1, 0);
	glVertex3d(-1, 1, -1);
	glVertex3d(1, 1, -1);

	glNormal3d(0, 2, 0);
	glVertex3d(0, 1, 1);
	glVertex3d(1, 1, -1);
	glVertex3d(-1, 1, -1);

	glEnd();  
}



void example_3d_primitives::render_cylinder()
{
	// The cylinder is first rendered by connected quads and then
	// two polygons for the top and bottom

	// Begin a strip of rectangles
	glBegin(GL_QUAD_STRIP);
	for (int i=0; i<=360; i+=10)  {
		// One quad is specified by 2 vertices that are connected
		// to the last 2 vertices. Basically they are an extruded
		// circle in the X-Z-Layer.
		glNormal3d(cos(i*M_PI/180.0), 0, sin(i*M_PI/180.0));
		glVertex3d(cos(i*M_PI/180.0), -1, sin(i*M_PI/180.0));
		glVertex3d(cos(i*M_PI/180.0), 1, sin(i*M_PI/180.0));
	}
	glEnd();

	// The top is a filled circle that is drawn with a single polygon
	glBegin(GL_POLYGON);
	glNormal3d(0, -1, 0);
	for (int i=0; i<=360; i+=10) {
		glVertex3d(cos(i*M_PI/180.0), -1, sin(i*M_PI/180.0));
	}
	glEnd();


	// The bottom is a filled circle that is drawn with a single polygon
	glBegin(GL_POLYGON);
	glNormal3d(0, 1, 0);
	for (int i=360; i>=0; i-=10) {
		glVertex3d(cos(i*M_PI/180.0), 1, sin(i*M_PI/180.0));
	}
	glEnd();
}



void example_3d_primitives::render_cube()
{
	// Use predefined methods here
	glutSolidCube(2.0);
}



void example_3d_primitives::render_sphere()
{
	// An example for quadrics in GLU (GL-Utilities. Not to be
	// confused with GL or GLUT :)
	GLUquadric *sphere = gluNewQuadric();
	gluSphere(sphere, 1.0, 25, 25);
	gluDeleteQuadric(sphere);
}




void example_3d_primitives::setup_projection()
{
	// For projection choose a perspective matrix with an aperture angle of
	// 45deg, an aspect ratio that corresponds to the width and height of the
	// window, z_near at 0.01 and z_far at 10.0
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, glutGet(GLUT_WINDOW_WIDTH) / static_cast<double>(glutGet(GLUT_WINDOW_HEIGHT)), 0.01, 10.0);

	// For the modelview matrix choose a view from the position (2.5, 2.5, 0) to
	// the position (0, 0, 0) where the up-direction is (0, 1, 0).
	// Also rotate with the specified angle around the Y-axis
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,1,5,  0,0,0,  0,1,0);
}



void example_3d_primitives::setup_light()
{
	// Enable lighting and colored materials
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	// Enable light source 0
	glEnable(GL_LIGHT0);

	// Set the modelview matrix to be the identity to avoid
	// having the light position moved with the terrain.
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Set light parameters
	float position[4]={1.0f,1.0f,1.0f,1.0f};
	float ambient_color[4]={0.0f,0.0f,0.0f,1.0f};
	float diffuse_color[4]={1.0f,1.0f,1.0f,1.0f};
	float specular_color[4]={1.0f,1.0f,1.0f,1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_color);

	glLightf(GL_LIGHT0,GL_SPOT_EXPONENT, 10.0f);   

	glPopMatrix();

	glEnable(GL_NORMALIZE);
}



void example_3d_primitives::advance_frame()
{
	angle = (angle+1)%360;
}



void example_3d_primitives::set_text(std::stringstream &stream)
{
	stream<<"Basic 3D primitives (from example_3d_primitives.cpp)";
}