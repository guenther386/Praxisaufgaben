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
such as "display the window content" or "act on key events". 
Furthermore the main context menu is initialized by calling the method 
"setup_context_menu".
Whenever one of the events described above occurs the appropriate functions
are called (They are however not called directly but via static functions
that forward the event. Read the included PDF if you are interested why
this is done and how it works). 
The actual rendering happens in the "display" method that completely
handles the rendering over to the "render" method of the "content"-variable
which is an instance of a child class of abstract_scene.
For animations a timer is set up to call the "timer" method every 1/30 sec
which calls the "advance_frame" method of the current "content" and 
refreshes the display.
**************************************************************************/

#pragma once


// Needed for openGL rendering and GLUT commands
#include "GL/glut.h"
// Needed for displaying text in the main window
#include "GL/freeglut_ext.h"
// Contains the interface for abstract_scene
#include "abstract_scene.h"



// An enumeration of menu actions. Whenever something
// from the context menu is selected the method "context_menu_select"
// is invoked with an element of this enumeration as a parameter
enum MenuActions 
{
	MA_CUBE_SYSTEM,				// Render the cube system
	MA_CUBE_SYSTEM_SPLIT,		// Render the cube system in split screen
	MA_CUBES_RECURSIVE,			// Render the recursive cubes
	MA_TERRAIN,					// Render the terrain
	MA_TERRAIN_SOLID,			// Show the terrain as solid
	MA_TERRAIN_WIREFRAME,		// Show the terrain as wireframe
	MA_TERRAIN_LEVELS,			// Show height level lines
	MA_EXAMPLE_PRIMITIVES,		// Render the primitives example
	MA_EXAMPLE_CPRIMITIVES,		// Render the consecutive primitives example
	MA_EXAMPLE_3D_PRIMITIVES,	// Render the 3D primitives example
	MA_EXAMPLE_TRANS_ORDER		// Render the transformation order example
};



class application
{
public:
	// Initialize all non-GLUT related variables
	application();

	// Run the program using the command line arguments
	int run(int argc, char* argv[]);

private:
	// The current scene to display
	abstract_scene *content;
	// States for the terrain scene
	bool terrain_solid, terrain_wireframe, terrain_levels;
	// Dirty flag to check if the menu must be updated
	bool menu_dirty;

	// The static instance of this program. Read the PDF for more details
	static application *instance;

	// Set the current scene
	void set_content(abstract_scene *new_content);

	// The event method on key presses
	void key_down(unsigned char key, int x, int y);

	// The event method on context menu selections
	void context_menu_select(int item);

	// The event method on timer callbacks
	void timer(int value);

	// The event method on window content rendering
	void display();

	// Initialize the context menu
	void setup_context_menu();

	// Update the context menu according to the settings
	void update_context_menu();

	// Static callbacks...
	static void key_down_callback(unsigned char key, int x, int y);
	static void context_menu_callback(int item);
	static void display_callback();
	static void timer_callback(int value);
	static void idle_callback();

};
