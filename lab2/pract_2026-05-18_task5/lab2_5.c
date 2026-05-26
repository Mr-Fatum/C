#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int n, m;
    // Запрашиваем у пользователя количество строк и столбцов
    printf("Enter the number of rows (n) and columns (m): ");
    scanf("%d%d", &n, &m);

    int **a = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        a[i] = (int *)malloc(m * sizeof(int));
    }

    srand(101);
    //srand((unsigned)time(NULL)); // unsigned для того, чтобы избежать предупреждения о несовпадении
                                 // типов и чтобы получать числа большиее 0, так как time() может
                                 // возвращать отрицательные значения

    for (int i = 0; i < n; i++) // заполняем массив случайными числами от 0 до 100
    {
        for (int j = 0; j < m; j++) // проходим по каждому элементу массива
        {
            a[i][j] = rand() % 101;
        }
    }

    printf("Array %d x %d:\n", n, m); // выводим массив на экран
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) // проходим по каждому элементу массива
        {
            printf("%4d", a[i][j]);
        }
        printf("\n");
    }

    // Перед циклом объявляем финальные переменные
    int minimax;
    int i1_res = 0;
    int j1_res = 0;
    int current_j = 0; // Временная переменная для индекса столбца текущей строки

    for (int i = 0; i < n; i++)
    {
        int row_max = a[i][0];
        current_j = 0;
        for (int j = 1; j < m; j++)
        {
            if (a[i][j] > row_max)
            {
                row_max = a[i][j];
                current_j = j; // Запоминаем, где он сейчас в этой строке
            }
        }

        // Теперь проверяем, стал ли этот максимум строки глобальным минимаксом
        if (i == 0 || row_max < minimax)
        {
            minimax = row_max;
            i1_res = i;         // Фиксируем строку
            j1_res = current_j; // Фиксируем правильный столбец, найденный выше!
        }
    }

    int maximin;
    int i2_res = 0;
    int j2_res = 0;
    int current_i = 0;
    for (int j = 0; j < m; j++) // проходим по каждому столбцу
    {
        int col_min = a[0][j];
        current_i = 0;
        for (int i = 1; i < n; i++) // проходим по каждой строке в текущем столбце
        {
            if (a[i][j] < col_min)
            {
                col_min = a[i][j];
                current_i = i; // Запоминаем, где он сейчас в этом столбце
            }
        }
        if (j == 0 || col_min > maximin)
        {
            maximin = col_min;
            i2_res = current_i;
            j2_res = j;
        }
    }

    printf("Minimax (minimum of row maximum): %d\n", minimax);
    printf("Index of Minimax: (%d, %d)\n", i1_res + 1, j1_res + 1);
    printf("Maximin (maximum of column minimum): %d\n", maximin);
    printf("Index of Maximin: (%d, %d)\n", i2_res + 1, j2_res + 1);

    for (int i = 0; i < n; i++) // освобождаем память, выделенную для каждой строки
    {
        free(a[i]);
    }
    free(a); // освобождаем память, выделенную для массива указателей

    return 0;
}
