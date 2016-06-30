#include <decls.h> // use include paths
#include <iostream>
using namespace std;
// uses some dynamically allocated memory
void pointer_test(int n)
{
	// allocate dynamic memory for array of n integers
	int i, *p_i = new int[n];
	// set array to square of indices (starting with 0)
	for (i=0; i<n; ++i)
		p_i[i] = i*i;
	// set another pointer to 6th array entry (index 5)
	int *p_j = p_i+5;
	cout << "p_i[5]=" << *p_j << endl;
	// deallocate dynamic memory
	delete [] p_i;
}

// illustrates use of arrays and pointers
void array_test()
{
	int i;
	// declare initialized array with 3 entries
	float v[3] = { 1.1f, 2.2f, 3.3f };
	// number of entries results from list of values
	int w[] = { 1,2,3,4 };
	// declare initialized two dimensional array
	double M[2][3] = { { 1,2,3 }, { 4,5,6 } };
	// print one element of array
	cout << "M[0][2]=" << M[0][2] << endl;
	// use address operator & to access 2d array with pointer
	double *p = &M[0][0];
	// print out matrix using post increment operator ++
	for (i=0; i<6; ++i)
		cout << " " << *p++ << ((i%3==2)?"\n":"");
	cout << endl;
}

// illustrates use of struct
void struct_test()
{
	// declare array of two initialized 3d vectors
	Vec3d vs[] = { { 1, -1, 0 }, { 0, 0, 1 } };
	// construct a copy of the first vector
	Vec3d v0 = vs[0];
	// print by accessing members with '.'-operator
	cout << "vs[0] = [" << v0.x << ", " 
		<< v0.y << ", " << v0.z << "]" << endl;
	// use pointer with '->'-operator
	Vec3d *v_ptr = &vs[1];
	cout << "vs[1] = [" << v_ptr->x << ", " 
		 << v_ptr->y << ", " << v_ptr->z << "]" << endl;
}
