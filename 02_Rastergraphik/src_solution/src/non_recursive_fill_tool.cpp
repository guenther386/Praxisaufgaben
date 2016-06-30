//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "non_recursive_fill_tool.h"
#include <deque>

// Initialize the tool and store a reference of a canvas_buffer
non_recursive_fill_tool::non_recursive_fill_tool(canvas_buffer& canvas): tool_base(canvas)
{
	// This tool has no shape and is not draggable
	shape = TS_NONE;
	is_draggable = false;
}


// A pixel to be put into the queue of pixels to process
struct waiting_pixel {
	int x, y; 
};



void non_recursive_fill_tool::draw(int x, int y)
{
	// Non-recursive filling works by a standard conversion
	// of recursive algorithms into iterative algorithms through
	// the introduction of a stack.
	// There is one pitfall concerning the time when to set
	// the actual pixel. This must be done before it is enqueued
	// and not at the beginning of the while-loop. In the latter
	// case pixels would be added multiple times. 
	// For example: 
	//   - iteration 1 acts on (2, 2) and adds its neighbours, among them (3, 2)
	//   - in iteration 2 the pixel (3, 2) would be set and its neighbours,
	//     including (3, 3) is enqueued
	//   - in iteration 3 the pixel (3, 3) would be set and its neighbours,
	//     including (2, 3) would be enqueued which is already in the list
	//     of pixels to fill because it is also a neighbour of (2,2).
	//     If it was filled BEFORE adding it to the queue in the iteration of
	//     (2, 2) than this error would not happen.
	// +---+---+---+      +---+---+---+      +---+---+---+
	// |   | 4 |   |      |   | - | 3 |      |   | - | 1 |
	// +---+---+---+      +---+---+---+      +---+---+---+
	// | 3 | o | 1 |      | - | o | o |      | - | o | o |  
	// +---+---+---+  ->  +---+---+---+  ->  +---+---+---+  
	// |   | 2 |   |      |   | - | 2 |      |   |2/-| o | <-- "2/-": enqueued twice
	// +---+---+---+      +---+---+---+      +---+---+---+
	// |   |   |   |      |   |   |   |      |   |   | 1 |
	// +---+---+---+      +---+---+---+      +---+---+---+
	// (ASCII-Art FTW!)

	waiting_pixel p;
	std::deque<waiting_pixel> stack; 

	// Put the initial pixel into the stack
	if (!canvas.get_pixel(x, y)) {
		p.x = x; 
		p.y = y; 
		canvas.set_pixel(x, y);
		stack.push_back(p);
	}
	
	// While there are pixels to be checked
	while (!stack.empty()) {
		int cur_x = stack.front().x; 
		int cur_y = stack.front().y;

		// Check the right neighbour
		if (cur_x+1<canvas.get_width() && !canvas.get_pixel(cur_x+1, cur_y)) {
			p.x = cur_x+1; 
			p.y = cur_y;
			canvas.set_pixel(cur_x+1, cur_y);
			stack.push_back(p);
		}


		// Check the neighbour below
		// Mind the order of the predicates in the if-clause
		if (cur_y+1<canvas.get_height() && !canvas.get_pixel(cur_x, cur_y+1)) {
			p.x = cur_x; 
			p.y = cur_y+1;
			// Set the pixel
			canvas.set_pixel(cur_x, cur_y+1);
			// And put it into the queue
			stack.push_back(p); 
		}

		// Check the left neighbour
		if (cur_x>0 && !canvas.get_pixel(cur_x-1,cur_y)){
			p.x = cur_x-1; 
			p.y = cur_y;
			canvas.set_pixel(cur_x-1, cur_y);
			stack.push_back(p);
		}


		// Check the neighbour above
		if (cur_y>0 && !canvas.get_pixel(cur_x,cur_y-1))  {
			p.x = cur_x; 
			p.y = cur_y-1;
			canvas.set_pixel(cur_x, cur_y-1);
			stack.push_back(p);
		}

		stack.pop_front(); 
	}
}



// Put debug output into the stream "stream" to be displayed in the
// main window
void non_recursive_fill_tool::set_text(std::stringstream& stream)
{
	stream<<"Tool: Non-Recursive Fill (click to fill)";
}