//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "dda_line_tool.h"
#include <algorithm>


// Initialize the tool and store a reference of a canvas_buffer
dda_line_tool::dda_line_tool(canvas_buffer& canvas): tool_base(canvas)
{
	shape = TS_LINE;
}



// Draw a line from (x0, y0) to (x1, y1)
void dda_line_tool::draw(int x0, int y0, int x1, int y1)
{
	double m, y;
	bool swapped;

	swapped = false;


	// DDA works by first constructing the standard case
	// (i.e. a line with a positive slope smaller than 1 and
	// drawn from left to right). In the drawing loop over x
	// the slope (which is a rational number) is added to y
	// (which in contrast to x is a double).

	// If the slope is bigger than 1 then exchange X and Y to
	// implicitly have the drawing loop over y where the slope will
	// be smaller than one then. Remember that there was a swap.
	if (abs(y1 - y0) > abs(x1 - x0)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		swapped = true;
	}

	// If the starting position is bigger than the stop position than
	// exchange the start and stop point.
	if (x0>x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	} 


	// Now with the almost-standard case the slope is calculated. Mind the
	// (double)-cast here which is neccessary to have a non-integer result!
	m = (y1 - y0) / static_cast<double>(x1 - x0); 


	y = y0;

	for (int x = x0; x<=x1; x++) {

		// Draw a pixel at (x, y) or (y, x) if x and y were swapped
		if (swapped)
			canvas.set_pixel( static_cast<int>(y+0.5), x);
		else
			canvas.set_pixel(x, static_cast<int>(y+0.5));

		// Add the slope to y
		y += m;
	}
}



// Put debug output into the stream "stream" to be displayed in the
// main window
void dda_line_tool::set_text(std::stringstream& stream)
{
	stream<<"Tool: DDA-Line (click and drag mouse to draw)";
}