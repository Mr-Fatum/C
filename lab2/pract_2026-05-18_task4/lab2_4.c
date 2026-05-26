#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int find_max_index(int *arr, int size)
{
    int max_idx = 0; // На старте считаем, что самый большой — нулевой элемент

    // Перебираем элементы от 1 до size - 1
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > arr[max_idx])
        {
            max_idx = i; // Если нашли элемент больше, запоминаем его индекс
        }
    }

    return max_idx; // Возвращаем индекс самого большого элемента
}

int main(void)
{

    int n;
    printf("Enter array size: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(sizeof(int) * n);

    int i;
    for (i = 0; i < n; i++)
    {
        printf("Enter a[%d]: ", i);
        scanf("%d", &arr[i]);
    }
    int temp;
    for (i = 0; i < n; i++)
    {
        int max_idx = find_max_index(arr, n - i);

        // 2. Меняем местами элемент на позиции max_idx и элемент на позиции (n - i)
        temp = arr[max_idx];
        arr[max_idx] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }

    printf("[");
    bool isFollow = false;
    for (i = 0; i < n; i++)
    {

        if (isFollow)
        {
            printf(", ");
        }
        else
        {
            isFollow = true;
        }

        printf("%d", arr[i]);
    }
    printf("]");

    free(arr);
    return 0;
}