// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#pragma once

#include "tool_base.h"
#include <deque>

using namespace std;


struct wait {
	int x, y; 
};


class line_fill_tool: public tool_base
{
public:
	line_fill_tool(canvas_buffer &canvas);
	void draw(int x, int y);
	void set_text(stringstream& stream);

private:
	bool enqueued_up, enqueued_down;
	deque<wait> stack;
	void fill(int x, int y, int dir);
};