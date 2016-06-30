#ifndef BLINN_PHONG_H
#define BLINN_PHONG_H

#include "material.h"
#include "phong.h"

class blinn_phong : public phong
{
public:	

	virtual tiny_vec<float,3> shade_specular(intersection_info* hit, light_source *light);
	
};

#endif