#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);

    /*
    int temp;
    while (b != 0)
    {
        temp = a;
        a = b;
        b = temp % b;
    }
    return a;
    */
}

int main()
{

    int n;
    printf("Enter array size: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(sizeof(int) * n); // определяем массив

    int i;
    for (i = 0; i < n; i++)
    { // циклом считываем все элементы массива, которые должен ввести пользователь
        printf("Enter a[%d]: ", i);
        scanf("%d", &arr[i]);
    }

    printf("Pairs of relatively prime numbers from your array:\n");
    // Внешний цикл идет от 0 до предпоследнего элемента (n-2)
    for (i = 0; i < n - 1; i++)
    {
        int j;
        for (j = i + 1; j < n; j++)
        {
            if (gcd(arr[i], arr[j]) == 1)
            {
                printf("(%d, %d)\n", arr[i], arr[j]);
            }
        }
    }
    free(arr); // освобождаем память занятую массивом
    return 0;
}
