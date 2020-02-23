#include <iostream>

using namespace std;

// Целочисленный право- и левосторонний двоичный поиск
// Только для отсортированного массива
// О(log n)


template <class ArrElements>
class BinarySearch {

public:
    // Поиск самого левого вхождения элемента
    static int leftBinSearch(ArrElements* a, size_t n, int key) {
        // Левая и правая границы
        int l = -1;
        int r = n;

        // Проверка на отсутствие элемента в массиве
        if (key < a[0] || key > a[n-1]) return -1;

        // Поиск середины и сужение границ
        while (l < r - 1) {
            int m = (l + r) / 2;
            if (a[m] < key)
                l = m;
            else
                r = m;
        }

        // Проверка, что элемент содержится
        if (a[r] == key)
            return r;
        else
            return -1;
    }


    // Поиск самого правого вхождения элемента
    static int rightBinSearch(ArrElements* a, int n,  int key) {
        // Левая и правая границы
        int l = -1;
        int r = n;

        // Проверка на отсутствие элемента в массиве
        if (key < a[0] || key > a[n-1]) return -1;

        // Поиск середины и сужение границ
        // Изменился знак в a[m] <= key
        while (l < r - 1) {
            int m = (l + r) / 2;
            if (a[m] <= key)
                l = m;
            else
                r = m;
        }

        if (a[r - 1] == key)
            return r - 1;
        else
            return -1;
    }
};





int main() {

    //---------------------------------------------
    freopen("binsearch.in", "r", stdin);
    freopen("binsearch.out", "w", stdout);
    //--------------------------------------------- /*/

    size_t n;
    int key;
    cin >> n;

    long long a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cin >> key;

    int l_index = BinarySearch<long long>::leftBinSearch(a, n, key);
    int r_index = BinarySearch<long long>::rightBinSearch(a, n, key);
    cout << "Left search: " << l_index << "\n";
    cout << "Right search: " << r_index << "\n";



}