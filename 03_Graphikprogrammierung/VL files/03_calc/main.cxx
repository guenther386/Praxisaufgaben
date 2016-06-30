#include <stdlib.h>
#include <iostream>

// this method is called when starting the program
int main(int argc, char** argv)
{
	// check if 3 arguments are given
	if (argc != 4) {
		std::cerr << "syntax:\ncalc num op num" << std::endl;
		return -1;
	}
	// declare several variables and initialize them
	int a = atoi(argv[1]), b = atoi(argv[3]), res;
	// switch over first symbol in second argument
	switch (argv[2][0]) {
	case '+' : res = a+b; break;
	case '-' : res = a-b; break;
	case '*' : res = a*b; break;
	default  : std::cerr << "operator '" << argv[2] 
					     << "' unknown" << std::endl;
			   return -1;
	}
	std::cout << "result = " << res << std::endl;
	return 0;
}