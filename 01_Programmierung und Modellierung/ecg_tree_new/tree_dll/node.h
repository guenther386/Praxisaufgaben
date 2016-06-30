#include <iostream>
#include <vector>
#ifdef TREE_DLL_EXPORTS
#define TREE_DLL_API __declspec(dllexport)
#elif TREE_DLL_IMPORTS
#define TREE_DLL_API __declspec(dllimport)
#else
#define TREE_DLL_API
#endif

class node{
public:
	TREE_DLL_API node(std::string name);
	TREE_DLL_API node();
	TREE_DLL_API ~node();
	TREE_DLL_API void print(std::ostream& str, int depth);
	TREE_DLL_API void node::print_it(std::ostream& str);
	TREE_DLL_API std::string get_name()const;
	TREE_DLL_API void set_name(std::string new_name);
	TREE_DLL_API int get_nr_children() const;
	TREE_DLL_API node* get_child(int i) const;
	TREE_DLL_API void node::add_child(node *c);

private:
	std::string name;
	std::vector<node*> child;
	static int node_id;
};

TREE_DLL_API node* create_complete_tree(int nr_child_nodes, int tree_depth);
TREE_DLL_API extern void operator << (std::ostream& str, node *n);