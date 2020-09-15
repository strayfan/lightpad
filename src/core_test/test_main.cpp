
#include <iostream>
#include "core/rbtree.h"

using namespace lightpad::core;
using namespace std;

struct node_int_val : public rbtree_node_base
{
	int val;
};

template<typename T>
class rbtree_int_op : public rbtree_op_base<T>
{

};

class rbtree_int_impl : public rbtree_base<node_int_val, rbtree_int_op>
{
public:
};

int main(int args, char** argv)
{
	rbtree_int_impl tree;
	return 0;
}