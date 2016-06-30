#include <iostream>

using namespace std;

void control_test()
{
	int a = 0, b = 0, c=0;
	// empty statements are allowed
	while (++a < 10) ;
	// any expression is a statement
	a += 5;
	// the {}-parentheses defines a statement block
	if (a > 9) { a = 0; b += 1; }
	// selection is done by if .. else
	if (a == 0) {
		if (b == 0)
			c = 1;
	}
	else a = 0;
	// or switch
	switch (a) {
		case 0 : a = 1;        // no break ==> go on with next case
		case 1 : a *= 2; break;// break jumps out of switch
		case 2 :
		case 3 : a /= 2;       // no block needed for more statements
				 cout << a << endl;
				 break;        // do the same in case of 2 and 3
		default: a = 0; break; // in any other case
	}
	// while loop is based on one condition-expression
	while (a > 5) {
		--a;
		cout << a << endl;
	}
	// do loop is similar to while but evaluates expression at end
	do {
		--a;
		cout << a << endl;
	} while (a > 0);
	// for loop is defined by init-, condition- and loop-expression
	for (a=0; a<5 && b==0; ++a) {
		if (a == b)
			break; // jumps out of for loop
		else
			if (--b < 0)
				continue; // early looping
		cout << a << endl;
	}
	// the above for loop is equivalent to
	a=0;
	while (a<5 && b==0) {
		if (a == b)
			break; // jumps out of for loop
		else
			if (--b < 0) {
				++a;
				continue; // early looping
			}
		cout << a << endl;
		++a;
	}
}