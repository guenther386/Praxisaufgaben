
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "scene.h"




class raytracer
{
	
	
public:
	enum sampling_type
	{
		NO_SUPER_SAMPLING,
		SUPER_SAMPLING_GRID_33,
		SUPER_SAMPLING_RANDOM_4,
		SUPER_SAMPLING_RANDOM_8,
		SUPER_SAMPLING_RANDOM_16
	};

	
	void setup(scene* s, int max_rec, sampling_type sampling=SUPER_SAMPLING_GRID_33);

	mat<tiny_vec<unsigned char,3> > render();	
	

protected:
	tiny_vec<float,3> trace( intersection_info* hit, int rec_level);
	

	

private:

	mat<tiny_vec<unsigned char,3> > raster_image;
	scene* render_scene;
	int max_recursion_level;
	int num_samples;
	sampling_type sampling;

};

#endif
