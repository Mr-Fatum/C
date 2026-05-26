#include <stdio.h>
#include <math.h>

int main(){
    int n, m;
    double a, b;

    printf("Enter two integers n and m:");
    scanf("%d%d", &n, &m);

    printf("Enter two real numbers a and b:");
    scanf("%lf%lf", &a, &b);
    
    int k, l; // упростим себе жизнь и определим новые переменные для удобства вычислений
    if (m <= n) { // чтобы не писать 2 раза один и тот же код, определим k и l в зависимости от того, какое из чисел больше
        k = n;
        l = m;
    } else {
        k = m;
        l = n;
    }
    double d = (b - a) / (k - l);
    double a0 = b - k * d;
    double ai;

    printf("Arithmetic progression between a and b (include a and b):\n");

    for (int i = 0; i < k - l + 1; i++) {
        ai = a0 + (l + i) * d;
        printf("a%d = %.2lf\n", l + i, ai);
    }
    return 0;
}
