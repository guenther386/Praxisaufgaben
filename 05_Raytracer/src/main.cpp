#ifdef WIN32
#pragma	warning (disable: 4996)
#endif

#include "raytracer.h"
#include "point_light.h"
#include "directional_light.h"
#include "spot_light.h"
#include "box.h"
#include "plane.h"
#include "sphere.h"
#include "cylinder.h"
#include "primitive_group.h"
#include "transformation_group.h" 
#include "kd_tree.h"
#include "triangle.h"
#include "blinn_phong.h"
#include "phong.h"
#include "image_io.h"

#include <iostream>		// IO for asking for number 1,2 or 3 
using namespace std;

static const bool g_USE_MESH_FILE = false ;


//student begin
//see task 1.4


scene* create_scene1()			// new scene1 by myself
{
	scene* my_own_scene1 = new scene();

	int resx = 1024;
	int resy = 768;

	camera *view = new camera();
	view->set_resolution(resx, resy);
	view->set_perspective(45, resx / (float)resy, 0.01f, 1000);
	view->set_look_at(tiny_vec<float, 3>(6, 6, 20), tiny_vec<float, 3>(6, 2, 6), tiny_vec<float, 3>(0, 1, 0));
	my_own_scene1->set_camera(view);

	my_own_scene1->set_clear_color(tiny_vec<float, 3>(0.1f, 0.1f, 0.2f));


	//root node of scene
	primitive_group *group = new primitive_group();
	my_own_scene1->set_root(group);
	


	// 2 new testing balls
	blinn_phong *random1mat = new blinn_phong();	// hellblauer ball
	random1mat->set_diffuse(0.3f, 0.9f, 0.9f);
	random1mat->set_specular(1.0f, 1.0f, 1.0f);

	blinn_phong *random2mat = new blinn_phong();	// gelber ball
	random2mat->set_diffuse(0.8f, 0.8f, 0.0f);
	random2mat->set_specular(0.0f, 0.8f, 1.0f);

	// tried to build a new own triangle
	triangle *tri_own = new triangle
	(tiny_vec<float, 3>(14.0f, 3.0f, -1.0f), tiny_vec<float, 3>(18.0f, 7.0f, -3.0f), tiny_vec<float, 3>(9.0f, 4.0f, -3.0f));
	tri_own->set_material(new phong());
	tri_own->get_material()->set_diffuse(0.7f, 0.1f, 0.9f);
	tri_own->get_material()->set_reflectivity(0.8f);
	group->add_primitive(tri_own);

	// 2 new axis aligned boxes	
	primitive* boxsmall_own1 = new box(tiny_vec<float, 3>(10.0f, -4.0, -4.0), tiny_vec<float, 3>(13.0f, 3.0f, 0.0f));
	boxsmall_own1->set_name("box small1");
	boxsmall_own1->set_material(new blinn_phong());
	boxsmall_own1->get_material()->set_diffuse(1.0f, 0.6f, 0.6f);
	boxsmall_own1->get_material()->set_reflectivity(0.2f);
	group->add_primitive(boxsmall_own1);

	primitive* boxsmall_own2 = new box(tiny_vec<float, 3>(7.0f, -1.0, -6.0), tiny_vec<float, 3>(9.0f, 2.0f, 3.0f));
	boxsmall_own2->set_name("box small2");
	boxsmall_own2->set_material(new blinn_phong());
	boxsmall_own2->get_material()->set_diffuse(0.21f, 0.75f, 1.0f);
	boxsmall_own2->get_material()->set_reflectivity(0.8f);
	group->add_primitive(boxsmall_own2);

	// new bigger ball
	primitive* bigone = new sphere(2.0, 1.0, 0.0, 2.0f);		// position
	bigone->set_name("big balls!");
	bigone->set_material(new blinn_phong());
	bigone->get_material()->set_diffuse(0.9f, 0.3f, 0.3f);		// farbe
	bigone->get_material()->set_reflectivity(0.5f);
	group->add_primitive(bigone);




	// ground plane
	primitive* pl = new plane(tiny_vec<float, 3>(0, 1, 0), -2.0f);
	pl->set_name("plane");
	pl->set_material(new blinn_phong());
	pl->get_material()->set_reflectivity(0.3f);
	pl->get_material()->set_diffuse(0.8f, 0.8f, 0.8f);
	pl->get_material()->set_specular(0.8f, 0.8f, 0.8f);
	group->add_primitive(pl);

	
	// 2 little balls
	primitive*s1 = new sphere(4.0, 0.2, 7.0, 0.8f);				// hellblauer kreis vorne freistehend
	//		(rote achse(links/rechts), grüne achse(höhe), blaue achse(ferne), größe)
	s1->set_name("light blue");
	s1->set_material(random1mat);
	group->add_primitive(s1);

	primitive*s2 = new sphere(11.0, 0.4, -40.0, 1.2f);			// gelber kreis weit weg freistehend
	//		(rote achse(links/rechts), grüne achse(höhe), blaue achse(ferne), größe)
	s2->set_name("yellow");
	s2->set_material(random2mat);
	group->add_primitive(s2);


	//a triangle mesh in a kdtree
	if (g_USE_MESH_FILE)
	{
		kd_tree *mesh = new kd_tree();
		if (!mesh->add_obj_mesh("../../data/buddha.obj") && !mesh->add_obj_mesh("data/buddha.obj")) {
			std::cout << "Could not load obj-File!" << std::endl;
		}
		else {
			group->add_primitive(mesh);
			mesh->build_tree_spatial_median();
		}
	}


	// default triangle
	triangle *tri = new triangle(tiny_vec<float, 3>(3.0f, 0.0f, -10.0f),
		tiny_vec<float, 3>(7.0f, 0.0f, -10.0f),
		tiny_vec<float, 3>(0.0f, 7.0f, -10.0f));
	tri->set_material(new phong());
	tri->get_material()->set_diffuse(0.4f, 0.8f, 0.4f);
	group->add_primitive(tri);


	//several different light sources

	//Point Light
	point_light* light0 = new point_light(-10, 10, 10);
	light0->set_color(0.5f, 1.0f, 1.0f);
	my_own_scene1->add_light(light0);

	//Spot light
	spot_light* spot = new spot_light();
	spot->set_color(0.5f, 0.5f, 0.0f);
	spot->set_position(7.5f, 10.0f, 11.0f);
	spot->set_spot_direction(0.25f, -1, -1);
	spot->set_spot_cutoff(10);
	spot->set_spot_exponent(250);
	my_own_scene1->add_light(spot);

	// Directional light
	directional_light *light1 = new directional_light(-1.0f, -1.0f, -0.3f);
	light1->set_color(0.5f, 0.3f, 0.3f);
	my_own_scene1->add_light(light1);


	return my_own_scene1;
}


scene* create_scene2()			// new scene2 by myself
{
	scene* my_own_scene2 = new scene();

	int resx = 1024;
	int resy = 768;

	camera *view = new camera();
	view->set_resolution(resx, resy);
	view->set_perspective(45, resx / (float)resy, 0.01f, 1000);
	view->set_look_at(tiny_vec<float, 3>(6, 6, 20), tiny_vec<float, 3>(6, 2, 6), tiny_vec<float, 3>(0, 1, 0));
	my_own_scene2->set_camera(view);

	my_own_scene2->set_clear_color(tiny_vec<float, 3>(0.1f, 0.1f, 0.2f));


	//root node of scene
	primitive_group *group = new primitive_group();
	my_own_scene2->set_root(group);



	// 2 little balls
	blinn_phong *random1mat = new blinn_phong();	// hellblauer ball
	random1mat->set_diffuse(0.3f, 0.9f, 0.9f);
	random1mat->set_specular(1.0f, 1.0f, 1.0f);

	blinn_phong *random2mat = new blinn_phong();	// gelber ball
	random2mat->set_diffuse(0.8f, 0.8f, 0.0f);
	random2mat->set_specular(0.0f, 0.8f, 1.0f);

	// 2 little balls
	primitive*s1 = new sphere(7.0, 5.0, 3.5, 0.4f);				// hellblauer kreis 
	//		(rote achse(links/rechts), grüne achse(höhe), blaue achse(ferne), größe)
	s1->set_name("light blue");
	s1->set_material(random1mat);
	group->add_primitive(s1);

	primitive*s2 = new sphere(11.0, -1.0, -10.0, 2.5f);			// gelber kreis klein
	//		(rote achse(links/rechts), grüne achse(höhe), blaue achse(ferne), größe)
	s2->set_name("yellow");
	s2->set_material(random2mat);
	group->add_primitive(s2);


	// built a new own triangle
	triangle *tri_own = new triangle
		(tiny_vec<float, 3>(14.0f, 9.0f, -1.0f), tiny_vec<float, 3>(18.0f, 3.0f, -3.0f), tiny_vec<float, 3>(9.0f, 7.0f, -3.0f));
	tri_own->set_material(new phong());
	tri_own->get_material()->set_diffuse(0.94f, 0.16f, 0.1f);
	tri_own->get_material()->set_reflectivity(1.0f);
	group->add_primitive(tri_own);

	// 2 new axis aligned boxes	
	primitive* boxsmall_own1 = new box(tiny_vec<float, 3>(10.0f, -1.0, 1.0), tiny_vec<float, 3>(16.0f, 1.5f, 5.0f));
	boxsmall_own1->set_name("box small1");
	boxsmall_own1->set_material(new blinn_phong());
	boxsmall_own1->get_material()->set_diffuse(1.0f, 0.6f, 0.6f);
	boxsmall_own1->get_material()->set_reflectivity(0.2f);
	group->add_primitive(boxsmall_own1);

	primitive* boxsmall_own2 = new box(tiny_vec<float, 3>(1.0f, -1.0, -3.0), tiny_vec<float, 3>(4.0f, 4.0f, 2.0f));
	boxsmall_own2->set_name("box blue");
	boxsmall_own2->set_material(new blinn_phong());
	boxsmall_own2->get_material()->set_diffuse(0.21f, 0.75f, 1.0f);
	boxsmall_own2->get_material()->set_reflectivity(0.8f);
	group->add_primitive(boxsmall_own2);

	// new bigger ball
	primitive* bigone = new sphere(6.0, 7.5, -4.0, 3.0f);		// position
	bigone->set_name("big balls!");
	bigone->set_material(new blinn_phong());
	bigone->get_material()->set_diffuse(1.0f, 0.8f, 0.35f);		// farbe
	bigone->get_material()->set_reflectivity(1.0f);
	group->add_primitive(bigone);





	// ground plane
	primitive* pl = new plane(tiny_vec<float, 3>(0, 1, 0), -2.0f);
	pl->set_name("plane");
	pl->set_material(new blinn_phong());
	pl->get_material()->set_reflectivity(0.3f);
	pl->get_material()->set_diffuse(0.8f, 0.8f, 0.8f);
	pl->get_material()->set_specular(0.8f, 0.8f, 0.8f);
	group->add_primitive(pl);

	
	//a triangle mesh in a kdtree
	if (g_USE_MESH_FILE)
	{
		kd_tree *mesh = new kd_tree();
		if (!mesh->add_obj_mesh("../../data/buddha.obj") && !mesh->add_obj_mesh("data/buddha.obj")) {
			std::cout << "Could not load obj-File!" << std::endl;
		}
		else {
			group->add_primitive(mesh);
			mesh->build_tree_spatial_median();
		}
	}


	// default triangle
	triangle *tri = new triangle(tiny_vec<float, 3>(6.0f, 0.0f, -7.0f),
		tiny_vec<float, 3>(3.0f, 0.0f, -10.0f),
		tiny_vec<float, 3>(0.0f, 8.0f, -6.0f));
	tri->set_material(new phong());
	tri->get_material()->set_diffuse(0.2f, 0.8f, 0.4f);
	group->add_primitive(tri);


	//several different light sources

	//Point Light
	point_light* light0 = new point_light(-10, 10, 10);
	light0->set_color(0.5f, 1.0f, 1.0f);
	my_own_scene2->add_light(light0);

	//Spot light
	spot_light* spot = new spot_light();
	spot->set_color(0.5f, 0.5f, 0.0f);
	spot->set_position(7.5f, 10.0f, 11.0f);
	spot->set_spot_direction(0.25f, -1, -1);
	spot->set_spot_cutoff(10);
	spot->set_spot_exponent(250);
	my_own_scene2->add_light(spot);

	// Directional light
	directional_light *light1 = new directional_light(-1.0f, -1.0f, -0.3f);
	light1->set_color(0.5f, 0.3f, 0.3f);
	my_own_scene2->add_light(light1);


	return my_own_scene2;
}

//student end



// just changing little things here
scene* create_scene3()
{
		scene* myscene = new scene();

		int resx = 1024;
		int resy = 768;

		camera *view = new camera();
		view->set_resolution(resx,resy);
		view->set_perspective(45,resx/(float)resy,0.01f,1000);
		view->set_look_at(tiny_vec<float,3>(6,6,20),tiny_vec<float,3>(6,2,6),tiny_vec<float,3>(0,1,0));
		myscene->set_camera(view);

		myscene->set_clear_color(tiny_vec<float,3>(0.1f,0.1f,0.2f));
		
		
		//root node of scene
		primitive_group *group = new primitive_group();
		myscene->set_root(group);


		//several materials
		blinn_phong *redmat = new blinn_phong();
		redmat->set_diffuse(1.0f,0.0f,0.0f);
		redmat->set_specular(1.0f,1.0f,1.0f);

		blinn_phong *greenmat = new blinn_phong();
		greenmat->set_diffuse(0.0f,1.0f,0.0f);
		greenmat->set_specular(1.0f,1.0f,1.0f);
		
		blinn_phong *bluemat = new blinn_phong();
		bluemat->set_diffuse(0.0f,0.0f,1.0f);
		bluemat->set_specular(1.0f,1.0f,1.0f);


		blinn_phong *graymat = new blinn_phong();
		graymat->set_diffuse(0.8f,0.8f,0.8f);
		graymat->set_specular(1.0f,1.0f,1.0f);
		
		// ground plane
		primitive* pl = new plane(  tiny_vec<float,3>(0, 1, 0) , -2.0f );
		pl->set_name( "plane" );
		pl->set_material(new blinn_phong());
		pl->get_material()->set_reflectivity( 0.3f );
		pl->get_material()->set_diffuse( 0.8f,0.8f,0.8f );
		pl->get_material()->set_specular( 0.8f,0.8f,0.8f );
		group->add_primitive(pl);

		//coordinate system axis
		cylinder* cylx = new cylinder(tiny_vec<float,3>(0,0,0),tiny_vec<float,3>(5.0f,0,0),0.2f );
		cylx->set_material(redmat);
		cylx->set_name( "cylinder X" );
		cylx->set_finite(true);
		cylx->set_caps(true);
		group->add_primitive(cylx);

		cylinder* cyly = new cylinder(tiny_vec<float,3>(0,0,0),tiny_vec<float,3>(0,5.0f,0),0.2f );
		cyly->set_name( "cylinder Y" );
		cyly->set_material(greenmat);
		cyly->set_finite(true);
		cyly->set_caps(true);
		group->add_primitive(cyly);

		cylinder* cylz = new cylinder(tiny_vec<float,3>(0,0,0),tiny_vec<float,3>(0,0,5.0f),0.2f );
		cylz->set_material(bluemat);
		cylz->set_name( "cylinder Z" );
		cylz->set_finite(true);
		cylz->set_caps(true);
		group->add_primitive(cylz);
			
	
		primitive *s1 = new sphere(  5.0, 0.0, 0.0 , 0.5f );
		s1->set_name( "x sphere" );
		s1->set_material(redmat);
		group->add_primitive(s1);

		primitive *s2 = new sphere(  0.0, 5.0, 0.0 , 0.5f );
		s2->set_name( "y sphere" );
		s2->set_material(greenmat );
		group->add_primitive(s2);
	
		primitive*s3 = new sphere(  0.0, 0.0, 5.0 , 0.5f );
		s3->set_name( "z sphere" );
		s3->set_material(bluemat);
		group->add_primitive(s3);

		primitive* s4 = new sphere(  0.0f, 0.0f, 0 , 0.5f );
		s4->set_name( "center" );
		s4->set_material(graymat);
		group->add_primitive(s4);
		
		//another big mirroring sphere
		primitive* sp = new sphere(  0.0, 1.0, -5.0 , 3.0f );
		sp->set_name( "big sphere" );
		sp->set_material(new blinn_phong());
		sp->get_material()->set_diffuse(  1.0f, 0.0f, 1.0f  );
		sp->get_material()->set_reflectivity(0.05f);
		group->add_primitive(sp);

		//an axis aligned box	
		primitive* boxsmall = new box(  tiny_vec<float,3>(11.0f, -2.0, -4.0) ,tiny_vec<float,3>(14.0f,2.0f,0.0f ) );
		boxsmall->set_name( "box small" );
		boxsmall->set_material(new blinn_phong());
		boxsmall->get_material()->set_diffuse(  0.5f, 0.5f, 0.5f  );
		boxsmall->get_material()->set_reflectivity(0.1f);
		group->add_primitive(boxsmall);
	
		
		//a triangle mesh in a kdtree
		if (g_USE_MESH_FILE)
		{
			kd_tree *mesh = new kd_tree();
			if (!mesh->add_obj_mesh("../../data/buddha.obj") && !mesh->add_obj_mesh("data/buddha.obj")) {
				std::cout<<"Could not load obj-File!"<<std::endl;
			} else {
				group->add_primitive(mesh);
				mesh->build_tree_spatial_median();
			}
		}
		
	
		triangle *tri = new triangle(tiny_vec<float,3>(3.0f,0.0f,-10.0f),
			tiny_vec<float,3>(7.0f,0.0f,-10.0f),
			tiny_vec<float,3>(0.0f,7.0f,-10.0f));
		tri->set_material(new phong());
		tri->get_material()->set_diffuse(0.4f,0.8f,0.4f);
		group->add_primitive(tri);

		//a transformed axis aligned box
		transformation_group* t1 = new transformation_group();
		t1->set_transformation( translate_44<float>(12.0f,0.0f,-20.0f)*rotatex_44<float>(45.0f)*rotatez_44<float>(45.0f));
		group->add_primitive(t1);
		
	
		primitive* box2 = new box(  tiny_vec<float,3>(-1.0, -1.0, -1.0) ,tiny_vec<float,3>(1.0,1.0f,1.0f ) );
		box2->set_material(new blinn_phong());
		box2->get_material()->set_diffuse(  1.0f, 1.0f, 1.0f  );
		box2->get_material()->set_reflectivity(0.1f);
		t1->add_primitive(box2);
		
	
		//several different light sources

		//Point Light
		point_light* light0 = new point_light(  -10, 10, 10  );
		light0->set_color(  0.5f, 1.0f, 1.0f  );		
		myscene->add_light(light0);

		//Spot light
		spot_light* spot = new spot_light(  );
		spot->set_color(0.5f,0.5f,0.0f);
		spot->set_position(7.5f, 10.0f, 11.0f);
		spot->set_spot_direction(0.25f,-1,-1);
		spot->set_spot_cutoff(10);
		spot->set_spot_exponent(250);
		myscene->add_light(spot);
		
		// Directional light
		directional_light *light1 = new directional_light(  -1.0f, -1.0f , -0.3f  );
		light1->set_color(0.5f, 0.3f, 0.3f);
		myscene->add_light(light1);

		
		return myscene;
}


int main(int argc, char** argv) 
{
	
	raytracer tracer;
	
	/*
	int i;

	// if query asking for input 1, 2 or 3 and then raytraces one of those scenes
	std::cout << "Enter 1 for my_scene1, 2 for my_scene2 and 3 for the default scene: ";
	std::cin >> i;
	std::cout << "You entered the number: " << i << ".\n \n";

	if (i = 1)
		tracer.setup(my_own_scene1, 2, raytracer::NO_SUPER_SAMPLING);
		if (i = 2)
			tracer.setup(my_own_scene2, 2, raytracer::NO_SUPER_SAMPLING);
			if (i = 3)
				tracer.setup(my_scene, 2, raytracer::NO_SUPER_SAMPLING);
	*/

	scene* my_own_scene1 = create_scene1();		// here my first own scene
	scene* my_own_scene2 = create_scene2();		// here my second own scene
	scene* my_scene = create_scene3();			// here the normal scene by default

	tracer.setup(my_scene, 2, raytracer::NO_SUPER_SAMPLING);

	//	tracer.setup(my_scene,2,raytracer::SUPER_SAMPLING_GRID_33);

	mat<tiny_vec<unsigned char, 3> > image = tracer.render();

	std::cout << "writing image...";
	write_bmp(image, "image.bmp");
	std::cout << "ready\n";

}
