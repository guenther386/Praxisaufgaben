//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "rectangle_tool.h"
#include <algorithm>


// Initialize the tool and store a reference of a canvas_buffer
rectangle_tool::rectangle_tool(canvas_buffer& canvas): tool_base(canvas)
{
	shape = TS_BOX;
}



// Draw a box from (x0, y0) to (x1, y1)
void rectangle_tool::draw(int x0, int y0, int x1, int y1)
{
	// Just take care to have the box from left to right
	// and top to bottom, mind that you can exchange X 
	// of the two points without having to exchange Y (and
	// vice versa) and draw 4 straight lines. That's the whole trick.

	// Swap x0 and x1 if needed
	if (x0>x1)
		std::swap(x0, x1);

	// Swap y0 and y1 if needed
	if (y0>y1)
		std::swap(y0, y1);

	// Draw horizontal lines
	for (int x=x0; x<=x1; x++) {
		canvas.set_pixel(x, y0);
		canvas.set_pixel(x, y1);
	}

	// Draw vertical lines
	for (int y=y0; y<=y1; y++) {
		canvas.set_pixel(x0, y);
		canvas.set_pixel(x1, y);
	}
}



// Put debug output into the stream "stream" to be displayed in the
// main window
void rectangle_tool::set_text(std::stringstream& stream)
{
	stream<<"Tool: Rectangle (click and drag mouse to draw)";
}