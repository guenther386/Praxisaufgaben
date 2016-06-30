//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
Cube system in split screen.
This class is inherited from cube_system to render different views of
the system. While the top left, top right and bottom left views are
orthographic projections of one of the major directions the fourth panel
in the lower right renders a perspective version of the scene. 
This class demonstrates how to implement orthographic views and split
screens.
*************************************************************************/
#pragma once

#include "cube_system.h"

class cube_system_split: public cube_system
{
public:
	// Render the scene
	void render();

	// Set debug text
	void set_text(std::stringstream &stream);
};