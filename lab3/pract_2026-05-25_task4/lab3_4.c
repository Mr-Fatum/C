#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct { // Представление точки на плоскости с координатами x и y.
    double x;
    double y;
} Point;


double distance_between(const Point *a, const Point *b) // Вычисляет евклидово расстояние между двумя точками a и b.
{
    double dx = a->x - b->x;
    double dy = a->y - b->y;
    return sqrt(dx * dx + dy * dy);
}

// Вычисляет площадь треугольника по формуле детерминанта.
// Это аналог формулы Герона, но без корней — используется векторное произведение двух сторон.
double triangle_area(const Point *a, const Point *b, const Point *c)
{
    return fabs((b->x - a->x) * (c->y - a->y) -
                (b->y - a->y) * (c->x - a->x)) * 0.5;
}

// Проверяет, образуют ли три точки невырожденный треугольник.
// Если площадь почти нулевая, точки лежат на одной прямой.
int is_triangle(const Point *a, const Point *b, const Point *c)
{
    return triangle_area(a, b, c) > 1e-12;
}


double triangle_perimeter(const Point *a, const Point *b, const Point *c) // Суммирует длины трех сторон треугольника.
{
    return distance_between(a, b) + distance_between(b, c) + distance_between(c, a);
}

int main(void)
{
    int n;

    printf("Enter number of points: "); 
    if (scanf("%d", &n) != 1 || n < 3) {
        return 0;
    }

    Point *points = malloc((size_t)n * sizeof(Point));
    if (points == NULL) {
        return 1;
    }

    printf("Enter coordinates (x y) for each point:\n");
    for (int i = 0; i < n; ++i) {
        printf("Point %d: ", i + 1); // Подсказка для каждой точки
        if (scanf("%lf %lf", &points[i].x, &points[i].y) != 2) {
            free(points);
            return 1;
        }
    }

    // Инициализация параметров лучшего треугольника.
    double best_perimeter = 0.0;
    int best_i = -1, best_j = -1, best_k = -1;

    // Перебираем все тройки точек без повторов (i < j < k).
    for (int i = 0; i < n - 2; ++i) {
        for (int j = i + 1; j < n - 1; ++j) {
            for (int k = j + 1; k < n; ++k) {
                
                if (!is_triangle(&points[i], &points[j], &points[k])) { // Пропускаем вырожденные треугольники, где три точки коллинеарны.
                    continue; // переходим к следующей тройке точек
                }

                double p = triangle_perimeter(&points[i], &points[j], &points[k]);// Вычисляем периметр текущего треугольника.
                // Сохраняем треугольник с наибольшим периметром.
                if (p > best_perimeter) {
                    best_perimeter = p;
                    best_i = i;
                    best_j = j;
                    best_k = k;
                }
            }
        }
    }

    // Если не найден ни один валидный треугольник, выводим сообщение.
    if (best_i < 0) {
        printf("No non-degenerate triangle can be formed.\n");
    } else {// Иначе печатаем координаты вершин треугольника с максимальным периметром.
        /* Формат %.2g выбрал потому, что он печатает число в наиболее компактном
         виде: либо в обычной десятичной записи, либо в экспоненциальной, если число
         слишком мало или слишком велико. Это удобнее, чем %lf, который всегда
         выводит фиксированное количество десятичных знаков и может давать лишние нули.*/
        printf("%.2g %.2g\n", points[best_i].x, points[best_i].y);
        printf("%.2g %.2g\n", points[best_j].x, points[best_j].y);
        printf("%.2g %.2g\n", points[best_k].x, points[best_k].y);
        printf("Perimeter: %.2g\n", best_perimeter);
    }

    free(points);
    return 0;
}
