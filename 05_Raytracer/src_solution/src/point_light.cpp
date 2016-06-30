#include "point_light.h"


point_light::point_light() : position(0,10,0)
{
}

point_light::point_light(float px, float py, float pz) : position(px,py,pz)
{
}
	
void point_light::set_position(float px, float py, float pz)
{
	position[0] = px;
	position[1] = py;
	position[2] = pz;
	
}
void point_light::set_position(const tiny_vec<float,3>& pos)
{
	position=pos;
}

tiny_vec<float,3> point_light::get_attenuation_factors(const intersection_info* hit)
{
	float d = hit->get_light_distance();                  
	float att = 1.0f/(const_attenuation + linear_attenuation*d +quadratic_attenuation*d*d);
	return tiny_vec<float,3>(att,att,att);
}

void point_light::calc_light_direction_and_distance(intersection_info *hit)
{
	tiny_vec<float,3> light_dir = position-hit->get_location();
	hit->set_light_distance(light_dir.length());
	hit->set_direction_to_light( light_dir/hit->get_light_distance());
}

