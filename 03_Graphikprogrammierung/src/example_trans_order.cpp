//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "example_trans_order.h"


example_trans_order::example_trans_order()
{
	angle = 0;
}



void example_trans_order::render()
{
	// Disable depth testing and lighting
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	// Clear the screen
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);	

	// Set a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, glutGet(GLUT_WINDOW_WIDTH) / static_cast<double>(glutGet(GLUT_WINDOW_HEIGHT)), 0.01, 10.0);
	
	// Clear the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0, 0, -7);

	glTranslated(-2, 1, 0);

	// The first example first translates and then rotates
	glPushMatrix();
	// Render the green quad
	glColor3d(0, 1, 0);
	render_quad();
	glTranslated(1, 0, 0.1);
	glRotated(angle, 0, 0, 1);
	// Render the transformed black quad
	glColor3d(0, 0, 0);
	render_quad();
	glPopMatrix();


	glTranslated(4, 0, 0);

	// The second example first rotates and then translates
	glPushMatrix();
	// Render the green quad
	glColor3d(0, 1, 0);
	render_quad();
	glRotated(angle, 0, 0, 1);
	glTranslated(1, 0, 0.1);
	// Render the transformed black quad
	glColor3d(0, 0, 0);
	render_quad();
	glPopMatrix();


	glTranslated(0, -2.5, 0);

	// The third example first rotates and then scales
	glPushMatrix();
	// Render the green quad
	glColor3d(0, 1, 0);
	render_quad();
	glRotated(angle, 0, 0, 1);
	glScaled(0.8, 0.3, 1.0);
	// Render the transformed black quad
	glColor3d(0, 0, 0);
	render_quad();
	glPopMatrix();


	glTranslated(-4, 0, 0);

	// The fourth example first scales and then rotates
	glPushMatrix();
	// Render the green quad
	glColor3d(0, 1, 0);
	render_quad();
	glScaled(0.8, 0.3, 1.0);
	glRotated(angle, 0, 0, 1);
	// Render the transformed black quad
	glColor3d(0, 0, 0);
	render_quad();
	glPopMatrix();


}



void example_trans_order::render_quad()
{
	// Render a quad by using a line loop.
	glBegin(GL_LINE_LOOP);
	glVertex3d(-0.5, -0.5, 0);
	glVertex3d(0.5, -0.5, 0);
	glVertex3d(0.5, 0.5, 0);
	glVertex3d(-0.5, 0.5, 0);
	glEnd();
}



void example_trans_order::advance_frame()
{
	angle = (angle+1)%360;
}


void example_trans_order::set_text(std::stringstream &stream)
{
	stream<<"Transformation order matters (top left: trans, rot; top right: rot, trans; bottom left: scale, rot; bottom right: rot, scale)";
}