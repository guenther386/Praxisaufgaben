//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "application.h"

#include <sstream>
#include <math.h>

#include "terrain.h"
#include "cube_system.h"
#include "cube_system_split.h"
#include "recursive_cubes.h"
#include "example_primitives.h"
#include "example_cons_primitives.h"
#include "example_3d_primitives.h"
#include "example_trans_order.h"


// Initialize all non-GLUT related variables
application::application()
{
	instance = this;

	content = 0;
	terrain_solid = true;
	terrain_wireframe = false;
	terrain_levels = false;
	
	menu_dirty = false;
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
	glutCreateWindow("ECG OpenGL");

	// Set the context menu
	setup_context_menu();

	// Initialize the starting scene
	context_menu_select(MA_CUBE_SYSTEM);

	// The following section tells GLUT which methods to call 
	// whenever certain events happen.
	// ... when the screen shall be displayed
	glutDisplayFunc(display_callback);
	// ... when a key was pressed
	glutKeyboardFunc(key_down_callback);
	// ... when GLUT is in idle state. Here we check if we must
	// update the context menu entries
	glutIdleFunc(idle_callback);

	// Run the timer callback which will trigger itself in the future
	timer_callback(0);

	// The main loop runs the program itself. It repeatedly asks
	// the operating system whether there are events to process
	// and, according to the type of the event, calls the right
	// method (that was defined above).
	glutMainLoop();

	return 0;
}



// The event method on context menu selections
void application::context_menu_select(int item)
{
	terrain *ter;

	switch(item)
	{
		// Show the cube system
		case MA_CUBE_SYSTEM:
			set_content(new cube_system());
			break;

		// Show the cube system in split screen
		case MA_CUBE_SYSTEM_SPLIT:
			set_content(new cube_system_split());
			break;

		// Show the recursive cubes
		case MA_CUBES_RECURSIVE:
			set_content(new recursive_cubes());
			break;

		// Show the terrain
		case MA_TERRAIN:
			ter = new terrain();
			// Apply the locally stored settings
			ter->set_show_solid(terrain_solid);
			ter->set_show_wireframe(terrain_wireframe);
			ter->set_show_levels(terrain_levels);
			set_content(ter);
			break;

		// Show the solid version of the terrain
		case MA_TERRAIN_SOLID:
			terrain_solid = !terrain_solid;
			// Test whether the actual scene is the terrain
			ter = dynamic_cast<terrain*>(content);
			// If so, then apply the setting
			if (ter)
				ter->set_show_solid(terrain_solid);
			break;

		// Show the wireframe version of the terrain
		case MA_TERRAIN_WIREFRAME:
			terrain_wireframe = !terrain_wireframe;
			// Test whether the actual scene is the terrain
			ter = dynamic_cast<terrain*>(content);
			// If so, then apply the setting
			if (ter)
				ter->set_show_wireframe(terrain_wireframe);
			break;

		// Show the height level lines of the terrain
		case MA_TERRAIN_LEVELS:
			terrain_levels = !terrain_levels;
			// Test whether the actual scene is the terrain
			ter = dynamic_cast<terrain*>(content);
			// If so, then apply the setting
			if (ter)
				ter->set_show_levels(terrain_levels);
			break;

		// Show the primitives example
		case MA_EXAMPLE_PRIMITIVES:
			set_content(new example_primitives());
			break;

		// Show the consecutive primitives example
		case MA_EXAMPLE_CPRIMITIVES:
			set_content(new example_consecutive_primitives());
			break;

		// Show the 3D primitives example
		case MA_EXAMPLE_3D_PRIMITIVES:
			set_content(new example_3d_primitives());
			break;

		// Show the transformation order example
		case MA_EXAMPLE_TRANS_ORDER:
			set_content(new example_trans_order());
			break;
	}

	// Mark the context menu as dirty and let it update by the
	// idle function.
	menu_dirty = true;

	// Update display
	display();
}




// Initialize the context menu
void application::setup_context_menu()
{

	glutCreateMenu(context_menu_callback);

	// Set the menu entries and associate them with the
	// appropriate menu action ID
	glutAddMenuEntry(" Show cube system       (c) ", MA_CUBE_SYSTEM);
	glutAddMenuEntry(" Show terrain           (t) ", MA_TERRAIN);
	glutAddMenuEntry(" ---- Terrain Settings ---- ", -1);
	glutAddMenuEntry(" ", MA_TERRAIN_SOLID);
	glutAddMenuEntry(" ", MA_TERRAIN_WIREFRAME);
	glutAddMenuEntry(" ", MA_TERRAIN_LEVELS);
	glutAddMenuEntry(" ---- Additional Tasks ---- ", -1);
	glutAddMenuEntry(" Show cube split screen (x) ", MA_CUBE_SYSTEM_SPLIT);
	glutAddMenuEntry(" Recursive cubes        (r) ", MA_CUBES_RECURSIVE);
	glutAddMenuEntry(" ----- Example Codes ------ ", -1);
	glutAddMenuEntry(" Basic primitives       (1) ", MA_EXAMPLE_PRIMITIVES);
	glutAddMenuEntry(" Consecutive primitives (2) ", MA_EXAMPLE_CPRIMITIVES);
	glutAddMenuEntry(" Simple 3D solids       (3) ", MA_EXAMPLE_3D_PRIMITIVES);
	glutAddMenuEntry(" Transformation orders  (4) ", MA_EXAMPLE_TRANS_ORDER);


	// Attach the menu to the right mouse button
    glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Initially fill in the missing menu entry names
	update_context_menu();
}


// Update the context menu according to the settings
void application::update_context_menu()
{
	std::stringstream mname;

	// Update the solid terrain menu point and display a
	// [X] or [ ] at the beginning according to the setting
	mname.str("");
	if (terrain_solid)
		mname<<"[X]";
	else
		mname<<"[ ]";
	mname<<" Show solid terrain (s) ";

	glutChangeToMenuEntry(4, mname.str().c_str(), MA_TERRAIN_SOLID);

	// Update the wireframe terrain menu point and display a
	// [X] or [ ] at the beginning according to the setting
	mname.str("");
	if (terrain_wireframe)
		mname<<"[X]";
	else
		mname<<"[ ]";
	mname<<" Show wireframe     (w) ";
	glutChangeToMenuEntry(5, mname.str().c_str(), MA_TERRAIN_WIREFRAME);

	// Update the level lines menu point and display a
	// [X] or [ ] at the beginning according to the setting
	mname.str("");
	if (terrain_levels)
		mname<<"[X]";
	else
		mname<<"[ ]";
	mname<<" Show level lines   (l) ";
	glutChangeToMenuEntry(6, mname.str().c_str(), MA_TERRAIN_LEVELS);
	
	// The menu is current now
	menu_dirty = false;
}



// The event method on window content rendering
void application::display()
{
	// Render the current scene
	content->render();


	// To render the debug text the modelview matrix is reset and the
	// projection is set to be an orthogonal projection where one unit
	// corresponds to one pixel of the window
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0, 1.0, -1.0);

	std::stringstream stream;
	content->set_text(stream);
	glColor3d(0.0, 0.0, 0.0);
	// Go to the bottom left of the window
	glRasterPos2i(10, glutGet(GLUT_WINDOW_HEIGHT)-10);
	// Render the string
	glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>(stream.str().c_str()));

	// Restore old projection and modelview matrix
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();


	// Swap the just filled back buffer with the front buffer
	// to display the result
	glutSwapBuffers();
}



// Set the current scene
void application::set_content(abstract_scene *new_content)
{
	if (content)
		delete content;
	content = new_content;
}



// The event method on key presses
void application::key_down(unsigned char key, int x, int y) 
{
	// According to the key different actions are performed
	// by using the "context_menu_select" method.
	switch(key)
	{
		case 'c': context_menu_select(MA_CUBE_SYSTEM); break;
		case 't': context_menu_select(MA_TERRAIN); break;
		case 'x': context_menu_select(MA_CUBE_SYSTEM_SPLIT); break;
		case 'r': context_menu_select(MA_CUBES_RECURSIVE); break;
		case 's': context_menu_select(MA_TERRAIN_SOLID); break;
		case 'w': context_menu_select(MA_TERRAIN_WIREFRAME); break;
		case 'l': context_menu_select(MA_TERRAIN_LEVELS); break;
		case '1': context_menu_select(MA_EXAMPLE_PRIMITIVES); break;
		case '2': context_menu_select(MA_EXAMPLE_CPRIMITIVES); break;
		case '3': context_menu_select(MA_EXAMPLE_3D_PRIMITIVES); break;
		case '4': context_menu_select(MA_EXAMPLE_TRANS_ORDER); break;
		case 27: glutDestroyWindow(1); break;

	}  
}



// The event method on timer callbacks
void application::timer(int value)
{
	if (content)
		content->advance_frame();

	glutPostRedisplay();
}





application *application::instance = 0;


void application::key_down_callback(unsigned char key, int x, int y)
{
	instance->key_down(key, x, y);
}


void application::display_callback()
{
	instance->display();
}

void application::context_menu_callback(int item)
{
	instance->context_menu_select(item);
}


void application::timer_callback(int value)
{
	instance->timer(value);
	// Trigger the timer again in 1000/30 milliseconds
	glutTimerFunc(1000/30, timer_callback, value);
}


void application::idle_callback()
{
	// Check if we need to update the context menu
	// and leave method if this is not the case.
	if (!instance->menu_dirty)
		return;

	instance->update_context_menu();		
}
