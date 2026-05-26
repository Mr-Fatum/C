#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int count_digits(unsigned int num)
{
    int count = 0;

    while (num != 0)
    {
        count++;
        num /= 10;
    }

    return count;
}

int main()
{
    int n;

    printf("Enter a natural number or zero: ");
    scanf("%u", &n);

    if (n == 0)
    {
        printf("0 = 0");
    }
    else
    {
        int digits = count_digits(n);
        int *numbers = (int *)malloc(sizeof(int) * digits);
        int num = n;

        // printf("Number of digits in number %u is %d \n", n, digits);

        for (int i = 1; i <= digits; i++)
        {
            numbers[digits - i] = num % 10;
            num /= 10;
        }

        bool isFollowing = false;
        printf("%d = ", n);

        for (int i = 0; i < digits; i++)
        {
            
            if (numbers[i] != 0)
            {
                if (isFollowing)
                    printf(" + ");
                else
                    isFollowing = true;
                    
                if (i == digits - 1)
                {
                    printf("%d", numbers[i]); // печатаем единицы
                }
                else if (i == digits - 2)
                {
                    if (numbers[i] != 0)
                    {
                        printf("%d * 10", numbers[i]); // печатаем десятки
                    }
                }
                else
                {
                    printf("%u*10^%d", numbers[i], digits - i - 1);
                }
            }
        }

        free(numbers);
    }
    return 0;
}
