#ifndef CYLINDER_H
#define CYLINDER_H

#include "primitive.h"
class cylinder: public primitive
{
public:
	cylinder();
	
	cylinder(const tiny_vec<float,3>& p1, const tiny_vec<float,3>& p2,const float r);
	
	void calc_normal(intersection_info* hit);
	
	bool closest_intersection(intersection_info* hit, float min_lambda, primitive* dont_hit);

	bool any_intersection(ray<float>& r,float min_lambda, float max_lambda, primitive* dont_hit); 
			
	void set_finite(bool b);
	
	bool is_finite();
	
	void set_caps(bool b);
	
	bool has_caps();


private:
	tiny_vec<float,3> bottom;
	tiny_vec<float,3> top;
	
	bool finite;
	bool caps;
	
	float radius;

};

#endif