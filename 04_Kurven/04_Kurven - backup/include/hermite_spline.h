//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
A simple hermite curve.
This class uses the interface "abstract_curve" to define a hermite curve.
Read the information in "abstract_curve.h" for more details.
*************************************************************************/

#pragma once

// provides the abstract curve interface
#include "abstract_curve.h"



class hermite_spline: public abstract_curve
{
public:
	// Initialize the curve and store a reference of the control points
	hermite_spline(std::vector<point2d>& control_points);

	// The specified "evaluate" method to evaluate a curve point as a
	// function of the domain parameter "t".
	point2d evaluate(double t);

	// The specified "evaluate_basis" to evaluate a basis function for
	// the control point "point_num" at the position "t"
	double evaluate_basis(int point_num, double t);


	// The specified "set_text" method to put arbitrary text into the
	// stream "stream"
	void set_text(std::stringstream &stream);

};