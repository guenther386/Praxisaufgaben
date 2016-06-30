#include "phong.h"
#include "utils.h"
	
tiny_vec<float,3> phong::shade_diffuse(intersection_info* hit, light_source *light)
{
	tiny_vec<float,3> col(0.0f,0.0f,0.0f);
	tiny_vec<float,3> attenuation = light->get_attenuation_factors(hit); 
		
	//student begin
	//see task 1.3.2


	float NLc = clamp(dot(hit->get_normal(), hit->get_direction_to_light()), 0.0f, 1.0f);
	col = NLc*diffuse*attenuation*light->get_color();


	//student end
	return col;	


}

tiny_vec<float,3> phong::shade_specular(intersection_info* hit, light_source *light)
{
	tiny_vec<float,3> col(0.0f,0.0f,0.0f);
	tiny_vec<float,3> attenuation = light->get_attenuation_factors(hit); 
	
	
	//student begin
	//see task 1.3.2


	if (dot(hit->get_normal(), hit->get_direction_to_light()) > 0)
	{
		tiny_vec<float, 3> R = hit->get_reflected_view_direction();
		float NRc = clamp(dot(hit->get_direction_to_light(), R), 0.0f, 1.0f);
		col = specular*std::pow(NRc, shininess)*attenuation*light->get_color();
	}


	//student end
	return col;	


}