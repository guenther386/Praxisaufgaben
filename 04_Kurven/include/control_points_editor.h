//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
The control points editor.
This class provides a simple graphical editor for control points. It is 
constructed by passing a reference on a list of control points which is
then changed according to mouse events. To recognize the events the user
of an instance of this class has to call mouse_move when the mouse is 
moved and mouse_button when the mouse button states change. Because only
a reference of the control points is used there is no method to return
the control points as the original version which is in the hand of the
user (of an object) is changed implicitly. To recognize whether a
change occured the user can call "control_points_changed" which returns
true in that case. To draw the control points a method called "draw"
is implemented.
**************************************************************************/

#pragma once
#include <vector>
#include "tiny_vec.h"


class control_points_editor
{
public:
	// Initialize members and use a reference of "control_points" 
	// as point list to modify
	control_points_editor(std::vector<point2d> &control_points);

	// Act on mouse moves. This method shall be called whenever
	// the mouse was moved
	void mouse_move(int x, int y);

	// Act on mouse button events. This function shall be called
	// whenever a button is pressed. The parameters "button" and "state"
	// are to be filled with the corresponding GLUT states
	void mouse_button(int button, int state);

	// Return true when the control point list was changed.
	bool control_points_changed();

	// Draw the control points
	void draw_control_points();

	// Draw the control polygon
	void draw_control_polygon();


private:
	// A reference on the control points
	std::vector<point2d> &control_points;
	// The last recognized mouse position
	int last_x, last_y;
	// The currently selected point for moving
	int selected_point;
	// A hovered point 
	int hovered_point;
	// True if the list of points was changed
	bool points_changed;

	// Draw a circle using openGL
	void draw_circle(int x, int y, int r);

	// Find the point which is under the mouse
	int find_hovered_point();


};