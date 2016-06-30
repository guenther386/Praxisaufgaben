#include "raytracer.h"
#include <omp.h>
#include <iomanip>
#include "timing.h"
#include <limits>
#include "utils.h"




void raytracer::setup(scene* s, int max_rec, sampling_type sampling)
{
	raster_image.resize(s->get_camera()->width(),s->get_camera()->height());
	render_scene = s;
	max_recursion_level = max_rec;	
	raytracer::sampling = sampling;
}

mat<tiny_vec<unsigned char,3> > raytracer::render()
{
	std::cout << "begin tracing";
	tic();
	int resx = raster_image.w();
	int resy = raster_image.h();

	camera * cam = render_scene->get_camera();
	tiny_vec<float,3> orig = cam->get_origin();
	
	int npixel = resx*resy;
	int ncomplete = 0;
	
	std::cout <<std::endl;
	#pragma omp parallel for schedule(dynamic, 5) 
	for(int y = 0; y < resy; ++y)
	{

		for(int x=0; x < resx; ++x)
		{
			
			tiny_vec<float,3> dir;
			intersection_info hit;
			tiny_vec<float,3> col(0,0,0);

			switch(sampling)
			{
			case NO_SUPER_SAMPLING:
				dir = cam->get_direction(x,y);
				hit = intersection_info(ray<float>(orig,dir),std::numeric_limits<float>::infinity()); 
				col = trace(&hit,0);
				break;
			
		
			case SUPER_SAMPLING_GRID_33:
				for(int i = 0; i < 9;i++)
				{
					dir = cam->get_multi_sample_grid_direction(x,y,i);
					intersection_info hit(ray<float>(orig,dir),std::numeric_limits<float>::infinity()); 
					col += trace(&hit,0);
				}
				col/=9.0f;
				break;

			case SUPER_SAMPLING_RANDOM_4:
				for(int i = 0; i < 4;i++)
				{
					dir = cam->get_multi_sample_random_direction(x,y);
					intersection_info hit(ray<float>(orig,dir),std::numeric_limits<float>::infinity()); 
					col += trace(&hit,0);
				}
				col/=4.0f;
				
			case SUPER_SAMPLING_RANDOM_8:
				for(int i = 0; i < 8;i++)
				{
					dir = cam->get_multi_sample_random_direction(x,y);
					intersection_info hit(ray<float>(orig,dir),std::numeric_limits<float>::infinity()); 
					col += trace(&hit,0);
				}
				col/=8.0f;
			case SUPER_SAMPLING_RANDOM_16:
				
				for(int i = 0; i < 16;i++)
				{
					dir = cam->get_multi_sample_random_direction(x,y);
					intersection_info hit(ray<float>(orig,dir),std::numeric_limits<float>::infinity()); 
					col += trace(&hit,0);
				}
				col/=16.0f;
				
				break;
			}
			raster_image(x,y) = convert_color(col);
		}

		#pragma omp critical
		{
			#pragma omp atomic
			ncomplete +=resx;
			
			std::cout << "\r"<< std::setw(6)<<std::setiosflags(std::ios::showpoint)<<std::fixed<<std::setprecision(2)  <<(100.0f*ncomplete)/npixel<< " % of image completed.";
		}
	}
	std::cout << "\n"<<std::endl;
	std::cout << "end tracing\n";
	toc();
	return raster_image;
}	


tiny_vec<float,3> raytracer::trace( intersection_info* hit, int rec_level)
{
	
	if(render_scene->get_root()->closest_intersection(hit,0.001f,hit->get_object())) //if intersection is found...
	{
		
		int nl = render_scene->num_lights();
		light_source *light;
	
		tiny_vec<float,3> color(0.0f,0.0f,0.0f);

		
		for(int i = 0; i < nl; ++i) // for each light...
		{
			
			light = render_scene->get_light(i);
			light->calc_light_direction_and_distance(hit);
			
			bool shadow=false;
			if(light->is_casting_shadows())
			{		
				ray<float> shadow_ray(hit->get_location(),hit->get_direction_to_light());
				shadow = render_scene->get_root()->any_intersection(shadow_ray,0.001f,hit->get_light_distance(),hit->get_object()); 
			}

			if(!shadow) // not in shadow ?
				 color += hit->get_object()->get_material()->shade(hit,light);
			

			if(rec_level < max_recursion_level)
			{
				float refl = hit->get_object()->get_material()->get_reflectivity();
				if(refl > 0)
				{
					intersection_info hit_reflect(ray<float>(hit->get_location(),hit->get_reflected_view_direction()),std::numeric_limits<float>::infinity());
					hit_reflect.set_object(hit->get_object());
					color += refl*trace(&hit_reflect,rec_level+1);
				}
			}


		}
		 return color;
	} 
	else
		return render_scene->get_clear_color();



}


