#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *GenArray(int n, int a, int b) // Функция для генерации массива случайных чисел в заданном диапазоне
{
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    for (int i = 0; i < n; i++)
    {
        int randomNumber = a + rand() % (b - a + 1); // Генерация случайного числа в диапазоне [a, b]
        arr[i] = randomNumber;     // ^^^^^^^^^^^^ так число получается именно в [a,b] включительно
    }
    return arr;
}

void main(void){
    int n, a, b;
    
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    printf("Enter the range (a and b): ");
    scanf("%d%d", &a, &b);
    
    srand(time(NULL)); // Инициализация генератора случайных чисел текущим временем
    
    int *array = GenArray(n, a, b); // Генерация массива случайных чисел
    if (array != NULL && n != 0)
    {
        printf("Generated array: ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", array[i]);
        }
        printf("\n");
        free(array);
    }
}