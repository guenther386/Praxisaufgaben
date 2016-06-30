//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
Template class for vectors.
This template class defines small vectors of a defined dimension with
an arbitrary data type. Basic operations such as addition of vectors and
multiplication of a vector and a scalar are supported via operator 
overloading. Also more advanced functions such as normalization and 
iterating through the elements are implemented.
At the end of this file the data types "point2d", "point3d" and 
"point4d" are specified as a tinyvec of doubles with the according dimension.
*************************************************************************/

#pragma once




#include <iostream>
#include <algorithm>
#include <cassert>
#include <math.h>

#ifdef _MSC_VER 
#pragma warning( push )
#pragma warning( disable : 4996 )
#endif
template <typename T,int N>
class tiny_vec
{

	T  _data[N];

public:
	typedef T              value_type;
	typedef T&             reference;
	typedef const T&       const_reference;
	typedef std::size_t    size_type;
	typedef std::ptrdiff_t difference_type;
	typedef T*             pointer;
	typedef const T*       const_pointer;
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	tiny_vec();

	template <typename InputIterator>
	tiny_vec(InputIterator first,InputIterator last)
	{
		std::copy(first,last,begin());
	}


	tiny_vec(size_t n, const T* marray);

	~tiny_vec();

	tiny_vec(const T&x,const T&y);

	tiny_vec(const T&x,const T&y, const T&z);

	tiny_vec(const T&x, const T&y, const T&z,const T& w);	

	int size() const;

	operator T*();

	operator const T*() const;

	void set(const T& x);

	void set(const T& x, const T& y);

	void set(const T& x, const T& y,const T& z);

	void set(const T& x, const T& y,const T& z, const T& w);

	tiny_vec& operator=(const T &s);

	tiny_vec& operator=(int s);

	tiny_vec& operator=(const tiny_vec & v);

	void fill(const T& s);
	
	void zeros();

	void ones();

	iterator begin();

	iterator end();

	const_iterator begin() const;

	const_iterator end() const;

	reverse_iterator rbegin();

	reverse_iterator rend();

	const_reverse_iterator rbegin() const;

	const_reverse_iterator rend() const;	

	bool operator==(const tiny_vec& v) const;

	bool operator!=(const tiny_vec& v) const;

	tiny_vec operator-() const;
	


	tiny_vec& operator+=(int s);

	tiny_vec& operator+=(float s);

	tiny_vec& operator+=(double s);


	
	tiny_vec operator+(int s) const;

	tiny_vec operator+(float s) const;

	tiny_vec operator+(double s) const;
	
	
	
	tiny_vec& operator-=(int s);

	tiny_vec& operator-=(float s);
		
	tiny_vec& operator-=(double s);
	

	
	tiny_vec operator-(int s) const;

	tiny_vec operator-(float s) const;

	tiny_vec operator-(double s) const;
	
	
	
	tiny_vec& operator*=(int s);

	tiny_vec& operator*=(float s);

	tiny_vec& operator*=(double s);
	

		
	tiny_vec operator*(int s) const;

	tiny_vec operator*(float s) const;

	tiny_vec operator*(double s) const;
	


	tiny_vec& operator/=(int s);

	tiny_vec& operator/=(float s);

	tiny_vec& operator/=(double s);


	
	tiny_vec operator/(int s) const;

	tiny_vec operator/(float s) const;
	
	tiny_vec operator/(double s) const;

	tiny_vec& operator+=(const tiny_vec& v);

	tiny_vec operator+(const tiny_vec& v) const;

	tiny_vec& operator-=(const tiny_vec& v);

	tiny_vec operator-(const tiny_vec& v) const;

	tiny_vec& operator*=(const tiny_vec& v);

	tiny_vec operator*(const tiny_vec& v) const;

	tiny_vec& operator/=(const tiny_vec& v);

	tiny_vec operator/(const tiny_vec& v) const;

	T& operator()(size_t i);

	T operator()(size_t i) const;

	T& x() {return _data[0];};
	T& y() {return _data[1];};
	T& z() {return _data[2];};

	T x() const {return _data[0];};
	T y() const {return _data[1];};
	T z() const {return _data[2];};


	void sort();

	void random_shuffle();

	T& min_elem();

	T min_elem() const;

	size_t min_index() const;

	T& max_elem();

	T max_elem() const;

	size_t max_index() const;

	T& median_elem();

	size_t median_index() const;

	T sqr_length() const;

	T length() const;

	void normalize();

};



template <typename T, int N>
tiny_vec<T,N>::tiny_vec(){}


template <typename T, int N>
tiny_vec<T,N>::tiny_vec(size_t n,const T* marray)
{			
	std::copy(marray,marray+N,begin());		
}

template <typename T, int N>
tiny_vec<T,N>::~tiny_vec(){}

template <typename T, int N>
tiny_vec<T,N>::tiny_vec(const T&x,const T&y)
{
	_data[0]=x;
	_data[1]=y;
}

template <typename T, int N>
tiny_vec<T,N>::tiny_vec(const T&x,const T&y, const T&z)
{
	_data[0]=x;
	_data[1]=y;
	_data[2]=z;
}

template <typename T, int N>
tiny_vec<T,N>::tiny_vec(const T&x, const T&y, const T&z,const T& w)
{
	_data[0]=x;
	_data[1]=y;
	_data[2]=z;
	_data[3]=w;
}

template <typename T, int N>
void tiny_vec<T,N>::set(const T& x)
{
	_data[0]=x;
}

template <typename T, int N>
void tiny_vec<T,N>::set(const T& x, const T& y)
{
	_data[0]=x;
	_data[1]=y;

}
template <typename T, int N>
void tiny_vec<T,N>::set(const T& x, const T& y,const T& z)
{
	_data[0]=x;
	_data[1]=y;
	_data[2]=z;

}
template <typename T, int N>
void tiny_vec<T,N>::set(const T& x, const T& y,const T& z, const T& w)
{
	_data[0]=x;
	_data[1]=y;
	_data[2]=z;
	_data[3]=w;
}

template <typename T, int N>
int tiny_vec<T,N>::size() const
{
	return N;
}

template <typename T, int N>
tiny_vec<T,N>::operator T*()
{
	return _data;
}


template <typename T, int N>
tiny_vec<T,N>::operator const T*() const
{
	return _data;
}

template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator=(const T &s)
{
	for(int i=0;i < N;i++)
		_data[i]=s;

	return *this;
}

template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator=(int s)
{
	for(int i=0;i<N;i++)
		_data[i]=(T)s;

	return *this;
}


template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator=(const tiny_vec & v)
{
	if(&v== this) return *this;

	std::copy(v.begin(),v.end(),begin());
	return *this;
}



template <typename T, int N>
void tiny_vec<T,N>::fill(const T& s)
{
	std::fill(begin(),end(),s);
}



template <typename T, int N>
void tiny_vec<T,N>::zeros()
{	
	T zero;
	zero=0;
	std::fill(begin(), end(), zero);
}

template <typename T, int N>
void tiny_vec<T,N>::ones()
{
	T one;
	one = 1;
	std::fill(begin(), end(), one);
}



template <typename T, int N>
typename tiny_vec<T,N>::iterator tiny_vec<T,N>::begin()
{
	return _data;
}

template <typename T, int N>
typename tiny_vec<T,N>::const_iterator tiny_vec<T,N>::begin() const
{
	return _data;
}

template <typename T, int N>
typename tiny_vec<T,N>::iterator tiny_vec<T,N>::end()
{
	return _data + N;
}

template <typename T, int N>
typename tiny_vec<T,N>::const_iterator tiny_vec<T,N>::end() const
{
	return _data +N;
}

template <typename T, int N>
typename tiny_vec<T,N>::reverse_iterator tiny_vec<T,N>::rbegin()
{
	return reverse_iterator(end());
}

template <typename T, int N>
typename tiny_vec<T,N>::reverse_iterator tiny_vec<T,N>::rend()
{
	return reverse_iterator(begin());
}

template <typename T, int N>
typename tiny_vec<T,N>::const_reverse_iterator tiny_vec<T,N>::rbegin() const
{
	return const_reverse_iterator(end());
}

template <typename T, int N>
typename tiny_vec<T,N>::const_reverse_iterator tiny_vec<T,N>:: rend() const
{
	return const_reverse_iterator(begin());
}

template <typename T, int N>
bool tiny_vec<T,N>::operator==(const tiny_vec<T,N>& v) const
{
	return std::equal(begin(),end(),v.begin());
}


template <typename T, int N>
bool tiny_vec<T,N>::operator!=(const tiny_vec<T,N>& v) const
{
	return !(*this == v);
}

template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator-() const
{
	return  (T)-1* *this;
}



template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator+=(int s)
{

	for(int i=0;i<size();i++)
		_data[i]+=s;
	return *this;
}

template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator+=(float s)
{

	for(int i=0;i<size();i++)
		_data[i]+=(T)s;
	return *this;
}

template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator+=(double s)
{

	for(int i=0;i<size();i++)
		_data[i]+=(T)s;
	return *this;
}



template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator+(int s) const
{
	tiny_vec r = *this;
	r += s;
	return r;
}


template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator+(float s) const
{
	tiny_vec r = *this;
	r += (T)s;
	return r;
}

template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator+(double s) const
{
	tiny_vec r = *this;
	r += (T)s;
	return r;
}



template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator-=(int s)
{

	for(int i=0;i<N;i++)
		_data[i]-=(T)s;

	return *this;
}

template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator-=(float s)
{

	for(int i=0;i<N;i++)
		_data[i]-=(T)s;

	return *this;
}
template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator-=(double s)
{

	for(int i=0;i<N;i++)
		_data[i]-=(T)s;

	return *this;
}



template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator-(int s) const
{
	tiny_vec r = *this;
	r -= (T)s;
	return r;
}



template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator-(float s) const
{
	tiny_vec r = *this;
	r -= (T)s;
	return r;
}



template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator-(double s) const
{
	tiny_vec r = *this;
	r -= (T)s;
	return r;
}



template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator*=(int s)
{
	for(int i=0; i <N; i++)
		_data[i]*=(T)s;

	return *this;
}

template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator*=(float s)
{
	for(int i=0; i <N; i++)
		_data[i]*=(T)s;

	return *this;
}

template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator*=(double s)
{
	for(int i=0; i <N; i++)
		_data[i]*=(T)s;

	return *this;
}



template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator*(int s) const
{
	tiny_vec<T,N> r = *this;
	r *= (T)s;
	return r;
}

template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator*(float s) const
{
	tiny_vec<T,N> r = *this;
	r *= (T)s;
	return r;
}

template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator*(double s) const
{
	tiny_vec<T,N> r = *this;
	r *= (T)s;
	return r;
}



template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator/=(int s)
{

	for(int i=0;i <N; i++)
		_data[i]/=(T)s;
	return *this;
}

template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator/=(float s)
{

	for(int i=0;i <N; i++)
		_data[i]/=(T)s;
	return *this;
}

template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator/=(double s)
{

	for(int i=0;i <N; i++)
		_data[i]/=(T)s;
	return *this;
}



template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator/(int s) const
{
	tiny_vec<T,N> r = *this;
	r /= (T)s;
	return r;
}

template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator/(float s) const
{
	tiny_vec<T,N> r = *this;
	r /= (T)s;
	return r;
}

template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator/(double s) const
{
	tiny_vec<T,N> r = *this;
	r /= (T)s;
	return r;
}

template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator+=(const tiny_vec& v)
{

	for(int i=0; i <N;i++)
		_data[i] += v[i];

	return *this;
}


template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator+(const tiny_vec& v) const
{
	tiny_vec r = *this;
	r += v;
	return r;
}


template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator-=(const tiny_vec& v)
{
	for(int i =0; i < N; i++)
		_data[i]-= v[i];

	return *this;
}


template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator-(const tiny_vec& v) const
{
	tiny_vec r = *this;
	r -= v;
	return r;
}


template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator*=(const tiny_vec& v)
{
	for(int i=0; i < N; i++)
		_data[i]*= v[i];
	return *this;
}


template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator*(const tiny_vec& v) const
{
	tiny_vec<T,N> r = *this;
	r *= v;
	return r;
}


template <typename T, int N>
tiny_vec<T,N>& tiny_vec<T,N>::operator/=(const tiny_vec& v)
{
	for(int i = 0; i < N; i++)
		_data[i] /= v[i];

	return *this;
}


template <typename T, int N>
tiny_vec<T,N> tiny_vec<T,N>::operator/(const tiny_vec<T,N>& v) const
{
	tiny_vec r = *this;
	r /= v;
	return r;
}


template <typename T, int N>
T& tiny_vec<T,N>::operator()(size_t i)
{
	assert(i >= 0 && i < N);
	return _data[i];
}

template <typename T, int N>
T tiny_vec<T,N>::operator()(size_t i) const
{
	assert(i >= 0 && i < N);
	return _data[i];
}

template <typename T, int N>
void tiny_vec<T,N>::sort()
{
	std::sort(begin(),end());
}

template <typename T, int N>
void tiny_vec<T,N>::random_shuffle()
{
	std::random_shuffle(begin(),end());
}

template <typename T, int N>
T& tiny_vec<T,N>::min_elem()
{
	return *std::min_element(begin(),end());
}

template <typename T, int N>
T tiny_vec<T,N>::min_elem() const
{
	return *std::min_element(begin(),end());
}

template <typename T, int N>
size_t tiny_vec<T,N>::min_index() const
{
	return std::distance(begin(),std::min_element(begin(),end()));
}

template <typename T, int N>
T& tiny_vec<T,N>::max_elem() 
{
	return *std::max_element(begin(),end());
}

template <typename T, int N>
T tiny_vec<T,N>::max_elem() const
{
	return *std::max_element(begin(),end());
}

template <typename T, int N>
size_t tiny_vec<T,N>::max_index() const
{
	return std::distance(begin(),std::max_element(begin(),end()));
}


template <typename T, int N>
T tiny_vec<T,N>::sqr_length() const
{
	iterator it= (double*)begin();
	T l = 0;
	while(it != end())
		l += (*it)*(*it++);

	return l;
}

template <typename T, int N>
T tiny_vec<T,N>::length() const
{
	T l = sqr_length();
	return sqrt(l);
}


template <typename T, int N>
tiny_vec<T,N> operator+(const T& s, const tiny_vec<T,N>& v)
{
	return v+s;
}


template <typename T, int N>
tiny_vec<T,N> operator+(int s, const tiny_vec<T,N>& v)
{
	return v+(T)s;
}

template <typename T, int N>
tiny_vec<T,N> operator-(const T& s, const tiny_vec<T,N>& v)
{
	return -v+s;
}


template <typename T, int N>
tiny_vec<T,N> operator-(int s, const tiny_vec<T,N>& v)
{
	return -v+(T)s;
}


template <typename T, int N>
tiny_vec<T,N> operator*(const T& s, const tiny_vec<T,N>& v)
{
	return v*s;
}


template <typename T, int N>
tiny_vec<T,N> operator*(int s, const tiny_vec<T,N>& v)
{
	return v*(T)s;
}

template <typename T, int N>
tiny_vec<T,N> operator/(const T& s, const tiny_vec<T,N>& v)
{
	return v*(T)(1.0/s);
}

template <typename T, int N>
tiny_vec<T,N> operator/(int s, const tiny_vec<T,N>& v)
{
	return v*(T)(1.0/s);
}

template <typename T, int N>
T dot(const tiny_vec<T,N>& v1, const tiny_vec<T,N>& v2)
{
	return std::inner_product(v1.begin(),v1.end(),v2.begin(),(T)0);
}



template <typename T>
tiny_vec<T,3> cross(const tiny_vec<T,3>& b, const tiny_vec<T,3>& c)
{
	tiny_vec<T,3> a;
	a[0] = b(1)*c(2) - b(2)*c(1);
	a[1] = b(2)*c(0) - b(0)*c(2);
	a[2] = b(0)*c(1) - b(1)*c(0);
	return a;
}


template <typename T, int N>
tiny_vec<T,N+1> homog(const tiny_vec<T,N>& v)
{
	tiny_vec<T,N+1> vh;
	std::copy(v.begin(),v.end(),vh.begin());
	vh(v.size()) = (T)1;
	return vh;
}

template <typename T, int N>
tiny_vec<T,N-1> unhomog(const tiny_vec<T,N>& v)
{
	tiny_vec<T,N-1> vh;
	T w = *(v.end()-1);

	for(int i = 0; i < N-1; i++)
		vh[i] = v[i]/w;

	return vh;
}




template <typename T, int N>
std::ostream& operator<<(std::ostream& out, const tiny_vec<T,N>& v)
{
	if(v.size() > 0)
		out << v[0];
	for(int i = 1; i < v.size(); i++)
		out <<" " <<v[i];
	return out;
}


template <typename T,int N>
std::istream& operator>>(std::istream& in, tiny_vec<T,N>& v)
{
	for(int i = 0; i < v.size(); i++)
		in >> v[i];

	return in;
}

template <typename T, int N>
void tiny_vec<T,N>::normalize()
{
	T l = length();
	if(l != 0)
		operator/=(l);
}



typedef tiny_vec<double, 2> point2d;
typedef tiny_vec<double, 3> point3d;
typedef tiny_vec<double, 4> point4d;
#ifdef _MSC_VER
#pragma warning( pop )
#endif



typedef tiny_vec<double, 2> vec2d;
typedef tiny_vec<double, 3> vec3d;
typedef tiny_vec<double, 4> vec4d;
