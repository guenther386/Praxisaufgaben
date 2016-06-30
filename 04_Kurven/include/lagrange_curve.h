//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
A lagrange curve.
This class uses the interface "abstract_curve" to define a lagrange curve.
Read the information in "abstract_curve.h" for more details.
*************************************************************************/

#pragma once

// provides the abstract curve interface
#include "abstract_curve.h"



class lagrange_curve: public abstract_curve
{
public:
	// Initialize the curve and store a reference of the control points
	lagrange_curve(std::vector<point2d>& control_points);

	// The specified "evaluate_basis" to evaluate a basis function for
	// the control point "point_num" at the position "t"
	double evaluate_basis(int point_num, double t);


	// The speficied "control_points_updated" to adjust the domain range
	// as a function of the number of control points
	void control_points_updated();

	// The specified "set_text" method to put arbitrary text into the
	// stream "stream"
	void set_text(std::stringstream &stream);

};