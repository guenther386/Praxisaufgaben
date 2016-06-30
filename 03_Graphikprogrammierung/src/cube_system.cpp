//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "cube_system.h"

// Initialize variables
cube_system::cube_system()
{
	angle = 0;
}



// Setup the scene and render cube system
void cube_system::render()
{
	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	// Disable lighting
	glDisable(GL_LIGHTING);

	// Clear the screen and depth buffer
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set the projection and view
	setup_projection();

	// Render the system
	render_system();
}




// Advance one frame by increasing the rotation angle
void cube_system::advance_frame()
{
	// Increase angle and perform a modulo 360
	angle = (angle+1)%360;
}





// Render the cube system
void cube_system::render_system()
{
	/********
	Task 2.1.2.    Program the transformation tree from the exercise sheet. To store the
	               active aggregated transformation matrix on top of a stack use glPushMatrix 
				   and to reactivate and remove the top element of the transformation stack
				   use glPopMatrix. For animation a variable "angle" (which has values
				   between 0 and 359) is defined. Use it for rotations as defined in
				   the transformation tree.
	Aufgabe 2.1.2. Programmieren Sie den Transformationsbaum aus dem Uebungsblatt.
	               Nutzen Sie glPushMatrix um die aktuelle Gesamttransformations-Matrix an die 
				   Spitze eines Stacks zu speichern und glPopMatrix um die vorderste Matrix
				   im Stack zu entfernen und zu reaktivieren. Fuer Animationen steht eine Variable
				   "angle" zur Verfuegung (die Werte zwischen 0 und 359 enthält). Nutzen Sie diese
				   Variable für Rotationen analog zu den Angaben im gegebenen Transformationsbaum.
	*********/


	// Remove the following statement (if wanted) as it just serves 2.1.1.
	// Entfernen Sie die folgende Anweisung gegebenenfalls, da sie lediglich dem Testen
	// von Aufgabe 2.1.1 dient.
	

	glPushMatrix();
		glRotated(angle, 0, 1, 0);
		render_cube();
	glPopMatrix();
		glRotated(-angle, 0, 1, 0);
		glTranslated(5, 0, 0);
		glScaled(0.6, 0.6, 0.6);
			render_cube();

	glPushMatrix();
		glRotated(2 * angle, 0, 0, 1);
		glTranslated(3, 0, 0);	
		glScaled(0.5, 0.5, 0.5);
		render_cube();
	glPopMatrix();
		glRotated(2 * angle + 180, 0, 0, 1);
		glTranslated(3, 0, 0);
		glScaled(0.5, 0.5, 0.5);
		render_cube();

}





// Render one single cube
void cube_system::render_cube()
{
	/********
	Task 2.1.1.    Tesellate a cube by specifying vertices and colors via the commands 
	               glVertex3d and glColor3d. Choose appropriate primitives (parameter to 
				   glBegin) and provide vertices and colors for all 6 sides. The cube shall 
				   range from (-1, -1, -1) to (1, 1, 1).
	Aufgabe 2.1.1. Tesellieren Sie einen Wuerfel, indem Sie Vertices und Farben mittels
	               der Kommandos glVertex3d und glColor3d spezifizieren. Waehlen Sie
				   zunaechst das passende Zeichenprimitiv (Parameter von glBegin) und
                   erstellen Sie Vertices und Farben für alle 6 Seiten. Der Wuerfel soll
				   von (-1, -1, -1) bis (1, 1, 1) reichen.
	*********/

	glBegin(GL_TRIANGLES);	// dreiecke zeichnen


	glColor3d(1, 0, 0);		// Rot
	glVertex3d(-1, -1, -1);
	glVertex3d(-1, 1, -1);
	glVertex3d(1, -1, -1);
	glVertex3d(-1, 1, -1);
	glVertex3d(1, -1, -1);
	glVertex3d(1, 1, -1);
	
	glColor3d(1, 1, 0);		 // Gelb
	glVertex3d(1, -1, -1);
	glVertex3d(1, 1, 1);
	glVertex3d(1, 1, -1);
	glVertex3d(1, -1, -1);
	glVertex3d(1, 1, 1);
	glVertex3d(1, -1, 1);

	
	glColor3d(0, 0, 1);		// Blau
	glVertex3d(-1, -1, 1);
	glVertex3d(1, 1, 1);
	glVertex3d(-1, 1, 1);
	glVertex3d(-1, -1, 1);
	glVertex3d(1, 1, 1);
	glVertex3d(1, -1, 1);
	
	glColor3d(0, 1, 1);		// Türkis
	glVertex3d(-1, -1, -1);
	glVertex3d(-1, 1, 1);
	glVertex3d(-1, 1, -1);
	glVertex3d(-1, -1, -1);
	glVertex3d(-1, 1, 1);
	glVertex3d(-1, -1, 1);


	glColor3d(0, 1, 0);		// Grün
	glVertex3d(1, 1, -1);
	glVertex3d(-1, 1, -1);
	glVertex3d(1, 1, 1);
	glVertex3d(-1, 1, -1);
	glVertex3d(1, 1, 1);
	glVertex3d(-1, 1, 1);

	glColor3d(1, 0, 1);		// Pink
	glVertex3d(-1, -1, -1);
	glVertex3d(1, -1, 1);
	glVertex3d(-1, -1, 1);
	glVertex3d(-1, -1, -1);
	glVertex3d(1, -1, 1);
	glVertex3d(1, -1, -1);


	glEnd();

}




// Set the projection and the view
void cube_system::setup_projection()
{
	// For projection choose a perspective matrix with an aperture angle of
	// 45deg, an aspect ratio that corresponds to the width and height of the
	// window, z_near at 0.01 and z_far at 100.0
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, glutGet(GLUT_WINDOW_WIDTH) / static_cast<double>(glutGet(GLUT_WINDOW_HEIGHT)), 0.01, 100.0);

	// For the modelview matrix choose a view from the position (10.0, 6.0, -10.0) to
	// the position (0, 0, 0) where the up-direction is (0, 1, 0).
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10.0,6.0,-10.0,  0,0,0,  0,1,0);
}



// Set debug text
void cube_system::set_text(std::stringstream &stream)
{
	stream<<"Showing cube system (with rotation parameter at "<<angle<<"°)";
}