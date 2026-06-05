#include <stdio.h>
#include <stdlib.h>

// Фильтрует массив по предикату pred.
// arr - исходный массив,
// n - количество элементов в массиве,
// out_count - указатель для записи размера результирующего массива,
// pred - функция-предикат, возвращающая ненулевое значение для элементов, которые нужно оставить.
int *filter(const int *arr, int n, int *out_count, int (*pred)(int)) {
    int *out = malloc(n * sizeof(int)); // выделяем память под максимально возможный результат
    if (!out) {
        *out_count = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (pred(arr[i])) {
            out[count++] = arr[i];
        }
    }
    *out_count = count; // сохраняем фактическое количество найденных элементов
    return out;
}


int is_even(int x) { // Проверяет, является ли число чётным.
    return x % 2 == 0;
}

// Возвращает сумму цифр числа.
// Абсолютное значение используется, чтобы корректно работать с отрицательными числами.
int sum_digits(int x) {
    x = abs(x);
    int sum = 0;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}


int odd_digit_sum(int x) { // Проверяет, имеет ли число нечётную сумму цифр.
    return sum_digits(x) % 2 != 0;
}


int is_prime(int x) { // Проверяет, является ли число простым.
    if (x < 2) {
        return 0;
    }
    if (x % 2 == 0) {
        return x == 2;
    }
    for (int i = 3; i * (long long)i <= x; i += 2) {
        if (x % i == 0) {
            return 0;
        }
    }
    return 1;
}


void print_array(const int *arr, int n) { 
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", arr[i]);
    }
    putchar('\n');
}

int main(void) {
    int a[] = {12, 7, 5, 18, 23, 30, 11, 101, 44, 39, 0, -13};
    int n = sizeof(a) / sizeof(a[0]);
    int count;

    // Фильтруем чётные числа и выводим результат.
    int *even = filter(a, n, &count, is_even);
    if (even) {
        printf("Even numbers:\n");
        print_array(even, count);
        free(even);
    }

    // Фильтруем числа с нечётной суммой цифр и выводим результат.
    int *odd_sum = filter(a, n, &count, odd_digit_sum);
    if (odd_sum) {
        printf("Numbers with odd digit sum:\n");
        print_array(odd_sum, count);
        free(odd_sum);
    }

    // Фильтруем простые числа и выводим результат.
    int *prime = filter(a, n, &count, is_prime);
    if (prime) {
        printf("Prime numbers:\n");
        print_array(prime, count);
        free(prime);
    }

    return 0;
}
