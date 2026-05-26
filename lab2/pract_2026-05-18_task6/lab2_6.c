#include <stdio.h>

int my_strlen(char *str)
{
    int count = 0;

    // Пока указатель смотрит не на нуль-терминатор
    while (str[count] != '\0')
    {
        count++;
    }

    return count;
}

int main()
{
    char source[100];
    char mess1[100];
    char mess2[100];

    printf("Enter a strig, what include only symbols from first half if ASCII table: ");
    gets(source);

    int i;
    int j;
    int k;

    int len = my_strlen(source);

    for (i = 0, j = 0, k = 0; i < len; i++)
    {
        if ((source[i] >= 'a' && source[i] <= 'z') || (source[i] >= 'A' && source[i] <= 'Z'))
        {
            mess1[j] = source[i];
            j++;
        }
        else
        {
            mess2[k] = source[i];
            k++;
        }
    }
    printf("Here all alfabetical symbols from your string: %s\n", mess1);
    printf("Here other symbols from your string: %s\n", mess2);
    return 0;
}