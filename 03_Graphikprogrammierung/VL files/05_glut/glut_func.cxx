#include "scene.h"
#include <GL/glut.h>
#include <cmath>

// define current view
static double translate_x = 0, translate_y = 0;
static double angle = 0;
static double scale = 1;

// define helper variables for interaction
static bool animate = false;
static bool wireframe = false;
static double last_time = 0;
static int last_x, last_y;
static int drag_button = -1;

// define global pointer to rendered scene
static node* scene = 0;

void init_application()
{
	// create scene and stream it out to console
	scene = create_random_scene(3);
	scene->stream_out(std::cout);
	std::cout << std::endl;

	// disable rendering of faces that do not face viewer
    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

	// configure depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

	// turn on lighting with one light and a material that is based on the current color
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

	// specify light source
	const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
	const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// specify default material
	const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
	const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
	const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat high_shininess[] = { 100.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

// callback to handle resize events of the window
void resize(int width, int height)
{
	// tell opengl to size of the 3d window
	glViewport(0, 0, width, height);
	// define perspective view frustum on projection matrix stack
    const float aspect_ratio = (float) width / (float) height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	double z_near = 0.02;
    glFrustum(-0.5*aspect_ratio*z_near, 0.5*aspect_ratio*z_near, 
		                   -0.5*z_near, 0.5*z_near, 
						        z_near, 100.0);
	// define eye and focus points as well as view up direction
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	gluLookAt(0,0,5,0,0,0,0,1,0);
}

// callback to display the scene
void display()
{
	// clear the framebuffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// perform transformation defined in mouse interaction
	glPushMatrix();
		glTranslated(translate_x, translate_y, 0);
		glRotated(angle, 0, 1, 0);
		glScaled(scale,scale,scale);
		// remember to be changed state attributes
		glPushAttrib(GL_POLYGON_BIT);
		// enable wireframe
		if (wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// draw the scene
		scene->draw();
		// restore opengl state
		glPopAttrib();
	glPopMatrix();
	// swap the newly rendered back buffer with the 
	//front buffer to make it visible
    glutSwapBuffers();
}

// handler for timer events
void timer(int data)
{
	// notify scene of timer event
    double time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	scene->animate(time-last_time, time);
	last_time = time;
	// re-trigger event if animation is activated
	if (animate)
		glutTimerFunc(20, timer, 0);
}

// handler for key press events
void key(unsigned char key, int x, int y)
{
	if (scene->handle_key_event(key))
		return;

    switch (key) {
    case 27 :
    case 'Q':
    case 'q': exit(0); break;
	case 'w' :
	case 'W' :
		wireframe = !wireframe;
		break;
	case 'a' :
	case 'A' :
		animate = !animate;
		if (animate)
		    glutTimerFunc(20, timer, 0);
		break;
    default : break;
    }
    glutPostRedisplay();
}

// handler for mouse button events
void mouse(int button, int state, int x, int y)
{
	// remember last mouse position
	last_x = x;
	last_y = y;
	// and button that is pressed for drag events
	if (state == GLUT_DOWN)
		drag_button = button;
	if (state == GLUT_UP && drag_button == button)
		drag_button = -1;
}

// handler for mouse drag events
void motion(int x, int y)
{
	// compute mouse motion
	int dx = x-last_x;
	int dy = y-last_y;
	// depending on drag button
	switch (drag_button) {
	case GLUT_LEFT_BUTTON :
		// perform rotation
		angle += 0.5*dx;
		glutPostRedisplay();
		break;
	case GLUT_MIDDLE_BUTTON :
		// translation
		translate_x += 0.01*dx;
		translate_y -= 0.01*dy;
		glutPostRedisplay();
		break;
	case GLUT_RIGHT_BUTTON :
		// or scaling
		scale *= exp(0.01*dy);
		glutPostRedisplay();
		break;
	}
	// remember mouse position for next event
	last_x = x;
	last_y = y;
}
