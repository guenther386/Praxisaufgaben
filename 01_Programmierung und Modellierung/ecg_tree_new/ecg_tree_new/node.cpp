#include "node.h"
#include <iostream>
#include <sstream>
#include <stack>

int node::node_id = 0;

node::node(std::string name){
	node_id++;
	name = name;
}

node::node(){
	node_id++;
	std::stringstream str_sm;
	str_sm << node_id;
	std::string node_id_string = str_sm.str();
	name = "node_" + node_id_string;
}

 std::string node::get_name() const{
	return name;
}
void node::set_name(std::string new_name){
	name = new_name;
}
 int node::get_nr_children() const{
	return child.size();
}
node* node::get_child(int i) const{
	return child[i];
}
void node::add_child(node *c){
	if (c)
		child.push_back(c);
}

node* create_complete_tree(int nr_child_nodes, int tree_depth){
	if (tree_depth == 0) {
		return NULL;
	} 
	else {
		node *n = new node();
		for (int i = 0; i < nr_child_nodes; i++) {
			n->add_child(create_complete_tree(nr_child_nodes, tree_depth - 1));
		}
		return n;
	}
}

void operator << (std::ostream& str, node *n){
	n->print_it(str);
}

node::~node(){
	std::cout << "enter ~node() of \"" << name << "\"" << std::endl;
	for (unsigned int i = 0; i < child.size(); i++) {
		delete child[i];
	}
	std::cout << "leave ~node() of \"" << name << "\"" << std::endl;
}

void node::print_it(std::ostream& str){
	std::stack<node*> stack;
	std::stack<int> depth;
	std::cout << name << std::endl;
	for (int i = 0; i < get_nr_children(); i++){
		stack.push(child[i]);
		depth.push(1);
	}
	while (!stack.empty()) {
		node* n = stack.top();
		int d = depth.top();
		for (int i = 0; i < d; i++){
			str << "    ";
		}
		str << n->get_name() << std::endl;
		stack.pop();
		depth.pop();
		for (int i = 0; i < n->get_nr_children(); i++){
			stack.push(n->child[i]);
			depth.push(d + 1);
		}
	}
}

void node::print(std::ostream& str, int depth){
	for (int i = 0; i < depth; i++) {
		str << "    ";
	}
	str << name << std::endl;
	for (int i = 0; i < get_nr_children(); i++) {
		child[i]->print(str, depth + 1);
	}
}
