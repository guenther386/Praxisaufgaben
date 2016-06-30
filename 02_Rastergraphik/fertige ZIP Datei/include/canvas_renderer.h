//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
Canvas Renderer.
This class is responsible for the graphical representation of a canvas
store. Among the "render" method that performs the actual rendering on
a grid a translation and zoom can be specified. Also this class provides
a method to convert screen coordinates to grid coordinates and to
snap screen coordinates to the next center of a pixel cell.
*************************************************************************/
#pragma once

// declares the canvas_buffer
#include "canvas_buffer.h"


class canvas_renderer
{
public: 
	// Initialize the renderer and store a reference of a canvas_buffer
	canvas_renderer(canvas_buffer &canvas);

	// Set the translation
	void set_translation(double x, double y);

	// Get the translation
	void get_translation(double &x, double &y) const;

	// Set the zoom factor
	void set_zoom(double factor);

	// Get the zoom factor
	double get_zoom() const;

	// Convert a screen position to a grid position
	void screen_to_grid(int sx, int sy, int &gx, int &gy) const;

	// Get the next cell center from the provided position
	void snap_screen_coords(int sx, int sy, int &scx, int &scy) const;

	// Render the contents of the canvas store
	void render() const;

	// Get the size of a cell in pixels
	double get_cell_size() const;

	// Reset translation and zoom factor
	void reset_view();

private:
	// Translation
	double trans_x, trans_y;
	// Zoom factor
	double zoom_factor;
	// A reference on the canvas store
	canvas_buffer &canvas;

	// Helper method to render the grid
	void render_grid() const;
};