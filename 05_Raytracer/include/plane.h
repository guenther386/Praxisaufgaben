#ifndef PLANE_H
#define PLANE_H

#include "primitive.h"

class plane: public primitive
{
public:
	plane();
	
	plane(const tiny_vec<float,3>& nml, float d);

	bool closest_intersection(intersection_info* hit, float min_lambda,primitive* dont_hit);
	
	bool any_intersection(ray<float>& r,float min_lambda, float max_lambda, primitive* dont_hit);
	

private:
	tiny_vec<float,3> normal;

	float distance;

};

#endif