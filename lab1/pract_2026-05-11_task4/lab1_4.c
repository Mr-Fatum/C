#include <stdio.h>
#include <math.h>
int main(){
    double d;

    printf("Enter the real number: ");
    scanf("%lf", &d);

    if (d > 0){
        printf("Absolute value of your real number is: %lf", d);
    } else {
        printf("Absolute value of your real number is: %lf", d * (-1));
    }
    return 0;   

}