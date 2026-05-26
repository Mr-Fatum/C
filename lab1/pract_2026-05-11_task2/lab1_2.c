#include <stdio.h>
#include <math.h>
int main(){
    double a0;
    double d;
    int n;
    printf("Enter an initial term of the arithmetic progression: ");
    scanf("%lf", &a0);
    printf("Enter a difference in arithmetic progression: ");
    scanf("%lf", &d);
    printf("Enter the member number of the arithmetic progression: ");
    scanf("%d", &n);
    printf("The term of the progression under the number %d is %f", n, a0+(n-1)*d);

    return 0;    
}