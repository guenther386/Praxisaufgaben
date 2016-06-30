#ifndef CAMERA_H
#define CAMERA_H

#include "tiny_vec.h"



class camera
{
public:
	
	void set_look_at(const tiny_vec<float,3>& eye, const tiny_vec<float,3>& center,const tiny_vec<float,3>& up);

	void set_perspective(float fov, float aspect, float znear, float zfar);

	void set_frustrum(float left, float right,float top,float bottom,float znear,float zfar);

	void set_resolution(int resx, int resy);

	tiny_vec<float,3>& get_origin();

	//get ray direction through center of pixel(i,j)
	tiny_vec<float,3> get_direction(int i, int j);

	//get ray direction through random position within pixel(i,j)
	tiny_vec<float,3> get_multi_sample_random_direction(int i, int j);

	tiny_vec<float,3> get_multi_sample_grid_direction(int i, int j,int sample,int grid_res=3);

	//image width in pixel
	int width();
	
	//image height in pixel
	int height();
	
	float get_znear();
	
	float get_zfar();

	camera();

private:
	tiny_vec<float,3> eye; 
	tiny_vec<float,3> u_dir;//x direction of camera coordinate frame
	tiny_vec<float,3> v_dir;//y direction of camera coordinate frame
	tiny_vec<float,3> w_dir;//z direction of camera coordinate frame

	float left,right,top,bottom,znear,zfar;//view frustrum distances in camera coordinate frame
	int res_u,res_v;
};

#endif

