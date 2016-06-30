#include "material.h"
#include "utils.h"



material::material():diffuse(0.8f,0.8f,0.8f),specular(0.4f,0.4f,0.4f),
	shininess(80),reflection(0.0f),refraction(0.0f)
{
}

void material::set_diffuse( tiny_vec<float,3>& col )
{ 
	diffuse = col;
}
void material::set_diffuse( float r, float g, float b) 
{
	diffuse[0]=r; 
	diffuse[1]=g;
	diffuse[2]=b;
}

tiny_vec<float,3>& material::get_diffuse()
{ 
	return diffuse; 
}

const tiny_vec<float,3>& material::get_diffuse() const
{ 
	return diffuse;
}

void material::set_specular( tiny_vec<float,3>& col )
{ 
	specular = col; 
}

void material::set_specular( float r, float g, float b)
{
	specular[0]=r; 
	specular[1]=g;
	specular[2]=
		b;
}
tiny_vec<float,3>& material::get_specular() 
{ 
	return specular;
}

const tiny_vec<float,3>& material::get_specular() const
{ 
	return specular; 
}

void material::set_shininess(float shine)
{
	shininess = shine;
}

float material::get_shininess() const
{
	return shininess;
}

void material::set_reflectivity(float refl) 
{ 
	reflection = refl; 
}

float material::get_reflectivity()const 
{ 
	return reflection; 
}

tiny_vec<float,3> material::shade(intersection_info* hit,light_source *light)
{
	tiny_vec<float, 3> ambient = 0.2f * diffuse * light->get_attenuation_factors(hit) * light->get_color();
	tiny_vec<float, 3> diffuse = shade_diffuse(hit, light);
	tiny_vec<float, 3> specular = shade_specular(hit, light);
	tiny_vec<float, 3> result = ambient + diffuse + specular;
	result.x() = std::min(1.0f, std::max(0.0f, result.x()));
	result.y() = std::min(1.0f, std::max(0.0f, result.y()));
	result.z() = std::min(1.0f, std::max(0.0f, result.z()));
	return result;
}

/*	void material::set_refractivity(float refrac)
{
	refraction = refrac; 
}

float material::get_refractivity()const 
{
	return refraction;
}
	
float material::get_index_of_refraction() const 
{
	return refrac_index;
}
*/

	






