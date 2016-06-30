//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "application.h"

#include <sstream>
#include <cmath>
#include <algorithm>

#include "bezier_curve.h"
#include "bspline.h"
#include "lagrange_curve.h"
#include "hermite_spline.h"
#define STEP_GRANUALIRITY 0.005


application::application()
{
	instance = this;

	// Set initial parameters
	curve_resolution = 1000;
	spline_degree = 2;
	show_basis_functions = false;
	show_grid = true;
	menu_dirty = true;

	cast_t = STEP_GRANUALIRITY;

	// Put 3 points into the list of control points
	control_points.push_back(point2d(100.0, 400.0));
	control_points.push_back(point2d(200.0, 50.0));
	control_points.push_back(point2d(550.0, 200.0));

	// Initialize the curve, the renderer and the editor
	curve = 0;
	ctl_editor = new control_points_editor(control_points);
	renderer = new curve_renderer();
}



application::~application()
{
	// Delete all allocated variables
	delete ctl_editor;
	delete curve;
	delete renderer;
}




// Run the program using the command line arguments
int application::run(int argc, char* argv[])
{
	// Initialize the GLUT system and let it evaluate additional
	// command line arguments.
	glutInit(&argc, argv);

	// Set the openGL display mode to double buffering and have
	// channels R,G,B active. 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Initialize main window size
	glutInitWindowSize(640, 480);
	// Set a title
	glutCreateWindow("ECG Kurven");

	// Set the context menu
	setup_context_menu();

	// Initialize the curve
	context_menu_select(MA_LAGRANGE_CURVE);

	// The following section tells GLUT which methods to call 
	// whenever certain events happen.
	// ... when the screen shall be displayed
	glutDisplayFunc(display_callback);
	// ... when a key was pressed
	glutKeyboardFunc(key_down_callback);
	// ... when a mouse button was pressed
	glutMouseFunc(mouse_button_callback);
	// ... when the mouse was moved with buttons pressed
	glutMotionFunc(mouse_move_callback);
	// ... when the mouse was moved without buttons pressed
	glutPassiveMotionFunc(mouse_move_callback);
	// ... when the menu state changes
	glutIdleFunc(idle_callback);

	// The main loop runs the program itself. It repeatedly asks
	// the operating system whether there are events to process
	// and, according to the type of the event, calls the right
	// method (that was defined above).
	glutMainLoop();

	return 0;
}



void application::set_curve_type(abstract_curve *c)
{
	// Delete the old curve if there is one,
	// set the parameter to be the active curve and
	// update the renderer.
	if (curve)
		delete curve;
	curve = c;
	curve->cast_t = cast_t;
	curve->control_points_updated();
	renderer->set_curve(curve);
	renderer->sample_curve(curve_resolution);
}




// The event method on context menu selections
void application::context_menu_select(int item)
{
	switch (item)
	{
		// Set bezier curve
	case MA_BEZIER_CURVE:
		set_curve_type(new bezier_curve(control_points));
		display();
		break;

		// Set lagrange curve
	case MA_LAGRANGE_CURVE:
		set_curve_type(new lagrange_curve(control_points));
		break;

		// Set hermite curve
	case MA_hermite_spline:
		set_curve_type(new hermite_spline(control_points));
		break;

		// Set bspline
	case MA_BSPLINE:
		set_curve_type(new bspline(control_points, spline_degree));
		break;

		// Activate or deactivate rendering of basis functions
	case MA_SHOW_BASIS:
		show_basis_functions = !show_basis_functions;
		menu_dirty = true;
		break;

		// Increase the degree
	case MA_INCREASE_DEGREE:
		spline_degree++;
		// If the active curve is of type "bspline" then recreate it
		// using the new degree
		if (dynamic_cast<bspline*>(curve))
			set_curve_type(new bspline(control_points, spline_degree));
		menu_dirty = true;
		break;

		// Decrease the degree
	case MA_DECREASE_DEGREE:
		if (spline_degree>1)
			spline_degree--;
		// If the active curve is of type "bspline" then recreate it
		// using the new degree
		if (dynamic_cast<bspline*>(curve))
			set_curve_type(new bspline(control_points, spline_degree));
		menu_dirty = true;
		break;

		// Delete control points
	case MA_DELETE_CTL_POINTS:
		control_points.clear();
		// Tell the curve and the renderer that the points changed
		curve->control_points_updated();
		renderer->sample_curve(curve_resolution);
		break;

		// Show or hide the grid
	case MA_SHOW_GRID:
		show_grid = !show_grid;
		menu_dirty = true;
		break;
	case MA_INCREASE_Casteljau_t:
		if (dynamic_cast<bezier_curve*>(curve)) {
			curve->cast_t = std::min(curve->cast_t + STEP_GRANUALIRITY, 1.0);
		}
		break;
	case MA_DECREASE_Casteljau_t:
		if (dynamic_cast<bezier_curve*>(curve)) {
			curve->cast_t = std::max(curve->cast_t - STEP_GRANUALIRITY, 0.0);
		}
		break;
	}

	// Update display
	display();
}




// Initialize the context menu
void application::setup_context_menu()
{
	glutCreateMenu(context_menu_callback);

	// Set the menu entries and associate them with the
	// appropriate menu action ID
	glutAddMenuEntry("    Connect with lagrange curve (l) ", MA_LAGRANGE_CURVE);
	glutAddMenuEntry("    Connect with bezier curve   (b) ", MA_BEZIER_CURVE);
	glutAddMenuEntry("    Connect with hermite curve  (h) ", MA_hermite_spline);
	glutAddMenuEntry("    Connect with spline         (s) ", MA_BSPLINE);
	// The name for menu entries which can change
	// (that means e.g. can have "[ ]" or "[X]") are set in "update_context_menu
	glutAddMenuEntry("", MA_SHOW_BASIS);
	glutAddMenuEntry("    ----- Spline Settings ----- ", -1);
	glutAddMenuEntry("", MA_INCREASE_DEGREE);
	glutAddMenuEntry("", MA_DECREASE_DEGREE);
	glutAddMenuEntry("    ------ Miscellaneous ------ ", -1);
	glutAddMenuEntry("", MA_SHOW_GRID);
	glutAddMenuEntry("    Delete control points       (c) ", MA_DELETE_CTL_POINTS);

	glutAddMenuEntry("    Increase Casteljau t        (p) ", MA_INCREASE_Casteljau_t);		// new menu entry p
	glutAddMenuEntry("    Decrease Casteljau t        (o) ", MA_DECREASE_Casteljau_t);		// new menu entry o

	// Attach the menu to the right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Initially fill in the missing menu entry names
	update_context_menu();
}




void application::update_context_menu()
{
	std::stringstream mname;

	// Update the basis function menu point and display a
	// [X] or [ ] at the beginning according to the setting
	mname.str("");
	if (show_basis_functions)
		mname << "[X]";
	else
		mname << "[ ]";
	mname << " Show basis functions        (f) ";
	glutChangeToMenuEntry(5, mname.str().c_str(), MA_SHOW_BASIS);

	// Update the spline degree menus and show the degree
	// in square brackets
	mname.str("");
	mname << "[" << spline_degree << "] Increase degree             (+) ";
	glutChangeToMenuEntry(7, mname.str().c_str(), MA_INCREASE_DEGREE);

	mname.str("");
	mname << "[";
	mname << spline_degree << "] Decrease degree             (-) ";
	glutChangeToMenuEntry(8, mname.str().c_str(), MA_DECREASE_DEGREE);


	// Update the grid menu point and display a
	// [X] or [ ] at the beginning according to the setting
	mname.str("");
	if (show_grid)
		mname << "[X]";
	else
		mname << "[ ]";
	mname << " Show grid                   (g) ";
	glutChangeToMenuEntry(10, mname.str().c_str(), MA_SHOW_GRID);

	menu_dirty = false;
}


// The event method on window content rendering
void application::display()
{
	// Set the projection to use orthogonal projection with
	// a coordinate system that increases from left to right
	// and from top to bottom where one unit corresponds to
	// one screen pixel
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0, 1.0, -1.0);

	// Reset Modelview transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Clear the screen
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Resample the curve if neccessary
	if (ctl_editor->control_points_changed()) {
		curve->control_points_updated();
		renderer->sample_curve(curve_resolution);
	}

	if (show_grid)
		render_grid();

	// Draw the control polygon
	ctl_editor->draw_control_polygon();
	// On top render the curve
	renderer->render_curve();
	// And on top of this render the control points
	ctl_editor->draw_control_points();

	// Eventually show the basis functions
	if (show_basis_functions)
		renderer->render_basis_functions();

	// ... and the debug output
	std::stringstream stream;
	curve->set_text(stream);
	glColor3d(0.0, 0.0, 0.0);
	// Go to the bottom left of the window
	glRasterPos2i(10, glutGet(GLUT_WINDOW_HEIGHT) - 10);
	//glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>(stream.str().c_str()));

	// Swap the just filled backbuffer with the front buffer
	// to display the result
	glutSwapBuffers();
}




// Render a regular grid
void application::render_grid()
{
	// Store the width and height of the window for easier access
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	// The grid size in pixels
	const int grid_size = 25;

	// Enable line stippling to render dotted lines
	glEnable(GL_LINE_STIPPLE);
	// Define the stipple pattern. The pattern is 0x8888 which is
	// 1000100010001000 in binary (draw one pixel and then skip three).
	// Every bit shall be used 1x consecutively.
	glLineStipple(1, 0x8888);

	// Set color to light gray
	glColor3d(0.8, 0.8, 0.8);

	// Render the horizontal lines
	glBegin(GL_LINES);
	for (int i = 0; i<height; i += grid_size) {
		glVertex2d(0, i);
		glVertex2d(width, i);
	}

	// Render the vertical lines
	for (int i = 0; i<width; i += grid_size) {
		glVertex2d(i, 0);
		glVertex2d(i, height);
	}


	glEnd();

	// Disable line stippling
	glDisable(GL_LINE_STIPPLE);
}





// The event method on key presses
void application::key_down(unsigned char key, int x, int y)
{
	// According to the key different actions are performed
	// by using the "context_menu_select" method.
	switch (key)
	{
	case 'b': context_menu_select(MA_BEZIER_CURVE); break;
	case 'l': context_menu_select(MA_LAGRANGE_CURVE); break;
	case 'h': context_menu_select(MA_hermite_spline); break;
	case 's': context_menu_select(MA_BSPLINE); break;
	case 'f': context_menu_select(MA_SHOW_BASIS); break;
	case '+': context_menu_select(MA_INCREASE_DEGREE); break;
	case '-': context_menu_select(MA_DECREASE_DEGREE); break;
		// Space or "c" clear the control points
	case ' ':
	case 'c': context_menu_select(MA_DELETE_CTL_POINTS); break;
	case 'g': context_menu_select(MA_SHOW_GRID); break;

	case 'p': context_menu_select(MA_INCREASE_Casteljau_t); break;
	case 'o': context_menu_select(MA_DECREASE_Casteljau_t); break;

		// ESC destroys the window and quits the program
	case 27: glutDestroyWindow(1); break;
	}
}




// The event method on mouse button presses
void application::mouse_button(int button, int state)
{
	// Just handled over to the control points editor
	ctl_editor->mouse_button(button, state);

	display();
}




// The event method on mouse motions
void application::mouse_move(int x, int y)
{
	// Just handled over to the control points editor
	ctl_editor->mouse_move(x, y);

	display();
}






application *application::instance = 0;


void application::key_down_callback(unsigned char key, int x, int y)
{
	instance->key_down(key, x, y);
}

void application::mouse_button_callback(int button, int state, int x, int y)
{
	instance->mouse_button(button, state);
}

void application::mouse_move_callback(int x, int y)
{
	instance->mouse_move(x, y);
}

void application::display_callback()
{
	instance->display();
}

void application::context_menu_callback(int item)
{
	instance->context_menu_select(item);
}

void application::idle_callback()
{
	if (instance->menu_dirty)
		instance->update_context_menu();
}