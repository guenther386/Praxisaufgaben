//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "cube_system.h"

// Initialize variables
cube_system::cube_system()
{
	angle = 0;
}



// Setup the scene and render cube system
void cube_system::render()
{
	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	// Disable lighting
	glDisable(GL_LIGHTING);

	// Clear the screen and depth buffer
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set the projection and view
	setup_projection();

	// Render the system
	render_system();
}



// Render the cube system
void cube_system::render_system()
{
	glPushMatrix();
		glPushMatrix();
			glRotated(angle, 0.0, 1.0, 0.0);
			render_cube();
		glPopMatrix();

		glRotated(-angle, 0, 1, 0);
		glTranslated(5, 0, 0);
		glScaled(0.6, 0.6, 0.6);
		render_cube();

			glPushMatrix();
				glRotated(2 * angle, 0, 0, 1);
				glTranslated(3, 0, 0);
				glScaled(0.5, 0.5, 0.5);
				render_cube();
			glPopMatrix();

			glPushMatrix();
				glRotated(2 * angle + 180, 0, 0, 1);
				glTranslated(3, 0, 0);
				glScaled(0.5, 0.5, 0.5);
				render_cube();
			glPopMatrix();

	glPopMatrix();
}



// Advance one frame by increasing the rotation angle
void cube_system::advance_frame()
{
	// Increase angle and perform a modulo 360
	angle = (angle+1)%360;
}



// Render one single cube
void cube_system::render_cube()
{
	glPushMatrix();
	for (int i=0; i<4; i++) {

		switch(i) {
			case 0: glColor3d(165/255.0, 165/255.0, 165/255.0); break;
			case 1: glColor3d( 73/255.0,  68/255.0,  41/255.0); break;
			case 2: glColor3d( 23/255.0,  54/255.0,  93/255.0); break;
			case 3: glColor3d(149/255.0,  55/255.0,  52/255.0); break;
		}

		glRotated(90, 0, 1, 0);
		glBegin(GL_QUADS);
			glVertex3d(-1, 1, -1);
			glVertex3d(1, 1, -1);
			glVertex3d(1, -1, -1);
			glVertex3d(-1, -1, -1);
		glEnd();
	}

	glBegin(GL_QUADS);
	glColor3d(118/255.0, 146/255.0, 60/255.0);
	glVertex3d(-1, 1, -1);
	glVertex3d(-1, 1, 1);
	glVertex3d( 1, 1, 1);
	glVertex3d(1, 1, -1);

	glColor3d(95/255.0, 73/255.0, 122/255.0);
	glVertex3d(1, -1, -1);
	glVertex3d( 1, -1, 1);
	glVertex3d(-1, -1, 1);
	glVertex3d(-1, -1, -1);

	glEnd(); 

	glPopMatrix();
}



// Set the projection and the view
void cube_system::setup_projection()
{
	// For projection choose a perspective matrix with an aperture angle of
	// 45deg, an aspect ratio that corresponds to the width and height of the
	// window, z_near at 0.01 and z_far at 100.0
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, glutGet(GLUT_WINDOW_WIDTH) / static_cast<double>(glutGet(GLUT_WINDOW_HEIGHT)), 0.01, 100.0);

	// For the modelview matrix choose a view from the position (10.0, 6.0, -10.0) to
	// the position (0, 0, 0) where the up-direction is (0, 1, 0).
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10.0,6.0,-10.0,  0,0,0,  0,1,0);
}



// Set debug text
void cube_system::set_text(std::stringstream &stream)
{
	stream<<"Showing cube system (with rotation parameter at "<<angle<<"°)";
}