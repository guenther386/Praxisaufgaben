#include <iostream>

// the following allows to skip the std:: prefix
using namespace std;
// if declared with void, no return is needed
int main(int argc, char** argv)
{
	// declare variable of integer type
	int i;
	// iterate variable from 0 to argc-1
	for (i=0; i<argc; ++i) {
		// print " with backshlash or as single char
		cout << "argv[" << i << "] = \""
			 << argv[i] << '"' << endl;
	}
	// two successive strings are concatenated
	// umlauts need to be specified in hexadecimal
	cout << "\ndr\x81" "cke <Return>" << endl;
	// read one character from input string
	cin.get();
	return 0;
}
