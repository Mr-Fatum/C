#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int n;
    printf("Enter your natural number less or equal 25: ");
    scanf("%d", &n);

    double res = -2.0;
    // Вычисляем верхнюю границу: 2 в степени n
    int total_combinations = 1 << n;
    int sum;
    int best_mask = 0;
    double buff;
    // Цикл перебора всех масок
    for (int mask = 1; mask < total_combinations; mask++)
    {
        sum = 0;
        // внутренний цикл для вычисления суммы квадратов для текущей маски
        for (int j = 0; j < n; j++)
        {
            if ((mask & (1 << j)) != 0) //  если j-й элемент включен в маску (т.е. на j-ом месте стоит 1), 
            {                           //  то добавляем его квадрат к сумме
                sum += (j + 1) * (j + 1);
            }
        }
        
        buff = sin(sum);
        if (buff > res) // сравниваем с текущим максимумом и обновляем его, если нашли большее значение
        {
            res = buff;
            best_mask = mask;
        }
    }
    printf("Max sin is: %lf\n", res);
    printf("[");
    bool isFollow = false;
    // красивый вывод элементов того набора, который дал максимальное значение синуса.
    for (int i = 0; i < n; i++)
    {
        // Проверяем, включен ли i-й элемент в наилучшую маску
        if ((best_mask & (1 << i)) != 0)
        {
            if (isFollow)
            {
                printf(", ");
            }
            else
            {
                isFollow = true;
            }
            printf("%d", i + 1);
        }
    }
    printf("]\n");

    return 0;
}