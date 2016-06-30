//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "recursive_cubes.h"


// Initialize variables
recursive_cubes::recursive_cubes()
{
	angle = 0;
	// Set maximum recursion depth
	depth = 4;
}



// Render the scene
void recursive_cubes::render()
{
	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Set the light parameters, projection and view
	setup_light();
	setup_projection();

	// Clear the screen
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Start the recursive rendering
	render_recursive(depth, true, 3);
}




void recursive_cubes::render_recursive(int r, bool render_all, int children)
{
	// first render the initial cube
	render_cube();


	/********
	Additional Task: Recursively render the cube tree. One cube in the
	                 tree contains another tree on every side which is
					 scaled by the factor 0.5 and translated to 4 units
					 away from the side. Use this method for the recursion.
					 The parameter "r" specifies the current recursion steps
					 that can still be made (must be decremented for every step)
					 while the parameter "render_all" is true if all sides shall
					 be rendered and false if the side facing a bigger side of
					 the last recursion step shall be omitted.
    Zusatzaufgabe:   Rendern Sie rekursiv den Wuerfelbaum. Ein Wuefel des Baums 
	                 enthält einen weiteren Wuerfelbaum auf jeder Seite, der um
					 den Faktor 0,5 skaliert und um 4 Einheiten von der Seite
					 weg verschoben wurde. Nutzen Sie diese Methode für die Rekursion.
					 Der Parameter "r" gibt die aktuell noch moeglichen Rekursions-
					 schritte ein (und muss also bei jedem Schritt verringert werden).
					 Der Paremter "render_all" soll auf true gesetzt werden, wenn
					 alle Seiten gerendert werden sollen und auf false, wenn die Seite,
					 die in Richtung einer größeren Seite eines Wuerfels aus dem vorherigen
					 Schritt zeigt, ausgelassen werden soll.
	************/





	// Hier wurde nur ein funktionsfähiger Weg gefunden an 4 Seiten des Würfels neue, skalierte Würfel zu zeichnen
	r = 0;
	if (r <= 3)
		// iterate through...
		for (int a = 0; a <= 3; a++){

		glPushMatrix();
			glRotated(a * 90 - 90, 0, 0, 1);
			glTranslated(2, 0, 0);
			glScaled(0.5, 0.5, 0.5);
			render_cube();
		glPopMatrix();
	}



	/* Hier wurde versucht einen rekursive Lösung zu finden; verursacht StackOverflow deshalb auskommentiert.
	
	depth = 4;
	if (depth < children)

		// iterate through
		for (children; children = 1; children--){

		glPushMatrix();
			glRotated(children * 90 - 90, 0, 0, 1);
			glTranslated(2, 0, 0);
			glScaled(0.5, 0.5, 0.5);
			render_cube();
			render_recursive(depth, true, children - 1);
		glPopMatrix();

		depth = depth - 1;
		}

	*/



}



// Render one single cube
void recursive_cubes::render_cube()
{
	// Set color to yellow
	glColor3d(1, 1, 0);
	// Render a cube with side length 2
	glutSolidCube(2);

}



// Set the projection and the view
void recursive_cubes::setup_projection()
{
	// For projection choose a perspective matrix with an aperture angle of
	// 45deg, an aspect ratio that corresponds to the width and height of the
	// window, z_near at 0.01 and z_far at 100.0
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, glutGet(GLUT_WINDOW_WIDTH) / static_cast<double>(glutGet(GLUT_WINDOW_HEIGHT)), 0.01, 100.0);

	// For the modelview matrix choose a view from the position (7.0, 3.0, 7.0) to
	// the position (0, 0, 0) where the up-direction is (0, 1, 0).
	// Also rotate with the specified angle around the Y-axis
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(7.0,3.0,7.0,  0,0,0,  0,1,0);
	glRotated(angle, 0, 1, 0);
}



// Set the light parameters
void recursive_cubes::setup_light()
{
	// Enable lighting
	glEnable(GL_LIGHTING);

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
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_color);


	glLightf(GL_LIGHT0,GL_SPOT_EXPONENT, 10.0f);   

	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glPopMatrix();
}



// Advance one frame
void recursive_cubes::advance_frame()
{
	// Increase angle and perform a modulo 360
	angle = (angle+1)%360;
}



// Set debug text
void recursive_cubes::set_text(std::stringstream &stream)
{
	stream<<"Recursive cubes with recursion depth "<<depth;
}