#include <iostream>
#include <vector>

class node{
public:
	node(std::string name);
	node();
	~node();
	void print(std::ostream& str, int depth);
	void node::print_it(std::ostream& str);
	std::string get_name()const;
	void set_name(std::string new_name);
	int get_nr_children() const;
	node* get_child(int i) const;
	void node::add_child(node *c);

private:
	std::string name;
	std::vector<node*> child;
	static int node_id;
};

node* create_complete_tree(int nr_child_nodes, int tree_depth);
extern void operator << (std::ostream& str, node *n);