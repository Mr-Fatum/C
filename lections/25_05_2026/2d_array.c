/*
2. Двумерные массивы
*/

#include <stdio.h>
#include <stdlib.h>

int main (void) {
  double **ar;
  int n, m;

  printf("Enter number of rows and columns: ");
  scanf("%d%d", &n, &m);

  // Блок хранения указателей на блоки строк
  ar = (double **)malloc(n * sizeof(double *));

  // Отвожу блоки строк
  for (int i = 0; i < n; i++) {
    ar[i] = (double *)
                malloc(m * sizeof(double));
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        ar[i][j] = (i+1)*(j+1);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        printf("%6.1lf", ar[i][j]);
    }
    printf("\n");
  }

  // Освобождаю массив
  for (int i = 0; i < n; i++) {
    free(ar[i]);
  }
  free(ar);

  return 0;
}
