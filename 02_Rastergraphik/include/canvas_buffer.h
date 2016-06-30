//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
Canvas Store.
This class stores a set of boolean pixels of the canvas and provides 
methods for modification. Set a pixel with the set_pixel method and get 
its state with the method "get_pixel". All methods that have a position
as a parameter will perform a boundary check and put an error message
to stdout if the boundaries are violated.
For debugging purposes the method "draw_test_shape" will draw a shape
that is suitable for testing the correctness of fill algorithms.
*************************************************************************/
#pragma once


class canvas_buffer
{
public:
	// Initialize the store with a defined with and height
	canvas_buffer(int width, int height);

	// Free the memory used for the pixels
	~canvas_buffer();


	// Set a pixel at (x, y)
	void set_pixel(int x, int y);

	// Clear the pixel at (x, y)
	void clear_pixel(int x, int y);

	// Get the state of a pixel at (x, y)
	bool get_pixel(int x, int y) const;

	// Clear all pixels on the canvas
	void clear_canvas();

	// Get the width of the canvas in pixels
	int get_width() const;

	// Get the height of the canvas in pixels
	int get_height() const;

	// Draw the test shape
	void draw_test_shape();


private:
	// The actual pixels store as array
	bool* pixels;
	// Width and height of the canvas
	int width, height;
};