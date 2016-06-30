#define _USE_MATH_DEFINES
#include <cmath>

#include "scene.h"
#include "particle_system.h"
#include <stdlib.h>
#include <GL/glut.h>

// recursive function to construct the scene tree
void create_random_tree(group_node* parent, unsigned max_depth)
{
	// randomly choose a geometry type
	int gt_idx = (rand()*geometry_node::LAST_GEOMETRY+RAND_MAX/2-1)/RAND_MAX;
	// convert back from int
	geometry_node::GeometryType gt = geometry_node::GeometryType(gt_idx);
	// create geometry node with random geometry type and random aspect in [0.5,1.0]
	parent->add_child(new geometry_node(gt,(double)rand()/RAND_MAX+0.5));
	// if recursion needed
	if (max_depth > 1)
		// add four transformation node children to parent node 
		for (unsigned i=0; i<4; ++i) {
			// which are rotated in 90 degrees steps, moved out and scaled down
			group_node* child_group = 
				new transform_node(90*i,node::V3d(0,0,1),node::V3d(2,0,0),0.25);
			parent->add_child(child_group);
			// recursive call of this function to create the children of the children
			create_random_tree(child_group, max_depth-1);
		}
}

/// construct some random scene with a style node as root node
node* create_random_scene(int max_depth)
{
	group_node* root = new style_node();
	create_random_tree(root, max_depth);
	return root;
}

// declare and initialize number of identations used when streaming out nodes
unsigned group_node::nr_identations = 0;

// draw group by calling callback handlers and child draw method in between 
void group_node::draw() 
{
	before_draw_children();
	for (unsigned i=0; i<get_nr_children(); ++i)
		get_child(i)->draw();
	after_draw_children();
};


/// serialize to disk
void group_node::stream_out(std::ostream& os) const 
{
	// in group node header write type name, node specific data and open parenthesis
	os << get_type_name() << " ";
	stream_node_data(os);
	os << " {\n";
	// for each child
	for (unsigned i=0; i<get_nr_children(); ++i) {
		// increase identation
		++nr_identations;
			os << std::string(2*nr_identations, ' ');
			// stream out child
			get_child(i)->stream_out(os);
			os << std::endl;
		// and decrease identation again
		--nr_identations;
	}
	// stream out closing parenthesis with current identation
	os << std::string(2*nr_identations, ' ') << "}";
}

bool group_node::handle_key_event(char key) 
{ 
	// pass key event on to the children and stopp as soon as the event has been handled
	for (unsigned i=0; i<get_nr_children(); ++i) {
		if (get_child(i)->handle_key_event(key))
			return true;
	}
	return false; 
}

void group_node::animate(double dt, double time)
{
	// pass the animation event on to the children
	for (unsigned i=0; i<get_nr_children(); ++i)
		get_child(i)->animate(dt, time);
}


// construct from transformation parameters
transform_node::transform_node(double _angle, const V3d& _axis, const V3d& _translation, double _scale)
	: angle(_angle), axis(_axis), translation(_translation), scale(_scale)
{
	anim_scale = 1;
}

// push transformation on transformation stack
void transform_node::before_draw_children()
{
	glPushMatrix();
		glRotated(angle, axis(0), axis(1), axis(2));
		glTranslated(translation(0),translation(1),translation(2));
		glScaled(anim_scale*scale,anim_scale*scale,anim_scale*scale);
}

// restore previous transformation with pop
void transform_node::after_draw_children()
{
	glPopMatrix();
}

void transform_node::stream_node_data(std::ostream& os) const
{
	// stream transformation data
	os << translation << " " << angle << " " << axis << " " << scale;
}

bool transform_node::handle_key_event(char key)
{
	// allow to increase or decrease the scale by '+'- and '-'-key
	switch (key) {
	case '+' : 
		scale *= 1.25;
		// post a redisplay event whenever something changes in the scene
		glutPostRedisplay();
		return true;
	case '-' : 
		scale /= 1.25;
		glutPostRedisplay();
		return true;
	}
	return group_node::handle_key_event(key);
}

void transform_node::animate(double dt, double time)
{
	anim_scale = 0.05*sin(0.01*angle*M_PI*time)+1;
	glutPostRedisplay();
	// dont forget to call the method of the base class to also animate the children
	group_node::animate(dt,time);
}

style_node::style_node(const V3d& _color, bool _wireframe, double _line_width)
	: color(_color), wireframe(_wireframe), line_width(_line_width)
{
}

void style_node::before_draw_children()
{
	glPushAttrib(GL_LINE_BIT|GL_POLYGON_BIT|GL_CURRENT_BIT);
		glColor3dv(color);
		if (wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth((float)line_width);
}

void style_node::after_draw_children()
{
	glPopAttrib();
}

void style_node::stream_node_data(std::ostream& os) const
{
	os << color << " " << wireframe << " " << line_width;
}


bool style_node::handle_key_event(char key)
{
	switch (key) {
	case 'w' :
	case 'W' :
		wireframe = !wireframe;
		glutPostRedisplay();
		return true;
	case 'l' : 
		line_width += 1;
		glutPostRedisplay();
		return true;
	case 'L' : 
		if (line_width > 1)
			line_width -= 1;
		glutPostRedisplay();
		return true;
	}
	return group_node::handle_key_event(key);
}

geometry_node::geometry_node(GeometryType _geometry_type, double _aspect) 
	: geometry_type(_geometry_type), aspect(_aspect)
{
	// allocate particle system only for the teapot geometry
	ps = 0;
	if (geometry_type == TEAPOT)
		ps = new particle_system();
}

// destruct also particles system
geometry_node::~geometry_node()
{
	if (ps)
		delete ps;
}


/// draw the node
void geometry_node::draw()
{
	switch (geometry_type) {
	case CUBE:   glutSolidCube(1); break;
	case SPHERE: glutSolidSphere(1,40,20); break;
	case CONE:   glutSolidCone(1,aspect,40,20); break;
	case TORUS:  glutSolidTorus(aspect,1,40,40); break;
	case TEAPOT: 
		// tesselation of the teapot specifies faces with wrong orientation
		glPushAttrib(GL_POLYGON_BIT);
			// therefore cull front instead of backfaces
			glCullFace(GL_FRONT);
			glutSolidTeapot(1); 
		glPopAttrib();
		break;
	default: break;
	}
	// draw particle system at tip of teapot
	if (ps) {
		glPushMatrix();
			glTranslated(1.5,0.5,0);
			ps->draw();
		glPopMatrix();
	}
}

void geometry_node::stream_out(std::ostream& os) const
{
	// declare name for each enum entry
	const char* names[] = { "cube", "sphere", "cone", "torus", "teapot" };
	os << get_type_name() << " " << geometry_type << " " << aspect;
}

/// handle key event
bool geometry_node::handle_key_event(char key)
{
	switch (key) {
	case 't' :
	case 'T' :
		if (++(int&)geometry_type == LAST_GEOMETRY)
		   geometry_type = FIRST_GEOMETRY;
		// in case of geometry change, ensure that particle system is present only for teapot
		if (geometry_type == TEAPOT)
			ps = new particle_system();
		else
			if (ps) {
				delete ps;
				ps = 0;
			}
		glutPostRedisplay();	   
		return true;
	case 's' : 
		aspect *= 1.25;
		glutPostRedisplay();	   
		return true;
	case 'S' : 
		aspect /= 1.25;
		glutPostRedisplay();	   
		return true;
	}
	return false;
}

void geometry_node::animate(double dt, double time)
{
	// pass on animation event to children
	if (ps) {
		ps->animate(dt, time);
		glutPostRedisplay();
	}
}
