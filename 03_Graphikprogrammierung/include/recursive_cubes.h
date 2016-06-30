//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
Recursive cubes.
This class represents a recursive cube tree where an element is recursively 
defined as a cube with the same element at each side (only smaller).
It demonstrates the use of glPushMatrix and glPopMatrix in the 
construction of recursive transformation trees.
The method "render" sets the projection and view via "setup_projection",
the scene light via "setup_light" and starts the recursion by calling
"render_recursive". This method calls itself to perform the actual
recursion. To render a single cube it uses "render_cube".
*************************************************************************/
#pragma once

#include "abstract_scene.h"

class recursive_cubes: public abstract_scene
{
public:
	// Initialize variables
	recursive_cubes();

	// Render the scene
	void render();

	// Advance one frame
	void advance_frame();

	// Set debug text
	void set_text(std::stringstream &stream);

private:
	// Rotation angle
	int angle;
	// Maximum recursion depth
	int depth;

	// The recursive render method. "r" contains the current
	// recursion depth and "render_first" is a flag to inicate
	// that all sides have neighbours.
	void render_recursive(int r, bool render_all, int children);

	// Render one single cube
	void render_cube();

	// Set the light parameters
	void setup_light();

	// Set the projection and the view
	void setup_projection();
};