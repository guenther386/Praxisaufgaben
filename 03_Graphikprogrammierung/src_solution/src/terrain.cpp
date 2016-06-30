//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "terrain.h"


// Load images and initialize variables
terrain::terrain()
{
	initialized = false;
	heightmap = 0;
	angle = 0;

	// The display list is not valid
	dl_valid = false;
	dl_handle = 0;

	// Try to load the heightmap. First try it from
	// "../../data" and then from "data/"
	if (!load_heightmap("../../data/tex_height.bmp") && 
		!load_heightmap("data/tex_height.bmp")) {
		std::cout<<"Could not load the heightmap!"<<std::endl;
		return;
	}

	// Try to load the texture. First try it from
	// "../../data" and then from "data/"
	if (!load_texture("../../data/tex_topo.bmp", &texture_handle) && 
		!load_texture("data/tex_topo.bmp", &texture_handle)) {
		std::cout<<"Could not load the texture!"<<std::endl;
		return;
	}

	initialized = true;

	// Basic initial settings
	set_show_solid(true);
	set_show_wireframe(false);
	set_show_levels(false);

}



// Unload images and textures
terrain::~terrain()
{
	// Delete the texture
	glDeleteTextures(1, &texture_handle);
	// Free the memory for the height map
	BMP_Free(heightmap);
	// Delete the display list if neccessary
	if (glIsList(dl_handle))
		glDeleteLists(dl_handle, 1);
}



// Render the actual scene
void terrain::render()
{
	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Enable automatic normalization of normals
	glEnable(GL_NORMALIZE);

	// Clear the screen
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Nothing to do if we are not properly initialized
	if (!initialized)
		return;

	// Setup perspective and modelview matrix
	setup_projection();
	// Setup light
	setup_light();


	// Render the solid terrain with lighting and texture mapping
	if (show_solid)
		render_solid_terrain();

	// Render the outline of the terrain
	if (show_wireframe)
		render_wireframe_terrain();

	// Eventually render level lines
	if (show_levels)
		render_level_lines();
}




// Render the terrain as solid
void terrain::render_solid_terrain()
{
	// Enable lighting
	glEnable(GL_LIGHTING);

	// This is a trick which is neccessary in order to draw lines
	// later on. Otherwise there would be artifacts due to a z-fight.
	glPolygonOffset(1, 1);
	glEnable(GL_POLYGON_OFFSET_FILL);

	// Enable texture mapping and bind our texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_handle);

	// Set the material color to white
	glColor3d(1, 1, 1);
	// Render the terrain
	render_terrain();

	// Disable texture mapping
	glDisable(GL_TEXTURE_2D);
	// Disable support for depth buffer offsets
	glDisable(GL_POLYGON_OFFSET_FILL); 
	// Disable lighting
	glDisable(GL_LIGHTING);
}




// Render the terrain as wireframe
void terrain::render_wireframe_terrain()
{
	// Set the line width to be 1 pixel
	glLineWidth(1.0);
	// Set the draw mode to draw outlines of polygons
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Set the color to black
	glColor3d(0, 0, 0);
	// Render the terrain
	render_terrain(); 

	// Set the draw mode to fill polygons
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}



// Render the terrain
void terrain::render_terrain()
{
	// Store width and height for faster access
	int map_width = get_heightmap_width();
	int map_height = get_heightmap_height();

	// Factors needed for texture mapping
	double factor_x = 1.0/static_cast<double>(map_width);
	double factor_y = 1.0/static_cast<double>(map_height);

	// Move and scale the coordinate system so that we can work with
	// whole units. That means that a vertex at height map position (x, y)
	// with a height of h can be placed as glVertex3d(x, h, y). The
	// terrain extents in the XZ-layer while the height is on the Y-axis.
	glPushMatrix();
	glTranslated(-1, 0, -1);
	glScaled(2.0/static_cast<double>(map_width), 1.0/256.0, 2.0/static_cast<double>(map_height));


	// Go through all rows (-1)
	for (int y = 0; y<map_height-1; y++) {

		// Begin a new triangle strip
		glBegin(GL_TRIANGLE_STRIP);

		// Draw the strip by consecutively passing two points
		for (int x = 0; x<map_width; x++) {

			// Set texture coordinates, normal and vertex for the first point
			glTexCoord2d(x*factor_x, y*factor_y);
			set_normal(x, y);
			glVertex3d(x, get_heightmap_value(x, y), y);

			// Set texture coordinates, normal and vertex for the second point
			glTexCoord2d(x*factor_x, (y+1)*factor_y);
			set_normal(x, y+1);
			glVertex3d(x, get_heightmap_value(x, y+1), y+1);
		}

		glEnd();
	}

	glPopMatrix();
}



// Calculate and set the normal for height map entry (x,y)
void terrain::set_normal(int x, int y)
{
	// The normal is estimated using central differences.
	// Also forward or backward differences could be used. Mind that no border
	// checks need to be done as this is handled in the get_heightmap_value method.

	// Get the vector in x-direction
	vec3d dx(2.0, get_heightmap_value(x+1, y) - get_heightmap_value(x-1, y), 0.0);
	// Get the vector in y-direction
	vec3d dz(0.0, get_heightmap_value(x, y+1) - get_heightmap_value(x, y-1), 2.0);

	// Normalize both vectors
	dx.normalize();
	dz.normalize();

	// Get a vector which is perpendicular to dx and dy by using the cross product
	vec3d normal = cross(dz, dx);

	// Pass the normal
	glNormal3d(normal.x(), normal.y(), normal.z());
}




// Render height level lines
void terrain::render_level_lines()
{
	// Set color to gray
	glColor3d(0.5, 0.5, 0.5);
	// Set the line width to 3 pixels
	glLineWidth(2.0);

	// Change the coordinate system so that one can work with whole units
	glPushMatrix();
	glTranslated(-1, 0, -1);
	glScaled(2.0/static_cast<double>(get_heightmap_width()), 1.0/256.0, 2.0/static_cast<double>(get_heightmap_height()));

	// Connect with lines
	glBegin(GL_LINES);

	// Render lines which were created in "create_level_lines" and stored into
	// the list "level_lines"
	for (int i=0; i<(int)level_lines.size(); i+=2) {
			glVertex3d(level_lines[i  ].x(), level_lines[i  ].y(), level_lines[i  ].z());
			glVertex3d(level_lines[i+1].x(), level_lines[i+1].y(), level_lines[i+1].z());
	}

	glEnd();

	// Set the width back to 1.0
	glLineWidth(1.0);

	glPopMatrix();
}



// Create height lines for the level "level"
void terrain::create_level_line(int level)
{
	/********
	Additional Task: Find iso lines with the "Marching Squares" algorithm for the 
	                 height value "level". Store the start and end points of the 
					 found lines in the list "level_lines".
    Zusatzaufgabe:   Finden Sie Hoehenlinien mittels des "Marching Squares"-Algorithmus
	                 fuer den Hoehenwert "level". Legen Sie die Start- und Endpunkte
					 der gefundenen Linien in der Liste "level_lines" ab.
	*************/
}



// Set the light parameters
void terrain::setup_light()
{
	// Enable lighting and colored materials
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	// Enable light source 0
	glEnable(GL_LIGHT0);

	// Set the modelview matrix to be the identity to avoid
	// having the light position moved with the terrain.
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Set light parameters
	float position[4]={1.0f,1.0f,1.0f,1.0f};
	float ambient_color[4]={0.0f,0.0f,0.0f,1.0f};
	float diffuse_color[4]={1.0f,1.0f,1.0f,1.0f};
	float specular_color[4]={1.0f,1.0f,1.0f,1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_color);

	glLightf(GL_LIGHT0,GL_SPOT_EXPONENT, 10.0f);   

	glPopMatrix();

	glDisable(GL_LIGHTING);

}



// Set the projection and the view
void terrain::setup_projection()
{
	// For projection choose a perspective matrix with an aperture angle of
	// 45deg, an aspect ratio that corresponds to the width and height of the
	// window, z_near at 0.01 and z_far at 10.0
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, glutGet(GLUT_WINDOW_WIDTH) / static_cast<double>(glutGet(GLUT_WINDOW_HEIGHT)), 0.01, 10.0);

	// For the modelview matrix choose a view from the position (2.5, 2.5, 0) to
	// the position (0, 0, 0) where the up-direction is (0, 1, 0).
	// Also rotate with the specified angle around the Y-axis
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.5,2.5,0,  0,0,0,  0,1,0);
	glRotated(angle, 0,1,0);
}



// Advance one frame
void terrain::advance_frame()
{
	// Increase angle and perform a modulo 360
	angle = (angle+1)%360;
}



// (De)activate solid rendering
void terrain::set_show_solid(bool state)
{
	show_solid = state;
	// The current display list is outdated now
	dl_valid = false;
}


// (De)activate wireframe rendering
void terrain::set_show_wireframe(bool state)
{
	show_wireframe = state;
	// The current display list is outdated now	
	dl_valid = false;
}


// (De)activate height level line rendering
void terrain::set_show_levels(bool state)
{
	show_levels = state;

	// If level lines shall be displayed then
	// recreate them in equidistant ranges
	if (show_levels) {
		level_lines.clear();
		for (int i=20; i<=255; i+=20)
			create_level_line(i);
	}

	// The current display list is outdated now
	dl_valid = false;
}




// Load the height map from the file "filename"
bool terrain::load_heightmap(const char *filename)
{
	// Load the heightmap by reading a bmp file
	heightmap = BMP_ReadFile(filename);

	// Return false and show an error message if the file
	// could not be loaded
	if (BMP_GetError() != BMP_OK) 
		return false;

	// All went well...
	return true;	
}




// Load a texture and store its handle in "handle"
bool terrain::load_texture(const char *filename, GLuint *handle)
{
	BMP *bitmap;

	// Load the texture by reading a bmp file
	bitmap = BMP_ReadFile(filename);

	// Return false and show an error message if the file
	// could not be loaded
	if (BMP_GetError() != BMP_OK) 
		return false;

	// Get a pointer to the bitmap data
	unsigned char* data = BMP_GetImageData(bitmap);

	// Generate one texture and store its ID in "handle"
	glGenTextures(1, handle);
	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, *handle);
	// Enable linear blending between different mipmapping levels
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	// Clamp the texture at the borders
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	// Transfer the image data to the graphics card.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP_GetWidth(bitmap), BMP_GetHeight(bitmap), 0, GL_RGB, GL_UNSIGNED_BYTE, data);	

	// Not needed anymore
	free(data);
	BMP_Free(bitmap);

	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}



// Return the width of the height map
int terrain::get_heightmap_width() const
{
	return BMP_GetWidth(heightmap);
}



// Return the height of the height map
int terrain::get_heightmap_height() const
{
	return BMP_GetHeight(heightmap);
}



// Return the height value at (x,y)
int terrain::get_heightmap_value(int x, int y) const
{
	// Returns one value from the heightmap. The image should
	// be in grayscale so just the red channel is returned.
	// The image is mirrored at the edges (by adjusting the
	// coordinates) to assure correct normal estimation.
	unsigned char r, g, b;

	// Mirror at the left and upper edge if neccessary
	x = abs(x);
	y = abs(y);

	// Mirror at the right and bottom edge if neccessary
	if (x>=get_heightmap_width())
		x = 2*get_heightmap_width()-x-1;
	if (y>=get_heightmap_height())
		y = 2*get_heightmap_height()-y-1;

	// Read the pixel and return the red component
	BMP_GetPixelRGB(heightmap, x, y, &r, &g, &b);

	return r;
}



// Set debug text
void terrain::set_text(std::stringstream &stream)
{
	if (!initialized) {
		stream<<"Cannot show terrain - not all files were loaded!";
		return;
	}
	stream<<"Showing terrain";

	if (!show_solid && !show_wireframe && !show_levels) {
		stream<<" (all features disabled)";
		return;
	}

	stream<<" (";
	if (show_solid)
		stream<<"as solid geometry";
	if (show_solid && show_wireframe)
		stream<<", ";
	if (show_wireframe)
		stream<<"as wireframe";
	if (show_wireframe && show_levels)
		stream<<", ";
	if (show_levels)
		stream<<"with level lines";
	stream<<")";
}