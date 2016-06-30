//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
The main program.
This class provides the functionality of the main program. The program
starts after calling the "run" method. This method initializes the GLUT
system for rendering (using OpenGL) and user interaction. During the
initialization process different methods are connected to certain events
such as "display the window content", "act on mouse motion and buttons"
or "act on key events". Furthermore the main context menu is initialized
by calling the method "setup_context_menu".
Whenever one of the events described above occurs the appropriate functions
are called (They are however not called directly but via static functions
that forward the event. Read the included PDF if you are interested why
this is done and how it works). 
The instance of this class maintains an abstract curve that can be any
of the implemented specific curve. Furthermore it maintains an instance of
the "curve_renderer" and the graphical "control_points_editor".
The rendering of the scene is done in the method "display" which configures
OpenGL for orthographic projection and then renders the curve, the control
points with the control polygon and the basis functions.
The curve is changed in the method "context_menu_select" which is called
whenever the user selects an option from the context menu. It is also used
when a key is pressed. 
**************************************************************************/

#pragma once


// Needed for arbitrary long lists
#include <vector>
// Needed for openGL rendering and GLUT commands
#include "GL/glut.h"
// Needed for displaying text in the main window
#include "GL/freeglut_ext.h"
// Needed for the data type "point2d"
#include "tiny_vec.h"

#include "control_points_editor.h"
#include "abstract_curve.h"
#include "curve_renderer.h"


// An enumeration of menu actions. Whenever something
// from the context menu is selected the method "context_menu_select"
// is invoked with an element of this enumeration as a parameter
enum MenuActions 
{
	MA_BEZIER_CURVE = 1,		// show bezier curve
	MA_LAGRANGE_CURVE,			// show lagrange curve
	MA_hermite_spline,			// show hermite curve
	MA_SHOW_BASIS,				// show the basis functions
	MA_BSPLINE,					// show a bspline
	MA_INCREASE_DEGREE,			// increase degree of the spline
	MA_DECREASE_DEGREE,			// decrease degree of the spline
	MA_DELETE_CTL_POINTS,		// delete control points
	MA_SHOW_GRID,				// show the dotted grid

	MA_DECREASE_Casteljau_t,	//	decrease degree of de casteljau implementation
	MA_INCREASE_Casteljau_t,	//	increase degree of de casteljau implementation
};




class application
{
public:
	// Initialize all non-GLUT related variables
	application();

	// Destroy allocated objects
	~application();

	int cast_t;

	// Run the program using the command line arguments
	int run(int argc, char* argv[]);

private:
	// The static instance of this program. Read the PDF for more details
	static application *instance;

	// The number of curve points to be evaluated for rendering the curve.
	// Change it in the constructor for a different resolution
	int curve_resolution;


	// The control points editor
	control_points_editor *ctl_editor;
	// The list of control points
	std::vector<point2d> control_points;
	// The curve to be evaluated
	abstract_curve *curve;
	// The renderer for the curve
	curve_renderer *renderer;
	// The degree of the spline
	int spline_degree;

	// Shall the basis functions be displayed?
	bool show_basis_functions;
	// Shall the grid be displayed?
	bool show_grid;

	bool menu_dirty;

	// The event method on key presses
	void key_down(unsigned char key, int x, int y);

	// The event method on mouse button presses
	void mouse_button(int button, int state);

	// The event method on mouse motions
	void mouse_move(int x, int y);

	// The event method on context menu selections
	void context_menu_select(int item);

	// The event method on window content rendering
	void display();

	// Render a regular grid
	void render_grid();

	// Initialize the context menu
	void setup_context_menu();

	// Update the context menu
	void update_context_menu();

	// Set the curve type to the curve "c"
	void set_curve_type(abstract_curve *c);

	// Static callbacks...
	static void key_down_callback(unsigned char key, int x, int y);
	static void mouse_button_callback(int button, int state, int x, int y);
	static void mouse_move_callback(int x, int y);
	static void context_menu_callback(int item);
	static void idle_callback();
	static void display_callback();

};