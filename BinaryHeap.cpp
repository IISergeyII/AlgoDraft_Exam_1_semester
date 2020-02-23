#include <iostream>
#include <vector>

using namespace std;

template <class ArrElements>
class Heap {
    // Двоичная куча для минимума на векторе
    vector<ArrElements> h;


    // Просеивание вниз
    // Используется, когда значение элемента увеличивается
    void siftDown(int i) {
        // left, right - потомки
        // j - индекс наименьшего сына
        int left, right, j;

        while (2*i + 1 < h.size()) {
            left = 2*i + 1;
            right = 2*i + 2;

            // Определение минимального потомка
            // Если i-й элемент меньше сыновей, поддерево уже является кучей
            j = left;
            if (right < h.size() && h[right] < h[left])
                j = right;
            if (h[i] <= h[j])
                break;
            swap(&h[i], &h[j]);
            i = j;
        }
    }

    // Просеивание вверх
    // Если элемент меньше своего отца, то меняем
    void siftUp(int i) {
        while (h[i] < h[(i - 1) / 2]) {
            swap(&h[i], &h[(i -  1) / 2]);
            i = (i - 1) / 2;
        }
    }

    static void swap(ArrElements* a, ArrElements* b) {
        ArrElements tmp = *a;
        *a = *b;
        *b = tmp;
    }



public:

    void insert(ArrElements key) {
        h.push_back(key);
        siftUp(h.size() - 1);
    }

    // В корне находится минимальный элемент
    // Компирование последнего элемента в корень
    // И востановление свойства кучи
    ArrElements extractMin() {
        ArrElements min = h[0];
        h[0] = h[h.size() - 1];
        h.erase(h.begin() + h.size() - 1);

        siftDown(0);
        return min;
    }

};


int main() {

    //---------------------------------------------
    freopen("heap.in", "r", stdin);
    freopen("heap.out", "w", stdout);
    //--------------------------------------------- /*/

    int n;
    cin >> n;

    Heap<int> heap;
    int t;
    for (int i = 0; i < n; ++i) {
        cin >> t;
        heap.insert(t);
    }

    for (int i = 0; i < n; ++i) {
        cout << heap.extractMin() << " ";
    }
    

    return 0;
}