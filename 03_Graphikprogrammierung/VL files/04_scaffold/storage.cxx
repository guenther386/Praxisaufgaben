#include <iostream>

using namespace std;

int global_i = 7;

struct id_type
{
	static int static_i;
	int my_i;
	id_type() {
		my_i = ++static_i;
	}
};

int id_type::static_i = 0;

void storage_test()
{
	int local_i = 7;
	id_type local_id;
	id_type* heap_id = new id_type();
	id_type* heap_ids = new id_type[10];
	// do something
	delete [] heap_ids;
	delete heap_id;
}