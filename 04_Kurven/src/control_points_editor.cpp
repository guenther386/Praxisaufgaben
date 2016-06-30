//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "control_points_editor.h"
#include "GL/glut.h"
#define _USE_MATH_DEFINES
#include <math.h>


// Constructor. Set the reference to the provided list
control_points_editor::control_points_editor(std::vector<point2d> &control_points):
control_points(control_points)
{
	last_x = 0;
	last_y = 0;
	selected_point = -1;
	hovered_point = -1;
	points_changed = false;
}




// Find the control point that is under the mouse
int control_points_editor::find_hovered_point()
{
	std::vector<point2d>::const_iterator iter;
	int num = 0;

	// Go through all control points
	for (iter = control_points.begin(); iter != control_points.end(); iter++) {
		// Calculate the distance from one control point to the mouse position
		double dist = sqrt((last_x - iter->x()) * (last_x - iter->x()) + (last_y - iter->y())*(last_y - iter->y()));

		// If the distance is less than 5 then we are in the circle that 
		// represents one control point.
		if (dist<5)
			return num;

		num++;
	}

	// Since we are here no control point was found, so return -1
	return -1;
}




// Method to be called whenever the mouse moves
void control_points_editor::mouse_move(int x, int y)
{
	// Store the mouse position for later use
	last_x = x;
	last_y = y;

	points_changed = false;

	// If currently no point is selected then check whether
	// the mouse hovers a point
	if (selected_point == -1)
		hovered_point = find_hovered_point();
	else {
		// Otherwise update the position of the selected point
		// and mark the control points list as changed
		control_points[selected_point].x() = last_x;
		control_points[selected_point].y() = last_y;
		points_changed = true;
	}
}




// Method to be called whenever a mouse button is pressed or released
void control_points_editor::mouse_button(int button, int state)
{
	points_changed = false;

	// We are just interested in events from the left button
	if (button != GLUT_LEFT_BUTTON)
		return;

	// If the button was pressed...
	if (state == GLUT_DOWN) {

		// If shift was pressed and a point is hovered then
		// erase the currently hovered point, mark the point set
		// as changed and jump out of this method.
		if ((glutGetModifiers() & GLUT_ACTIVE_SHIFT) && hovered_point != -1) {
			control_points.erase(control_points.begin() + hovered_point);
			hovered_point = -1;
			points_changed = true;
			return;
		}

		// If the mouse is over a point then this is the point
		// to be moved from now on
		if (hovered_point != -1)
			selected_point = hovered_point;
		else {
			// Otherwise a new point will be created and it is 
			// indicated that the point list has changed.
			control_points.push_back(point2d((double)last_x, (double)last_y));
			selected_point = control_points.size()-1;
			points_changed = true;
		}
	}

	// If the left mouse button was released then no point
	// is selected for movements anymore.
	if (state == GLUT_UP) 
		selected_point = -1;
}




// Return true if the control points list changed
bool control_points_editor::control_points_changed()
{
	bool old_points_changed = points_changed;

	points_changed = false;

	return old_points_changed;
}



// Draw the control polygon
void control_points_editor::draw_control_polygon()
{
	std::vector<point2d>::const_iterator iter;

	glColor3d(0.8, 0.8, 0.8);

	glBegin(GL_LINE_STRIP);
	for (iter = control_points.begin(); iter != control_points.end(); iter++)
		glVertex3d(iter->x(), iter->y(), 0.0);
	glEnd();
}





// Draw the control points
void control_points_editor::draw_control_points()
{
	std::vector<point2d>::const_iterator iter;
	int num = 0;

	// Go through all control points
	for (iter = control_points.begin(); iter != control_points.end(); iter++) {

		// Draw a black filled circle where the control point is
		glColor3d(0,0,0);
		draw_circle(static_cast<int>(iter->x()), static_cast<int>(iter->y()), 5);

		// Set the color to red if the current point is selected
		if (num == selected_point || num == hovered_point)
			glColor3d(1, 0, 0);
		// ... or to white if not
		else
			glColor3d(1, 1, 1);

		// Draw a smaller circle inside the black one.
		draw_circle(static_cast<int>(iter->x()), static_cast<int>(iter->y()), 4);

		num++;
	}
}



// Draw a circle.
void control_points_editor::draw_circle(int x, int y, int r)
{
	// Draw a circle by generating a circular polygon. Every vertex is a
	// point on a circle with a distance of 10 degree.
	// As the sin and cos function take arguments in radiants rather than
	// in degree a conversion has to be made.
	glBegin(GL_POLYGON);
	for (int angle = 0; angle<360; angle+=10)
		glVertex3d(x + sin(static_cast<double>(angle)/180.0*M_PI)*r, y + cos(static_cast<double>(angle)/180.0*M_PI)*r, 0);
	glEnd();
}