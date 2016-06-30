//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
Abstract curve.
This class provides a basic interface for all curve types. It is 
constructed by passing a reference of a list of control points. 
It corresponds to the mathematical formulation of a curve c(t) via the
"evaluate" method that returns a certain point as a function of the
domain parameter "t". The range of "t" can be obtained with the methods
"get_min_t" and "get_max_t".
Since every point on a curve is generally the sum of the control
points weightened with basis functions for every control point
the interface declares the method "evaluate_basis" as a function
of the parameter "t" and a control point. Specific curves have to
implement that method accordingly.
Because the control points are updated outside of an inherited instance
of this class the method "control_points_updated" is called after
every change, addition or removal of a control point.
The rendering of the curve is not part of this interface but provided
in another class called "curve_renderer".
For debugging purpose an additional method called "set_text" is
provided. Text put into the stream which is passed as a parameter to
this function will be displayed in the main window.
**************************************************************************/

#pragma once

// needed for arbitrary long lists
#include <vector>
// needed for the set_text method
#include <sstream>
// needed for the data type "point2d"
#include "tiny_vec.h"


class abstract_curve 
{
public:
	// Initialize the curve and store a reference of the control points
	abstract_curve(std::vector<point2d> &control_points);

	virtual ~abstract_curve();

	// Get the minimum value of the domain
	double get_min_t();
	// Get the maximum value of the domain
	double get_max_t();

	// casteljau t
	double get_casteljau_t();
	int casteljau_t;

	// Evaluate a curve point as a function of the parameter "t". The
	// range of that function is given by "get_min_t" and "get_max_t"
	virtual point2d evaluate(double t);

	// Evaluate a basis as a function of a control point and 
	// the parameter "t"
	virtual double evaluate_basis(int point_num, double t) = 0;

	// Shall be called whenever the control point set changes
	virtual void control_points_updated();


	// Get a constant list of control points
	const std::vector<point2d>& get_control_points() const;

	// Put a text into the stream "stream" which will be displayed
	// in the main window
	virtual void set_text(std::stringstream &stream);

protected:
	// Range of the domain
	double t_min, t_max, t_de_cast;
	// The reference of the control points
	std::vector<point2d> &control_points;
};