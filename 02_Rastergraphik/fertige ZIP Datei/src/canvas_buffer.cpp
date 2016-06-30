//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "canvas_buffer.h"
#include <iostream>

// Initialize the store with a defined with and height
canvas_buffer::canvas_buffer(int width, int height)
{
	this->width = width;
	this->height = height;

	pixels = new bool[width*height];
	clear_canvas();
}


// Free the memory used for the pixels
canvas_buffer::~canvas_buffer()
{
	delete [] pixels;
}


// Set a pixel at (x, y)
void canvas_buffer::set_pixel(int x, int y)
{
	// Display an error message if the position is out of bounds
	if (x<0 || y<0 || x>=width || y>=height) {
		std::cout<<"Error in set_pixel: Coordinates "<<x<<", "<<y<<" are out of range ("<<width<<" x "<<height<<")"<<std::endl;
		return;
	}

	pixels[x+y*width] = true;
}


// Clear the pixel at (x, y)
void canvas_buffer::clear_pixel(int x, int y)
{
	// Display an error message if the position is out of bounds
	if (x<0 || y<0 || x>=width || y>=height) {
		std::cout<<"Error in clear_pixel: Coordinates "<<x<<", "<<y<<" are out of range ("<<width<<" x "<<height<<")"<<std::endl;
		return;
	}

	pixels[x+y*width] = false;
}


// Get the state of a pixel at (x, y)
bool canvas_buffer::get_pixel(int x, int y) const
{
	// Display an error message if the position is out of bounds
	if (x<0 || y<0 || x>=width || y>=height) {
		std::cout<<"Error in get_pixel: Coordinates "<<x<<", "<<y<<" are out of range ("<<width<<" x "<<height<<")"<<std::endl;
		return false;
	}

	return pixels[x+y*width];
}



// Clear all pixels on the canvas
void canvas_buffer::clear_canvas()
{
	for (int i=0; i<width*height; i++)
		pixels[i] = false;
}



// Get the width of the canvas in pixels
int canvas_buffer::get_width() const
{
	return width;
}


// Get the height of the canvas in pixels
int canvas_buffer::get_height() const
{
	return height;
}



// Draw the test shape
void canvas_buffer::draw_test_shape()
{
	// Two horizontal lines
	for (int i = 1; i < width-1; i++) {
		set_pixel(i, 1); 
		set_pixel(i, height-2); 
	}

	// 2 vertical lines crossing with a gap of one pixel in the middle
	for (int i = 1; i < width/2; i++) {
		set_pixel(i, i); 
		set_pixel(i, width - i - 1); 
			
		set_pixel(width-i, i); 
		set_pixel(width-i, width - i - 1); 
	}
}