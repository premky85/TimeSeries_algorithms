//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>


inline double matrix_get(int x_pos, int y_pos, double t[], int x_size, int y_size);
inline void matrix_put(double value, int x_pos, int y_pos, double t[], int x_size, int y_size);

double dtw_diag_cache(double *a, double *b, int n, int m) {
    int mo = m;
    m = n + m - 1;
    double *t = (double*)malloc(m * n * sizeof(double));
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, n, m);
    for (int i = 1; i < n; ++i) {
        double m1 = matrix_get(i - 1, i - 1, t, n, m);
        double m2 = a[i];
        double m3 = b[0];

        double v = fabs(a[i] - b[0]) + matrix_get(i - 1, i - 1, t, n, m);
        matrix_put(v, i, i, t, n, m);
    }
    for (int i = 1; i < mo; ++i) {
        double m5 = matrix_get(0, i - 1, t, n, m);
        double m2 = a[0];
        double m3 = b[i];


        double v = fabs(a[0] - b[i]) + matrix_get(0, i - 1, t, n, m);
        matrix_put(v, 0, i, t, n, m);
    }

    for (int i = 2; i < n; ++i) {
        for (int j = 1; j < i; ++j) {
            double m1 = matrix_get(j, i - 1, t, n, m);
            double m2 = matrix_get(j - 1, i - 1, t, n, m);
            double m3 = matrix_get(j - 1, i - 2, t, n, m);
            double m4 = a[j];
            double m5 = b[i - j];
            double value = fabs(a[j] - b[i - j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, j, i, t, n, m);
        }
    }

    for (int i = n; i < mo; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            double m1 = matrix_get(j + 1, i - 1, t, n, m);
            double m2 = matrix_get(j, i - 1, t, n, m);
            double m3 = matrix_get(j, i - 2, t, n, m);
            double m4 = a[j + 1];
            double m5 = b[((2 * n - 1) - i) - j + 2*(i - n)];
            double value = fabs(a[j + 1] - b[((2 * n - 1) - i) - j + 2*(i - n)]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, j + 1, i, t, n, m);
        }
    }

    for (int i = mo; i < mo + 1; ++i) {
        for (int j = 0; j < n + mo - i - 1; ++j) {
            double m1 = matrix_get(j + 1, i - 1, t, n, m);
            double m2 = matrix_get(j, i - 1, t, n, m);
            double m3 = matrix_get(j , i - 2, t, n, m);
            double m4 = a[j + 1];
            double m5 = b[mo - j - 1];
            double value = fabs(a[j + 1] - b[mo - j - 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, j, i, t, n, m);
        }
    }

    for (int i = mo + 1; i < m ; ++i) {
        for (int j = 0; j < n + mo - i - 1; ++j) {
            double m1 = matrix_get(j, i - 1, t, n, m);
            double m2 = matrix_get(j + 1, i - 1, t, n, m);
            double m3 = matrix_get(j + 1, i - 2, t, n, m);
            double m4 = a[j + 1 + i - mo];
            double m5 = b[mo - j - 1];
            double value = fabs(a[j + 1 + i - mo] - b[mo - j - 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, j, i, t, n, m);
        }
    }

    double rez = matrix_get(0, m - 1, t, n, m);

    free(t);
    return rez;
}