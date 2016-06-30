#pragma once

#include <cmath>
#include <limits>
#include <algorithm>
#include <iostream>

/** A vector with zero based index that stores N components of type T.*/
template <typename T, unsigned N>
class fvec 
{
protected:
	/// elements of vector
	T v[N];
public:
	/// creates a vector not initialized
	fvec() {}
	/// creates a vector initialized to constant value a
	fvec(const T &a) { std::fill(v, v+N, a); }
	/// construct and init first two coordinates to the given values	
	fvec(const T &x, const T &y) { set(x,y); }
	/// construct and init first three coordinates to the given values	
	fvec(const T &x, const T &y, const T &z) { set(x,y,z); }
	/// construct and init first four coordinates to the given values	
	fvec(const T &x, const T &y, const T &z,const T &w) { set(x,y,z,w); }	
	/// creates a column vector initialized to array a
	fvec(const T *a) { std::copy(a, a+N, v); }
	/// copy constructor
	fvec(const fvec &rhs) { if (this != &rhs) std::copy(rhs.v, rhs.v+N, v); }
	/// assign vector rhs, if vector and rhs have different sizes, vector has been resized to match the size of
	fvec& operator = (const fvec &rhs) { if (this != &rhs) std::copy(rhs.v, rhs.v+N, v); return *this; }
	/// assign a to every element
	fvec & operator = (const T &a) { std::fill(v, v+N, a); return *this; }	
	///set the first two components
	void set(const T &x, const T &y) { v[0] = x; v[1] = y; }
	///set the first three components
	void set(const T &x, const T &y, const T &z) { v[0] = x; v[1] = y; v[2] = z; }
	///set the first four components
	void set(const T &x, const T &y, const T &z, const T &w) { v[0] = x; v[1] = y; v[2] = z; v[3] = w; }
	/// access i'th element
	T& operator()(const int i) { return v[i]; }
	/// access i'th element of const vector
	const T & operator()(const int i) const { return v[i]; }
	/// cast into array. This allows calls like glVertex<N><T>v(p) instead of glVertex<N><T,N>(p.x(),p.y(),....)
	operator T*() { return v; }
	/// cast into const array
	operator const T*() const { return v; }

	//@name operators
	//@{
	///in place addition of a scalar s
	fvec<T,N>& operator += (const T& s) { for (unsigned i=0;i<N;++i) v[i] += s; return *this; }
	///in place subtraction by scalar s
	fvec<T,N>& operator -= (const T& s) { for (unsigned i=0;i<N;++i) v[i] -= s; return *this; }
	///in place multiplication with s
	fvec<T,N>& operator *= (const T& s) { for (unsigned i=0;i<N;++i) v[i] *= s; return *this; }
	///in place division by scalar s
	fvec<T,N>& operator /= (const T& s) { for (unsigned i=0;i<N;++i) v[i] /= s; return *this; }
	///in place vector addition
	template <typename S> 
	fvec<T,N>& operator += (const fvec<S,N>& _v)  { for (unsigned i=0; i<N;++i) v[i] += _v(i); return *this; }
	///in place vector subtraction
	template <typename S> 
	fvec<T,N>& operator -= (const fvec<S,N>& _v) { for (unsigned i=0; i<N;++i) v[i] -= _v(i); return *this; }
	///in place componentwise vector multiplication
	template <typename S> 
	fvec<T,N>& operator *= (const fvec<S,N>& _v) { for (unsigned i=0; i<N;++i) v[i] *= _v(i); return *this; }
	///in place componentwise vector division
	template <typename S> 
	fvec<T,N>& operator /= (const fvec<S,N>& _v) { for (unsigned i=0; i<N;++i) v[i] /= _v(i); return *this; }
	///vector addition
	template <typename S> 
	fvec<T,N> operator + (const fvec<S,N>& v) const { fvec<T,N> r = *this; r += v; return r; }
	///componentwise addition of scalar
	fvec<T,N> operator + (const T& s) const { fvec<T,N> r = *this; r += s; return r; }
	///componentwise subtraction of scalar
	fvec<T,N>  operator - (const T& s) const { fvec<T,N> r = *this; r -= s; return r; }
	///vector subtraction
	template <typename S> 
	fvec<T,N>  operator -  (const fvec<S,N>& v) const { fvec<T,N> r = *this; r -= v; return r; }
	///componentwise vector multiplication
	template <typename S>
	fvec<T,N> operator *  (const fvec<S,N>& v) const { fvec<T,N> r = *this; r *= v; return r; }
	///componentwise vector division
	template <typename S> 
	fvec<T,N>  operator / (const fvec<S,N>& v) const { fvec<T,N> r = *this; r /= v; return r; }
	///negates the vector
	fvec<T,N>  operator-(void) const { fvec<T,N> r; for (unsigned i=0; i<N; ++i) r(i) = -v[i]; return r; }
	///multiplication with scalar s
	fvec<T,N>  operator * (const T& s) const { fvec<T,N> r = *this; r *= s; return r; }
	///divides vector by scalar s
	fvec<T,N>  operator / (const T& s) const { fvec<T,N> r = *this; r /= s; return r; }
	///test for equality
	template <typename S> 
	bool operator == (const fvec<S,N>& v) const { 
		for (unsigned i=0;i<N;++i) 
			if(operator()(i) != (T)v(i)) return false; 
		return true; 
	}
	///test for inequality
	template <typename S> 
	bool operator != (const fvec<S,N>& v) const { 
		for (unsigned i=0;i<N;++i) 
			if(operator()(i) != (T)v(i)) return true; 
		return false; 
	}
	//@}

	//@name functions
	//@{
	///length of the vector L2-Norm
	T length() const { return (T)sqrt((double)sqr_length()); }
	///componentwise absolute values
	void abs() {	
		if(std::numeric_limits<T>::is_signed) {
			for(unsigned i = 0; i < N;i++)
				v[i]=(T)std::abs((double)v[i]);
		}
	}
	///ceil componentwise
	void ceil() {
		for(unsigned i = 0; i < N;i++)
			v[i]=(T)::ceil((double)v[i]);
	}

	///floor componentwise
	void floor() {
		for(unsigned i = 0; i < N;i++)
			v[i]=(T)::floor((double)v[i]);
	}

	///round componentwise
	void round() {
		for(unsigned i = 0; i < N;i++)
			v[i]=(T)::floor((double)v[i]+0.5);	
	}


	///square length of vector
	T sqr_length() const {
		T l=0;		
		for(unsigned i = 0; i!=N;i++)
			l+= operator()(i)*operator()(i);
		return l;
	}
	/// normalize the vector using the L2-Norm and return the length
	double normalize()  {
		T l     = length();
		T inv_l = (T)1.0/l;
		for(unsigned i = 0; i<N; i++)
			 operator()(i)=inv_l*operator()(i);
		return l;
	}
	//@}
};

/// return normalized vector
template<typename T, unsigned N>
fvec<T,N> normalize(const fvec<T,N>& v) { fvec<T,N> w(v); w.normalize(); return w; }

///output of a vector
template<typename T, unsigned N>
std::ostream& operator << (std::ostream& out, const fvec<T,N>& v)
{
	for (unsigned i=0;i<N-1;++i)
		out << v(i)<<" ";
	out << v(N-1);
	return out;

}

///input of a vector
template<typename T, unsigned N>
std::istream& operator>>(std::istream& in, fvec<T,N>& v)
{
	for (unsigned i=0;i<N;++i)
		in >> v(i);	
	return in;
}

///returns the product of a scalar s and vector v
template <typename T, unsigned N>
fvec<T,N> operator * (const T& s, const fvec<T,N>& v) 
{
	fvec<T,N> r = v; r *= s; return r; 
}

///returns the dot product of vector v and w
template <typename T, unsigned N>
inline T dot(const fvec<T,N>& v, const fvec<T,N>& w) 
{ 
	T r = 0; 
	for (unsigned i=0;i<N;++i) r += v(i)*w(i); 
	return r; 
}

///returns the length of vector v 
template <typename T, unsigned N>
inline T length(const fvec<T,N>& v) 
{
	return sqrt(dot(v,v));
}

///returns the squared length of vector v 
template <typename T, unsigned N>
inline T sqr_length(const fvec<T,N>& v) 
{
	return dot(v,v);
}


///returns the cross product of vector v and w
template < typename T, unsigned N>
inline fvec<T,N> cross(const fvec<T,N>& v, const fvec<T,N>& w) 
{ 
	fvec<T,N> r(3);
	r(0)= v(1)*w(2) - v(2)*w(1);
	r(1)= v(2)*w(0) - v(0)*w(2);
	r(2)= v(0)*w(1) - v(1)*w(0);
	return r;
}
