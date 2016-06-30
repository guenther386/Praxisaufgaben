//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
A BSpline.
This class uses the interface "abstract_curve" to define a bspline.
Read the information in "abstract_curve.h" for more details.
*************************************************************************/

// provides the abstract curve interface
#include "abstract_curve.h"


class bspline: public abstract_curve
{
public:
	// Initialize the curve and store a reference of the control points.
	// Also the degree of the curve is provided through this constructor
	bspline(std::vector<point2d>& control_points, int degree);



	// hier die eigene funktion evalute_deboor()
	double bspline::evaluate_deboor(int point_num, double t);



	// The specified "evaluate_basis" to evaluate a basis function for
	// the control point "point_num" at the position "t"
	double evaluate_basis(int point_num, double t);

	// Another version of the evaluate_basis method with a specifyable
	// degree. This method can be used for the recursive evaluation of 
	// the basis functions
	double evaluate_basis(int degree, int point_num, double t);

	// The specified "control_points_updated" to adjust the knot vector
	// when control points are added or removed
	void control_points_updated();


	// The specified "set_text" method to put arbitrary text into the
	// stream "stream"
	void set_text(std::stringstream &stream);


private:
	// The degree of the spline
	int degree;
	// The knot vector (Knotenvektor)
	std::vector<double> u;

	// Calculate the knot vector. This method is called from 
	// "control_points_updated"
	void calculate_knot_vector();
};