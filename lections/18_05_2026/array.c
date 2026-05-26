#include <stdio.h>
#include <stdlib.h>

/*
 * Ввести массив. Вывести разности между каждой парой соседних элементов
 */

int main(void) {
  int n;
  printf("Enter array size: ");
  scanf("%d", &n);
  double *a = (double *)
                     malloc(sizeof(double)*n);

  int i;
  for (i = 0; i < n; i++) {
      printf("Enter a[%i]: ", i);
      scanf("%lf", &a[i]);
      // Приоритет амперсанда ниже приоритета скобок !
      // scanf("%d", a+i);
  }

  // Вывожу, что просят
  for (i = 0; i < n-1; i++) {
    printf("Difference a[%d] - a[%d] is %lf\n",
           i+1, i, a[i+1] - a[i]);
  }

  // Освобождаю массив!
  free (a);

  return 0;
}

