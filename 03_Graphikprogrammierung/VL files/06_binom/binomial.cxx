#include <stdlib.h>
#include <iostream>
#include <string>

// comparison of two implementations to compute binomial coefficients
// according to the recursive rule underlying the Pascal triangle

using namespace std;

// very simple recursive implementation
long long binomial_recursive(int n, int i)
{
	// check for termination of recursion
	if (i == 0 || i == n)
		return 1;
	// perform recursion
	return binomial_recursive(n-1,i-1)+binomial_recursive(n-1,i);
}

// advanced implementation with a statically stored hash 
long long binomial_hash(int n, int i)
{
	// check for boundary conditions
	if (i == 0 || i == n)
		return 1;
	// declare pointer to pointer of hashed values
	// the static declaration is persistent over several
	// calls and initialized to 0 when encountered first
	static long long **row_hash = 0;
	// ensure that array of pointers is allocated
	if (!row_hash) {
		// allocate 100 pointers
		row_hash = new long long*[100];
		// initialize to null pointers
		int j;
		for (j=0; j<100; ++j)
			row_hash[j] = 0;
	}
	// ensure that currently queried row is computed
	if (!row_hash[n]) {
		// if not allocate memory for row
		row_hash[n] = new long long[n+1];
		// compute row entries with recursion
		int j;
		for (j=0; j<=n; ++j)
			row_hash[n][j] = binomial_hash(n-1,j-1)+binomial_hash(n-1,j);
	}
	// return hashed value
	return row_hash[n][i];
}

// function that dispatches call to specific implementation
long long binomial(int n, int i, bool hashed = true)
{
	// check for valid input values
	if (n < 1 || i < 0 || i > n) {
		cerr << "called binomial with invalid arguments n=" << n << ", i=" << i << endl;
		return 0;
	}
	// dispatch to hashed or recursive implementation
	return hashed ? binomial_hash(n,i) : binomial_recursive(n,i);
}


int main(int argc, char** argv)
{
	// check whether first command line argument is "hashed"
	bool hashed = false;
	if (argc > 1)
		if (string(argv[1]) == "hashed") {
			// if so set flag and
			hashed = true;
			// discard first command line arg
			++argv;
			--argc;
		}

	// check for valid number of arguments
	if (argc != 2 && argc != 3) {
		cerr << "usage:\nbinomial [hashed] n [i]" << argc << endl;
		return- 1;
	}
	// convert first argument to integer
	int n = atoi(argv[1]);
	// show first argument
	cout << "n=" << n << endl;
	// if only one argument is provided
	if (argc == 2) {
		// print complete row
		int i;
		for (i=0; i<=n; ++i)
			cout << binomial(n,i,hashed) << " ";
	}
	else {
		// otherwise convert second argument
		int i = atoi(argv[2]);
		// show its value
		cout << "i=" << i << endl;
		// and print binomial coefficient
		cout << binomial(n,i,hashed);
	}
	cout << endl;
	return 0;
}