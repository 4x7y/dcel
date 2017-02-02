#ifndef GEO_BTREE_HPP
#define GEO_BTREE_HPP

#include <iostream>
using std::cout;

namespace geo
{
std::vector<int> ar;

template<class _Ty> class BinaryBalanceTreeTree;

template<class _Ty>
class Node {
public:

	Node() { left = right = NULL; }
	Node(const T& el, Node *l = 0, Node *r = 0) {

		key = el; left = l; right = r;
	}
	T key;

	Node *left, *right;
};

template <class _Ty>
class BinaryBalanceTree
{
public:
	BinaryBalanceTree() { root = 0; }
	~BinaryBalanceTree() { clear(); }
	void clear() { clear(root); root = 0; }
	bool isEmpty() { return root == 0; }
	void inorder() { inorder(root); }
	void insert(const _Ty& el);
	void visit(Node<_Ty> * p);
	int height() { return height(root); }
	void balance(_Ty data[], int first, int last);
	void display() { display(root, 1); }
	void moveDown(_Ty data[], int first, int last);
	_Ty* search(const _Ty& el) const { return search(root, el); }
	void deleteByMerging(Node<_Ty>*&);
	void findAndDeleteByMerging(const _Ty&);

protected:
	Node<_Ty> *root;

	void clear(Node<_Ty> *p);
	void inorder(Node<_Ty> *p);
	int largest(Node<_Ty> *p);
	int height(Node<_Ty> *p);
	void display(Node<_Ty> *ptr, int level);
	_Ty* search(Node<_Ty>*, const _Ty&) const;
};

template<class  _Ty>
void BinaryBalanceTree<_Ty>::clear(Node<_Ty> *p)
{
	if (p != 0) {
		clear(p->left);
		clear(p->right);
		delete p;
	}
}

template<class  _Ty>
void BinaryBalanceTree<_Ty>::inorder(Node<_Ty> *p) {
	//TO DO! This is for an inorder tree traversal!

	if (p != 0)
	{
		inorder(p->left);
		visit(p);
		inorder(p->right);
	}

}

template<class _Ty>
void BinaryBalanceTree<_Ty>::insert(const T &el) {
	Node<_Ty> *p = root, *prev = 0;
	while (p != 0) {
		prev = p;
		if (p->key < el)
			p = p->right;
		else
			p = p->left;
	}
	if (root == 0)
		root = new Node<_Ty>(el);
	else if (prev->key<el)
		prev->right = new Node<_Ty>(el);
	else
		prev->left = new Node<_Ty>(el);
}


template<class  _Ty>
void BinaryBalanceTree<_Ty>::visit(Node<_Ty> * p) {
	std::cout << p->key << ' ';
	ar.push_back(p->key);
}


template<class  _Ty>
int BinaryBalanceTree<_Ty>::height(Node<_Ty> *p) {
	int left, right;

	if (p == NULL)
		return 0;
	left = height(p->left);
	right = height(p->right);
	if (left > right)
		return left + 1;
	else
		return right + 1;
}

template<class  _Ty>
void BinaryBalanceTree<_Ty>::moveDown(T data[], int first, int last) {
	int largest = 2 * first + 1;
	while (largest <= last) {
		if (largest < last && data[largest] < data[largest + 1])
			largest++;
		if (data[first] < data[largest]) {
			swap(data[first], data[largest]);
			first = largest;
			largest = 2 * first + 1;
		}
		else largest = last + 1;
	}
}

template<class  _Ty>
void BinaryBalanceTree<_Ty>::balance(T data[], int first, int last) {
	if (first <= last) {
		int middle = (first + last) / 2;
		insert(data[middle]);
		balance(data, first, middle - 1);
		balance(data, middle + 1, last);
	}

}


template<class  _Ty>
void BinaryBalanceTree<_Ty>::display(Node<_Ty> *ptr, int level)
{
	int i;
	if (ptr != NULL)
	{
		display(ptr->right, level + 1);
		cout << endl;
		if (ptr == root)
			cout << "Root -> ";
		for (i = 0; i < level && ptr != root; i++)
			cout << "        ";
		cout << ptr->key;
		display(ptr->left, level + 1);
	}
}

template<class  _Ty>
_Ty* BinaryBalanceTree<_Ty>::search(Node<_Ty>* p, const T& el) const {
	while (p != 0)
		if (el == p->key)
			return &p->key;
		else if (el < p->key)
			p = p->left;
		else
			p = p->right;
	return 0;
}


template<class  _Ty>
void BinaryBalanceTree<_Ty>::deleteByMerging(Node<_Ty>*& node) {
	Node<_Ty> *tmp = node;
	if (node != 0) {
		if (!node->right)
			node = node->left;
		else if (node->left == 0) node = node->right;
		else {
			tmp = node->left;
			while (tmp->right != 0)
				tmp = tmp->right;
			tmp->right =
				node->right;
			tmp = node;
			node = node->left;
		}
		delete tmp;
	}
}

template<class  _Ty>
void BinaryBalanceTree<_Ty>::findAndDeleteByMerging(const T& el) {
	Node<_Ty> *node = root, *prev = 0;
	while (node != 0) {
		if (node->key == el)
			break;
		prev = node;
		if (el < node->key)
			node = node->left;
		else node = node->right;
	}
	if (node != 0 && node->key == el)
		if (node == root)
			deleteByMerging(root);
		else if (prev->left == node)
			deleteByMerging(prev->left);
		else deleteByMerging(prev->right);
	else if (root != 0)
		cout << "element" << el << "is not in the tree\n";
	else cout << "the tree is empty\n";
}

} // namespace geo


#endif /* GEO_BTREE_HPP */