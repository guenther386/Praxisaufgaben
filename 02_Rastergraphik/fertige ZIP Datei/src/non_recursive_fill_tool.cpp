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
	waiting_pixel p;
	std::deque<waiting_pixel> stack; 

	/************
	Task 3.2.2.    Implement a filling algothim without recursion. Use a stack instead.
				   The source code below inserts the first element into the stack and 
				   starts a loop that reads the front element from the stack and removes
				   it. Your task is to fill the functionality in the loop. Before you begin
				   think about when to set the pixel (at the beginning of the loop or after 
				   the stack was updated with neighbours). Use "canvas.set_pixel" to set
				   a pixel and "canvas.get_pixel" to read the state of a pixel.
    Aufgabe 3.2.2. Implementieren Sie einen Füllalgorithmus ohne Rekursion zu verwenden.
	               Nutzen Sie stattdessen einen Stack. Der vorgegebene Quelltext unten fuegt
				   das erste Element in den Stack ein und startet eine Schleife, die das 
				   vorderste Element aus dem Stack liest und es anschließend entfernt.
				   Ihre Aufgabe ist es die Funktionalitaet im Inneren der Schleife zu
				   ergaenzen. Bevor Sie beginnen machen Sie sich Gedanken an welcher Stelle
				   das tatsaechliche Setzen eines Pixels erfolgt (am Beginn der Schleife oder
				   nachdem der Stack mit Nachbarinformationen aktualisiert wurde). Nutzen
				   Sie "canvas.set_pixel" um einen Pixel zu setzen und "canvas.get_pixel" um
				   den Zustand eines Pixels zu erhalten.
   *************/



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
		// Complete the algorithm here

		stack.pop_front(); 
	}
}



// Put debug output into the stream "stream" to be displayed in the
// main window
void non_recursive_fill_tool::set_text(std::stringstream& stream)
{
	stream<<"Tool: Non-Recursive Fill (click to fill)";
}