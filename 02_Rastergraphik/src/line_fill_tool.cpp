// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "line_fill_tool.h"
#include <deque>


line_fill_tool::line_fill_tool(canvas_buffer& canvas): tool_base(canvas)
{
	shape = TS_NONE;
	is_draggable = false;
}


void line_fill_tool::draw(int x, int y)
{
	wait l;
	stack.clear();

	if (!canvas.get_pixel(x, y)) {
		l.x = x;
		l.y = y;
		stack.push_back(l);
	}

	while (!stack.empty()) {

		int cur_x = stack.front().x;
		int cur_y = stack.front().y;

		enqueued_up = false;
		enqueued_down = false;

		fill(cur_x, cur_y, -1);
		fill(cur_x + 1, cur_y, 1);

		stack.pop_front();
	}
}


void line_fill_tool::fill(int x, int y, int dir)
{
	wait l;
	if (x<canvas.get_width() && canvas.get_pixel(x, y))
		return;

	for (int i = x; i >= 0 && i<canvas.get_width() && !canvas.get_pixel(i, y); i += dir) {

		canvas.set_pixel(i, y);

		if (y>0) {
			if (!enqueued_up && !canvas.get_pixel(i, y - 1)) {
				l.x = i;
				l.y = y - 1;
				stack.push_back(l);
				enqueued_up = true;
			}

			if (canvas.get_pixel(i, y - 1))
				enqueued_up = false;
		}

		if (y + 1<canvas.get_height()) {
			if (!enqueued_down && !canvas.get_pixel(i, y + 1)) {
				l.x = i;
				l.y = y + 1;
				stack.push_back(l);
				enqueued_down = true;
			}

			if (canvas.get_pixel(i, y + 1))
				enqueued_down = false;
		}
	}
}


void line_fill_tool::set_text(stringstream& stream)
{
	stream<<"Tool: Line Fill (click to fill)";
}