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

};

class Node {
public:
    Node* next = nullptr;
    int key = 0;

    Node(Node* next, int key){
        this->next = next;
        this->key = key;
    }
};

class LinkedList {
public:
    Node* root = nullptr;

    void add(int key){
        if (root == nullptr) {
            root = new Node(nullptr, key);
        } else {
            root = new Node(root, key);
        }
    }

    // O(n^2)
    // Вставками
    void sort(){
        if (root == nullptr || root->next == nullptr)
            return;

        // Со второго

        // Правая граница отсортированной части
        Node* prev_to_insert = root;
        // То, что хотим вставить в отсортированную часть
        Node* to_insert = root->next;

        // Начиная со второго, проходимся
        while (to_insert != nullptr) {
            // Определяем место, куда будем вставлять первый элемент > уже отсортированной части
            Node* current = root;
            Node* previous = nullptr;
            while (current->key <= to_insert->key && current->next != to_insert) {
                previous = current;
                current = current->next;
            }

            // Меняем правую границу слева?
            if (current->next == to_insert) {
                if (current->key <= to_insert->key) {
                    prev_to_insert = to_insert;
                    to_insert = to_insert->next;
                    continue;
                } else {
                    // Отдельная обработка ситуации когда: 3 | 2
                    Node* temp = new Node(to_insert->next, to_insert->key);
                    temp->next = root;
                    root = temp;
                    Node* to_delete = prev_to_insert->next;
                    prev_to_insert->next = prev_to_insert->next->next;
                    to_insert = to_insert->next;
                    delete to_delete;
                    continue;
                }
            }

            // Скопировали
            Node* temp = new Node(to_insert->next, to_insert->key);

            //
            // Вставляем слева
            //
            // previous - после которого хотим вставить
            // current - первый, который больше
            if (previous == nullptr) {
                temp->next = root;
                root = temp;
            } else {
                previous->next = temp;
                temp->next = current;
            }

            Node* to_delete = prev_to_insert->next;

            // Удаляем из основной части (правой)
            prev_to_insert->next = prev_to_insert->next->next;

            to_insert = to_insert->next;


            delete to_delete;

        }


    }

};

int main() {
    ios_base::sync_with_stdio(false);
    // ======================
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // ====================== */

    HashSet<int> hashSet;
    LinkedList linkedList;

    int n;
    cin >> n;

    if (n == 0) {
        cout << "Empty list";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        linkedList.add(k);
    }


    // Reverse

    Node* previous = nullptr;
    Node* current = linkedList.root;

    while (current != nullptr) {
        Node* next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    linkedList.root = previous;


    // Delete

    previous = nullptr;
    current = linkedList.root;

    while (current != nullptr) {
        if (hashSet.exists(current->key)) {
            Node* next = current->next;
            delete(current);
            current = next;
            previous->next = current;
        } else {
            hashSet.insert(current->key);
            previous = current;
            current = current->next;
        }
    }


    // Output

    linkedList.sort();

    current = linkedList.root;
    while (current != nullptr) {
        cout << current->key << " ";
        current = current->next;
    }

    return 0;
}