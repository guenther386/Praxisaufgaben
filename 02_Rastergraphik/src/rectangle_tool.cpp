// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "rectangle_tool.h"
#include <algorithm>


rectangle_tool::rectangle_tool(canvas_buffer& canvas): tool_base(canvas)
{
	shape = TS_BOX;
}


void rectangle_tool::draw(int x0, int y0, int x1, int y1)
{
	if (x0 > x1)
		std::swap(x0, x1);
	if (y0 > y1)
		std::swap(y0, y1);

	for (int x = x0; x <= x1; x++) {
		canvas.set_pixel(x, y0);
		canvas.set_pixel(x, y1);
	}

	for (int y = y0; y <= y1; y++) {
		canvas.set_pixel(x0, y);
		canvas.set_pixel(x1, y);
	}
}


void rectangle_tool::set_text(std::stringstream& stream)
{
	stream<<"Tool: Rectangle (click and drag mouse to draw)";
}