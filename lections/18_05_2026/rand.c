/* Ввожу n, вывожу n случайных целых чисел, потом n случайных вещественных чисел от 0 до 1 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int main(void) {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    srand(time(NULL));

    int i;
    for (i = 0; i < n; i++) {
        int k = rand();
        printf("%d ", k);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        double k = (double)rand();
        printf("%.6lf ", k / RAND_MAX);
    }
    printf("\n");

    return 0;
}
