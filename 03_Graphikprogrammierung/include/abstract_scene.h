//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
Abstract scene.
This class provides the basic super class for all scenes. To render a
frame of the implemented scene the method "render" must be called. If
the scene is animated the method "advance_frame" can be overwritten. It
is called every 1/30sec (from the application-class).
For debugging purpose a method "set_text" is provided which modifies a
text stream that will be displayed in the main window.
*************************************************************************/
#pragma once

#include <sstream>
#include <iostream>
#include "GL/glut.h"

class abstract_scene
{
public:
	// Virtual Destructor
	virtual ~abstract_scene() {};
	// Render the scene
	virtual void render() = 0;

	// Advance one frame
	virtual void advance_frame();

	// Put a text into the stream "stream" which will be displayed
	// in the main window
	virtual void set_text(std::stringstream &stream);
};
