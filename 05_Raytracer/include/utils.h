#pragma once
#include <cstdlib>





template <typename T>
T clamp(T v,T lo, T hi)
{
	return (std::max)((std::min)(hi,v),lo);
}


//find the real roots of ax^2 +bx+c = 0
// the number of real roots is returned
template <typename T>
int solve_real_quadratic(const T& a, const T& b, const T& c, T x[2]) 
{

	if(a == 0)
	{
		if(b == 0)
			return 0;
		else
		{
			x[0] = -c/b;
			return 1;
		}
	}
	T d = b*b -  4*a*c;

	if(d >= 0)
	{
		T q = sqrt(d)/(2 *a);
		if(q == 0)
		{
			x[0] = (-b/(2 * a)) ;
			return 1;
		}
		else
		{
			x[0] = (-b/(2 * a)) + q;
			x[1] = (-b/(2 * a)) - q;
			return 2;
		}
	}
	return 0;
        
} 



// helper function -> scalar of 2 vectors with 3 numbers
template <typename T>
float dot_product(tiny_vec<T, 3> aloha, tiny_vec<T, 3> bahoms)
{

	return aloha.x()*bahoms.x() + aloha.y()*bahoms.y() + aloha.z()*bahoms.z();

}


inline tiny_vec<unsigned char,3> convert_color(const tiny_vec<float,3>& v)
{
	tiny_vec<unsigned char,3> col;
	col[0] = (unsigned char)clamp(v[0]*255.0f,0.0f,255.0f);
	col[1] = (unsigned char)clamp(v[1]*255.0f,0.0f,255.0f);
	col[2] = (unsigned char)clamp(v[2]*255.0f,0.0f,255.0f);
	return col;
}


inline float random(float a, float b)
{
	return ((b-a)*((float)rand()/RAND_MAX))+a;
}