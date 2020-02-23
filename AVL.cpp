#include <iostream>

#include <fstream>
#include <istream>
#include <algorithm>

#include <vector>
#include <queue>
#include <string>

using namespace std;



/*

== RawNode<T>(key, leftChildIndex, rightChildIndex) ==
Input nodes from command line.

bool leftExists()
bool rightExists()

*/


template<typename T>
class RawNode {

public:

	T key = 0;
	int leftChildIndex = -1;
	int rightChildIndex = -1;

	RawNode<T>(T k = 0, int l = -1, int r = -1) {
		key = k;
		leftChildIndex = l;
		rightChildIndex = r;
	}

	bool leftExists() {
		return leftChildIndex != -1;
	}

	bool rightExists() {
		return rightChildIndex != -1;
	}

};




/*

== Node<T>(key, [leftChildPointer = nullptr, rightChildPointer = nullptr, index = -1]) ==
== Node<T>(key, [index = -1]) ==

bool leftExists()
bool rightExists()

*/


template<typename T>
class Node {

public:

	T key = 0;
	int height = 1;
	int absoluteIndex = -1;

	Node<T>* leftChild = nullptr;
	Node<T>* rightChild = nullptr;

	Node(T k, Node<T> * leftChildPointer = nullptr, Node<T> * rightChildPointer = nullptr, int index = -1) {
		key = k;
		leftChild = leftChildPointer;
		rightChild = rightChildPointer;
		absoluteIndex = index;
	}

	Node(int k, int index = -1) {
		key = k;
		absoluteIndex = index;
	}

	bool leftExists() {
		return leftChild != nullptr;
	}

	bool rightExists() {
		return rightChild != nullptr;
	}

};


/*

== AVL<T>() ==
== AVL<T>(vector<RawNode<T>*> * inputTree) ==

Node<T> * root()
size_t size()

int balance(Node<T>* v)

void insert(int k)
void remove(int k)
Node<T>* search(int k)

Node<T>* rotateLeft(Node<T>* v)
Node<T>* rotateRight(Node<T>* v)

enum traversalType { preOrder, inOrder, postOrder};
vector<RawNode<T>*> traverse([type = postOrder])



*/

template<typename T>
class AVL {

public:

	// Empty Constructor
	AVL() {

	}

	// Constructor for Input Nodes
	AVL(vector<RawNode<T>*> tree) {
		
		inputTree = tree;

		if (inputTree.empty()) {
			return;
		}

		size = inputTree.size();

		root = new Node<T>((T)inputTree[0]->key, 0);
		initDFS(root);

		calculateHeights();

	}

	// Tree properties
	Node<T>* root = nullptr;
	size_t size = 0;

private:
	
	// Temporary private variables
	vector<RawNode<T>*> inputTree;
	vector<RawNode<T>*> outputTree;


	// Recursive DFS RawNode to Node converter
	void initDFS(Node<T>* v) {

		if (inputTree[v->absoluteIndex]->leftExists()) {
			auto i = inputTree[v->absoluteIndex]->leftChildIndex;
			v->leftChild = new Node<T>(inputTree[i]->key, i);
			initDFS(v->leftChild);
		}
		else {
			v->leftChild = nullptr;
		}

		if (inputTree[v->absoluteIndex]->rightExists()) {
			auto i = inputTree[v->absoluteIndex]->rightChildIndex;
			v->rightChild = new Node<T>(inputTree[i]->key, i);
			initDFS(v->rightChild);
		}
		else {
			v->rightChild = nullptr;
		}

	}



private:

	// Recalculate heights
	void calculateHeights() {
		if (root == nullptr) {
			return;
		}

		heightDFS(root);
	}

	// Recursive height calculation
	void heightDFS(Node<T>* v) {

		if (v->leftExists()) {
			heightDFS(v->leftChild);
		}

		if (v->rightExists()) {
			heightDFS(v->rightChild);
		}

		updateHeight(v);

	}

	int leftHeight(Node<T>* v) {
		if (v->leftExists()) {
			return v->leftChild->height;
		} else {
			return 0;
		}
	}

	int rightHeight(Node<T>* v) {
		if (v->rightExists()) {
			return v->rightChild->height;
		} else {
			return 0;
		}
	}

	void updateHeight(Node<T>* v) {
		v->height = max(leftHeight(v), rightHeight(v)) + 1;
	}

public:

	// Balance of node
	int balance(Node<T>* v) {

		if (v == nullptr) {
			return 0;
		}

		int l = 0;
		int r = 0;

		if (v->leftExists()) {
			l = v->leftChild->height;
		}

		if (v->rightExists()) {
			r = v->rightChild->height;
		}

		return r - l;
	}


	Node<T>* rotateLeft(Node<T>* v) {

		if (v == nullptr) {
			return nullptr;
		}

		Node<T>* u = v->rightChild;
		v->rightChild = u->leftChild;
		u->leftChild = v;

		updateHeight(v);
		updateHeight(u);

		return u;

	}

	Node<T>* rotateRight(Node<T>* v) {

		if (v == nullptr) {
			return nullptr;
		}

		Node<T>* u = v->leftChild;
		v->leftChild = u->rightChild;
		u->rightChild = v;

		updateHeight(v);
		updateHeight(u);

		return u;
	}

	// Does the balancing
	Node<T>* toBalance(Node<T>* v) {

		if (v == nullptr) {
			return nullptr;
		}

		updateHeight(v);

		if (balance(v) > 1) {
			if (balance(v->rightChild) < 0) {
				v->rightChild = rotateRight(v->rightChild);
			}
			return rotateLeft(v);
		}

		if (balance(v) < -1) {
			if (balance(v->leftChild) > 0) {
				v->leftChild = rotateLeft(v->leftChild);
			}
			return rotateRight(v);
		}

		return v;

	}

	// Traversal
	enum traversalType { preOrder, inOrder, postOrder};

	vector<RawNode<T>*> traverse(traversalType type = postOrder) {

		queue<Node<T>*> q;
		q.push(root);

		int counter = 1;
		while (!q.empty()) {

			Node<T>* v = q.front();
			q.pop();

			int leftIndex = 0;
			int rightIndex = 0;

			if (type == preOrder) {
				outputTree.push_back(new RawNode<T>(v->key, leftIndex, rightIndex));
				if (v->leftExists()) { q.push(v->leftChild); leftIndex = ++counter; }
				if (v->rightExists()) { q.push(v->rightChild); rightIndex = ++counter; }
			}

			if (type == inOrder) {
				if (v->leftExists()) { q.push(v->leftChild); leftIndex = ++counter;}
				outputTree.push_back(new RawNode<T>(v->key, leftIndex, rightIndex));
				if (v->rightExists()) { q.push(v->rightChild); rightIndex = ++counter; }
			}

			if (type == postOrder) {
				if (v->leftExists()) { q.push(v->leftChild); leftIndex = ++counter; }
				if (v->rightExists()) { q.push(v->rightChild); rightIndex = ++counter; }
				outputTree.push_back(new RawNode<T>(v->key, leftIndex, rightIndex));
			}

		}

		return outputTree;

	}

public:

	void insert(int k) {
		root = insert(root, k);
	}

	void remove(int k) {
		root = remove(root, k);
	}

	Node<T>* search(int k) {
		return search(root, k);
	}

private:
	Node<T>* insert(Node<T>* n, int k) {

		if (n == nullptr) {
			size += 1;
			return new Node<T>(k, nullptr, nullptr, size);
		}

		// Left
		if (k < n->key) {
			n->leftChild = insert(n->leftChild, k);
		}
		else {
			// Right
			n->rightChild = insert(n->rightChild, k);
		}

		return toBalance(n);

	}


	Node<T>* remove(Node<T>* n, int k) {

		if (n == nullptr) {
			return nullptr;
		}

		if (k != n->key) {

			// Left
			if (k < n->key) {
				n->leftChild = remove(n->leftChild, k);
			}
			else {
				// Right
				n->rightChild = remove(n->rightChild, k);
			}

		} else {

			size -= 1;

			// If leaf
			if (!(n->leftExists()) && !(n->rightExists())) {
				// Removed
				return nullptr;
			}

			// If not left
			if (!n->leftExists()) {

				// Swap Right
				n = n->rightChild;

			} else {

				// Find the rightest
				Node<T>* rightest = n->leftChild;
				while (rightest->rightExists()) {
					rightest = rightest->rightChild;
				}

				// Change key, remove
				n->key = rightest->key;
				n->leftChild = remove(n->leftChild, rightest->key);

			}

		}

		return toBalance(n);

	}

	Node<T>* search(Node<T>* n, int k) {

		if (n == nullptr) {
			return nullptr;
		}

		if (k == n->key) {
			return n;
		}

		if (k < n->key) {
			return search(n->leftChild, k);
		}
		else {
			return search(n->rightChild, k);
		}

	}

};



template<typename T>
class BST {


	// Tree properties
	Node<T>* root = nullptr;
	size_t size = 0;


public:

	// Empty Constructor
	BST() {

	}

	// Constructor for Input Nodes
	BST(vector<RawNode<T>*> tree) {

		inputTree = tree;

		if (inputTree.empty()) {
			return;
		}

		size = inputTree.size();

		root = new Node<T>((T)inputTree[0]->key, 0);
		initDFS(root);

		calculateHeights();

	}

protected:


	// Temporary protected variables
	vector<RawNode<T>*> inputTree;
	vector<RawNode<T>*> outputTree;


	// Recursive DFS RawNode to Node converter
	void initDFS(Node<T>* v) {

		if (inputTree[v->absoluteIndex]->leftExists()) {
			auto i = inputTree[v->absoluteIndex]->leftChildIndex;
			v->leftChild = new Node<T>(inputTree[i]->key, i);
			initDFS(v->leftChild);
		}
		else {
			v->leftChild = nullptr;
		}

		if (inputTree[v->absoluteIndex]->rightExists()) {
			auto i = inputTree[v->absoluteIndex]->rightChildIndex;
			v->rightChild = new Node<T>(inputTree[i]->key, i);
			initDFS(v->rightChild);
		}
		else {
			v->rightChild = nullptr;
		}

	}


public:

	void insert(int k) {
		if (exists(k)) {
			return;
		}
		root = insert(root, k);
	}

	void remove(int k) {
		if (!exists(k)) {
			return;
		}
		root = remove(root, k);
	}

	Node<T>* search(T k) {
		return search(root, k);
	}

	int next(int key) {
		Node<T>* t = next(root, key);
		return (t != nullptr) ? t->key : INT32_MIN;
	}

	int prev(int key) {
		Node<T>* t = prev(root, key);
		return (t != nullptr) ? t->key : INT32_MIN;
	}

	bool exists(T key) {
		return search(key) != nullptr;
	}

	int height() {
		return root->height;
	}

	// Balance of node
	int balance(Node<T>* v) {

		if (v == nullptr) {
			return 0;
		}

		int l = 0;
		int r = 0;

		if (v->leftExists()) {
			l = v->leftChild->height;
		}

		if (v->rightExists()) {
			r = v->rightChild->height;
		}

		return r - l;
	}

protected:

	// Recalculate heights
	void calculateHeights() {
		if (root == nullptr) {
			return;
		}

		heightDFS(root);
	}

	// Recursive height calculation
	void heightDFS(Node<T>* v) {

		if (v->leftExists()) {
			heightDFS(v->leftChild);
		}

		if (v->rightExists()) {
			heightDFS(v->rightChild);
		}

		updateHeight(v);

	}

	int leftHeight(Node<T>* v) {
		if (v->leftExists()) {
			return v->leftChild->height;
		}
		else {
			return 0;
		}
	}

	int rightHeight(Node<T>* v) {
		if (v->rightExists()) {
			return v->rightChild->height;
		}
		else {
			return 0;
		}
	}

	void updateHeight(Node<T>* v) {
		v->height = max(leftHeight(v), rightHeight(v)) + 1;
	}


	Node<T>* insert(Node<T>* n, int k) {

		if (n == nullptr) {
			size += 1;
			return new Node<T>(k, nullptr, nullptr, size);
		}

		// Left
		if (k < n->key) {
			n->leftChild = insert(n->leftChild, k);
		} else {
			// Right
			n->rightChild = insert(n->rightChild, k);
		}

		return n;

	}


	Node<T>* remove(Node<T>* n, int k) {

		if (n == nullptr) {
			return nullptr;
		}

		if (k != n->key) {

			// Left
			if (k < n->key) {
				n->leftChild = remove(n->leftChild, k);
			}
			else {
				// Right
				n->rightChild = remove(n->rightChild, k);
			}

		}
		else {

			size -= 1;

			// If leaf
			if (!(n->leftExists()) && !(n->rightExists())) {
				// Removed
				return nullptr;
			}

			// If not left
			if (!n->leftExists()) {

				// Swap Right
				n = n->rightChild;

			}	else  {

				// Find the rightest
				Node<T>* rightest = n->leftChild;
				while (rightest->rightExists()) {
					rightest = rightest->rightChild;
				}

				// Change key, remove
				n->key = rightest->key;
				n->leftChild = remove(n->leftChild, rightest->key);

			}

		}

		return n;

	}

	Node<T>* search(Node<T>* n, T k) {

		if (n == nullptr) {
			return nullptr;
		}

		if (k == n->key) {
			return n;
		}

		if (k < n->key) {
			return search(n->leftChild, k);
		}
		else {
			return search(n->rightChild, k);
		}

	}


	Node<T>* next(Node<T>* n, int key) {

		Node<T>* t = n;
		Node<T>* next = nullptr;

		while (t != nullptr) {
			if (key < t->key) {
				next = t;
				t = t->leftChild;
			} else {
				t = t->rightChild;
			}
		}

		return next;

	}

	Node<T>* prev(Node<T>* n, int key) {

		Node<T>* t = n;
		Node<T>* prev = nullptr;

		while (t != nullptr) {
			if (key <= t->key) {
				t = t->leftChild;
			}	else {
				prev = t;
				t = t->rightChild;
			}
		}

		return prev;

	}


public:

	// Traversal
	enum traversalType { preOrder, inOrder, postOrder };

	vector<RawNode<T>*> traverse(traversalType type = postOrder) {

		queue<Node<T>*> q;
		q.push(root);

		int counter = 1;
		while (!q.empty()) {

			Node<T>* v = q.front();
			q.pop();

			int leftIndex = 0;
			int rightIndex = 0;

			if (type == preOrder) {
				outputTree.push_back(new RawNode<T>(v->key, leftIndex, rightIndex));
				if (v->leftExists()) { q.push(v->leftChild); leftIndex = ++counter; }
				if (v->rightExists()) { q.push(v->rightChild); rightIndex = ++counter; }
			}

			if (type == inOrder) {
				if (v->leftExists()) { q.push(v->leftChild); leftIndex = ++counter; }
				outputTree.push_back(new RawNode<T>(v->key, leftIndex, rightIndex));
				if (v->rightExists()) { q.push(v->rightChild); rightIndex = ++counter; }
			}

			if (type == postOrder) {
				if (v->leftExists()) { q.push(v->leftChild); leftIndex = ++counter; }
				if (v->rightExists()) { q.push(v->rightChild); rightIndex = ++counter; }
				outputTree.push_back(new RawNode<T>(v->key, leftIndex, rightIndex));
			}

		}

		return outputTree;

	}

};
