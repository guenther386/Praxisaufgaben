#ifndef PHONG_H
#define PHONG_H

#include "material.h"

class phong : public material
{
public:
	
	virtual tiny_vec<float,3> shade_diffuse(intersection_info* hit, light_source *light);
	virtual tiny_vec<float,3> shade_specular(intersection_info* hit, light_source *light);
	
};

#endif