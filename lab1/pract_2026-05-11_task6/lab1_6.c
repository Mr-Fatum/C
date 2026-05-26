#include <stdio.h>
#include <math.h>
int main(){
    int a = 1234;
    int k;
    do {
        printf("Enter your suggestion: ");
        scanf("%d", &k);
        if (k > a){
            printf("Your number is bigger than mine\n");
        } else if (k < a){
            printf("Your number is less than mine\n");
        }
    } while (k != a);
    printf("Good job! You got it ^_^\n");
    return 0;
}