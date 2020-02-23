#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>

using namespace std;

template <typename T>
class Node {

public:

    T key;

    Node* child1;
    Node* child2;

    Node(T k) {
        key = k;
        child1 = nullptr;
        child2 = nullptr;
    }
};

template <typename T>
class Tree {
    Node<T>* begin = nullptr;
    size_t len = 0;

    Node<T>* search(Node<T>* n, T k) {

        if (n == nullptr) {
            return n;
        }

        if (n->key == k) {
            return n;
        }

        if (k < n->key) {
            return search(n->child1, k);
        } else {
            return search(n->child2, k);
        }

    }

    Node<T>* insert(Node<T>* n, T k) {

        if (n == nullptr) {
            return new Node<T>(k);
        }

        if (k < n->key) {
            n->child1 = insert(n->child1, k);
        } else {
            n->child2 = insert(n->child2, k);
        }

        return n;
    }

    Node<T>* remove(Node<T>* n, T k) {
        if (n == nullptr) {
            return n;
        }

        if (n->key != k) {

            if (k < n->key) {
                n->child1 = remove(n->child1, k);
            }
            else {
                n->child2 = remove(n->child2, k);
            }
        } else {

            int i = 0;
            if (n->child1 != nullptr) { i++; }
            if (n->child2 != nullptr) { i++; }

            if (i != 2) {
                if (n->child1 != nullptr) {
                    n = n->child1;
                }
                else {
                    n = n->child2;
                }
            }
            else {

                Node<T>* min_node = n->child2;
                while (min_node->child1 != nullptr) {
                    min_node = min_node->child1;
                }

                n->key = min_node->key;
                n->child2 = remove(n->child2, n->key);
            }

        }
        return n;
    }

    vector<T> t;

    void inOrderTraversal(Node<T>* v) {
        if (v != nullptr) {
            inOrderTraversal(v->child1);
            t.push_back(v->key);
            inOrderTraversal(v->child2);
        }
    }

public:

    void insert(T k) {
        if (!exists(k)) {
            begin = insert(begin, k);
            len++;
        }

    }

    bool exists(T k) {
        return search(begin, k) != nullptr;
    }

    void remove(T k) {
        if (exists(k)) {
            begin = remove(begin, k);
            len--;
        }
    }

    int size() {
        return len;
    }

    vector<T> traverse() {
        t.resize(0);
        inOrderTraversal(begin);
        return t;
    }

};


template <typename T>
struct HashPair {
    string key;
    Tree<T>* value;

    HashPair* next = nullptr;

    HashPair<T>(string k, T d, HashPair* n) {
        key = k;
        value = new Tree<T>;
        value->insert(d);
        next = n;
    }
};

// Множественное отображение
// Хеш-таблица, в элементах хранятся деревья
template <typename T>
class MHashMap {

private:
    const unsigned int M = 115249;
    vector<HashPair<T>*> table;


public:
    MHashMap() {
        table.resize(M);
    }

    unsigned long long hash(string v) {

        unsigned long long hash = 0, p_pow = 1;
        for (char i : v) {
            hash += (i - 'a' + 1) * p_pow;
            p_pow *= M;
        }
        return (unsigned long long) (hash) % M;
    }

    void insert(string k, T d) {

        HashPair<T>* f = getVal(k);
        if (f != nullptr) {
            f->value->insert(d);
            return;
        }

        int h = hash(k);
        auto* t = new HashPair<T>(k, d, table[h]);
        t->next = table[h];
        table[h] = t;
    }

    void remove(string k, T d) {

        unsigned long long h = hash(k);
        HashPair<T>* node = table[h];
        HashPair<T>* p_node = nullptr;
        while (node != nullptr) {
            if (node->key == k) {

                node->value->remove(d);

                if (node->value->size() == 0) {
                    if (p_node == nullptr) {
                        table[h] = node->next;
                    }
                    else {
                        p_node->next = node->next;
                        node->next = nullptr;
                    }
                    return;
                }
            }
            p_node = node;
            node = node-> next;
        }

    }

    void removeAll(string k) {
        int h = hash(k);
        HashPair<T>* node = table[h];
        HashPair<T>* p_node = nullptr;
        while (node != nullptr) {
            if (node->key == k) {

                if (p_node == nullptr) {
                    table[h] = node->next;
                }
                else {
                    p_node->next = node->next;
                    node->value = nullptr;
                    node->value = nullptr;
                }
                return;
            }
            p_node = node;
            node = node->next;
        }

    }


    HashPair<T>* getVal(string k) {
        HashPair<T>* node = table[hash(k)];
        while (node != nullptr) {
            if (node->key == k) {
                return node;
            }
            node = node->next;
        }
        return nullptr;
    }

    vector<T> get(string k) {
        HashPair<T>* node = getVal(k);
        return (node == nullptr) ? vector<string>() : node->value->traverse();
    }

};


int main() {
    ios_base::sync_with_stdio(false);
    // ======================
    freopen("multimap.in", "r", stdin);
    freopen("multimap.out", "w", stdout);
    // ====================== */

    MHashMap<string> a;

//  Example
//    put a a
//    put a b
//    put a c
//    get a
//    delete a b
//    get a
//    deleteall a
//    get a


    while (!cin.eof()) {

        string t, k, m;
        cin >> t;

        if (t == "put") {
            cin >> k >> m;
            a.insert(k, m);
        }

        if (t == "delete") {
            cin >> k >> m;
            a.remove(k, m);
        }

        if (t == "deleteall") {
            cin >> k;
            a.removeAll(k);
        }

        if (t == "get") {
            cin >> k;
            vector<string> t = a.get(k);
            cout << t.size() << " ";
            for (auto x : t) {
                cout << x << " ";
            }
            cout << "\n";
        }

    }

    return 0;
}