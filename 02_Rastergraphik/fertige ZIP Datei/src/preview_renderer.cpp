//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "preview_renderer.h"

#include "GL/glut.h"

// define math constants such as M_PI in math.h
#define _USE_MATH_DEFINES
// needed for mathematical operations
#include <math.h>

// Initialize the preview renderer
preview_renderer::preview_renderer()
{
	// Initially disabled with no shape
	start_x = 0;
	start_y = 0;
	dest_x = 0;
	dest_y = 0;
	shape = TS_NONE;
	enabled = false;
}


// Enable rendering of previews
void preview_renderer::enable_rendering()
{
	enabled = true;
}


// Disable rendering of previews
void preview_renderer::disable_rendering()
{
	enabled = false;
}


// Set the start of a 2-point shape
void preview_renderer::set_start(int x, int y)
{
	start_x = x;
	start_y = y;
	dest_x = start_x;
	dest_y = start_y;
}


// Set the destination of a 2-point shape
void preview_renderer::set_dest(int x, int y)
{
	dest_x = x;
	dest_y = y;
}


// Set the shape
void preview_renderer::set_shape(ToolShape shape)
{
	this->shape = shape;
}


// Render the preview
void preview_renderer::render()
{
	// Do nothing if rendering is disabled
	if (!enabled)
		return;

	// Set the color to green
	glColor3d(0, 1, 0);

	// Render different shapes according to the value in "shape"
	// which was set using the "set_shape" command
	switch(shape) {

		// Render a line
		case TS_LINE:
			glBegin(GL_LINES);
			glVertex2d(start_x, start_y);
			glVertex2d(dest_x, dest_y);
			glEnd();
			break;

		// Render a box
		case TS_BOX:
			glBegin(GL_LINE_STRIP);
			glVertex2d(start_x, start_y);
			glVertex2d(dest_x, start_y);
			glVertex2d(dest_x, dest_y);
			glVertex2d(start_x, dest_y);
			glVertex2d(start_x, start_y);
			glEnd();
			break;

		// Render a circle
		case TS_CIRCLE:
			glBegin(GL_LINE_STRIP);
			// Calculate the radius
			double radius = sqrt(static_cast<double>((dest_x-start_x)*(dest_x-start_x) + (dest_y-start_y)*(dest_y-start_y)));
			// Render the circle by providing consecutive points with
			// the calculated radius around the start point in 5deg steps
			for (int a=0; a<=360; a+=5) 
				glVertex2d(start_x+cos(a/180.0*M_PI)*radius, start_y+sin(a/180.0*M_PI)*radius);
			glEnd();
	}
}
