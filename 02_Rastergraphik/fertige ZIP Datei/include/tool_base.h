//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
Abstract tool.
This class provides the basic superclass for all tools (pen, lines, circle...)
The constructor of the class takes a reference of a canvas_buffer as parameter
on which the pixels are changed. 
The user of an instance of a derived class can use two different draw methods:
One version that operates only with the information of a single position
(e.g. the pen or the fill tools) and one that needs two pixel positions
(e.g. the line, circle or box). Also every tool maintains an element of
the enumerations of possible shapes (which are used for the preview tool).
For debugging purpose a method "set_text" is provided which modifies a
text stream that will be displayed in the main window.
*************************************************************************/
#pragma once

// needed for the set_text method
#include <sstream>
// declares the canvas_buffer
#include "canvas_buffer.h"


// Enumeration of possible shapes
enum ToolShape
{
	TS_LINE,		// a line
	TS_BOX,			// a box
	TS_CIRCLE,		// a circle
	TS_NONE			// no shape
};




class tool_base
{
public:
	// Initialize the tool and store a reference of a canvas_buffer
	tool_base(canvas_buffer &canvas);

	// Draw with one point provided
	virtual void draw(int x, int y);
	// Draw with two points provided
	virtual void draw(int x0, int y0, int x1, int y1);

	// Get the shape that this tool will draw
	const ToolShape get_shape() const;

	// Put a text into the stream "stream" which will be displayed
	// in the main window
	virtual void set_text(std::stringstream& stream);

	// Return true if draw(x, y) is valid during dragging operations
	const bool is_tool_draggable() const;

protected:
	// The shape which is initialized in the constructor
	ToolShape shape;
	// A reference of the canvas store
	canvas_buffer &canvas;

	bool is_draggable;
};