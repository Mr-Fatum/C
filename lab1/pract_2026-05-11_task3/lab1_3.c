#include <stdio.h>
#include <math.h>
int main(){
    double r;
    double ang;
    double pi = atan(1.0) * 4;

    printf("Enter a radus of the circle: ");
    scanf("%lf", &r);

    printf("Enter an angle in degrees: ");
    scanf("%lf", &ang);

    double angle = (ang * pi)/180;

    printf("The length of the chord corresponding to the angle equals %lf \n"
           "The area of the segment corresponding to the angle equals %lf", 2 * r * sin(angle/2), (r * r / 2) * (angle - sin(angle)));
    return 0;    
}