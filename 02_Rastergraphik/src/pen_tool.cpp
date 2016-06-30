//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "pen_tool.h"

// Initialize the tool and store a reference of a canvas_buffer
pen_tool::pen_tool(canvas_buffer &canvas): tool_base(canvas)
{
	shape = TS_NONE;
}



// Set the pixel at (x, y)
void pen_tool::draw(int x, int y)
{
	// The pen algorithm is too complicated to be commented :). 
	canvas.set_pixel(x, y);
}



// Put debug output into the stream "stream" to be displayed in the
// main window
void pen_tool::set_text(std::stringstream& stream)
{
	stream<<"Tool: Pen (click and hold left button to draw)";
}