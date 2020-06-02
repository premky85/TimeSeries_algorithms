//
// Created by premk on 2. 02. 20.
//
#include <math.h>
#include <stdlib.h>
inline double matrix_get(int x_pos, int y_pos, double t[], int x_size, int y_size);
inline void matrix_put(double value, int x_pos, int y_pos, double t[], int x_size, int y_size);


double dtw_bk(double *a, double *b, int m, int n) {
    double *t = (double*)malloc(m * n * sizeof(double));

    matrix_put(fabs(a[m - 1] - b[n - 1]), m - 1, n - 1, t, m, n);
    for (int i = m - 2; i >= 0; --i) {
        double value = matrix_get(i + 1, n - 1, t, m, n) + fabs(a[i] - b[n - 1]);
        matrix_put(value, i, n - 1, t, m, n);
    }
    for (int i = n - 2; i >= 0; --i) {
        double value = matrix_get(m - 1, i + 1, t, m, n) + fabs(a[m - 1] - b[i]);
        matrix_put(value, m - 1, i, t, m, n);
    }
    for (int j = n - 2; j >= 0; --j) {
        for (int i = m - 2; i >= 0; --i) {
            double m1 = matrix_get(i + 1, j + 1, t, m, n);
            double m2 = matrix_get(i + 1, j, t, m, n);
            double m3 = matrix_get(i, j + 1, t, m, n);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, m, n);
        }

    }
    double rez = matrix_get(0, 0, t, m, n);
    free(t);

    return rez;
}