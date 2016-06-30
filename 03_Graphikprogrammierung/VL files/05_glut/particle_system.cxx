#include "particle_system.h"
#include <GL/glut.h>
#include <iostream>

/// construct from the maximum number of particles
particle_system::particle_system(unsigned _max_nr_particles)
	: max_nr_particles(_max_nr_particles), initial_velocity(5),
	  particle_frequency(100), max_age(1)
{
}

/// draw particles
void particle_system::draw()
{
	glPushAttrib(GL_POINT_BIT|GL_CURRENT_BIT|GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		glEnable(GL_POINT_SMOOTH);
		glPointSize(10);
		glBegin(GL_POINTS);
			for (unsigned i = 0; i < particles.size(); ++i) {
				particle& p = particles[i];
				glColor3dv(p.color);
				glVertex3dv(p.position);
			}
		glEnd();
	glPopAttrib();
}

/// create, animate and kill particles
void particle_system::animate(double dt, double time)
{
	// propagate particls
	unsigned i;
	for (i = 0; i < particles.size(); ++i) {
		// remove particles that are too old
		if (time - particles[i].birth_time > max_age) {
			particles.erase(particles.begin()+i);
			--i;
			continue;
		}
		// animate remaining particels
		particle& p = particles[i];
		// apply gravity in y-direction
		p.velocity(1) -= 9.81*dt;
		// apply friction
		p.velocity *= 0.97;
		// increment position
		p.position    += dt*p.velocity;
	}
	// check if more particles can be create
	if (particles.size() >= max_nr_particles)
		return;
	// compute number of to be created particels
	double nr_new_particles_d = dt*particle_frequency;
	unsigned nr_new_particles = (unsigned) nr_new_particles_d;
	nr_new_particles_d -= nr_new_particles;
	if ((double)rand()/RAND_MAX < nr_new_particles_d)
		++nr_new_particles;
	if (nr_new_particles + particles.size() > max_nr_particles)
		nr_new_particles = max_nr_particles - particles.size();

	// create new particles
	for (i = 0; i < nr_new_particles; ++i) {
		particle p;
		p.position = particle::V3d(0.0);
		p.velocity(0) = (double)rand()/RAND_MAX - 0.5 - 0.3*initial_velocity;
		p.velocity(1) = (double)rand()/RAND_MAX - 0.5 + 0.9*initial_velocity;
		p.velocity(2) = (double)rand()/RAND_MAX - 0.5;
		p.color(0) = (double)rand()/RAND_MAX;
		p.color(1) = (double)rand()/RAND_MAX;
		p.color(2) = (double)rand()/RAND_MAX;
		p.birth_time = i*dt/nr_new_particles;
		p.position += p.birth_time*p.velocity;
		p.birth_time += time;
		particles.push_back(p);
	}
}
