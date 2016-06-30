//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
Terrain.
This class represents a textured and shaded terrain. Both, the texture
and the height map is read from a bmp file (in the constructor). 
The height map is mapped to a regular grid consisting of triangle strips.
During rendering the normals needed for lighting are calculated.
There are some additional rendering modes:
- solid: The terrain with texture and lighting
- wireframe: The wireframe of the elevated triangle mesh
- levels: Some height levels that were evaluated using the marching
  squares algorithm.
The rendering is done in the "render" method which sets the projection
and view via "setup_projection" and the light via "setup_light".
Depending on the settings (that can be changed using "set_show_solid",
"set_show_wireframe" and "set_show_levels") different passes are rendered
using the appropriate rendering method ("render_solid_terrain", 
"render_wireframe_terrain", "render_level_lines"). They call the
"render_terrain" method.
*************************************************************************/
#pragma once

#include "GL/glut.h"
#include "abstract_scene.h"
#include "qdbmp.h"
#include "tiny_vec.h"
#include <vector>

class terrain: public abstract_scene
{
public:
	// Load images and initialize variables
	terrain();

	// Unload images and textures
	~terrain();

	// Render the actual scene
	void render();

	// Advance one frame
	void advance_frame();

	// (De)activate solid rendering
	void set_show_solid(bool state);

	// (De)activate wireframe rendering
	void set_show_wireframe(bool state);

	// (De)activate height level line rendering
	void set_show_levels(bool state);

	// Set debug text
	void set_text(std::stringstream &stream);

private:
	// The current rotation angle
	int angle;
	// The heightmap data
	BMP *heightmap;
	// Texture handle
	GLuint texture_handle;
	// Is everything loaded?
	bool initialized;
	// Setting states
	bool show_solid, show_wireframe, show_levels;

	// Display list handle
	GLuint dl_handle;
	// True if the display list is valid
	bool dl_valid;

	// List of line points
	std::vector<point3d> level_lines;

	// Render the terrain
	void render_terrain();
	// Calculate and set the normal for height map entry (x,y)
	void set_normal(int x, int y);


	// Render the terrain as solid
	void render_solid_terrain();
	// Render the terrain as wireframe
	void render_wireframe_terrain();
	// Render height level lines
	void render_level_lines();
	// Create height lines for the level "level"
	void create_level_line(int level);

	
	// Load the height map from the file "filename"
	bool load_heightmap(const char *filename);
	// Return the width of the height map
	int get_heightmap_width() const;
	// Return the height of the height map
	int get_heightmap_height() const;
	// Return the height value at (x,y)
	int get_heightmap_value(int x, int y) const;

	// Set the light parameters
	void setup_light();
	// Set the projection and the view
	void setup_projection();

	// Load a texture and store its handle in "handle"
	bool load_texture(const char* filename, GLuint *handle);

};