// declare functions with implementation in different file
extern void test_show_list();
extern void pointer_test(int n);
extern void array_test();
extern void struct_test();
extern void overload_test();
extern void reference_test();
extern void namespace_test();
extern void storage_test();
extern void ds_test();
extern void control_test();

// if arguments are not used, no name has to be specified
int main(int, char**)
{
	test_show_list();
	pointer_test(7);
	array_test();
	struct_test();
	overload_test();
	reference_test();
	storage_test();
	namespace_test();
	ds_test();
	control_test();
	return 0;
}
