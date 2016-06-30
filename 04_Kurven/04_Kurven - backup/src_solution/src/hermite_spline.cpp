//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "hermite_spline.h"
#include <math.h>


// Initialize the curve and store a reference of the control points
hermite_spline::hermite_spline(std::vector<point2d>& control_points): abstract_curve(control_points)
{

}




// Evaluate the curve at "t"
point2d hermite_spline::evaluate(double t)
{
	int n = control_points.size();

	if (n<3)
		return point2d(0.0, 0.0);

	point2d q1 = control_points[0];
	point2d q2 = control_points[n-1];
	point2d m1 = control_points[1] - control_points[0];
	point2d m2 = control_points[n-1] - control_points[n-2];

	return q1*evaluate_basis(0, t) + 
		   m1*evaluate_basis(1, t) + 
		   m2*evaluate_basis(2, t) + 
		   q2*evaluate_basis(3, t);
}




// Evaluate a basis as a function of the control point "point_num"
// (counted from zero) and the domain parameter t
double hermite_spline::evaluate_basis(int point_num, double t)
{
	switch (point_num){
	case 0:
		return pow(1-t,2)*(1+2*t);
	case 1:
		return t*pow(1-t,2);
	case 2:
		return -pow(t,2)*(1-t);
	case 3:
		return (3-2*t)*pow(t,2);
	default:
		return 0;
	}
}



// Set debug text
void hermite_spline::set_text(std::stringstream &stream)
{
	stream<<"Type: Hermite (simple)";
}