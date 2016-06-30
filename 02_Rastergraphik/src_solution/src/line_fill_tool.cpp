//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "line_fill_tool.h"
#include <deque>


// Initialize the tool and store a reference of a canvas_buffer
line_fill_tool::line_fill_tool(canvas_buffer& canvas): tool_base(canvas)
{
	// This tool has no shape and is not draggable
	shape = TS_NONE;
	is_draggable = false;
}



// Fill the shape that contains the point (x, y)
void line_fill_tool::draw(int x, int y)
{
	// This implementation of line fill works by first providing
	// a starting line which contains the position (x, y). From
	// this position the line is first drawn to the left. At every
	// pixel it is checked whether the pixel above is already set
	// and if not, a new line is put into a queue of lines to process.
	// The same happens with the pixels below. To avoid putting the
	// same lines into the queue multiple times (for neighbouring
	// pixels) a state enqueued_above and enqueued_below is maintained
	// that will be set to true after a line above or below was added
	// to the queue. It is reset to false again when the line above or
	// below ends, i.e. when an already set pixel occurs. From the 
	// beginning of the next unset pixel a new line is put into the queue.

	waiting_line l;
	stack.clear();

	// Put the initial line into the queue
	if (!canvas.get_pixel(x, y)) {
		l.x = x; 
		l.y = y; 
		stack.push_back(l);
	}

	// While there are lines to process...
	while (!stack.empty()) {

		int cur_x = stack.front().x;
		int cur_y = stack.front().y;

		enqueued_above = false;
		enqueued_below = false;

		// Fill the line by growing left
		fill_line(cur_x, cur_y, -1);
		// Fill the line by growing right
		fill_line(cur_x+1, cur_y, 1);

		// Pop the first element from the queue
		stack.pop_front();
	}
}





// Fill a line and add lines above and below to the stack if needed
void line_fill_tool::fill_line(int x, int y, int dir)
{
	waiting_line l;

	// Return if the pixel is already set or exceeds the boundary
	if (x<canvas.get_width() && canvas.get_pixel(x, y))
		return;

	// Go into the provided direction until the x-coordinate is out of
	// range or hits a set pixel
	for (int i=x; i>=0 && i<canvas.get_width() && !canvas.get_pixel(i, y); i+=dir) {

		// Set the pixel
		canvas.set_pixel(i, y);

		// Check the line above
		if (y>0) {
			// If the pixel above is not set and no line that will process that
			// pixel is in the queue then add one
			if (!enqueued_above && !canvas.get_pixel(i, y-1)) {
				l.x = i;
				l.y = y-1;
				stack.push_back(l);
				enqueued_above = true;
			}

			// If the line for the pixels above is interrupted then allow new lines
			if (canvas.get_pixel(i, y-1))
				enqueued_above = false;
		}

		// Check the line below
		if (y+1<canvas.get_height()) {
			// If the pixel below is not set and no line that will process that
			// pixel is in the queue then add one
			if (!enqueued_below && !canvas.get_pixel(i, y+1)) {
				l.x = i;
				l.y = y+1;
				stack.push_back(l);
				enqueued_below = true;
			}

			// If the line for the pixels below is interrupted then allow new lines
			if (canvas.get_pixel(i, y+1))
				enqueued_below = false;
		} 
	}
}




// Put debug output into the stream "stream" to be displayed in the
// main window
void line_fill_tool::set_text(std::stringstream& stream)
{
	stream<<"Tool: Line Fill (click to fill)";
}