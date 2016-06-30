//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#pragma once

#include "abstract_scene.h"

class example_consecutive_primitives: public abstract_scene 
{
public:
	void render();
	void set_text(std::stringstream &stream);
};