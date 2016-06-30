#include <iostream>
#include <vector>

using namespace std;

void reference_test()
{
	int  i = 7;
	int& i_ref = i;
	++i;
	// this will print 8
	cout << i_ref << endl;
	i_ref *= 2;
	// this will print 16
	cout << i << endl;
}

void pointer_emulation()
{
	int  i = 7;
	int* i_ptr = &i;
	++i;
	// this will print 8
	cout << *i_ptr << endl;
	*i_ptr *= 2;
	// this will print 16
	cout << i << endl;
}

// multiply each vector element by s
void scale(vector<int>& V, int s)
{
	unsigned i;
	for (i=0; i<V.size(); ++i)
		V[i] *= s;
}
// show vector elements as list
void show(const vector<int>& V)
{
	unsigned i;
	for (i=0; i<V.size(); ++i) {
		if (i>0)
			cout << ", ";
		cout << V[i];
	}
}
// split a vector at j-th element into two
// vectors (head and tail), both being
// return values of the function
void split(const vector<int>& V, unsigned j,
		   vector<int>& head, vector<int>& tail)
{
	unsigned i;
	head.clear(); tail.clear();
	for (i=0; i<V.size(); ++i) {
		if (i<j)
			head.push_back(V[i]);
		else
			tail.push_back(V[i]);
	}
}