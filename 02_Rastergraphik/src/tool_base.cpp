//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "tool_base.h"

// Initialize the tool and store a reference of a canvas_buffer
tool_base::tool_base(canvas_buffer &canvas): canvas(canvas)
{
	shape = TS_NONE;
	is_draggable = true;
}



// Draw with one point provided
void tool_base::draw(int x, int y)
{
	// Nothing implemented here. Children of this class can implement
	// this method if needed
}


// Draw with two points provided
void tool_base::draw(int from_x, int from_y, int to_x, int to_y)
{
	// Nothing implemented here. Children of this class can implement
	// this method if needed
}



// Get the shape that this tool will draw
const ToolShape tool_base::get_shape() const
{
	return shape;
}



// Put a text into the stream "stream" which will be displayed
// in the main window
void tool_base::set_text(std::stringstream &stream)
{
	// Nothing implemented here. Children of this class can implement
	// this method if needed
}



// Return true if draw(x, y) is valid during dragging operations
const bool tool_base::is_tool_draggable() const
{
	return is_draggable;
}