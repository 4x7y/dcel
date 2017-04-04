#ifndef GEO_RBTREE_HPP
#define GEO_RBTREE_HPP

#include <iostream>

template<typename ValueT, typename SearchT, class Compare>
class RBTree
{
	typedef enum { RED, BLACK } Color;
	typedef bool(*comp_func)(const ValueT&, const ValueT&);

public:
	struct Node {
		ValueT				value;
		Color				color;
		Node				*leftTree, *rightTree, *parent;

		Node()
			: color(RED)
			, leftTree(nullptr)
			, rightTree(nullptr)
			, parent(nullptr)
		{}

		Node* grandparent() const
		{
			if (parent == nullptr) {
				return nullptr;
			}
			return parent->parent;
		}

		Node* uncle() const
		{
			if (grandparent() == nullptr) {
				return nullptr;
			}

			if (parent == grandparent()->rightTree) {
				return grandparent()->leftTree;
			}
			return grandparent()->rightTree;
		}

		Node* sibling() {
			if (parent->leftTree == this) {
				return parent->rightTree;
			}
			return parent->leftTree;
		}
	};


private:
//public:

	//Node *root, *NIL;
	Compare* comp;

	//bool less(ValueT& left, ValueT& right)
	//{
	//	return comp->less(left, right);
	//}

	void rotate_right(Node* p) {
		Node *gp = p->grandparent();
		Node *fa = p->parent;
		Node *y = p->rightTree;

		fa->leftTree = y;

		if (y != NIL) {
			y->parent = fa;
		}
		p->rightTree = fa;
		fa->parent = p;

		if (root == fa) {
			root = p;
		}
		p->parent = gp;

		if (gp != nullptr) {
			if (gp->leftTree == fa) {
				gp->leftTree = p;
			}
			else {
				gp->rightTree = p;
			}
		}
	}

	void rotate_left(Node *p) {
		if (p->parent == nullptr) {
			root = p;
			return;
		}
		Node *gp = p->grandparent();
		Node *fa = p->parent;
		Node *y = p->leftTree;

		fa->rightTree = y;

		if (y != NIL) {
			y->parent = fa;
		}
		p->leftTree = fa;
		fa->parent = p;

		if (root == fa) {
			root = p;
		}
		p->parent = gp;

		if (gp != nullptr) {
			if (gp->leftTree == fa)
				gp->leftTree = p;
			else
				gp->rightTree = p;
		}
	}

	void inorder(Node *p) const {
		if (p == NIL) {
			return;
		}

		if (p->leftTree) {
			inorder(p->leftTree);
		}

		std::cout << p->value << " ";

		if (p->rightTree) {
			inorder(p->rightTree);
		}
	}

	Node* get_smallest_child(Node *p) const {
		if (p->leftTree == NIL) {
			return p;
		}
		return get_smallest_child(p->leftTree);
	}

	bool delete_child(Node *p, const ValueT& data) {
		if (comp->less(data, p->value)) {
			if (p->leftTree == NIL) {
				return false;
			}
			return delete_child(p->leftTree, data);
		}

		if (comp->less(p->value, data)) {
			if (p->rightTree == NIL) {
				return false;
			}
			return delete_child(p->rightTree, data);
		}

		if (p->rightTree == NIL) {
			delete_one_child(p);
			return true;
		}
		Node *smallest = get_smallest_child(p->rightTree);
		//std::swap(p->value, smallest->value);
		ValueT temp=p->value;
		p->value=smallest->value;
		smallest->value=temp;
		delete_one_child(smallest);

		return true;
	}

	void delete_one_child(Node *p) {
		Node *child = p->leftTree == NIL ? p->rightTree : p->leftTree;
		if (p->parent == nullptr && p->leftTree == NIL && p->rightTree == NIL) {
			p = nullptr;
			root = p;
			return;
		}

		if (p->parent == nullptr) {
			delete  p;
			child->parent = nullptr;
			root = child;
			root->color = BLACK;
			return;
		}

		if (p->parent->leftTree == p) {
			p->parent->leftTree = child;
		}
		else {
			p->parent->rightTree = child;
		}
		child->parent = p->parent;

		if (p->color == BLACK) {
			if (child->color == RED) {
				child->color = BLACK;
			}
			else
				delete_case(child);
		}

		delete p;
	}

	void delete_case(Node *p) {
		if (p->parent == nullptr) {
			p->color = BLACK;
			return;
		}
		if (p->sibling()->color == RED) {
			p->parent->color = RED;
			p->sibling()->color = BLACK;
			if (p == p->parent->leftTree)
				rotate_left(p->sibling());
			else
				rotate_right(p->sibling());
		}
		if (p->parent->color == BLACK && p->sibling()->color == BLACK
			&& p->sibling()->leftTree->color == BLACK && p->sibling()->rightTree->color == BLACK) {
			p->sibling()->color = RED;
			delete_case(p->parent);
		}
		else if (p->parent->color == RED && p->sibling()->color == BLACK
			&& p->sibling()->leftTree->color == BLACK && p->sibling()->rightTree->color == BLACK) {
			p->sibling()->color = RED;
			p->parent->color = BLACK;
		}
		else {
			if (p->sibling()->color == BLACK) {
				if (p == p->parent->leftTree && p->sibling()->leftTree->color == RED
					&& p->sibling()->rightTree->color == BLACK) {
					p->sibling()->color = RED;
					p->sibling()->leftTree->color = BLACK;
					rotate_right(p->sibling()->leftTree);
				}
				else if (p == p->parent->rightTree && p->sibling()->leftTree->color == BLACK
					&& p->sibling()->rightTree->color == RED) {
					p->sibling()->color = RED;
					p->sibling()->rightTree->color = BLACK;
					rotate_left(p->sibling()->rightTree);
				}
			}
			p->sibling()->color = p->parent->color;
			p->parent->color = BLACK;
			if (p == p->parent->leftTree) {
				p->sibling()->rightTree->color = BLACK;
				rotate_left(p->sibling());
			}
			else {
				p->sibling()->leftTree->color = BLACK;
				rotate_right(p->sibling());
			}
		}
	}

	void insert(Node *p, ValueT& data) {
		if (!comp->less(p->value, data)) {
			if (p->leftTree != NIL)
				insert(p->leftTree, data);
			else {
				Node *tmp = new Node();
				tmp->value = data;
				tmp->leftTree = tmp->rightTree = NIL;
				tmp->parent = p;
				p->leftTree = tmp;
				insert_case(tmp);
			}
		}
		else {
			if (p->rightTree != NIL)
				insert(p->rightTree, data);
			else {
				Node *tmp = new Node();
				tmp->value = data;
				tmp->leftTree = tmp->rightTree = NIL;
				tmp->parent = p;
				p->rightTree = tmp;
				insert_case(tmp);
			}
		}
	}

	void insert_case(Node *p) {
		if (p->parent == nullptr) {
			root = p;
			p->color = BLACK;
			return;
		}
		if (p->parent->color == RED) {
			if (p->uncle()->color == RED) {
				p->parent->color = p->uncle()->color = BLACK;
				p->grandparent()->color = RED;
				insert_case(p->grandparent());
			}
			else {
				if (p->parent->rightTree == p && p->grandparent()->leftTree == p->parent) {
					rotate_left(p);
					rotate_right(p);
					p->color = BLACK;
					p->leftTree->color = p->rightTree->color = RED;
				}
				else if (p->parent->leftTree == p && p->grandparent()->rightTree == p->parent) {
					rotate_right(p);
					rotate_left(p);
					p->color = BLACK;
					p->leftTree->color = p->rightTree->color = RED;
				}
				else if (p->parent->leftTree == p && p->grandparent()->leftTree == p->parent) {
					p->parent->color = BLACK;
					p->grandparent()->color = RED;
					rotate_right(p->parent);
				}
				else if (p->parent->rightTree == p && p->grandparent()->rightTree == p->parent) {
					p->parent->color = BLACK;
					p->grandparent()->color = RED;
					rotate_left(p->parent);
				}
			}
		}
	}

	void delete_tree(Node *p) {
		if (!p || p == NIL) {
			return;
		}
		delete_tree(p->leftTree);
		delete_tree(p->rightTree);
		delete p;
	}


	Node* get_smaller(Node* p, const SearchT& value)
	{
		if (comp->less(value, p->value))
		{
			if (p->leftTree == NIL)
			{
				return nullptr;
			}

			return get_smaller(p->leftTree, value);
		}

		if (comp->less(p->value, value))
		{
			if (p->rightTree == NIL)
			{
				return p;
			}

			Node* ps = get_smaller(p->rightTree, value);
			if (ps == nullptr)
			{
				return p;
			}

			return ps;
		}

		return p;
	}

	Node* get_larger(Node* p, const SearchT& value)
	{
		if (comp->less(value, p->value))
		{
			if (p->leftTree == NIL)
			{
				return p;
			}

			Node* pl = get_larger(p->leftTree, value);
			if (pl == nullptr)
			{
				return p;
			}

			return pl;
		}

		if (comp->less(p->value, value))
		{
			if (p->rightTree == NIL)
			{
				return nullptr;
			}

			return get_larger(p->rightTree, value);
		}

		return p;
	}

public:
	Node *root, *NIL;
	RBTree(Compare* cmp = nullptr)
	{
		NIL = new Node();
		NIL->color = BLACK;
		root = nullptr;
		this->comp = cmp;
	}

	~RBTree()
	{
		if (root) {
			delete_tree(root);
		}
		delete NIL;
	}

	void inorder()
	{
		if (root == nullptr) {
			return;
		}
		inorder(root);
	}

	void insert(ValueT& x) {
		if (root == nullptr) {
			root = new Node();
			root->color = BLACK;
			root->leftTree = root->rightTree = NIL;
			root->value = x;
		}
		else {
			insert(root, x);
		}
	}

	bool delete_value(const ValueT& data) {
		return delete_child(root, data);
	}

	bool get_smaller(const SearchT& value, ValueT& smaller)
	{
		Node* p = get_smaller(root, value);

		if (p == nullptr)
		{
			return false;
		}

		smaller = p->value;
		return true;
	}

	bool get_larger(const SearchT& value, ValueT& larger)
	{
		Node* p = get_larger(root, value);

		if (p == nullptr)
		{
			return false;
		}

		larger = p->value;
		return true;
	}
};

#endif