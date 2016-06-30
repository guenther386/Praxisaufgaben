//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "recursive_fill_tool.h"

// Initialize the tool and store a reference of a canvas_buffer
recursive_fill_tool::recursive_fill_tool(canvas_buffer& canvas): tool_base(canvas)
{
	// This tool has no shape and is not draggable
	shape = TS_NONE;
	is_draggable = false;
}



// Fill the shape that contains the point (x, y)
void recursive_fill_tool::draw(int x, int y)
{
	// Fill the actual pixel and check whether the neighbours
	// also need to be filled. If this is the case then recursively
	// call "draw" again.
	// Note that the pitfall of the non-recursive version (described there)
	// does not exist.

	// Set the pixel
	canvas.set_pixel(x,y);

	// Check the neighbour below. Mind the order of the predicates in the
	// if-clause
	if (y+1<canvas.get_height() && !canvas.get_pixel(x,y+1)) 
		draw(x,y+1); 

	// Check the right neighbour
	if (x+1<canvas.get_width() && !canvas.get_pixel(x+1,y)) 
		draw(x+1,y);

	// Check the neighbour above
	if (y-1>=0 && !canvas.get_pixel(x,y-1)) 
		draw(x,y-1);

	//Check the left neighbour
	if (x-1>=0 && !canvas.get_pixel(x-1,y)) 
		draw(x-1,y); 
}



// Put debug output into the stream "stream" to be displayed in the
// main window
void recursive_fill_tool::set_text(std::stringstream& stream)
{
	stream<<"Tool: Recursive Fill (click to fill)";
}