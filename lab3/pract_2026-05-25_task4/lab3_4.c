#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Представление точки на плоскости с координатами x и y.
typedef struct {
    double x;
    double y;
} Point;

// Вычисляет евклидово расстояние между двумя точками a и b.
static double distance_between(const Point *a, const Point *b)
{
    double dx = a->x - b->x;
    double dy = a->y - b->y;
    return sqrt(dx * dx + dy * dy);
}

// Вычисляет площадь треугольника по формуле детерминанта.
// Это аналог формулы Герона, но без корней — используется векторное произведение двух сторон.
static double triangle_area(const Point *a, const Point *b, const Point *c)
{
    return fabs((b->x - a->x) * (c->y - a->y) -
                (b->y - a->y) * (c->x - a->x)) * 0.5;
}

// Проверяет, образуют ли три точки невырожденный треугольник.
// Если площадь почти нулевая, точки лежат на одной прямой.
static int is_triangle(const Point *a, const Point *b, const Point *c)
{
    return triangle_area(a, b, c) > 1e-12;
}

// Суммирует длины трех сторон треугольника.
static double triangle_perimeter(const Point *a, const Point *b, const Point *c)
{
    return distance_between(a, b) + distance_between(b, c) + distance_between(c, a);
}

int main(void)
{
    int n;

    // Считываем количество точек. Если данных недостаточно или точек меньше трех.
    if (scanf("%d", &n) != 1 || n < 3) {
        return 0;
    }

    // Выделяем массив точек динамически, размер зависит от введенного n.
    Point *points = malloc((size_t)n * sizeof(Point));
    if (points == NULL) {
        return 1;
    }

    // Считаем координаты каждой точки.
    for (int i = 0; i < n; ++i) {
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
                // Пропускаем вырожденные треугольники, где три точки коллинеарны.
                if (!is_triangle(&points[i], &points[j], &points[k])) {
                    continue;
                }
                // Вычисляем периметр текущего треугольника.
                double p = triangle_perimeter(&points[i], &points[j], &points[k]);
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
    } else {
        // Иначе печатаем координаты вершин треугольника с максимальным периметром.
        printf("%.9g %.9g\n", points[best_i].x, points[best_i].y);
        printf("%.9g %.9g\n", points[best_j].x, points[best_j].y);
        printf("%.9g %.9g\n", points[best_k].x, points[best_k].y);
        printf("Perimeter: %.9g\n", best_perimeter);
    }

    free(points);
    return 0;
}
