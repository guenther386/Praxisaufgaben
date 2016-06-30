//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2015 CGV TU Dresden - All Rights Reserved
//
#include "lagrange_curve.h"

lagrange_curve::lagrange_curve(std::vector<point2d>& control_points): abstract_curve(control_points)
{

}




// Called when the control points change.
void lagrange_curve::control_points_updated()
{
	// Update the valid range for "t" according to the
	// number of control points
	t_max = control_points.size()-1;
	if (t_max<0)
		t_max = 0;
}




// Evaluate a basis as a function of the control point "point_num"
// (counted from zero) and the domain parameter t
double lagrange_curve::evaluate_basis(int point_num, double t)
{
	double result = 1.0;

	for (int i=0; i<(int)control_points.size(); i++)
		if (i != point_num)
			result *= (t - i)/(point_num-i);

	return result;
}




// Set debug text
void lagrange_curve::set_text(std::stringstream &stream)
{
	stream<<"Type: Lagrange";
}