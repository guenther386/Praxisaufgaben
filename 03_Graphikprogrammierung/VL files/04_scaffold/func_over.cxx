#include <iostream>

using namespace std;

void show(int v) {
	cout << "int : " << v;
}
void show(float v) {
	cout << "float : " << v;
}

// implementation for rvalues
void show(const double& v) {
	cout << "const double : " << v;
}
// implementation for lvalues
void show(double& v) {
	cout << "double : " << v;
}

void overload_test()
{
	double d=3;
	// d is lvalue
	show(d); cout << endl;
	// 3.0 is rvalue
	show(3.0); cout << endl;
}
