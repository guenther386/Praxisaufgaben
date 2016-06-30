#include "sphere.h"
#include "utils.h"


sphere::sphere():radius(1.0f),sqr_radius(1.0f)
{
	center.zeros();
}

sphere::sphere(float cx, float cy, float cz, float r):center(cx,cy,cz),radius(r)
{
	sqr_radius=r*r;
}

sphere::sphere(const tiny_vec<float,3>& c, float r):center(c),radius(r)
{
	sqr_radius=r*r;
}

void sphere::set_radius(float r)
{
	radius = r;
	sqr_radius = r*r;
}

void sphere::calc_normal(intersection_info* hit)const 
{
	tiny_vec<float,3> nml = hit->get_location()-center;
	nml.normalize();
	
	hit->set_normal(nml);
}

std::pair<tiny_vec<float,3>, tiny_vec<float,3> > sphere::calc_bounds()
{
	return std::make_pair(center-radius,center+radius);
}

bool sphere::closest_intersection(intersection_info* hit, float min_lambda, primitive* dont_hit)
{
	//student begin
	//see task 1.2.1


	if (this == dont_hit)
		return false;
	ray<float> r = hit->get_incoming_ray();

	tiny_vec<float, 3> ray_origin = r.get_origin();
	tiny_vec<float, 3> ray_direction = r.get_direction();
	tiny_vec<float, 3> ray_inv_direction = r.get_inv_direction();

	ray_origin -= center;

	float a, b, c;

	a = dot_product(ray_direction, ray_direction);
	b = 2 * dot_product(ray_direction, ray_origin);
	c = dot_product(ray_origin, ray_origin) - sqr_radius;

	float x[2];
	int roots = solve_real_quadratic<float>(a, b, c, x);
	float lambda = x[0] <= 0 ? x[0] : x[1];

	if (roots > 0 && lambda > min_lambda && lambda < hit->get_lambda())
	{
		hit->set_object(this);
		hit->set_lambda(lambda);
		calc_normal(hit);
		return true;
	}
	else {
		return false; // kein schnittpunkt
	}

	//student end

}

bool sphere::any_intersection(ray<float>& r,float min_lambda,float max_lambda, primitive* dont_hit)
{

	//student begin
	//see task 1.2.1


	if (this == dont_hit)
		return false;

	tiny_vec<float, 3> ray_origin = r.get_origin();
	tiny_vec<float, 3> ray_direction = r.get_direction();
	tiny_vec<float, 3> ray_inv_direction = r.get_inv_direction();

	ray_origin -= center;

	float a, b, c;

	a = dot_product(ray_direction, ray_direction);
	b = 2 * dot_product(ray_direction, ray_origin);
	c = dot_product(ray_origin, ray_origin) - sqr_radius;

	float x[2];
	int roots = solve_real_quadratic<float>(a, b, c, x);
	float lambda = x[0] <= 0 ? x[0] : x[1];


	if (roots > 0 && lambda > min_lambda && lambda < max_lambda)
	{
		return true;
	}
	else
	{
		return false; // kein schnittpunkt
	}

	//student end

}
