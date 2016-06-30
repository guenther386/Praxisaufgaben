#pragma once

#include <vector>
#include "fvec.h"

/// particle structure
struct particle
{
	typedef fvec<double,3> V3d;
	V3d position;
	V3d velocity;
	V3d color;
	double birth_time;
};

/// very simple particle system with gravity force
class particle_system
{
protected:
	unsigned max_nr_particles;
	double initial_velocity;
	double particle_frequency;
	double max_age;
	/// vector of particels
	std::vector<particle> particles;
public:
	/// construct from the maximum number of particles
	particle_system(unsigned _max_nr_particles = 1000);
	/// draw particles
	void draw();
	/// create, animate and kill particles
	void animate(double dt, double time);
};
