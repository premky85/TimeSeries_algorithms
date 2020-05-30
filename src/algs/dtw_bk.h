//
// Created by premk on 2. 02. 20.
//
#include <math.h>
#include <stdlib.h>
inline double matrix_get(int x_pos, int y_pos, double t[], int x_size, int y_size);
inline void matrix_put(double value, int x_pos, int y_pos, double t[], int x_size, int y_size);


double dtw_bk(double *a, double *b, int n, int m) {
    double *t = (double*)malloc(n * m * sizeof(double));

    matrix_put(fabs(a[n - 1] - b[m - 1]), n - 1, m - 1, t, n, m);
    for (int i = n - 2; i >= 0; --i) {
        double value = matrix_get(i + 1, m - 1, t, n, m) + fabs(a[i] - b[m - 1]);
        matrix_put(value, i, m - 1, t, n, m);
    }
    for (int i = m - 2; i >= 0; --i) {
        double value = matrix_get(n - 1, i + 1, t, n, m) + fabs(a[n - 1] - b[i]);
        matrix_put(value, n - 1, i, t, n, m);
    }
    for (int i = n - 2; i >= 0; --i) {
        for (int j = m - 2; j >= 0; --j) {
            double m1 = matrix_get(i + 1, j + 1, t, n, m);
            double m2 = matrix_get(i + 1, j, t, n, m);
            double m3 = matrix_get(i, j + 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
        }

    }
    double rez = matrix_get(0, 0, t, n, m);
    free(t);

    return rez;
}