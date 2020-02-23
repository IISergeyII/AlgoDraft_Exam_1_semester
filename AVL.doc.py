
== RawNode<T>(key, leftChildIndex, rightChildIndex) ==
Input nodes from command line.

bool leftExists()
bool rightExists()

  
  

== Node<T>(key, [leftChildPointer = nullptr, rightChildPointer = nullptr, index = -1]) ==
== Node<T>(key, [index = -1]) ==
Working nodes with pointers.

bool leftExists()
bool rightExists()

  
  
  

== AVL<T>() ==
== AVL<T>(vector<RawNode<T>*> * inputTree) ==
AVL tree.
  
  
Node<T> * root
size_t size

int balance(Node<T>* v)

void insert(int k)
void remove(int k)
Node<T>* search(int k)

Node<T>* rotateLeft(Node<T>* v)
Node<T>* rotateRight(Node<T>* v)

enum traversalType { preOrder, inOrder, postOrder};
vector<RawNode<T>*> traverse([type = postOrder])




== BST<T>() ==
== BST<T>(vector<RawNode<T>*> * inputTree) ==
BST tree.
  
  
Node<T> * root
size_t size

int balance(Node<T>* v)

int prev(int k)
int next(int k)
bool exists(int k)
int height()

void insert(int k)
void remove(int k)
Node<T>* search(int k)

enum traversalType { preOrder, inOrder, postOrder};
vector<RawNode<T>*> traverse([type = postOrder])

