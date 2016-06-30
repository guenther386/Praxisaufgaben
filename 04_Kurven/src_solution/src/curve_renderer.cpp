//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "curve_renderer.h"

#include "GL/glut.h"
#include "GL/freeglut_ext.h"


// Initialize the curve renderer
curve_renderer::curve_renderer()
{
	// no curve yet
	curve = 0;

	// Width and heigth of the basis function graph
	basis_width = 300;
	basis_height = 100;
}


// Set the active curve to render
void curve_renderer::set_curve(abstract_curve *curve)
{
	this->curve = curve;
}



// Sample the curve using "sample_count" samples and store the
// result in the list "samples".
void curve_renderer::sample_curve(int sample_count)
{
	samples.clear();

	// Nothing to sample if there are not at least 2 control points
	if (curve->get_control_points().size()<2)
		return;

	double t=0;

	for (int i=0; i<sample_count; i++) {

		t = i/static_cast<double>(sample_count-1)*(curve->get_max_t() - curve->get_min_t());
		samples.push_back(curve->evaluate(t));
	} 
}


// Render the curve
void curve_renderer::render_curve()
{
	int n = samples.size();

	// Set the color to green
	glColor3d(0, 1, 0);

	glBegin(GL_LINE_STRIP);
	for (int i=0; i<n; i++) {
		glVertex3d(samples[i].x(), samples[i].y(), 0);
	}
	glEnd();
}


// Render the basis functions coordinate system
void curve_renderer::render_basis_axes()
{
	glPushMatrix();
	// Translate to the lower right corner
	glTranslated(glutGet(GLUT_WINDOW_WIDTH) - basis_width - 10, glutGet(GLUT_WINDOW_HEIGHT) - basis_height - 10, 0);

	// Render the axes
	glColor3d(0, 0, 0);
	glBegin(GL_LINES);
	// Vertical 
	glVertex2d(0, basis_height);
	glVertex2d(0, -basis_height);
	// Horizontal
	glVertex2d(0, 0);
	glVertex2d(basis_width, 0);
	// Small vertical at the end of the abszissa
	glVertex2d(basis_width, -3);
	glVertex2d(basis_width, 3);
	glEnd();

	// Render the maximum t
	double t_max = curve->get_max_t();
	if (t_max<=0.0)
		t_max = 1.0;

	std::stringstream s;
	s<<t_max;

	glColor3d(0.0, 0.0, 0.0);
	glRasterPos2i(basis_width-5, 15);
	glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>(s.str().c_str()));

	glPopMatrix();
}


// A helper function you can use to set a color for the basis function
void curve_renderer::set_basis_color(int i)
{
	i++;
	// Set the color according to the basis function to render
	glColor3d(i%2, (i%3)/2.0, (i%5)/6.0);
}



// Render the basis functions
void curve_renderer::render_basis_functions()
{
	double t_max = curve->get_max_t();

	// Only render the axes if the range is too small
	if (t_max <=0.0) {
		render_basis_axes();
		return;
	}

	// Translate to the lower bottom of the screen and scale
	// into the local coordinate system of the basis function graph
	glPushMatrix();
	glTranslated(glutGet(GLUT_WINDOW_WIDTH) - basis_width - 10, glutGet(GLUT_WINDOW_HEIGHT) - basis_height - 10, 0);
	glScaled(basis_width/t_max, -basis_height, 1);

	// Render the basis functions
	for (unsigned int i=0; i<curve->get_control_points().size(); i++) {

		glBegin(GL_LINE_STRIP);

		set_basis_color(i);
		for (double t = 0; t<=t_max; t+=t_max/100)
			glVertex2d(t, curve->evaluate_basis(i, t));
		glEnd();
	}

	glPopMatrix();


	// Render the axes
	render_basis_axes();
}