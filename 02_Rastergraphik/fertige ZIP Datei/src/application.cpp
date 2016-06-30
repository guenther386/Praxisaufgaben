//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "application.h"

#include <sstream>
#include <math.h>
#include "pen_tool.h"
#include "dda_line_tool.h"
#include "bresenham_line_tool.h"
#include "bresenham_circle_tool.h"
#include "recursive_fill_tool.h"
#include "non_recursive_fill_tool.h"
#include "line_fill_tool.h"
#include "rectangle_tool.h"


application::application()
{
	instance = this;

	// No dragging, so invalidate the start coordinates
	start_gx = -1;
	start_gy = -1;
	is_dragging = false;

	// Initialize the canvas with a size of 100x100
	canvas = new canvas_buffer(100, 100);

	// Initialize the renderer
	renderer = new canvas_renderer(*canvas);
	// No tool selected
	tool = 0;

	// Not in scroll mode
	is_scroll_mode = false;
}



application::~application()
{
	delete canvas;
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
	glutInitWindowSize(620, 640);
	// Set a title
	glutCreateWindow("ECG Rastergraphik");

	// Set the context menu
	setup_context_menu();
	
	// Initialize the starting tool
	context_menu_select(MA_TOOL_PEN);

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
	// ... when the wheel was pressed or moved
	glutMouseWheelFunc(mouse_wheel_callback);

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
	switch(item)
	{
		// Set the pen as tool
		case MA_TOOL_PEN:
			set_tool(new pen_tool(*canvas)); 
			break;

		// Set the dda line tool
		case MA_TOOL_DDA_LINE:
			set_tool(new dda_line_tool(*canvas));
			break;

		// Set the bresenham line tool
		case MA_TOOL_BRESENHAM_LINE:
			set_tool(new bresenham_line_tool(*canvas));
			break;

		// Set the bresenham circle tool
		case MA_TOOL_CIRCLE:
			set_tool(new bresenham_circle_tool(*canvas));
			break;

		// Set the box tool
		case MA_TOOL_RECTANGLE:
			set_tool(new rectangle_tool(*canvas));
			break;

		// Set the recursive fill tool
		case MA_FILL_RECURSIVE:
			set_tool(new recursive_fill_tool(*canvas));
			break;

		// Set the non-recursive fill tool
		case MA_FILL_NONRECURSIVE:
			set_tool(new non_recursive_fill_tool(*canvas));
			break;

		// Set the line fill tool
		case MA_FILL_LINE:
			set_tool(new line_fill_tool(*canvas));
			break;

		// Clear the canvas
		case MA_CLEAR_CANVAS:
			canvas->clear_canvas();
			break;

		// Draw the test shape
		case MA_TEST_SHAPE:
			canvas->draw_test_shape();
			break;

		// Reset translation and zoom
		case MA_RESET_VIEW: 
			renderer->reset_view();
			break;
	}

	// Update display
	display();
}



// Set the current tool to use
void application::set_tool(tool_base *new_tool)
{
	if (tool)
		delete tool;

	tool = new_tool;
	// Also update the preview helper class
	preview.set_shape(tool->get_shape());
}



// Initialize the context menu
void application::setup_context_menu()
{
	glutCreateMenu(context_menu_callback);

	// Set the menu entries and associate them with the
	// appropriate menu action ID
    glutAddMenuEntry(" ------ Primitive Tools ------ ", -1);
    glutAddMenuEntry(" Pen                       (p) ", MA_TOOL_PEN);
    glutAddMenuEntry(" -------- Shape Tools -------- ", -1);
    glutAddMenuEntry(" Line (using DDA)          (d) ", MA_TOOL_DDA_LINE);
    glutAddMenuEntry(" Line (using Bresenham)    (b) ", MA_TOOL_BRESENHAM_LINE);
    glutAddMenuEntry(" Circle (using Bresenham)  (o) ", MA_TOOL_CIRCLE);
    glutAddMenuEntry(" Rectangle                 (s) ", MA_TOOL_RECTANGLE);
    glutAddMenuEntry(" ------------ Fill ----------- ", -1);
    glutAddMenuEntry(" Recursive Fill            (r) ", MA_FILL_RECURSIVE);
    glutAddMenuEntry(" Non-recursive Fill        (f) ", MA_FILL_NONRECURSIVE);
    glutAddMenuEntry(" Line-Fill                 (l) ", MA_FILL_LINE);
	glutAddMenuEntry(" ------- Miscellaneous ------- ", -1);
    glutAddMenuEntry(" Clear canvas              (c) ", MA_CLEAR_CANVAS);
    glutAddMenuEntry(" Draw test shape           (t) ", MA_TEST_SHAPE);
    glutAddMenuEntry(" Reset view             (bcks) ", MA_RESET_VIEW);


	// Attach the menu to the right mouse button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
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
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Render the grid
	renderer->render();

	// Render the preview (if enabled)
	preview.render();

	// Render the debug output
	std::stringstream stream;
	tool->set_text(stream);
	glColor3d(0.0, 0.0, 0.0);
	// Go to the bottom left of the window
	glRasterPos2i(10, glutGet(GLUT_WINDOW_HEIGHT)-10);
	glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>(stream.str().c_str()) );

	// Swap the just filled back buffer with the front buffer
	// to display the result
	glutSwapBuffers();
}




// The event method on key presses
void application::key_down(unsigned char key, int x, int y) 
{
	// According to the key different actions are performed
	// by using the "context_menu_select" method.
	switch(key)
	{
		case 'p': context_menu_select(MA_TOOL_PEN); break;
		case 'd': context_menu_select(MA_TOOL_DDA_LINE); break;
		case 'b': context_menu_select(MA_TOOL_BRESENHAM_LINE); break;
		case 'o': context_menu_select(MA_TOOL_CIRCLE); break;
		case 's': context_menu_select(MA_TOOL_RECTANGLE); break;
		case 'r': context_menu_select(MA_FILL_RECURSIVE); break;
		case 'f': context_menu_select(MA_FILL_NONRECURSIVE); break;
		case 'l': context_menu_select(MA_FILL_LINE); break;
		// Space or "c" clears the canvas
		case 'c': 
		case ' ': context_menu_select(MA_CLEAR_CANVAS); break;
		// Return or "t" displays the test shape
		case 13:
		case 't': context_menu_select(MA_TEST_SHAPE); break;
		// Backspace resets the view
		case 8: context_menu_select(MA_RESET_VIEW); break;
		// ESC destroys the window and quits the program
		case 27: glutDestroyWindow(1); break;
	} 
}



// The event method on mouse button presses
void application::mouse_button(int button, int state, int x, int y) 
{
	int gx, gy, snapped_x, snapped_y;

	// If the mouse wheel was pressed
	if (button == GLUT_MIDDLE_BUTTON) {
		// If the wheel is pressed then we are in scroll mode
		// otherwise we leave this mode
		is_scroll_mode = (state == GLUT_DOWN);
		last_mouse_x = -1;
		last_mouse_y = -1;
	}

	// All button handling is for the left mouse button only
	if (button != GLUT_LEFT_BUTTON) 
		return;

	// Transform mouse coordinates to grid coordinates
	renderer->screen_to_grid(x, y, gx, gy);
	// Get the next center of a canvas cell 
	renderer->snap_screen_coords(x, y, snapped_x, snapped_y);

	// If the left mouse button was pressed then enable
	// preview rendering and set the start position
	if (state == GLUT_DOWN) {
		preview.enable_rendering();
		preview.set_start(snapped_x, snapped_y);
		is_dragging = true;
		start_gx = gx;
		start_gy = gy;

		if (gx>=0 && gx<canvas->get_width() && gy>=0 && gy<canvas->get_height())
			tool->draw(gx, gy);
	}
	else 
	// If the mouse button was released and starting positions are
	// set then disable the preview rendering and draw the two-coordinate
	// shape
	if (is_dragging) {
		preview.disable_rendering();
		tool->draw(start_gx, start_gy, gx, gy);	
		is_dragging = false;
	}

	display();
}



// The event method on mouse motions (with pressed buttons)
void application::mouse_move(int x, int y) 
{
	int gx, gy, snapped_x, snapped_y;
	double trans_x, trans_y;

	// If we are in scroll mode (wheel is pressed) then add the mouse
	// movements to the canvas translation
	if (is_scroll_mode && last_mouse_x != -1 && last_mouse_y != -1) {

		renderer->get_translation(trans_x, trans_y);
		trans_x += x-last_mouse_x;
		trans_y += y-last_mouse_y;
		renderer->set_translation(trans_x, trans_y);
	}


	// Transform mouse coordinates to grid coordinates
	renderer->screen_to_grid(x, y, gx, gy);
	// Get the next center of a canvas cell 
	renderer->snap_screen_coords(x, y, snapped_x, snapped_y);

	// If the grid position is valid then draw the one-position shape
	// If the tool is not draggable (i.e. only clicks and not drag operations
	// draw) then do nothing
	if (gx>=0 && gx<canvas->get_width() && gy>=0 && gy<canvas->get_height() && 
		is_dragging && tool->is_tool_draggable())
		tool->draw(gx, gy);

	// Update the destination in the preview tool
	preview.set_dest(snapped_x, snapped_y);

	last_mouse_x = x;
	last_mouse_y = y;

	display();
}


// The event method on mouse wheel rotations
void application::mouse_wheel(int button, int dir, int x, int y)
{
	double trans_x, trans_y;
	double zoom, zoom_old;

	// Get the current zoom factor
	zoom = renderer->get_zoom();

	zoom_old = zoom;

	// If the wheel is moved up then increase the zoom factor
	// otherwise decrease it
	if (dir>0) {
		zoom+=0.2;
	}
	else {
		zoom-=0.2;
		if (zoom<0.2)
			zoom = 0.2;
	}

	// Set the new factor
	renderer->set_zoom(zoom);

	// Also change the translation so that the location of the
	// mouse keeps its position. This is done by adding the difference
	// of the zoomed mouse location and its original position
	// [the difference is expressed  through (1.0 - zoom/zoom_old) which
	// is an exclusion of (x-trans_x) or (y-trans_y) resp.]
	renderer->get_translation(trans_x, trans_y);

	trans_x += (x-trans_x)*(1.0-zoom/zoom_old);
	trans_y += (y-trans_y)*(1.0-zoom/zoom_old);

	renderer->set_translation(trans_x, trans_y);

	display();
}





application *application::instance = 0;


void application::key_down_callback(unsigned char key, int x, int y)
{
	instance->key_down(key, x, y);
}

void application::mouse_button_callback(int button, int state, int x, int y)
{
	instance->mouse_button(button, state, x, y);
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

void application::mouse_wheel_callback(int button, int dir, int x, int y)
{
	instance->mouse_wheel(button, dir, x, y);
}
