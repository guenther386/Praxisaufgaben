//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "bspline.h"

// Initialize the curve and store a reference of the control points.
// Also the degree of the curve is provided through this constructor
bspline::bspline(std::vector<point2d>& control_points, int degree):
abstract_curve(control_points)
{
	this->degree = degree;
}




// The specified "control_points_updated" to adjust the knot vector
// when control points are added or removed
void bspline::control_points_updated()
{
	// Update the knot vector
	calculate_knot_vector();

	// Set the valid range for "t"
	if (u.size() != 0) {
		t_min = u[0];
		t_max = u[u.size()-1];
	}
}




// Calculate the knot vector. This method is called from 
// "control_points_updated"
void bspline::calculate_knot_vector()
{
	// Initialize variables according to the script
	int K = control_points.size();
	int g = degree;
	int n = K - g;

	// Clear and resize the knot vector to the right size
	u.clear();
	u.resize(K + g + 1);

	for (int i=0; i<=g; i++)
		u[i] = 0;

	for (int i=g+1; i<=K; i++)
		u[i] = i-g;

	for (int i=K+1; i<K+g+1; i++)
		u[i] = K-g;
}




// Evaluate the basis as a function of the control point "point_num"
// (counted from zero) and the parameter "t".
double bspline::evaluate_basis(int point_num, double t)
{
	// Make the basis function be defined at t=max_t
	if (t >= get_max_t())
		if (point_num == control_points.size()-1)
			return 1.0;
		else
			return 0.0;

	// Call the recursive version
	return evaluate_basis(degree, point_num, t);
}




// Another version of the evaluate_basis method with a specifyable
// degree. This method can be used for the recursive evaluation of 
// the basis functions
double bspline::evaluate_basis(int g, int i, double t)
{
	if(g == 0) {
		if(t >= u[i] && t < u[i+1])
			return 1.0;
		else
			return 0.0;
	}

	double a = u[i+g] - u[i];

	if( a != 0)
		a = (t-u[i])/a;

	double b = u[i+1+g] - u[i+1];

	if( b != 0)
		b = (u[i+1+g]-t)/b;

	return 
		a*evaluate_basis(g-1, i, t)+
		b*evaluate_basis(g-1, i+1, t);
}



// Set debug text
void bspline::set_text(std::stringstream &stream)
{
	stream<<"Type: BSpline (with degree "<<degree<<")";
}