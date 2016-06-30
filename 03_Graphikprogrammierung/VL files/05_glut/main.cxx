#include <GL/glut.h>

// declare external functions in glut_func.cxx without a header
extern void resize(int width, int height);
extern void display();
extern void key(unsigned char key, int x, int y);
extern void mouse(int button, int state, int x, int y);
extern void motion(int x, int y);
extern void timer(int data);
extern void init_application();

int main(int argc, char *argv[])
{
	// init glut
    glutInitWindowSize(1024,768);
    glutInitWindowPosition(100,20);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	// create window
	glutCreateWindow("Viewer");
	// set callback handlers
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	// application specific initialization that also initializes opengl
	init_application();
	// start main loop
    glutMainLoop();
    return 0;
}
