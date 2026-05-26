/*
1. Функциональные типы

Ассемблер:
  mov esi, offset ret_label
  jmp procedure
ret_label:
  ...

procedure:
  ...
  ;ret
  jmp esi ; косвенный переход

Косвенный вызов процедуры:
  call esi


Функциональный объект - это адрес (процедуры) и информация об аргументах, которая хранится в голове у программиста


В Си тоже есть!
*/

/*
В Си можно объявлять свои типы:
typedef тип синоним_типа;

typedef
  double (*arrfunc) (int len, double *ar);
arrfunc - функциональный тип функций, которые принимаюь вещественный массив и возвращают вещественное число

Haskell:
arrfunc :: [Double] -> Double

arrfunc *func;

*/

#include <stdio.h>

typedef
  double (*arrfunc) (int len, double *ar);

double maxAr(int len, double ar[]) {
    double cur = ar[0];

    for (int i = 0; i < len; i++) {
        if (cur < ar[i]) cur = ar[i];
    }

    return cur;
}

double minAr(int len, double ar[]) {
    double cur = ar[0];

    for (int i = 0; i < len; i++) {
        if (cur > ar[i]) cur = ar[i];
    }

    return cur;
}


double avgAr(int len, double ar[]) {
    double sum = 0;

    for (int i = 0; i < len; i++) {
        sum += ar[i];
    }

    return sum / len;
}


int main(void) {
  arrfunc funcs[3] =
    { minAr, maxAr, avgAr };
  arrfunc func = minAr;

  double ar[] =
    { -5, 10, 8, -3.14, 0, 2.71, 15, -1 };
  int len = 8, op;

  printf("0 - min; 1 - max; 2 - average.\n");
  printf("Enter your operation: ");
  scanf ("%d", &op);

  double res = (*funcs[op])(len, ar);
  printf("Your result is %lf\n", res);

  double res1 = (*func)(len, ar);
  printf("The only function result is %lf\n", res1);

  return 0;
}




