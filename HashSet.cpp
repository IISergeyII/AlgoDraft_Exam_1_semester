#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

template <typename T>
class HashPair {

public:
    HashPair* next;
    T date;

    HashPair(T d, HashPair* n) {
        date = d;
        next = n;
    }
};

// Множество на хэш таблице,
// Построенной по методу цепочек
// В среднем все действия за O(1)
template <typename T>
class HashSet {

private:
    // Большое простое число M
    const unsigned int M = 115249;
    vector<HashPair<T>*> table;

public:
    HashSet() {
        table.resize(M);
    }

    // Побитовое или в качестве основы хэш функции
    unsigned int hash(unsigned int v) {
        return ((unsigned int)v ^ M) % M;
    }

    bool exists(T v) {
        HashPair<T>* node = table[hash(v)];
        while (node != nullptr) {
            if (node->date == v) {
                return true;
            }
            node = node->next;
        }
        return false;
    }

    void insert(T d) {
        if (exists(d)) {
            return;
        }
        unsigned int h = hash(d);
        auto* t = new HashPair<T>(d, table[h]);
        table[h] = t;
    }


    void remove(T d) {
        unsigned int h = hash(d);
        HashPair<T>* node = table[h];
        HashPair<T>* p_node = nullptr; // Previous node
        while (node != nullptr) {
            if (node->date == d) {
                if (p_node == nullptr) {
                    table[h] = node->next;
                }
                else {
                    p_node->next = node->next;
                    node->next = nullptr;
                }
            }
            p_node = node;
            node = node->next;
        }
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    // ======================
    freopen("set.in", "r", stdin);
    freopen("set.out", "w", stdout);
    // ====================== */

    HashSet<int> a;

//    Пример:
//    insert 2
//    insert 5
//    insert 3
//    exists 2
//    exists 4
//    insert 2
//    delete 2
//    exists 2


    while (!cin.eof()) {
        string t;
        cin >> t;

        int k;
        cin >> k;

        if (t == "insert") {
            a.insert(k);
        }

        if (t == "delete") {
            a.remove(k);
        }
        if (t == "exists") {
            cout << (a.exists(k) ? "true" : "false") << "\n";
        }
    }


    return 0;
}