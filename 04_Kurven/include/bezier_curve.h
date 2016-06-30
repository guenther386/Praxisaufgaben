//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
A Bezier curve.
This class uses the interface "abstract_curve" to define a bezier curve.
Read the information in "abstract_curve.h" for more details.
*************************************************************************/

#pragma once

// provides the abstract curve interface
#include "abstract_curve.h"



class bezier_curve: public abstract_curve
{
public:
	// Initialize the curve and store a reference of the control points
	bezier_curve(std::vector<point2d>& control_points);

	// The specified "evaluate_basis" to evaluate a basis function for
	// the control point "point_num" at the position "t"
	double evaluate_basis(int point_num, double t);

	// The specified "set_text" method to put arbitrary text into the
	// stream "stream"
	void set_text(std::stringstream &stream);


private:
	// A helper function to calculate "n choose k"
	double binomial_coefficient(int n, int k);
};