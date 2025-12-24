#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <locale.h>

double f(double x);
double solve(double y, double a, double b, double eps);
double derivative(double x);
void table(double a, double b, double step);
void minmax(double a, double b, double step,
    double* minx, double* minv,
    double* maxx, double* maxv);

double fact2(int n);

int main() {
    setlocale(LC_ALL, "RUS");

    int choice;
    double x, a, b, step, y;

    do {
        printf("\n====== Меню ======\n");
        printf("1. Значение функции в точке\n");
        printf("2. Таблица значений\n");
        printf("3. Минимум / максимум на отрезке\n");
        printf("4. Найти x по Y\n");
        printf("5. Производная в точке\n");
        printf("0. Выход\n ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("x = ");
            scanf("%lf", &x);
            printf("f(%.5f) = %.6f\n", x, f(x));
            break;

        case 2:
            printf("a = ");
            scanf("%lf", &a);
            printf("b = ");
            scanf("%lf", &b);
            printf("step = ");
            scanf("%lf", &step);
            table(a, b, step);
            break;

        case 3: {
            double minx, minv, maxx, maxv;

            printf("a = ");
            scanf("%lf", &a);
            printf("b = ");
            scanf("%lf", &b);
            printf("step = ");
            scanf("%lf", &step);

            minmax(a, b, step, &minx, &minv, &maxx, &maxv);

            printf("\nМинимум: f(%.5f) = %.6f\n", minx, minv);
            printf("Максимум: f(%.5f) = %.6f\n", maxx, maxv);
            break;
        }

        case 4:
            printf("Y = ");
            scanf("%lf", &y);
            printf("a = ");
            scanf("%lf", &a);
            printf("b = ");
            scanf("%lf", &b);
            printf("x ~= %.6f\n", solve(y, a, b, 1e-6));
            break;

        case 5:
            printf("x = ");
            scanf("%lf", &x);
            printf("f'(%.5f) = %.6f\n", x, derivative(x));
            break;
        }

    } while (choice != 0);

    return 0;
}


double f(double x) {
    if (x < 1) {
        return exp(-fabs(x)) / atan(1 + x * x);
    }
    else if (x < 6) {
        return (x * x * cos(3 * x) * tanh(x)) /
            sqrt(1 + pow(x, 6));
    }
    else {
        double s = 0;
        for (int n = 0; n <= 4; n++) {
            s += pow(-1, n) * pow(x, 2 * n + 1) /
                (fact2(2 * n + 1) * (n + 3));
        }
        return s;
    }
}


double fact2(int n) {
    double r = 1;
    for (int i = n; i > 0; i -= 2)
        r *= i;
    return r;
}


double solve(double y, double a, double b, double eps) {
    for (double x = a; x <= b; x += eps) {
        if (fabs(f(x) - y) < eps)
            return x;
    }
    return NAN;
}


double derivative(double x) {
    double h = 1e-6;
    return (f(x + h) - f(x)) / h;
}


void table(double a, double b, double step) {
    printf("\n----------------------------------------\n");
    printf("|      x       |        f(x)           |\n");
    printf("----------------------------------------\n");

    for (double t = a; t <= b; t += step)
        printf("| %12.5f | %21.6f |\n", t, f(t));

    printf("----------------------------------------\n");
}


void minmax(double a, double b, double step,
    double* minx, double* minv,
    double* maxx, double* maxv) {

    *minx = a;
    *maxx = a;
    *minv = f(a);
    *maxv = f(a);

    for (double t = a; t <= b; t += step) {
        double v = f(t);
        if (v < *minv) { *minv = v; *minx = t; }
        if (v > *maxv) { *maxv = v; *maxx = t; }
    }
}
