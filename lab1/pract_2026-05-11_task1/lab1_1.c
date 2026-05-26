#include <stdio.h>
#include <math.h>
int main()
{
    int n;
    double s;
    printf ("Enter an integer: ");
    scanf ("%d", &n);
    s = sqrt(n);
    printf ("You have entered %d, it doubled is %d, "
    "its square root is %lf\n", n, 2*n, s);
    return 0;
}
