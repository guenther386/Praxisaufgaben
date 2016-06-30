#include "node.h"

int main(){
	node* tree = create_complete_tree(2, 4);
	std::cout << tree;
	return 0;
}