#include "blinn_phong.h"
#include "utils.h"



tiny_vec<float,3> blinn_phong::shade_specular(intersection_info* hit, light_source *light)
{
		
	tiny_vec<float,3> attenuation = light->get_attenuation_factors(hit); 
	tiny_vec<float,3> col(0.0f,0.0f,0.0f);

	//studen begin
	//see task 1.3.1


	if (dot(hit->get_normal(), hit->get_direction_to_light()) > 0)
	{
		tiny_vec<float, 3> V = hit->get_direction_to_camera();
		tiny_vec<float, 3> H = hit->get_direction_to_light() + V;
		H.normalize();
		float NHc = clamp(dot(hit->get_normal(), H), 0.0f, 1.0f);
		col = specular*std::pow(NHc, shininess)*attenuation*light->get_color();
	}


	//student end
	return col;	

}

