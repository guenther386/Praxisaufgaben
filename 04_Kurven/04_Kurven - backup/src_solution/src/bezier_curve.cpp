//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "bezier_curve.h"
#include <math.h>


// Initialize the curve and store a reference of the control points
bezier_curve::bezier_curve(std::vector<point2d>& control_points): abstract_curve(control_points)
{

}




// A helper function to calculate "n choose k"
double bezier_curve::binomial_coefficient(int n, int k)
{
	// Exploit symmetry of pascals triangle
	if (k*2>n)
		k = n-k;

	if (k<0)
		return 0;

	int result = 1;

	// Do not produce too big numbers by dividing
	// the result after each step
	for (int i=0; i<k;++i)
		result = (result*(n-i)) / (i+1);

	return result;
}




// Evaluate a basis as a function of the control point "point_num"
// (counted from zero) and the domain parameter t
double bezier_curve::evaluate_basis(int point_num, double t)
{
	int n = control_points.size()-1;
	int i = point_num;

	return binomial_coefficient(n, i)*pow(t, i)*pow(1.0-t, n-i);
}



// Set debug text
void bezier_curve::set_text(std::stringstream &stream)
{
	stream<<"Type: Bezier";
}