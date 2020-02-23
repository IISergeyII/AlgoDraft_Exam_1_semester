#include <iostream>

template<class ArrElements>
class QSort {
public:

    // Быстрая сортировка при помощи разбиения Хоара
    // Нестабильная сортировка
    // O(n^2) - худшее время
    // O(n log n) - в среднем
    //
    // Усовершенствование:
    // Берем случайный элемент за базу, относительно которой будем сортировать
    // В общем случае мы избавляемся от случая, когда в качестве базы мы берем наибольший или наименьший из элементов,
    // что позволяет ускорить работу алгоритма

    static void swap(ArrElements *a, ArrElements *b) {
        ArrElements tmp = *a;
        *a = *b;
        *b = tmp;
    }


    static long partition(ArrElements *a, long l, long r) {
        // Разбиваем на две чати методом Хоара

        ArrElements key = a[l + (rand() % (r - l))];
        long i = l;
        long j = r;
        while (i <= j) {
            while (a[i] < key) i++;
            while (a[j] > key) j--;
            if (i >= j) break;
            swap(&a[i++], &a[j--]);
        }
        return j;
    }

    static void q_sort(ArrElements *a, long l, long r) {
        // a - указатель на массив
        // l - индекс левой границы
        // r - индекс правой границы
        // Все границы включительно
        if (l < r) {
            long q = partition(a, l, r);
            q_sort(a, l, q);
            q_sort(a, q + 1, r);
        }
    }
};


int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    long n;
    std::cin >> n;

    long long a[n];
    for (long i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    QSort<long long>::q_sort(a, 0, n - 1);

    for (long i = 0; i < n; ++i) {
        std::cout << a[i] << " ";
    }

    return 0;
}
