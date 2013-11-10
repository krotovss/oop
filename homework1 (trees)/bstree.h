#ifndef BSTREE_H
#define BSTREE_H

template<class T>
class BSTree {
public:
	BSTree() : root_(0), size_(0) {}

	void insert(T key)
	{
		if (has(key))
			return;

		Node* x = root_;
		Node* y = 0;
		Node* z = new Node(key);

		while (x != 0) {
			y = x;
			if (z->key < x->key)
				x = x->left;
			else
				x = x->right;
		}

		z->parent = y;

		if (y == 0)
			root_ = z;
		else if (z->key < y->key)
			y->left = z;
		else
			y->right = z;

		size_++;
	}

	void remove(T key)
	{
		Node* z = search(root_, key);
		if (z == 0)
			return;
		size_--;

		if (z->left == 0)
			transplant(z, z->right);
		else if (z->right == 0)
			transplant(z, z->left);
		else {
			Node* y = minimum(z->right);
			if (y->parent != z) {
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
		}

		delete z;
		z = 0;
	}

	T prev(T key) const
	{
		if (key <= minimum())
			return minimum();
		Node* x = search_x(root_, key);
		if (x == 0)
			return key;
		if (x->key < key)
			return x->key;
		return predecessor(x)->key;
		/*Node* x = search(root_, key);
		return x == 0 ? key : predecessor(x)->key;*/
	}

	T next(T key) const
	{
		if (key >= maximum())
			return maximum();
		Node* x = search_x(root_, key);
		if (x == 0)
			return key;
		if (x->key > key)
			return x->key;
		return successor(x)->key;
		/*Node* x = search(root_, key);
		return x == 0 ? key : successor(x)->key;*/
	}

	T minimum() const
	{
		return minimum(root_)->key;
	}

	T maximum() const
	{
		return maximum(root_)->key;
	}

	bool has(T key) const
	{
		return search(root_, key) != 0;
	}

	bool empty() const
	{
		return root_ == 0;
	}

	size_t size() const
	{
		return size_;
	}

	void clear()
	{
		size_ = 0;
		deep_remove(root_);
	}

	~BSTree()
	{
		clear();
	}
private:
	struct Node {
		T key;
		Node* left;
		Node* right;
		Node* parent;

		Node(T key) : key(key), left(0), right(0), parent(0) {}
		Node(Node* x) : key(x->key), 
			left(x->left), right(x->right), parent(x->parent) {}
	};

	Node* root_;
	size_t size_;

	Node* search(Node* x, T key) const
	{
		while (x != 0 && x->key != key) {
			if (key < x->key)
				x = x->left;
			else
				x = x->right;
		}
		return x;
	}

	Node* search_x(Node* x, T key) const
	{
		Node* z = x;
		while (x != 0 && x->key != key) {
			if (key < x->key) {
				z = x;
				x = x->left;
			}
			else {
				z = x;
				x = x->right;
			}
		}
		return x == 0 ? z : x;
	}

	Node* minimum(Node* x) const
	{
		while (x->left != 0)
			x = x->left;
		return x;
	}

	Node* maximum(Node* x) const
	{
		while (x->right != 0)
			x = x->right;
		return x;
	}

	Node* predecessor(Node* x) const
	{
		if (x->left != 0)
			return maximum(x->left);
		Node* y = x->parent;
		while (y != 0 && x == y->left) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	Node* successor(Node* x) const
	{
		if (x->right != 0)
			return minimum(x->right);
		Node* y = x->parent;
		while (y != 0 && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	void transplant(Node* u, Node* v)
	{
		if (u->parent == 0)
			root_ = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		if (v != 0)
			v->parent = u->parent;
	}

	void deep_remove(Node*& x)
	{
		if (x == 0)
			return;
		deep_remove(x->right);
		deep_remove(x->left);
		delete x;
		x = 0;
	}
};

#endif // BSTREE_H