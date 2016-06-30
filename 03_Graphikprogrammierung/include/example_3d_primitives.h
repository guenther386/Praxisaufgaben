//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#pragma once

#include "abstract_scene.h"

class example_3d_primitives: public abstract_scene
{
public:
	example_3d_primitives();
	void render();
	void set_text(std::stringstream &stream);
	void advance_frame();

private:
	int angle;

	void render_tetrahedron();
	void render_cylinder();
	void render_cube();
	void render_sphere();

	void setup_projection();
	void setup_light();
};