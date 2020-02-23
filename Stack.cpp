#include <iostream>
#include <vector>

using namespace std;


// Stack на vector
// LIFO - Last In First Out
template <typename T>
class Stack {
    vector<T> stack;

public:

    bool empty() {
        return (stack.empty());
    }

    void push(T elem) {
        stack.push_back(elem);
    }

    T pop() {
        if (!empty()) {
            T res = stack[stack.size() - 1];
            stack.erase(stack.begin() + stack.size() - 1);
            return res;
        }
    }

};


// Свой тип данных для примера
template <typename T>
struct MyType {
    T field1;
    T field2;

    MyType(T t1, T t2) {
        field1 = t1;
        field2 = t2;
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    // ======================
    freopen("stack.in", "r", stdin);
    freopen("stack.out", "w", stdout);
    // ====================== */


    // Пример работы со своим типом данных
    MyType<int> m1(1, 1);
    MyType<int> m2(3, 3);

    Stack<MyType<int>> st;
    st.push(m1);
    st.push(m2);

    while (!st.empty()) {
        cout << st.pop().field1 << " ";
    }

    return 0;
}