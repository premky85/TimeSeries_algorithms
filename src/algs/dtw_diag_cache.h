//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>


inline double matrix_get(int y_pos, int x_pos, double t[], int y_size, int x_size);
inline void matrix_put(double value, int y_pos, int x_pos, double t[], int y_size, int x_size);

double dtw_diag_cache(double *a, double *b, int n, int m) {
    int no = n;
    n = m + n - 1;
    double *t = (double*)malloc(n * m * sizeof(double));
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, n, m);
    for (int i = 1; i < no; ++i) {
        double v = fabs(a[i] - b[0]) + matrix_get(i - 1, 0, t, n, m);
        matrix_put(v, i, 0, t, n, m);
    }
    for (int j = 1; j < m; ++j) {
        double v = fabs(a[0] - b[j]) + matrix_get(j - 1, j - 1, t, n, m);
        matrix_put(v, j, j, t, n, m);
    }

    for (int i = 2; i < m; ++i) {
        for (int j = 1; j < i; ++j) {
            double m1 = matrix_get(i - 1, j, t, n, m);
            double m2 = matrix_get(i - 1, j - 1, t, n, m);
            double m3 = matrix_get(i - 2, j - 1, t, n, m);
            double value = fabs(a[i - j] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
        }
    }

    for (int i = m; i < no; ++i) {
        for (int j = 1; j < m; ++j) {
            double m1 = matrix_get(i - 1, j, t, n, m);
            double m2 = matrix_get(i - 1, j - 1, t, n, m);
            double m3 = matrix_get(i - 2, j - 1, t, n, m);
            double value = fabs(a[i - j] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
        }
    }

    for (int i = no; i < no + 1; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            double m1 = matrix_get(i - 1, j + 1, t, n, m);
            double m2 = matrix_get(i - 1, j, t, n, m);
            double m3 = matrix_get(i - 2, j, t, n, m);
            double value = fabs(a[i - j - 1] - b[j + 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
        }
    }

    for (int i = no + 1; i < n ; ++i) {
        for (int j = 0; j < m + no - i - 1; ++j) {
            double m1 = matrix_get(i - 1, j, t, n, m);
            double m2 = matrix_get(i - 1, j + 1, t, n, m);
            double m3 = matrix_get(i - 2, j + 1, t, n, m);
            double value = fabs(a[no - j - 1] - b[j + 1 + i - no]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
        }
    }

    double rez = matrix_get(n - 1, 0, t, n, m);

    free(t);
    return rez;
}