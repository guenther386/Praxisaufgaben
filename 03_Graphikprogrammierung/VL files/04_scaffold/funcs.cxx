#include <iostream>
using namespace std;
// computes n*(n-1)*...*2*1
int faculty(int n)
{
	if (n == 0)
		return 1;
	return n*faculty(n-1);
}
// another implementation with ?:-operator
int fac(int n) { return n?n*fac(n-1):1; }
// function without return value and default argument
void show_list(unsigned n, float* L, char sep = ',')
{
	unsigned i;
	for (i=0; i<n; ++i) {
		if (i>0) cout << sep << ' ';
		cout << L[i];
	}
	cout << endl;
}
// the function can be called with or without 3rd 
void test_show_list()
{
	float L[] = { 1.1f, 2.2f, 3.3f, 4.4f };
	show_list(4,L);        // prints "1.1, 2.2, 3.3, 4.4"
	show_list(3,L+1,';');  // prints "2.2; 3.3; 4.4"
}
