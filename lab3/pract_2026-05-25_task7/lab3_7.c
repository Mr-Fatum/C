#include <stdio.h>
#include <math.h>

/* Определение структуры для комплексного числа */
typedef struct {
    double re;  /* действительная часть */
    double im;  /* мнимая часть */
} Complex; // так называется тип данных для комплексных чисел

/* Чтение комплексного числа из ввода: две вещественные части */
Complex cRead(void) {
    Complex z;
    if (scanf("%lf %lf", &z.re, &z.im) != 2) {
        /* Если ввод некорректный, возвращаем 0 + 0i */
        z.re = 0.0;
        z.im = 0.0;
    }
    return z;
}

/* Печать комплексного числа в виде a + bi или a - bi */
void cPrint(Complex z) {
    if (z.im < 0.0) {
        printf("%.6f - %.6fi", z.re, -z.im);
    } else {
        printf("%.6f + %.6fi", z.re, z.im);
    }
}

/* Сложение комплексных чисел */
Complex cAdd(Complex a, Complex b) {
    Complex r = {a.re + b.re, a.im + b.im};
    return r;
}

/* Вычитание комплексных чисел */
Complex cSub(Complex a, Complex b) {
    Complex r = {a.re - b.re, a.im - b.im};
    return r;
}

/* Умножение комплексных чисел */
Complex cMul(Complex a, Complex b) {
    Complex r = {a.re * b.re - a.im * b.im,
                 a.re * b.im + a.im * b.re};
    return r;
}

/* Деление комплексных чисел. Если знаменатель равен нулю, возвращаем 0 */
Complex cDiv(Complex a, Complex b) {
    double denom = b.re * b.re + b.im * b.im;
    Complex r = {0.0, 0.0};
    if (denom != 0.0) {
        r.re = (a.re * b.re + a.im * b.im) / denom;
        r.im = (a.im * b.re - a.re * b.im) / denom;
    }
    return r;
}

/* Действительная часть комплексного числа */
double cReal(Complex z) {
    return z.re;
}

/* Мнимая часть комплексного числа */
double cImag(Complex z) {
    return z.im;
}

/* Сопряжённое комплексное число: знак мнимой части меняется */
Complex cConj(Complex z) {
    Complex r = {z.re, -z.im};
    return r;
}

/* Модуль комплексного числа: sqrt(re^2 + im^2) */
double cAbs(Complex z) {
    return hypot(z.re, z.im);
}

/* Аргумент комплексного числа в радианах */
double cArg(Complex z) {
    return atan2(z.im, z.re);
}

int main(void) {
    Complex a, b;

    /* Ввод двух комплексных чисел */
    printf("Enter real and imaginary parts of first complex number: ");
    a = cRead();
    printf("Enter real and imaginary parts of second complex number: ");
    b = cRead();

    /* Вывод результатов операций */
    printf("a = "); cPrint(a); printf("\n");
    printf("b = "); cPrint(b); printf("\n");
    printf("a + b = "); cPrint(cAdd(a, b)); printf("\n");
    printf("a - b = "); cPrint(cSub(a, b)); printf("\n");
    printf("a * b = "); cPrint(cMul(a, b)); printf("\n");
    printf("a / b = "); cPrint(cDiv(a, b)); printf("\n");
    printf("Re(a) = %.6f\n", cReal(a));
    printf("Im(a) = %.6f\n", cImag(a));
    printf("Conj(a) = "); cPrint(cConj(a)); printf("\n");
    printf("|a| = %.6f\n", cAbs(a));
    printf("Arg(a) = %.6f\n", cArg(a));

    return 0;
}


рубашку стирать в пакете для стирки 

фрак просто проополоска чтобы небыло соли
в ванной набрать 10-15 см воды, полвать тёплой водой штаны и фрак, затем просто повесить без отжима
минут 5 надо полежать

НЕ ОТЖИМАТЬ!!!!

бабочку вместе с рубашкой 

воротничёк намочить, щёткой зубной, смыть простым мылом 
положить и самостоятельно высохнет 

