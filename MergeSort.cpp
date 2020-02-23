#include <iostream>
using namespace std;

template <class ArrElements>
class MergeSort{
public:

    // Сортировка слиянием
    // Стабильная сортировка за Ѳ (n log n) (тета)

    static void merge(ArrElements *p, size_t l, size_t q, size_t r){
        ArrElements L[q - l + 1];
        ArrElements R[r - q];
        size_t left_counter = 0;
        size_t right_counter = 0;

        // Копируем левую и правую части массива в L и R соответственно
        // L и R - уже отсортированы

        for (size_t i = l; i <= q; ++i) {
            L[left_counter] = p[i];
            left_counter++;
        }

        for (size_t i = q + 1; i <= r; ++i) {
            R[right_counter] = p[i];
            right_counter++;
        }

        left_counter = 0;
        right_counter = 0;
        size_t k = l;

        // Копируем обратно элементы L и R в массив соблюдая порядок

        while (left_counter < q - l + 1 && right_counter < r - q) {

            // Для стабильности - знак нестрогий

            if (L[left_counter] <= R[right_counter]) {
                p[k] = L[left_counter];
                left_counter++;
            } else {
                p[k] = R[right_counter];
                right_counter++;
            }
            k++;
        }

        // Копируем оставшиеся элементы из L и R

        while (left_counter < q - l + 1) {
            p[k] = L[left_counter];
            left_counter++;
            k++;
        }

        while (right_counter < r - q) {
            p[k] = R[right_counter];
            right_counter++;
            k++;
        }

    }

    // Сортируем части массива, разделяя его каждый раз напополам
    // Если у нас остался один элемент в массиве, то он уже отсортирован
    // ==> сливаем с другой частью
    static void merge_sort(ArrElements *p, size_t l, size_t r){
        if (l < r) {
            size_t q = (l + r) / 2;
            merge_sort(p, l, q);
            merge_sort(p, q + 1, r);
            merge(p, l, q, r);
        }
    }
};


int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);

    long n;
    std::cin >> n;

    long long a[n];
    for (long i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    MergeSort<long long>::merge_sort(a, 0, n - 1);

    for (long i = 0; i < n; ++i) {
        std::cout << a[i] << " ";
    }

    return 0;
}
