#include <stdio.h>
#include <math.h>
int main(){
    double a;
    int n;

    printf("Enter a real number: ");
    scanf("%lf", &a);
    printf("Enter a power in which you want to raise yout number: ");
    scanf("%d", &n);
    
    int k;
    double res = 1;

    if (n==0) {
        printf("%lf raise to the power %d is equal to 1", a, n);
    } else if (n > 0) {
        for(k = 1; k <= n; k++){
            res *= a;
        }
    } else {
        for(k = 1; k <= n*(-1); k++){
            res /= a;
        }
    }
    printf("%lf raise to the power %d equals %lf", a, n, res);
    return 0;
}