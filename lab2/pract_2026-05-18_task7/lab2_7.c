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

int main(){
    int n;
    char str[100];
    printf("Enter an integer: ");
    scanf("%d", &n);
    getchar();
    printf("Enter a string: ");
    gets(str);

    int len = my_strlen(str);
    char str1[100];
    int i;
    for (i = 0; i < n; i++){
        if (i >= len){
            str1[i] = '*';
        } else {
            str1[i] = str[i];
        }
    }
    str[n] = '\0';

    printf("Your new string: %s\n", str1);
    return 0;
}
