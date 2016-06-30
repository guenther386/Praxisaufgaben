//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "canvas_renderer.h"
#include "GL/glut.h"

#include <math.h>

// Initialize the renderer and store a reference of a canvas_buffer
canvas_renderer::canvas_renderer(canvas_buffer& canvas): canvas(canvas)
{
	reset_view();
}



// Reset translation and zoom factor
void canvas_renderer::reset_view()
{
	zoom_factor = 1;
	trans_x = 10;
	trans_y = 10;
}


// Set the zoom factor
void canvas_renderer::set_zoom(double factor)
{
	zoom_factor = factor;
}


// Get the zoom factor
double canvas_renderer::get_zoom() const
{
	return zoom_factor;
}


// Get the translation
void canvas_renderer::get_translation(double &x, double &y) const
{
	x = trans_x;
	y = trans_y;
}


// Set the translation
void canvas_renderer::set_translation(double x, double y)
{
	trans_x = x;
	trans_y = y;
}


// Render the contents of the canvas store
void canvas_renderer::render() const
{
	double cell_size = get_cell_size();
	int width = canvas.get_width();
	int height = canvas.get_height();

	// Enable a scissor test to prevent rendering above the debug messages 
	// in the main window
	glEnable(GL_SCISSOR_TEST);
	glScissor(0, 29, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)-29);

	glPushMatrix();
	// Translate and scale so that one unit corresponds to one pixel
	glTranslated(trans_x, trans_y, 0);
	glScaled(cell_size, cell_size, 1);

	glColor3d(0, 0, 0);
	glBegin(GL_QUADS);
	for (int x=0; x<width; x++)
		for (int y=0; y<height; y++)
			// Whenever a pixel is set draw a black quad
			if (canvas.get_pixel(x, y)) {
				glVertex2d(x, y);
				glVertex2d(x+1, y);
				glVertex2d(x+1, y+1);
				glVertex2d(x, y+1);
			}
	glEnd();
	glPopMatrix();

	// Render the grid
	render_grid();

	glDisable(GL_SCISSOR_TEST);

}



// Convert a screen position to a grid position
void canvas_renderer::screen_to_grid(int sx, int sy, int &gx, int &gy) const
{
	double cell_size = get_cell_size();

	gx = static_cast<int>(floor((sx-trans_x)/cell_size));
	gy = static_cast<int>(floor((sy-trans_y)/cell_size));
}


// Get the next cell center from the provided position
void canvas_renderer::snap_screen_coords(int sx, int sy, int &scx, int &scy) const
{
	double cell_size = get_cell_size();

	// Align the coordinates to the border of a cell and add half the cell
	// size to place them in the center
	scx = static_cast<int>((floor((sx-trans_x)/cell_size) + 0.5) * cell_size + trans_x);
	scy = static_cast<int>((floor((sy-trans_y)/cell_size) + 0.5) * cell_size + trans_y); 
}



// Get the size of a cell in pixels
double canvas_renderer::get_cell_size() const
{
	double cell_x = (glutGet(GLUT_WINDOW_WIDTH)-20)*zoom_factor/static_cast<double>(canvas.get_width());
	double cell_y = (glutGet(GLUT_WINDOW_HEIGHT)-40)*zoom_factor/static_cast<double>(canvas.get_height());

	double cell = cell_x;
	if (cell_y<cell)
		cell = cell_y;

	return cell;
}



// Helper method to render the grid
void canvas_renderer::render_grid() const
{
	double cell_size = get_cell_size();
	int width = canvas.get_width();
	int height = canvas.get_height();

	glPushMatrix();

	// Translate and scale so that one unit corresponds to one pixel
	glTranslated(trans_x, trans_y, 0);
	glScaled(cell_size, cell_size, 1);


	// Enable blending and make the grid more transparent the smaller
	// the cells are. This prevents the view from being cluttered
	// with grid lines.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); 

	if (cell_size<5)
		glColor4d(0.8, 0.8, 0.8, (cell_size-2)/3.0);
	else
		glColor3d(0.8, 0.8, 0.8);

	glBegin(GL_LINES);

	// Draw vertical lines
	for (int x=1; x<width; x++) {
		glVertex2d(x, 0);
		glVertex2d(x, height);
	}

	// Draw horizontal lines
	for (int y=1; y<height; y++) {
		glVertex2d(0, y);
		glVertex2d(width, y); 
	}
	glEnd();

	glDisable(GL_BLEND);


	glColor3d(0.8, 0.8, 0.8);

	// Draw the border lines which shall not be affected by the blending
	glBegin(GL_LINE_STRIP);
	
	glVertex2d(0, 0);
	glVertex2d(0, height);
	glVertex2d(width, height);
	glVertex2d(width, 0);
	glVertex2d(0, 0);

	glEnd();


	glPopMatrix();
}
