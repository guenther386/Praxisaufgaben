//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
The curve renderer.
This class is responsible for rendering curves using OpenGL. The curve
to render must implement the interface "abstract_curve" and is provided
via the "set_curve" method. The method "render_curve" performs the 
rendering. Whenever the curve changes the method "sample_curve" is called
which samples the curve at equidistant intervals of the domain parameter "t".
The number of samples can be specified using the parameter "sample_count".
For rendering the basis functions the method "render_basis_functions" is
provided which also invokes the method "render_basis_axes" for rendering
the coordinate system.
*************************************************************************/

#pragma once

// provides the abstract curve interface
#include "abstract_curve.h"

class curve_renderer
{
public:
	// Initialize the curve renderer
	curve_renderer();

	// Sample the curve using "sample_count" samples and store the
	// result in the list "samples".

	void sample_curve(int sample_count);
	// Set the active curve to render
	void set_curve(abstract_curve *curve);

	// render de_casteljau
	void render_de_cast(std::vector<point2d> remaining_control_points, double t);

	// Render the curve
	void render_curve();

	// Render the basis functions
	void render_basis_functions();

private:
	// The curve to render
	abstract_curve *curve;

	// A list of samples of the curve
	std::vector<point2d> samples;

	// The width and height of the coordinate system of the basis functions
	int basis_width, basis_height;


	// Render the basis functions coordinate system
	void render_basis_axes();
	// Set an OpenGL color for a basis function "i"
	void set_basis_color(int i);
};