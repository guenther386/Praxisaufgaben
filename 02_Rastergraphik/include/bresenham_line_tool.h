//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
Bresenham-Line tool.
This class is inherited from "tool_base" to define a tool for drawing
lines using the bresenham algorithm on a canvas_buffer. 
Read the information in "tool_base.h" for more information.
*************************************************************************/
#pragma once

// provides the declaration of the super class tool_base
#include "tool_base.h"

class bresenham_line_tool: public tool_base
{
public:
	// Initialize the tool and store a reference of a canvas_buffer
	bresenham_line_tool(canvas_buffer &canvas);

	// Draw a line from (x0, y0) to (x1, y1)
	void draw(int x0, int y0, int x1, int y1);

	// Put debug output into the stream "stream" to be displayed in the
	// main window
	void set_text(std::stringstream& stream);
};