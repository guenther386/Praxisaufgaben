#include "camera.h"
#include "utils.h"

	
void camera::set_look_at(const tiny_vec<float,3>& eye, const tiny_vec<float,3>& center,const tiny_vec<float,3>& up)
{
	camera::eye = eye;
	w_dir = eye-center;
	w_dir.normalize();

	v_dir = up;
	v_dir.normalize();
	
	u_dir = cross(v_dir,w_dir);
	u_dir.normalize();

	v_dir = cross(w_dir,u_dir);
	v_dir.normalize();
}

void camera::set_perspective(float fov, float aspect, float znear, float zfar)
{

	top = znear*tan(fov*3.14159f/360.0f);
	bottom = -top;
	right = aspect *top;
	left = -right;
	camera::zfar = zfar;
	camera::znear = znear;
}

void camera::set_frustrum(float left, float right,float top,float bottom,float znear,float zfar)
{
	camera::left = left;
	camera::right = right;
	camera::top = top;
	camera::bottom = bottom;
	camera::znear = znear;
	camera::zfar = zfar;
}

void camera::set_resolution(int resx, int resy)
{
	res_u = resx;
	res_v = resy;
}

tiny_vec<float,3>& camera::get_origin()
{
	return eye;
}

//get ray direction through center of pixel(i,j)
tiny_vec<float,3> camera::get_direction(int i, int j)
{
	float us =left + (right-left)*(i+0.5f)/res_u;
	float vs =bottom + (top-bottom)*(res_v-(j+0.5f))/res_v;
	float ws =-znear;		
	tiny_vec<float,3> dir =  us*u_dir + vs*v_dir + ws*w_dir;
	dir.normalize();
	
	return dir;
}

//get ray direction through random position within pixel(i,j)
tiny_vec<float,3> camera::get_multi_sample_random_direction(int i, int j)
{
	float us =left + (right-left)*(i+random(0.0f,1.0f))/res_u;
	float vs =bottom + (top-bottom)*(res_v-(j+random(0.0f,1.0f)))/res_v;
	float ws =-znear;		
	tiny_vec<float,3> dir =  us*u_dir + vs*v_dir + ws*w_dir;
	dir.normalize();
	
	return dir;
}

tiny_vec<float,3> camera::get_multi_sample_grid_direction(int i, int j,int sample,int grid_res)
{
	float gs = 1.0f/grid_res;
	float gsh = gs*0.5f;

	float di = gsh+(sample % grid_res)*gs;
	float dj = gsh + (sample / grid_res)*gs;

	float us =left + (right-left)*(i+di)/res_u;
	float vs =bottom + (top-bottom)*(res_v-(j+dj))/res_v;
	float ws =-znear;		
	tiny_vec<float,3> dir =  us*u_dir + vs*v_dir + ws*w_dir;
	dir.normalize();
	
	return dir;
}

//image width in pixel
int camera::width()
{
	return res_u;
}

//image height in pixel
int camera::height()
{
	return res_v;
}

float camera::get_znear()
{
	return znear;
}

float camera::get_zfar()
{
	return zfar;
}

camera::camera():eye(0,0,0),u_dir(1,0,0),v_dir(0,1,0),w_dir(0,0,1),res_u(640),res_v(480)
{
	set_perspective(45.0f, res_u/(float)res_v, 0.01f, 100.0f);
}
