//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "bresenham_circle_tool.h"
#include <algorithm>
#include <math.h>

// Initialize the tool and store a reference of a canvas_buffer
bresenham_circle_tool::bresenham_circle_tool(canvas_buffer& canvas): tool_base(canvas)
{
	// This tool draws circles!
	shape = TS_CIRCLE;
}



// Draw a circle with center (x0, y0) and (x1, y1) on the circle
void bresenham_circle_tool::draw(int x0, int y0, int x1, int y1)
{
	// Calculate the radius
	int r = static_cast<int>( sqrt( static_cast<double>( (x0-x1)*(x0-x1) + (y0-y1)*(y0-y1) ) ) );

	int x,y,d;

	x=0;
	y=r;
	d = 3-2*r;

	while(x < y){
		// Draw all 8 octants
		canvas.set_pixel(x0+x,y0+y);
		canvas.set_pixel(x0+y,y0+x);
		canvas.set_pixel(x0+y,y0-x);
		canvas.set_pixel(x0+x,y0-y);

		canvas.set_pixel(x0-x,y0+y);
		canvas.set_pixel(x0-y,y0+x);
		canvas.set_pixel(x0-y,y0-x);
		canvas.set_pixel(x0-x,y0-y);

		if(d < 0)
			d += 4*x+6;
		else {
			d +=  + 4*(x - y) +10;
			y--;
		}
		x++;

	}

	// Draw the missing pixels to connect the octants
	if(x==y)
	{
		canvas.set_pixel(x0+x,y0+y);
		canvas.set_pixel(x0+y,y0+x);
		canvas.set_pixel(x0+y,y0-x);
		canvas.set_pixel(x0+x,y0-y);

		canvas.set_pixel(x0-x,y0+y);
		canvas.set_pixel(x0-y,y0+x);
		canvas.set_pixel(x0-y,y0-x);
		canvas.set_pixel(x0-x,y0-y);
		
	} 
}



// Put debug output into the stream "stream" to be displayed in the
// main window
void bresenham_circle_tool::set_text(std::stringstream& stream)
{
	stream<<"Tool: Bresenham-Circle (click and drag mouse to draw)";
}