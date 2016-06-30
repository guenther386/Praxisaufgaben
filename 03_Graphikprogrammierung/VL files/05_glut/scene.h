#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "fvec.h"

// declare the particle system class without including its header
class particle_system;

//! Abstract base class for all node types in the scene.
/*! It supports drawing, serialization and event handling. */
class node
{
public:
	/// define type of 3d vectors
	typedef fvec<double,3> V3d;
	/// constructor of node is empty
	node() {}
	/// virtual destructor is needed for proper clean up
	virtual ~node() {}
	/// return the type name of the node class, this must be implemented in derived classes
	virtual std::string get_type_name() const = 0;
	/// draw the node, this must be implemented in derived classes
	virtual void draw() = 0;
	/// serialize to disk, this must be implemented in derived classes
	virtual void stream_out(std::ostream& os) const = 0;
	/// handle key event and return whether the event has been handled
	virtual bool handle_key_event(char key) { return false; }
	/// animation callback
	virtual void animate(double dt, double time) {}
};

/// construct some random scene
extern node* create_random_scene(int max_depth);

//! A group node can have several child nodes. 
/*! All callback functions are handed on to the children. */
class group_node : public node
{
private:
	/// number of identation when streaming out tree
	static unsigned nr_identations;
protected:
	/// keep vector of child nodes
	std::vector<node*> children;
public:
	/// constructor of node is empty
	group_node() {}
	/// destruct all children
	~group_node() { for (unsigned i=0; i<children.size(); ++i) delete children[i]; }
	/// return the type name of the node class
	std::string get_type_name() const { return "group_node"; }
	/**@name access to children*/
	//@{
	/// return the total number of children
	unsigned get_nr_children() const { return children.size(); }
	/// return the i-th child
	node* get_child(unsigned i) const { return children[i]; }
	/// add another child to the group
	void add_child(node* _child) { children.push_back(_child); }
	//@}

	/**@name drawing methods*/
	//@{
	/// this is called by the draw method before the child nodes are drawn
	virtual void before_draw_children() {}
	/// this is called by the draw method after the child nodes have been drawn
	virtual void after_draw_children() {}
	/// draw the node
	void draw();
	//@}

	/**@name streaming methods*/
	//@{
	/// stream all information specific to a given node type
	virtual void stream_node_data(std::ostream& os) const {}
	/// serialize to disk
	void stream_out(std::ostream& os) const;
	//@}
	/// handle key event and return whether the event has been handled
	bool handle_key_event(char key);
	/// animation callback
	void animate(double dt, double time);
};

/** group node with transformation that is applied to all children */
class transform_node : public group_node
{
protected:
	/// rotation angle
	double angle;
	/// axis around which to rotate
	V3d axis;
	/// translation vector
	V3d translation;
	/// scale factor
	double scale;
	/// additional scale factor used by animation
	double anim_scale;
public:
	/// construct from transformation parameters
	transform_node(double _rot_angle = 0, const V3d& _axis = V3d(0,0,1), 
				   const V3d& _translation = V3d(0,0,0), 
		           double _scale = 1);
	/// return the type name of the node class
	std::string get_type_name() const { return "transform_node"; }
	/// push transformation on transformation stack
	void before_draw_children();
	/// restore previous transformation with pop
	void after_draw_children();
	/// stream all information specific to a given node type
	void stream_node_data(std::ostream& os) const;
	/// handle key event	
	bool handle_key_event(char key);
	/// sets the anim_scale member depending on the time and rotation angle
	void animate(double dt, double time);
};

/** style node */
class style_node : public group_node
{
protected:
	/// whether to draw in wireframe mode
	bool wireframe;
	/// line width used in wireframe mode
	double line_width;
	/// surface color
	V3d color;
public:
	/// construct style node
	style_node(const V3d& _color = V3d(1,0,0), bool _wireframe = false, double _line_width = 1);
	/// return the type name of the node class
	std::string get_type_name() const { return "style_node"; }
	/// push opengl state attributes onto attribute stack
	void before_draw_children();
	/// restore previous attribute values with pop
	void after_draw_children();
	/// stream all information specific to a given node type
	void stream_node_data(std::ostream& os) const;
	/// handle key event
	bool handle_key_event(char key);
};

/** transformation node */
class geometry_node : public node
{
public:
	/// declare enumerate with different geometry types
	enum GeometryType { 
		FIRST_GEOMETRY, 
		CUBE = FIRST_GEOMETRY, 
		SPHERE, CONE, TORUS, TEAPOT, 
		LAST_GEOMETRY 
	};
protected:
	/// declare member to store geometry type
	GeometryType geometry_type;
	/// aspect ratio of geometries with two characteristic sizes
	double aspect;
	/// optional particles system
	particle_system* ps;
public:
	/// construct with standard geometry being a cube
	geometry_node(GeometryType _geometry_type = CUBE, double _aspect = 1);
	/// destruct also particles system
	~geometry_node();
	/// return the type name of the node class
	std::string get_type_name() const { return "geometry_node"; }
	/// draw the node
	void draw();
	/// serialize to disk
	void stream_out(std::ostream& os) const;
	/// handle key event
	bool handle_key_event(char key);
	/// animation callback calls the animate function of the particle system
	void animate(double dt, double time);
};