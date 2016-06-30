//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "abstract_curve.h"

// Initialize the curve and store a reference of the control points
abstract_curve::abstract_curve(std::vector<point2d> &control_points): control_points(control_points)
{
	t_min = 0;
	t_max = 1;
}


abstract_curve::~abstract_curve() {}

// Evaluate the curve at "t"
point2d abstract_curve::evaluate(double t)
{
	point2d sample(0.0, 0.0);

	for (unsigned int i=0; i<control_points.size(); i++)
		sample += evaluate_basis(i, t) * control_points[i];

	return sample;
}



// Get the minimum value of the domain
double abstract_curve::get_min_t()
{
	return t_min;
}




// Get the maximum value of the domain
double abstract_curve::get_max_t()
{
	return t_max;
}




// Get a constant list of control points
const std::vector<point2d>& abstract_curve::get_control_points() const
{
	return control_points;
}




// Shall be called whenever the control point set changes
void abstract_curve::control_points_updated()
{
	// ... does nothing and should be specified in inherited classes
	// if needed.
}




// Put a text into the stream "stream" which will be displayed
// in the main window
void abstract_curve::set_text(std::stringstream &stream)
{
	// ... does nothing and should be specified in inherited classes
	// if needed.
}
