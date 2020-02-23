#include <iostream>
using namespace std;

template <class T>
class KStatistic {
public:

    static void swap(T &a, T &b){
        T t = a;
        a = b;
        b = t;
    }

    static T findKStatistic(T a[], long k, long n){
        k -= 1;
        long left = 0, right = n - 1;
        while (true) {

            // Увеличиваем производительность, рассматривая два / один элемент
            // Условие выхода
            if (left + 1 >= right) {
                if (right == left + 1 && a[right] < a[left])
                    swap (a[left], a[right]);
                return a[k];
            }

            // Меняем местами middle и left + 1 для того, чтобы увеличить производительность в общем случае
            unsigned mid = (left + right) / 2;
            swap (a[mid], a[left + 1]);

            // Сортируем a[left], a[left + 1], a[right] в порядке возрастания
            // Находим медиану ряда
            if (a[left] > a[right])
                swap (a[left], a[right]);
            if (a[left + 1] > a[right])
                swap (a[left + 1], a[right]);
            if (a[left] > a[left + 1])
                swap (a[left], a[left + 1]);

            // Выберем a[left + 1] в качестве опорного ("средний")
            // Повышается скорость работы, так как не будет выбран максимум / минимум в общем случае
            // Быстрой сортировкой Хоара отсортируем a[left + 1 : right], right - не включительно
            unsigned i = left + 1, j = right;
            T cur = a[left + 1];
            while (true)
            {
                while (a[++i] < cur);
                while (a[--j] > cur);
                if (i > j)
                    break;
                swap (a[i], a[j]);
            }

            // Вставляем опорный элемент
            a[left + 1] = a[j];
            a[j] = cur;

            // Смотрим, какую границу надо рассмотреть следующей
            if (j >= k)
                right = j - 1;
            if (j <= k)
                left = i;
        }
    }
};


int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("kth.in", "r", stdin);
    freopen("kth.out", "w", stdout);

    long n;
    long k;
    long A, B, C;

    cin >> n;
    cin >> k;

    int a[max(n, 2l)];

    cin >> A;
    cin >> B;
    cin >> C;
    cin >> a[0];
    cin >> a[1];

    // Генерация элементов
    for (long i = 2; i < n; ++i) {
        a[i] = A * a[i - 2] + B * a[i - 1] + C;
    }

    // Вывод
    cout << KStatistic<int>::findKStatistic(a, k, n);

    return 0;
}
