
#ifndef MAT_H
#define MAT_H


#include "vec.h"
#include "tiny_vec.h"
#include <fstream>

#ifdef _HAS_CPP0X
#include <random>
#endif

#ifdef _MSC_VER
#pragma	warning (disable: 4996)
#endif




template <typename T>
class mat;




template <typename RandomAccessIterator>
struct step_iterator:
	public std::iterator<typename std::random_access_iterator_tag,typename std::iterator_traits<RandomAccessIterator>::value_type>

{
public:
	typedef std::iterator<typename std::random_access_iterator_tag,typename std::iterator_traits<RandomAccessIterator>::value_type> base_type;
	typedef typename base_type::pointer pointer;
	typedef typename base_type::reference reference;
	typedef typename base_type::value_type value_type;
	typedef typename base_type::difference_type difference_type;
private:
	RandomAccessIterator internal_iter;
	int step;


	friend class mat<value_type>;

	step_iterator( RandomAccessIterator begin,int step=1):internal_iter(begin),step(step) 
	{}
	
	
public:
	
	
	step_iterator():internal_iter(NULL)
	{
		step=0;
	}
    
	step_iterator(const step_iterator& other)
	{
		internal_iter=other.internal_iter;
		step=other.step;
	}

    step_iterator& operator=(const step_iterator& other)
	{
		if(*this != other)
		{
			internal_iter = other.internal_iter;
			step = other.step;
		}
		return *this;
	}

	bool operator==(const step_iterator& other) const
	{
		return internal_iter == other.internal_iter;
	}
     
	bool operator!=(const step_iterator& other) const
	{
		return !(*this==other);
	}

	reference operator*()
	{
		return *internal_iter;
	}
      
	reference operator*() const
	{
		return *internal_iter;
	}
	pointer operator->()
	 {
		  return &**this;
	 }
      
	pointer operator->() const
	 {
		  return &**this;
	 }

      step_iterator& operator ++()
	  {
		  
		  internal_iter+=step;
		  return *this;
	  }

      step_iterator operator ++(int)
	  {
		  step_iterator tmp=*this;
	      ++*this;
		  return tmp;

	  }
	  step_iterator& operator --()
	  { 
		  internal_iter-=step;
		  return *this;
	  }
      step_iterator operator --(int)
	  {
		  step_iterator tmp=*this;
	      --*this;
		  return tmp;
	  }

	 
     
	  step_iterator& operator +=(difference_type n)
	  {
		  internal_iter+=n*step;
		  return *this;
		 
	  }

	  step_iterator& operator -=(difference_type n)
	  {
		  internal_iter-=n*step;
		  return *this;
	  }

	  step_iterator operator -(difference_type n) const
	  {
		  step_iterator tmp=*this;
	      tmp-=n;
		  return tmp;
	  }
	  difference_type operator-(const step_iterator& right) const
		{	
		return (internal_iter - right.internal_iter)/step;
		}
	 

	  step_iterator operator +(difference_type n)const
	  {
		  step_iterator tmp=*this;
	      tmp+=n;
		  return tmp;
	  }

	  reference operator[](difference_type offset) const
	  {
		return (*(*this + offset));
	  }

	  bool operator <(const step_iterator& other) const
	  {
		  if(step > 0)
			return internal_iter < other.internal_iter;
		  else
			return internal_iter > other.internal_iter;
	  }
	  
	  bool operator >(const step_iterator& other) const
	  {
		   if(step > 0)
			   return internal_iter > other.internal_iter;
		   else
			   return internal_iter < other.internal_iter;
	  }

	  bool operator <=(const step_iterator& other) const
	  {
		   if(step > 0)
			   return internal_iter <= other.internal_iter;
		   else
			   return internal_iter >= other.internal_iter;
	  }
	  
	  bool operator >=(const step_iterator& other) const
	  {
		  if(step > 0)
			  return internal_iter >= other.internal_iter;
		  else
			  return internal_iter <= other.internal_iter;
	  }  
};
    
    template<typename S> class mat;

//column major full matrix 
template <typename T>
class mat
{
	T* _data;
	size_t _nrows,_ncols,_size;
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

	typedef iterator col_iterator;
	typedef const col_iterator const_col_iterator;
	typedef std::reverse_iterator<col_iterator> reverse_col_iterator;
	typedef std::reverse_iterator<const_col_iterator> const_reverse_col_iterator;

	typedef step_iterator<iterator> row_iterator;
	typedef const row_iterator const_row_iterator;
	typedef std::reverse_iterator<row_iterator> reverse_row_iterator;
	typedef std::reverse_iterator<const_row_iterator> const_reverse_row_iterator;

	typedef step_iterator<iterator > diag_iterator;
	typedef const diag_iterator const_diag_iterator;
	typedef std::reverse_iterator<diag_iterator> reverse_diag_iterator;
	typedef std::reverse_iterator<const_diag_iterator> const_reverse_diag_iterator;

	typedef step_iterator<iterator > anti_diag_iterator;
	typedef const anti_diag_iterator const_anti_diag_iterator;
	typedef std::reverse_iterator<anti_diag_iterator> reverse_anti_diag_iterator;
	typedef std::reverse_iterator<const_anti_diag_iterator> const_reverse_anti_diag_iterator;



	//default constructor
	mat():_data(NULL),_nrows(0),_ncols(0),_size(0)
	{
	}
	//constructs a matrix with m rows and n columns
	mat(size_t m, size_t n):_nrows(m),_ncols(n),_size(m*n)
	{
		_data = new T[_size];
	}
	//copy constructor
	mat(const mat<T>& m)
	{
		_nrows = m._nrows;
		_ncols = m._ncols;
		_size  = _nrows*_ncols;
		_data = new T[_size];
		std::copy(m.begin(),m.end(),begin());
	}
#ifdef _HAS_CPP0X
	//move constructor
	mat(mat<T> && v):_nrows(0),_ncols(0),_size(0),_data(NULL)
	{
		std::swap(_nrows,v._nrows);
		std::swap(_ncols,v._ncols);
		std::swap(_size,v._size);
		std::swap(_data,v._data);
	}
#endif
	~mat()
	{
		clear();
	}

	void clear()
	{
		if(_data)
		{
			delete [] _data;
			_data=NULL;
			_size=0;
			_nrows=0;
			_ncols=0;
		}
	}

	size_t size() const
	{
		return _size;
	}

	size_t nrows() const
	{
		return _nrows;
	}
	
	size_t w() const
	{
		return _nrows;
	}

	size_t h() const
	{
		return _ncols;
	}

	size_t ncols() const
	{
		return _ncols;
	}

	operator T*()
	{
		return _data;
	}

	operator const T*() const
	{
		return _data;
	}

	mat& operator=(const mat<T>& m)
	{
		if(this == &m)
			return *this;
		resize(m._nrows,m._ncols);
		std::copy(m.begin(),m.end(),begin());
		return *this;

	}

	template <typename S>
	operator mat<S>()
	{
		mat<S> u(_nrows,_ncols);
		auto it = u.begin();
#ifdef _HAS_CPP0X
		std::for_each(begin(),end(),[&it](const T& v){*it++ = (S) v; });
#else
		auto end = u.end();
		iterator vit = begin();
		while(it != end)
			*it++ = (S) *vit++;
#endif
		return u;
	}

#ifdef _HAS_CPP0X
	mat& operator=(mat<T>&& m)
	{
		if(this == &m)
			return *this;
		std::swap(_nrows,m._nrows);
		std::swap(_ncols,m._ncols);
		std::swap(_size,m._size);
		std::swap(_data,m._data);
		return *this;
	}
#endif

	mat& operator=(const T& s)
	{
#ifdef _HAS_CPP0X
		std::for_each(begin(),end(),[&s](T& elem){elem=s;});
#else
		for(int i = 0; i < (int)_size; i++)
			_data[i] = s;
#endif
		return *this;
	}	
	
	mat operator-() const
	{
		
		return  (T)(-1)* (*this);
	}

	mat& operator+=(const T& s)
	{
#ifdef _HAS_CPP0X
		std::for_each(begin(),end(),[&s](T& elem){elem+=s;});
#else
		for(int i = 0; i < _size; i++)
			_data[i] += s;
#endif
		return *this;
	}

	mat operator+(const T& s) const
	{
		mat r = *this;
		r += s;
		return r;
	}

	mat& operator-=(const T& s)
	{
#ifdef _HAS_CPP0X
		std::for_each(begin(),end(),[&s](T& elem){elem-=s;});
#else
		for(int i = 0; i < _size; i++)
			_data[i] -= s;
#endif
		return *this;
	}

	mat operator-(const T& s) const
	{
		mat r = *this;
		r -= s;
		return r;
	}

	mat& operator*=(const T& s)
	{
#ifdef _HAS_CPP0X
		std::for_each(begin(),end(),[&s](T& elem){elem *= s;});
#else
		for(int i = 0; i < (int)_size; i++)
			_data[i] *= s;
#endif
		return *this;
	}

	mat operator*(const T& s) const
	{
		mat r = *this;
		r *= s;
		return r;
	}

	mat& operator/=(const T& s)
	{
#ifdef _HAS_CPP0X
		std::for_each(begin(),end(),[&s](T& elem){elem/=s;});
#else
		for(int i = 0; i < _size; i++)
			_data[i] /= s;
#endif
		return *this;
	}
	mat operator/(const T& s) const
	{
		mat r = *this;
		r /= s;
		return r;
	}
	mat& operator+=(const mat& m)
	{
#ifdef _HAS_CPP0X
		mat::const_iterator mit=m.begin();
		std::for_each(begin(),end(),[&mit](T& elem){elem+=*mit++;});
#else
		for(int i=0; i < _size; i++)
			_data[i] = m._data[i];
#endif
		return *this;
	}

	mat operator+(const mat&m)
	{
		mat r =m;
		r+=*this;
		return r;
	}

	mat operator-(const mat&m)
	{
		mat r =m;
		r-=*this;
		return r;
	}

	mat& operator-=(const mat& m)
	{
#ifdef _HAS_CPP0X
		mat::const_iterator mit=m.begin();
		std::for_each(begin(),end(),[&mit](T& elem){elem-=*mit++;});
#else
		for(int i = 0; i < _size; i++)
			_data[i] -= m._data[i];
#endif
		return *this;
	}

	void reshape(size_t m, size_t n)
	{
		assert(m*n == _size);
		_nrows = m;
		_ncols = n;
	}
	void resize(size_t m, size_t n)
	{
  		if(_nrows == m && _ncols == n)
			return;
		if(_data)
			delete [] _data;
		_nrows = m;
		_ncols = n;
		_size = m*n;
		if(_size > 0)
			_data = new T[_size];	
	}

	void zeros(size_t m, size_t n)
	{
		resize(m,n);
		T zero = 0;
		std::fill(begin(),end(),zero);
	}

	void zeros(size_t m)
	{
		resize(m,m);
		T zero;
		zero= 0;
		std::fill(begin(),end(),zero);
	}

	void ones(size_t m)
	{
		resize(m,m);
		T one;
		one = 1;
		std::fill(begin(),end(),one);
	}

	void ones(size_t m, size_t n)
	{
		resize(m,n);
		T one;
		one = 1;
		std::fill(begin(),end(),one);
	}

	void fill(const T& s)
	{
		std::fill(begin(),end(),s);
	}

	

	T& operator()(size_t i)
	{
		return _data[i];
	}

	T operator()(size_t i) const
	{
		return _data[i];
	}

	T& operator[](size_t i)
	{
		return _data[i];
	}

	T operator[](size_t i) const
	{
		return _data[i];
	}

	T& operator()(size_t i, size_t j)
	{
		assert(i < _nrows && j < _ncols);
		return _data[j*_nrows +i];
	}

	T operator()(size_t i, size_t j) const
	{
		assert(i < _nrows && j < _ncols);
		return _data[j*_nrows + i];
	}

	vec<T> col(size_t i) const
	{
		vec<T> v(_nrows);
		std::copy(col_begin(i),col_end(i),v.begin());
		return v;
	}
	vec<T> row(size_t i) const
	{
		vec<T> v(_ncols);
		std::copy(row_begin(i),row_end(i),v.begin());
		return v;
	}

	void set_row(size_t i,const vec<T>& v)
	{
		std::copy(v.begin(),v.end(),row_begin(i));
	}

	void set_col(size_t i,const vec<T>& v)
	{
		std::copy(v.begin(),v.end(),col_begin(i));
	}

	iterator begin()
	{
		return _data;
	}

	const_iterator begin() const
	{
		return _data;
	}

	iterator end()
	{
		return _data + _size;
	}

	const_iterator end() const
	{
		return _data+ _size;
	}
	col_iterator col_begin(int c)
	{
		return col_iterator(_data+(c*_nrows));
	}
	col_iterator col_end(int c)
	{
		return col_iterator(_data+(c+1)*_nrows );
	}
	const_col_iterator col_begin(int c) const
	{
		return const_col_iterator(_data+(c*_nrows));
	}
	const_col_iterator col_end(int c) const
	{
		return const_col_iterator(_data+(c+1)*_nrows );
	}
	reverse_col_iterator col_rbegin(int c)
	{	
		return (reverse_col_iterator(col_end(c)));
	}
	reverse_col_iterator col_rend(int c)
	{
		return (reverse_col_iterator(col_begin(c)));
	}
	const_reverse_col_iterator col_rbegin(int c) const
	{	
		return (const_reverse_col_iterator(col_end(c)));
	}
	const_reverse_col_iterator col_rend(int c) const
	{	
		return (const_reverse_col_iterator(col_begin(c)));
	}
	row_iterator row_begin(int r)
	{
		return row_iterator(_data+r,_nrows);
	}
	row_iterator row_end(int r)
	{
		return row_iterator(_data+(r+_size),_nrows);
	}
	const_row_iterator row_begin(int r) const
	{
		return const_row_iterator(_data+r,_nrows);
	}
	const_row_iterator row_end(int r) const
	{
		return const_row_iterator(_data+(r+_size),_nrows);
	}
	reverse_row_iterator row_rbegin(int r)
	{	
		return (reverse_row_iterator(row_end(r)));
	}
	reverse_row_iterator row_rend(int r)
	{
		return (reverse_row_iterator(row_begin(r)));
	}
	const_reverse_row_iterator row_rbegin(int r) const
	{	
		return (const_reverse_row_iterator(row_end(r)));
	}
	const_reverse_row_iterator row_rend(int r) const
	{	
		return (const_reverse_row_iterator(row_begin(r)));
	}
	diag_iterator diag_begin(int d=0)
	{
		if(d <= 0)
			return diag_iterator(_data-d ,_nrows+1);
		else
			return diag_iterator(_data+d*_nrows,_nrows+1);
		
	}
	diag_iterator diag_end(int d=0)
	{	
		if(d <= 0)
		{
			int n=std::min<int>(_nrows+d,_ncols); 
			return diag_iterator(_data-d+n*(_nrows+1),_nrows+1);
		}
		else
		{
			int n = std::min<int>(_ncols-d,_nrows);
			return diag_iterator(_data+d*_nrows+n*(_nrows+1),_nrows+1) ;
		}
	}
	const_diag_iterator diag_begin(int d=0) const
	{
		if(d <= 0)
			return const_diag_iterator(_data-d ,_nrows+1);
		else	
			return const_diag_iterator(_data+d*_nrows,_nrows+1);
		
	}
	const_diag_iterator diag_end(int d=0) const
	{
		if(d <= 0)
		{
			int n=std::min<int>(_nrows+d,_ncols); 
			return const_diag_iterator(begin()-d+n*(_nrows+1),_nrows+1);
		}
		else
		{
			int n = std::min<int>(_ncols-d,_nrows);
			return const_diag_iterator(begin()+d*_nrows+n*(_nrows+1),_nrows+1) ;
		}
	}
	reverse_diag_iterator diag_rbegin(int d=0)
	{	
		return (reverse_diag_iterator(diag_end(d)));
	}
	reverse_diag_iterator diag_rend(int d=0)
	{
		return (reverse_diag_iterator(diag_begin(d)));
	}
	const_reverse_diag_iterator diag_rbegin(int d=0) const
	{	
		return (const_reverse_diag_iterator(diag_end(d)));
	}
	const_reverse_diag_iterator diag_rend(int d=0) const
	{	
		return (const_reverse_diag_iterator(diag_begin(d)));
	}
	anti_diag_iterator anti_diag_begin(int d=0)
	{
		if(d >= 0)
			return anti_diag_iterator(_data+(_ncols-1-d)*_nrows ,1-_nrows);
		else
			return anti_diag_iterator(_data+(_ncols-1)*_nrows-d ,1-_nrows);
	}
	anti_diag_iterator anti_diag_end(int d=0)
	{
		if(d >= 0)
		{
			int n=std::min(_ncols-d,_nrows);
			return anti_diag_iterator(_data+(_ncols-1-d)*_nrows +n*(1-_nrows),1-_nrows);
		}
		else
		{
			int n=std::min(_nrows+d,_ncols);
			return anti_diag_iterator(_data+(_ncols-1)*_nrows-d +n*(1-_nrows),1-_nrows);
		}
	}
	const_anti_diag_iterator anti_diag_begin(int d=0) const
	{
		if(d >= 0)
			return const_anti_diag_iterator(_data+(_ncols-1-d)*_nrows ,1-_nrows);
		else
			return const_anti_diag_iterator(_data+(_ncols-1)*_nrows-d ,1-_nrows);
	}
	const_anti_diag_iterator anti_diag_end(int d=0) const
	{
		if(d >= 0)
		{
			int n=std::min(_ncols-d,_nrows);
			return const_anti_diag_iterator(begin()+(_ncols-1-d)*_nrows +n*(1-_nrows),1-_nrows);
		}
		else
		{
			int n=std::min(_nrows+d,_ncols);
			return const_anti_diag_iterator(begin()+(_ncols-1)*_nrows-d +n*(1-_nrows),1-_nrows);
		}
	}
	reverse_anti_diag_iterator anti_diag_rbegin(int d=0)
	{	
		return (reverse_anti_diag_iterator(anti_diag_end(d)));
	}
	reverse_anti_diag_iterator anti_diag_rend(int d=0)
	{
		return (reverse_anti_diag_iterator(anti_diag_begin(d)));
	}
	const_reverse_anti_diag_iterator anti_diag_rbegin(int d=0) const
	{	
		return (const_reverse_anti_diag_iterator(anti_diag_end(d)));
	}
	const_reverse_anti_diag_iterator anti_diag_rend(int d=0) const
	{	
		return (const_reverse_anti_diag_iterator(anti_diag_begin(d)));
	}

	void transpose()
	{
		
			mat m(_ncols,_nrows);
	   
			for(int i = 0; i < (int)_ncols;i++)
				std::copy(col_begin(i),col_end(i),m.row_begin(i));
			reshape(_nrows,_ncols);
			operator=(m);
		
	}

	void abs()
	{
#ifdef _HAS_CPP0X
		std::for_each(begin(), end(),[](T& v){v=std::abs(v);});
#else
		for(int i = 0; i < _size; i++)
			_data[i] = std::abs(_data[i]);
#endif
	}
	

};



// y+= a*x
template <typename T, typename It1, typename It2>
void saxpy(const T& a, It1 xfirst, It1 xlast,It2 yfirst)
{
	It1 itx = xfirst;
	It2 ity = yfirst;
	

	while(itx != xlast)
		*ity++ += a* (*itx++);
}

//y += A*x
template <typename T, typename It1, typename It2>
void gaxpy(const mat<T>& A, It1 xfirst, It1 xlast,It2 yfirst)
{
	It1 itx = xfirst;
	It2 ity = yfirst;

	for(size_t i = 0; i < A.ncols(); i++)
		saxpy(*itx++,A.col_begin(i),A.col_end(i),yfirst);
		
}


template <typename T>
vec<T> operator*(const mat<T>& m, const vec<T>& v)
{
	assert(m.ncols() == v.size());
	vec<T> r;
	r.zeros(m.nrows());
	
auto it = v.begin();
	for(size_t i = 0; i < m.ncols(); i++)
		saxpy(*it++,m.col_begin(i), m.col_end(i),r.begin());
	
	return r;
}

template <typename T,int N>
vec<T> operator*(const mat<T>& m, const tiny_vec<T,N>& v)
{
	assert(m.ncols() == N);
	vec<T> r;
	r.zeros(m.nrows());
	
	auto it = v.begin();
	for(size_t i = 0; i < m.ncols(); i++)
		saxpy(*it++,m.col_begin(i), m.col_end(i),r.begin());
	
	return r;
}

template <typename T>
mat<T> operator*(const mat<T>& m1, const mat<T>& m2)
{
	assert(m1.ncols() == m2.nrows());
	mat<T> r;
	r.zeros(m1.nrows(),m2.ncols());
	for(size_t i = 0; i <m2.ncols(); i++)
		gaxpy(m1,m2.col_begin(i),m2.col_end(i),r.col_begin(i));

	return r;
}


template <typename T>
mat<T> transpose(const mat<T>& m)
{
	mat<T> r = m;
	r.transpose();
	return r;
}



template <typename T>
mat<T> operator+(const T& s, const mat<T>& m)
{
	return m+s;
}

template <typename T>
mat<T> operator-(const T& s, const mat<T>& m)
{
	return -m+s;
}


template <typename T>
mat<T> operator*(const T& s, const mat<T>& m)
{
	return m*s;
}

template <typename T>
mat<T> operator/(const T& s, const mat<T>& m)
{
	return m*(T)(1.0/s);
}





///compute inverse of 2x2 matrix
template <typename T>
mat<T> inv_22(const mat<T>& m) 
{
	
	mat<T> im(2,2);
	T t4 = 1.0 / (-m(0,0) * m(1,1) + m(0,1) * m(1,0));
	im(0,0) = -m(1,1) * t4;
	im(1,0) = m(1,0) * t4;
	im(0,1) = m(0,1) * t4;
	im(1,1) = -m(0,0) * t4;
	
	return im;
}

///compute inverse of 3x3 matrix
template <typename T>
mat<T> inv_33(const mat<T>& m) 
{
	
	mat<T> im(3,3);
	T t4 = m(2,0) * m(0,1);
	T t6 = m(2,0) * m(0,2);
	T t8 = m(1,0) * m(0,1);
	T t10 = m(1,0) * m(0,2);
	T t12 = m(0,0) * m(1,1);
	T t14 = m(0,0) * m(1,2);
	T t17 = (T)1.0 / (t4 * m(1,2) - t6 * m(1,1) - t8 * m(2,2) + t10 * m(2,1) + t12 * m(2,2) - t14 * m(2,1));
	im(0,0) = (m(1,1) * m(2,2) - m(1,2) * m(2,1)) * t17;
	im(0,1) = -(m(0,1) * m(2,2) - m(0,2) * m(2,1)) * t17;
	im(0,2) = (m(0,1) * m(1,2) - m(0,2) * m(1,1)) * t17;
	im(1,0) = -(-m(2,0) * m(1,2) + m(1,0) * m(2,2)) * t17;
	im(1,1) = (-t6 + m(0,0) * m(2,2)) * t17;
	im(1,2) = -(-t10 + t14) * t17;
	im(2,0) = (-m(2,0) * m(1,1) + m(1,0) * m(2,1)) * t17;
	im(2,1) = -(-t4 + m(0,0) * m(2,1)) * t17;
	im(2,2) = (-t8 + t12) * t17;
	return im;
}

//compute inverse of 4x4 matrix
template <typename T>
mat<T> inv_44(const mat<T>& m) 
{
	
	mat<T> im(4,4);
	T t1 = m(3,3) * m(1,1);
	T t3 = m(3,2) * m(1,1);
	T t7 = m(3,1) * m(1,2);
	T t9 = m(3,1) * m(1,3);
	T t11 = m(3,2) * m(2,1);
	T t14 = m(0,0) * m(1,1);
	T t19 = m(0,0) * m(3,3);
	T t20 = m(1,2) * m(2,1);
	T t22 = m(3,1) * m(0,0);
	T t23 = m(1,2) * m(2,3);
	T t25 = m(1,3) * m(2,2);
	T t27 = m(3,2) * m(0,0);
	T t28 = m(2,1) * m(1,3);
	T t30 = m(1,1) * m(3,0);
	T t31 = m(0,3) * m(2,2);
	T t33 = m(2,0) * m(0,3);
	T t35 = m(0,2) * m(2,3);
	T t37 = m(2,0) * m(0,2);
	T t39 = m(3,0) * m(0,2);
	T t41 = m(3,1) * m(1,0);
	T t43 = t14 * m(3,3) * m(2,2) - t14 * m(3,2) * m(2,3) - t19 * t20 + 
		t22 * t23 - t22 * t25 + t27 * t28 - t30 * t31 + t3 * t33 + t30 * t35 
		- t1 * t37 - t39 * t28 - t41 * t35;
	T t45 = m(3,0) * m(0,1);
	T t47 = m(1,0) * m(3,3);
	T t50 = m(2,0) * m(3,3);
	T t51 = m(0,1) * m(1,2);
	T t53 = m(3,2) * m(1,0);
	T t56 = m(0,2) * m(2,1);
	T t58 = m(3,0) * m(0,3);
	T t63 = m(3,2) * m(2,0);
	T t64 = m(0,1) * m(1,3);
	T t66 = m(1,0) * m(0,3);
	T t68 = -t7 * t33 - t45 * t23 - t47 * m(0,1) * m(2,2) + t50 * t51 + t53 *
		m(0,1) * m(2,3) + t47 * t56 + t58 * t20 + t9 * t37 + t41 * t31 + t45 *
		t25 - t63 * t64 - t11 * t66;
	T t70 = (T)1.0 / (t43 + t68);
	T t72 = m(3,3) * m(0,1);
	T t74 = m(3,2) * m(0,1);
	T t78 = m(0,3) * m(3,1);
	T t108 = m(2,0) * m(1,2);
	T t111 = m(1,3) * m(3,0);
	T t131 = m(0,0) * m(1,2);
	T t135 = m(1,0) * m(0,2);
	T t148 = m(3,1) * m(2,0);
	T t150 = m(1,0) * m(2,1);
	T t156 = m(0,0) * m(2,1);
	T t158 = m(0,0) * m(2,3);
	T t161 = m(2,0) * m(0,1);
	im(0,0) = (t1 * m(2,2) - t3 * m(2,3) - m(3,3) * m(1,2) * m(2,1) + 
		t7 * m(2,3) - t9 * m(2,2) + t11 * m(1,3)) * t70;
	im(0,1) = -(t72 * m(2,2) - t74 * m(2,3) - t56 * m(3,3) + t35 * m(3,1) - 
		t78 * m(2,2) + m(0,3) * m(3,2) * m(2,1)) * t70;
	im(0,2) = (t72 * m(1,2) - t74 * m(1,3) - t1 * m(0,2) + m(0,2) * m(3,1) *
		m(1,3) + t3 * m(0,3) - t78 * m(1,2)) * t70;
	im(0,3) = -(t51 * m(2,3) - t64 * m(2,2) - m(1,1) * m(0,2) * m(2,3) + t56 *
		m(1,3) + m(1,1) * m(0,3) * m(2,2) - m(0,3) * m(1,2) * m(2,1)) * t70;
	im(1,0) = -(t47 * m(2,2) - t53 * m(2,3) + m(1,3) * m(3,2) * m(2,0) - t108 *
		m(3,3) + t23 * m(3,0) - t111 * m(2,2)) * t70;
	im(1,1) = (t19 * m(2,2) - t27 * m(2,3) - t58 * m(2,2) + t63 * m(0,3) + t39 *
		m(2,3) - t50 * m(0,2)) * t70;
	im(1,2) = -(t19 * m(1,2) - t27 * m(1,3) - t47 * m(0,2) - t58 * m(1,2) + t111 *
		m(0,2) + t66 * m(3,2)) * t70;
	im(1,3) = (t131 * m(2,3) - m(0,0) * m(1,3) * m(2,2) - t135 * m(2,3) - t108 *
		m(0,3) + m(1,3) * m(2,0) * m(0,2) + t66 * m(2,2)) * t70;
	im(2,0) = (-m(1,1) * m(2,0) * m(3,3) + m(1,1) * m(2,3) * m(3,0) - t28 *
		m(3,0) + t148 * m(1,3) + t150 * m(3,3) - m(2,3) * m(3,1) * m(1,0)) * t70;
	im(2,1) = -(t156 * m(3,3) - t158 * m(3,1) + t33 * m(3,1) - t161 * m(3,3) - m(2,1) *
		m(3,0) * m(0,3) + m(2,3) * m(3,0) * m(0,1)) * t70;
	im(2,2) = (t19 * m(1,1) - t22 * m(1,3) - t58 * m(1,1) - t47 * m(0,1) + t41 *
		m(0,3) + t45 * m(1,3)) * t70;
	im(2,3) = -(-m(2,3) * m(1,0) * m(0,1) + t158 * m(1,1) - t33 * m(1,1) + t161 *
		m(1,3) - t156 * m(1,3) + t150 * m(0,3)) * t70;
	im(3,0) = -(-t3 * m(2,0) + t30 * m(2,2) + t11 * m(1,0) - m(3,0) * m(1,2) *
		m(2,1) - t41 * m(2,2) + t7 * m(2,0)) * t70;
	im(3,1) = (-t22 * m(2,2) + t27 * m(2,1) - t39 * m(2,1) + t148 * m(0,2) + t45 *
		m(2,2) - t63 * m(0,1)) * t70;
	im(3,2) = -(-t53 * m(0,1) + t27 * m(1,1) - t39 * m(1,1) + t41 * m(0,2) - t22 *
		m(1,2) + t45 * m(1,2)) * t70;
	im(3,3) = t70 * (t161 * m(1,2) - t37 * m(1,1) - m(1,0) * m(0,1) * m(2,2) + t135 *
		m(2,1) + t14 * m(2,2) - t131 * m(2,1));

	return im;
}


template <typename T>
mat<T> abs(const mat<T>& m)
{
	mat<T> r = m;
	r.abs();
	return r;
}



///creates a 4x4 translation matrix
template <typename T>
mat<T> translate_44(const T&x, const T &y, const T&z)
{
	mat<T> m(4,4);
	m(0,0)=1; m(0,1)= 0; m(0,2)= 0; m(0,3)= x;
	m(1,0)=0; m(1,1)= 1; m(1,2)= 0; m(1,3)= y;
	m(2,0)=0; m(2,1)= 0; m(2,2)= 1; m(2,3)= z;
	m(3,0)=0; m(3,1)= 0; m(3,2)= 0; m(3,3)= 1;
	return m;
}


///creates a 4x4 scale matrix
template <typename T>
mat<T> scale_44(const T&sx, const T &sy, const T&sz)
{
	mat<T> m(4,4);
	m(0,0)=sx; m(0,1)= 0; m(0,2)= 0; m(0,3)= 0;
	m(1,0)=0; m(1,1)=sy; m(1,2)= 0; m(1,3)= 0;
	m(2,0)=0; m(2,1)= 0; m(2,2)= sz; m(2,3)= 0;
	m(3,0)=0; m(3,1)= 0; m(3,2)= 0; m(3,3)= 1;
	return m;
}




///creates a 4x4 rotation matrix around the x axis, the angle is in degree   
template<typename T>
 mat<T> rotatex_44(const T& angle)
{
	T angler = angle*(T)3.14159/(T)180.0;
	mat<T> m(4,4);
    m(0,0)=1; m(0,1)= 0; m(0,2)= 0; m(0,3)= 0;
	m(1,0)=0; m(1,1)= (T)cos((double)angler); 
	m(1,2)= -(T)sin((double)angler); m(1,3)= 0;
	m(2,0)=0; m(2,1)= (T)sin((double)angler); 
	m(2,2)= (T)cos((double)angler); m(2,3)= 0;
	m(3,0)=0; m(3,1)= 0; m(3,2)= 0; m(3,3)= 1;
    return m;
}

///creates a 4x4 rotation matrix around the y axis, the angle is in degree  
template<typename T>
mat<T> rotatey_44(const T& angle)
{
	T angler=angle*(T)3.14159/(T)180.0;
    mat<T> m(4,4);
    m(0,0)=(T)cos((double)angler); m(0,1)= 0; 
	m(0,2)= (T)sin((double)angler); m(0,3)= 0;
	m(1,0)=0; m(1,1)=1; m(1,2)= 0; m(1,3)= 0;
	m(2,0)=-(T)sin((double)angler); m(2,1)= 0; 
	m(2,2)= (T)cos((double)angler); m(2,3)= 0;
	m(3,0)=0; m(3,1)= 0; m(3,2)= 0; m(3,3)= 1;
    return m;
}

///creates a 4x4 rotation matrix around the z axis, the angle is in degree  
template<typename T>
mat<T> rotatez_44(const T& angle)
{
	T angler=angle*(T)3.14159/(T)180.0;
	mat<T> m(4,4);
    m(0,0)=(T)cos((double)angler); 
	m(0,1)= -(T)sin((double)angler); m(0,2)= 0; m(0,3)= 0;
	m(1,0)=(T)sin((double)angler); 
	m(1,1)= (T)cos((double)angler); m(1,2)= 0; m(1,3)= 0;
	m(2,0)=0; m(2,1)= 0; m(2,2)= 1; m(2,3)= 0;
	m(3,0)=0; m(3,1)= 0; m(3,2)= 0; m(3,3)= 1;
    return m;
}



///creates a perspective transformation matrix in the same way as gluPerspective does
template<typename T>
mat<T> perspective_44(const T& fovy, const T&aspect, const T& znear, const T& zfar)
{
	T fovyr = (T)(fovy*3.14159/180.0);
	T f = (T)(cos(fovyr/2.0f)/sin(fovyr/2.0f));
	mat<T> m(4,4);
	m(0,0)=f/aspect; m(0,1)= 0; m(0,2)= 0; m(0,3)= 0;
	m(1,0)=0; m(1,1)= f; m(1,2)= 0; m(1,3)= 0;
	m(2,0)=0; m(2,1)= 0; m(2,2)= (zfar+znear)/(znear-zfar); 
	m(2,3)= (2*zfar*znear)/(znear-zfar);
	m(3,0)=0; m(3,1)= 0; m(3,2)= -1; m(3,3)= 0;
	return m;
}

template<typename T>
mat<T> frustrum_44(const T& left,const T& right,const T& top,const T& bottom, const T& znear, const T& zfar)
{
	
	T A = (right + left)/(right - left);
	T B = (top + bottom)/(top - bottom);
	T C = -(zfar + znear)/(zfar - znear);
	T D = -(2*zfar*znear)/(zfar - znear);
	T E = 2*znear/(right-left);
	T F = 2*znear/(top-bottom);
	mat<T> m(4,4);
	m(0,0)=E; m(0,1)= 0; m(0,2)= A; m(0,3)= 0;
	m(1,0)=0; m(1,1)= F; m(1,2)= B; m(1,3)= 0;
	m(2,0)=0; m(2,1)= 0; m(2,2)= C; m(2,3)= D;
	m(3,0)=0; m(3,1)= 0; m(3,2)= -1; m(3,3)= 0;
	return m;
}



template <typename T>
mat<T> eye(size_t m, size_t n)
{
	mat<T> r(m,n);
	r=(T)0;
	std::fill(r.diag_begin(),r.diag_end(),(T)1);
	return r;
}

template <typename T>
mat<T> eye(size_t m)
{
	return eye<T>(m,m);
}

template <typename T>
mat<T> ones(size_t m, size_t n)
{
	mat<T> r(m,n);
	r=(T)1;
	return r;
}

template <typename T>
mat<T> ones(size_t m)
{
	return ones<T>(m,m);
}

/*
template <typename T>
mat<T> rand(size_t m, size_t n)
{
	
	std::mt19937 engine;
	std::uniform_real_distribution<T> distribution;
	auto generator = std::bind(distribution, engine);

	mat<T> mr(m,n);
	std::for_each(mr.begin(),mr.end(),[&](T& f){f=generator();});
	return mr;
}


template <typename T>
mat<T> randn(size_t m, size_t n)
{
		
	std::mt19937 engine;
	std::normal_distribution<T> distribution((T)0,(T)1);
	auto generator = std::bind(distribution, engine);
	mat<T> mr(m,n);
	std::for_each(mr.begin(),mr.end(),[&](T& f){f=generator();});
	return mr;
}*/

template <typename T>
mat<T> zeros(size_t m, size_t n)
{
	mat<T> r(m,n);
	r=(T)0;
	return r;
}

template <typename T>
mat<T> zeros(size_t m)
{
	return zeros<T>(m,m);
}

template <typename T>
mat<T> cross_mat(vec<T>& v)
{
	mat<T> C(3,3);
	auto it = C.begin();
	
	*it++ = 0;
	*it++ = v(2);
	*it++ = -v(1);

	*it++ = -v(2);
	*it++ = 0;
	*it++ = v(0);

	*it++ = v(1);
	*it++ = -v(0);
	*it = 0;

	return C;
}


template <typename T>
mat<T> cross_mat(tiny_vec<T,3>& v)
{
	mat<T> C(3,3);
	auto it = C.begin();
	
	*it++ = 0;
	*it++ = v(2);
	*it++ = -v(1);

	*it++ = -v(2);
	*it++ = 0;
	*it++ = v(0);

	*it++ = v(1);
	*it++ = -v(0);
	*it = 0;

	return C;
}



inline bool read_fmat(mat<float>& m,const std::string& filename)
{

	std::ifstream myFile (filename.c_str(), std::ios::binary);
    if (myFile) 
	{
		int _w,_h;
		myFile.read((char*)&_w, sizeof(int));
		myFile.read((char*)&_h, sizeof(int));
		int n=_w*_h;
		if(n == 0)
		{
			myFile.close();
			return false;
		}

		m.resize(_w,_h);

		myFile.read((char*)&(m(0,0)), n*sizeof(float));	
		myFile.close();
		m.transpose();
		return true;   
    }
	return false;
}

inline bool write_fmat(mat<float>& m, const std::string& filename) 
{
	mat<float> im=m;
	im.transpose();
	int w = im.nrows();
	int h = im.ncols();
	int n=w*h;
	if(w == 0||h == 0)
		return false;

	
	std::ofstream myFile (filename.c_str(), std::ios::binary);
    if (myFile) 
	{
		 myFile.write((char*)&w, sizeof(int));
		 myFile.write((char*)&h, sizeof(int));
		 int n=w*h;
		 if(n > 0)
			myFile.write((char*)&(im(0,0)), n*sizeof(float));
		 myFile.close();
		 return true;   
    }
	return false;
   
}

inline bool read_imat(mat<int>& m,const std::string& filename)
{

	std::ifstream myFile( filename.c_str(),  std::ios::binary);
    if (myFile) 
	{
		int _w,_h;
		myFile.read((char*)&_w, sizeof(int));
		myFile.read((char*)&_h, sizeof(int));
		int n=_w*_h;
		if(n == 0)
		{
			myFile.close();
			return false;
		}

		m.resize(_w,_h);

		myFile.read((char*)&(m(0,0)), n*sizeof(int));	
		myFile.close();
		m.transpose();
		return true;   
    }
	return false;
}

inline bool write_imat(mat<int>& m, const std::string& filename) 
{
	mat<int> im=m;
	im.transpose();
	int w = im.nrows();
	int h = im.ncols();
	int n=w*h;
	if(w == 0||h == 0)
		return false;

	
	std::ofstream myFile (filename.c_str(), std::ios::binary);
    if (myFile) 
	{
		 myFile.write((char*)&w, sizeof(int));
		 myFile.write((char*)&h, sizeof(int));
		 int n=w*h;
		 if(n > 0)
			myFile.write((char*)&(im(0,0)), n*sizeof(int));
		 myFile.close();
		 return true;   
    }
	return false;
   
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const mat<T>& m)
{
	for(size_t i = 0; i < m.nrows(); i++)
	{
#ifdef _HAS_CPP0X
		auto it = m.row_begin(i);
		if(it != m.row_end(i))
			out << *it ++;
		std::for_each(it, m.row_end(i),[&out](const T& elem){ out << " "<<elem;});
#else
		if(m.ncols() > 0)
			out << m(i,0);
		for(int j = 1; j < m.ncols();i++)
			out << " "<<m(i,j);
#endif
		out << std::endl;
	}
	return out;
}


inline std::ostream& operator<<(std::ostream& out, const mat<unsigned char>& m)
{
	for(size_t i = 0; i < m.nrows(); i++)
	{
		if(m.ncols() > 0)
			out << m(i,0);
		for(int j = 1; j < (int)m.ncols();i++)
			out << " "<<(int)m(i,j);
		out << std::endl;
	}
	return out;
}

template <typename T>
std::istream& operator>>(std::istream& in,  mat<T>& m)
{
#ifdef _HAS_CPP0X
	std::for_each(m.begin(), m.end(),[&in]( T& elem){ in >> elem;});
#else
	for(int i = 0;i < (int)m.size(); i++)
		in >> m._data[i];
#endif
	m.transpose();
	return in;
}

#endif
