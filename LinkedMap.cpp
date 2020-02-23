#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

template <typename T>
class HashPair {

public:
    HashPair* next;

    HashPair* l_next;
    HashPair* l_prev;

    string key;
    T date;

    HashPair(const string& k, T d, HashPair* l_n, HashPair* l_p) {
        key = k;
        date = d;
        l_next = l_n;
        l_prev = l_p;
    }
};


template <typename T>
class LHashMap {

private:
    const unsigned int M = 115249;
    vector<HashPair<T>*> table;

    // Указатель на место для добавления нового элемента
    HashPair<T>* begin = new HashPair<T>("none", "none", nullptr, nullptr);

public:
    LHashMap() {
        table.resize(M);
        begin->l_next = begin;
        begin->l_prev = begin;
    }

    unsigned long long hash(const string& v) {

        unsigned long long hash = 0, p_pow = 1;
        for (char i : v) {
            hash += (i - 'a' + 1) * p_pow;
            p_pow *= M;
        }
        return (unsigned long long) (hash) % M;
    }

    void insert(const string& k, T d) {

        HashPair<T>* f = getVal(k);
        if (f != nullptr) {
            f->date = d;
            return;
        }

        int h = hash(k);
        auto* t = new HashPair<T>(k, d, begin, begin->l_prev);
        begin->l_prev->l_next = t;
        t->next = table[h];
        table[h] = t;
        begin->l_prev = t;
    }

    void remove(string k) {

        int h = hash(k);
        HashPair<T>* node = table[h];
        HashPair<T>* p_node = nullptr;
        while (node != nullptr) {
            if (node->key == k) {

                node->l_next->l_prev = node->l_prev;
                node->l_prev->l_next = node->l_next;

                if (p_node == nullptr) {
                    table[h] = node->next;
                }
                else {
                    p_node->next = node->next;
                    node->next = nullptr;
                }
            }
            p_node = node;
            node = node-> next;
        }

    }

    HashPair<T>* getVal(string k) {
        HashPair<T>* node = table[hash(k)];
        while (node != nullptr) {
            if (node->key == k) {
                return node;
            }
            node = node -> next;
        }
        return nullptr;
    }

    string get(const string& k) {
        HashPair<T>* node = getVal(k);
        return (node == nullptr ? "none" : node->date);
    }

    string prev(const string& k) {
        HashPair<T>* node = getVal(k);
        return (node == nullptr ? "none" : node->l_prev->date);
    }

    string next(const string& k) {
        HashPair<T>* node = getVal(k);
        return (node == nullptr ? "none" : node->l_next->date);
    }

};


int main() {
    ios_base::sync_with_stdio(false);
    // ======================
    freopen("linkedmap.in", "r", stdin);
    freopen("linkedmap.out", "w", stdout);
    // ====================== */

    LHashMap<string> a;

//    Example
//    put zero a
//    put one b
//    put two c
//    put three d
//    put four e
//    get two
//    prev two
//    next two
//    delete one
//    delete three
//    get two
//    prev two
//    next two
//    next four


    while (!cin.eof()) {

        string t, x, v;
        cin >> t;

        if (t == "put") {
            cin >> x >> v;
            a.insert(x, v);
        }

        if (t == "delete") {
            cin >> x;
            a.remove(x);
        }

        if (t == "get") {
            cin >> x;
            cout << a.get(x) << "\n";
        }

        if (t == "prev") {
            cin >> x;
            cout << a.prev(x) << "\n";
        }

        if (t == "next") {
            cin >> x;
            cout << a.next(x) << "\n";
        }

    }

    return 0;
}