#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

// Как пример хэш будет вычисляеться от строки
template <typename T>
class HashPair {

public:
    HashPair* next;
    string key;
    T date;

    HashPair(const string& k, T d, HashPair* n) {
        key = k;
        date = d;
        next = n;
    }
};

// Ассоциативный массив на хэш таблице,
// построенной по методу цепочек
// В среднем все действия за O(1)
template <typename T>
class HashMap {

private:
    // Большое простое число M
    const unsigned long long M = 115249;
    vector<HashPair<T>*> table;

public:
    HashMap() {
        table.resize(M);
    }

    unsigned long long hash(const string& v) {

        unsigned long long hash = 0, p_pow = 1;
        for (char i : v) {
            hash += (i - 'a' + 1) * p_pow;
            p_pow *= M;
        }
        return (unsigned long long) (hash) % M;
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

    void insert(const string& k, T d) {

        HashPair<T>* f = getVal(k);
        if (f != nullptr) {
            f->date = d;
            return;
        }

        unsigned long long h = hash(k);
        auto* t = new HashPair<T>(k, d, table[h]);
        t->next = table[h];
        table[h] = t;
    }

    void remove(string k) {

        unsigned long long h = hash(k);
        HashPair<T>* node = table[h];
        HashPair<T>* p_node = nullptr;

        while (node != nullptr) {
            if (node->key == k) {
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

};


int main() {
    ios_base::sync_with_stdio(false);
    // ======================
    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);
    // ====================== */

    HashMap<string> a;

//    Example
//    put hello privet
//    put bye poka
//    get hello
//    get bye
//    delete hello
//    get hello


    while (!cin.eof()) {

        string t, k, v;
        cin >> t;

        if (t == "put") {
            cin >> k >> v;
            a.insert(k, v);
        }

        if (t == "delete") {
            cin >> k;
            a.remove(k);
        }

        if (t == "get") {
            cin >> k;
            cout << a.get(k) << "\n";
        }

    }

    return 0;
}