//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>


inline double matrix_get(int y_pos, int x_pos, double t[], int y_size, int x_size);
inline void matrix_put(double value, int y_pos, int x_pos, double t[], int y_size, int x_size);

double dtw_diag(double *a, double *b, int n, int m) {
    double *t = (double*)malloc(n * m * sizeof(double));
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, n, m);
    for (int i = 1; i < n; ++i) {
        double value = matrix_get(i - 1, 0, t, n, m) + fabs(a[i] - b[0]);
        matrix_put(value, i, 0, t, n, m);
    }
    for (int j = 1; j < m; ++j) {
        double value = matrix_get(0, j - 1, t, n, m) + fabs(a[0] - b[j]);
        matrix_put(value, 0, j, t, n, m);
    }


    for (int i = 1; i < m; ++i) {
        for (int j = 0; j < i; ++j) {
            double m1 = matrix_get(i - j - 1, j, t, n, m);
            double m2 = matrix_get(i - j - 1, j + 1, t, n, m);
            double m3 = matrix_get(i - j, j, t, n, m);
            double value = fabs(a[i - j] - b[j + 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i - j, j + 1, t, n, m);
        }

    }

    for (int i = m; i < n; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            double m1 = matrix_get(i - j, j, t, n, m);
            double m2 = matrix_get(i - j - 1, j, t, n, m);
            double m3 = matrix_get(i - j - 1, j + 1, t, n, m);
            double value = fabs(a[i - j] - b[j + 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i - j, j + 1, t, n, m);
        }

    }

    for (int i = n; i < m + n - 1; ++i) {
        for (int j = 0; j < n + m - i - 2; ++j) {
            double m1 = matrix_get(n - 1 - j, j + 1 + i - n, t, n, m);
            double m2 = matrix_get(n - 2 - j, j + 1 + i - n, t, n, m);
            double m3 = matrix_get(n - 2 - j, j + 2 + i - n, t, n, m);
            double value = fabs(a[n - 1 - j] - b[j + 2 + i - n]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, n - 1 - j, j + 2 + i - n, t, n, m);
        }
    }

    double rez = matrix_get(n - 1, m - 1, t, n, m);
    free(t);
    return rez;
}