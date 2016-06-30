//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
Helper class to render previews.
This class renders definable shapes. It is used to display the previews
for the drawing tools. It can be enabled/disabled and rendered using the
"render" method.
*************************************************************************/
#pragma once

// provides the declaration of the super class tool_base
#include "tool_base.h"

class preview_renderer 
{
public:
	// Initialize the preview renderer
	preview_renderer();

	// Enable rendering of previews
	void enable_rendering();
	// Disable rendering of previews
	void disable_rendering();
	// Set the start of a 2-point shape
	void set_start(int x, int y);
	// Set the destination of a 2-point shape
	void set_dest(int x, int y);
	// Set the shape
	void set_shape(ToolShape shape);

	// Render the preview
	void render();

private:
	// The actual shape id
	ToolShape shape;
	// Start and destination of the shape
	int start_x, start_y, dest_x, dest_y;
	// State indicating whether rendering is enabled
	bool enabled;
};