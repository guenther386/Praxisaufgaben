#include "primitive_group.h"



primitive_group::~primitive_group()
{
	clear();
}

bool primitive_group::closest_intersection(intersection_info* hit, float min_lambda,primitive* dont_hit)
{
	if(dont_hit == this)
		return false;

	bool intersect=false;
	for(std::vector<primitive*>::iterator it = primitives.begin();
		it != primitives.end();
		++it) //find closest intersection 
	{
		
		if( (*it)->closest_intersection(hit,min_lambda,dont_hit))
			intersect = true;
	}
	return intersect;
}

bool primitive_group::any_intersection(ray<float>& r,float min_lambda, float max_lambda,primitive* dont_hit)
{
	if(dont_hit == this)
		return false;
	
			
	for(std::vector<primitive*>::iterator it = primitives.begin();
		it != primitives.end();
		++it) 
	{
	
		if( (*it)->any_intersection(r,min_lambda,max_lambda,dont_hit))
			return true;
	}
	return false;

}

void primitive_group::add_primitive(primitive* p)
{
	primitives.push_back(p);
}

void primitive_group::clear()
{
	for(std::vector<primitive*>::iterator it = primitives.begin();
		it != primitives.end();
		++it) 
	{
		delete *it;
	}

	primitives.clear();
}

	