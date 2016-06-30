// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "bresenham_circle_tool.h"
#include <algorithm>
#include <math.h>


bresenham_circle_tool::bresenham_circle_tool(canvas_buffer& canvas): tool_base(canvas)
{
	shape = TS_CIRCLE;
}


void bresenham_circle_tool::draw(int x0, int y0, int x1, int y1)
{
	int r = static_cast<int>(sqrt(static_cast<double>((x0-x1)*(x0-x1) + (y0-y1)*(y0-y1))));

	int a, b, c;
	b = 0;
	c = r;
	a = 6 - 3 * r;

	while (b < c){
		canvas.set_pixel(x0 + b, y0 + c);
		canvas.set_pixel(x0 + c, y0 + b);
		canvas.set_pixel(x0 + c, y0 - b);
		canvas.set_pixel(x0 + b, y0 - c);

		canvas.set_pixel(x0 - b, y0 + c);
		canvas.set_pixel(x0 - c, y0 + b);
		canvas.set_pixel(x0 - c, y0 - b);
		canvas.set_pixel(x0 - b, y0 - c);

		if (a<0)
			a += 6 * b + 9;
		else {
			a += +6 * (b - c) + 11;
			c--;
		}
		b++;
	}

	if (b == c)
	{
		canvas.set_pixel(x0 + b, y0 + c);
		canvas.set_pixel(x0 + c, y0 + b);
		canvas.set_pixel(x0 + c, y0 - b);
		canvas.set_pixel(x0 + b, y0 - c);
		canvas.set_pixel(x0 - b, y0 + c);
		canvas.set_pixel(x0 - c, y0 + b);
		canvas.set_pixel(x0 - c, y0 - b);
		canvas.set_pixel(x0 - b, y0 - c);
	}
}


void bresenham_circle_tool::set_text(std::stringstream& stream)
{
	stream<<"Tool: Bresenham-Circle (click and drag mouse to draw)";
}