#include <iostream>

using namespace std;

class vec
{
protected:
	// store number of elements
	unsigned n;
	// store pointer to coordinates
	double* crds;
public:
	// standard constructor
	vec() : n(0), crds(0) 
	{
		cout << "default construct " << this << endl;
	}
	// copy constructor
	vec(const vec& v) : n(v.n)
	{
		cout << "copy construct " << this << endl;
		crds = new double[n];
		for (unsigned i=0; i<n; ++i)
			crds[i] = v.crds[i];
	}
	// construct from number of elements
	vec(unsigned _n, double _v) : n(_n)
	{
		cout << "construct " << this << endl;
		crds = new double[n];
		for (unsigned i=0; i<n; ++i)
			crds[i] = _v;
	}
	// destructor removes coords from heap
	~vec()
	{
		cout << "destruct " << this << endl;
		if (crds)
			delete [] crds;
	}
	// assignment operator
	vec& operator = (const vec& v)
	{
		cout << "assign " << this << endl;
		// avoid assignment to myself
		if (this == &v) return *this;
		// allocate memory
		if (n != v.n) {
			delete [] crds;
			crds = new double [n = v.n];
		}
		// copy values 
		for (unsigned i=0; i<n; ++i)
			crds[i] = v.crds[i];
		// return reference to myself
		return *this;
	}
	// add assign operator
	vec& operator += (const vec& v)
	{
		for (unsigned i=0; i<n; ++i)
			crds[i] += v.crds[i];
		return *this;
	}
	// multiply assign scalar
	vec& operator *= (double s)
	{
		for (unsigned i=0; i<n; ++i)
			crds[i] *= s;
		return *this;
	}
	// add operator
	vec operator + (const vec& v) const
	{
		vec r(*this);
		r += v;
		return r;
	}
	// give << operator access to protected members
	friend ostream& operator << (ostream&, const vec&);
};

// pre-multiplication with scalar outside of class
vec operator * (double s, const vec& v)
{
	vec u = v;
	u *= s;
	return u;
}

// implement << operator
ostream& operator << (ostream& os, const vec& v)
{
	for (unsigned i=0; i<v.n; ++i) {
		if (i > 0)
			os << ", ";
		os << v.crds[i];
	}
	return os;
}

template <typename T, unsigned n>
class fvec
{
protected:
	T crds[n];
public:
	// standard constructor
	fvec() {}
	// copy constructor
	fvec(const fvec<T,n>& v) {
		for (unsigned i=0; i<n; ++i)
			crds[i] = v.crds[i];
	}
	// construct from value
	fvec(const T& s) {
		for (unsigned i=0; i<n; ++i)
			crds[i] = s;
	}
	// assignment operator
	fvec<T,n>& operator = (const fvec<T,n>& v) {
		for (unsigned i=0; i<n; ++i)
			crds[i] = v.crds[i];
		return *this;
	}
	// add assign operator
	fvec<T,n>& operator += (const fvec<T,n>& v)
	{
		for (unsigned i=0; i<n; ++i)
			crds[i] += v.crds[i];
		return *this;
	}
	// give << operator access to protected members
	friend ostream& operator << (ostream&, const fvec<T,n>&);
};

// implement << operator
template <typename T, unsigned n>
ostream& operator << (ostream& os, const fvec<T,n>& v) {
	for (unsigned i=0; i<n; ++i) {
		if (i > 0)
			os << ", ";
		os << v.crds[i];
	}
	return os;
}

void test_template()
{
	fvec<double,3> vd(3.0);
	fvec<float,4> vf(1.0);
}

template <int i>
struct fibonacci
{
	static const int value = fibonacci<i-1>::value+
		                     fibonacci<i-2>::value;
};
template <>
struct fibonacci<0>
{
	static const int value = 1;
};
template <>
struct fibonacci<1>
{
	static const int value = 1;
};

void tt()
{
	int a[] = { 1,2,3,4,5 };
	int b=1, c=2, s;
	s = c += a[3]*!--b^c|a[1]&a[2]+2-1;
}

void ds_test()
{
	// construct vec u
	vec u(3,1.0);
	{
		// copy construct v
		vec v = u;
		// assign to u
		u = v;
		// destruct v because
		// it goes out of scope
	}
	// copy construct v
	vec w(u);
	// destruct u and w in
	// arbitrary order
	std::cout <<  "fibonacci(5)=" << fibonacci<5>::value << std::endl;
	std::cout <<  "fibonacci(6)=" << fibonacci<6>::value << std::endl;
	std::cout <<  "fibonacci(7)=" << fibonacci<7>::value << std::endl;
	std::cout <<  "fibonacci(8)=" << fibonacci<8>::value << std::endl;
	std::cout <<  "fibonacci(9)=" << fibonacci<9>::value << std::endl;
	std::cout <<  "fibonacci(10)=" << fibonacci<10>::value << std::endl;
}

// array of 3 pointers to int
typedef int* Arr_of_ptrs[3];
// pointer to array with 3 elements
typedef int (*Ptr2arr)[3];
// use of array pointers
void test_array_pointers()
{
	int a[3] = { 1, 2, 3 };
	int* ap[3] = { a,a+1,a+2 };
	Arr_of_ptrs aP = { ap[1], ap[0], ap[2] };
	int (*pa)[3] = &a;
	Ptr2arr pA = pa;
}

// some example function
int round(float v) { return (int)v; }
// pointer to int function with float argument
typedef int (*Func)(float);
// use of function pointer type
void use_func(Func f) {
	cout << f(5.0f) << endl;
}
// use of function pointer directly
void use_func_2(int (*f)(float)) {
	cout << f(5.0f) << endl;
}

#define ONLY_TREE

#include <vector>

using namespace std;

class node
{
protected:
#ifdef ONLY_TREE
	/// store node at incoming edge
	node* parent;
#else
	/// store nodes at incoming edges
	std::vector<node*> parents;
#endif
	/// store nodes at outgoing edges
	std::vector<node*> children;
public:
	// access to children (similar for parents)
	unsigned get_nr_children() const {
		return children.size();
	}
	node* get_child(int loc) const {
		return children[loc];
	}
	int find_child(node* n) const {
		unsigned i;
		for (i=0; i<get_nr_children(); ++i)
			if (get_child(i) == n)
				return i;
		return -1;
	}
	bool is_child(node* n) const {
		return find_child(n) != -1;
	}
	void append_child(node* n) { 
		children.push_back(n); 
	}
	void insert_child(node* n, int loc) { 
		children.insert(children.begin()+loc,n); 
	}
	void remove_child(int loc) {
		children.erase(children.begin()+loc);
	}
};

#include <deque>

void breadth_first(node* T)
{
	// store nodes on tree level in deque
	deque<node*> Q;
	// sort in root node
	Q.push_back(T);
	while (!Q.empty()) {
		// get node from beginning of deque
		node* N = Q.front();
		Q.pop_front();
		
		// visit node N here
		
		// append children to the end
		unsigned i;
		for (i=0; i<N->get_nr_children();++i)
			Q.push_back(N->get_child(i));
	}
}

void depth_first(node* N)
{
	// visit node N here

	unsigned i;
	for (i=0; i<N->get_nr_children();++i)
		depth_first(N->get_child(i));
}


