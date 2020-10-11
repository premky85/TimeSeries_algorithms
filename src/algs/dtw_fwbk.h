//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>

inline double matrix_get(int y_pos, int x_pos, double t[], int y_size, int x_size);
inline void matrix_put(double value, int y_pos, int x_pos, double t[], int y_size, int x_size);

double dtw_fwbk(double *a, double *b, int n, int m) {
    double *t = (double*)malloc(n * m * sizeof(double));


    int half = floor((double)(n) / 2);
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, n, m);
    for (int j = 1; j < m; ++j) {
        double value = matrix_get(0, j - 1, t, m, n) + fabs(a[0] - b[j]);
        matrix_put(value, 0, j, t, n, m);
    }
    for (int i = 1; i < half; ++i) {
        double value = matrix_get(i - 1, 0, t, n, m) + fabs(a[i] - b[0]);
        matrix_put(value, i, 0, t, n, m);
    }

    for (int i = 1; i < half; ++i) {
        for (int j = 1; j < m; ++j) {
            double m1 = matrix_get(i - 1, j - 1, t, n, m);
            double m2 = matrix_get(i - 1, j, t, n, m);
            double m3 = matrix_get(i, j - 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
        }
    }

    matrix_put(fabs(a[n - 1] - b[m - 1]), n - 1, m - 1, t, n, m);
    for (int i = n - 2; i >= half; --i) {
        double value = matrix_get(i + 1, m - 1, t, n, m) + fabs(a[i] - b[m - 1]);
        matrix_put(value, i, m - 1, t, n, m);
    }
    for (int j = m - 2; j >= 0; --j) {
        double value = matrix_get(n - 1, j + 1, t, n, m) + fabs(a[n - 1] - b[j]);
        matrix_put(value, n - 1, j, t, n, m);
    }

    for (int i = n - 2; i >= half; --i) {
        for (int j = m - 2; j >= 0; --j) {
            double m1 = matrix_get(i + 1, j + 1, t, n, m);
            double m2 = matrix_get(i + 1, j, t, n, m);
            double m3 = matrix_get(i, j + 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
        }
    }

    double d = INFINITY;
    for (int k = 0; k < m - 1; ++k) {
        double x = matrix_get(half - 1, k, t, n, m) + matrix_get(half, k, t, n, m);
        double y = matrix_get(half - 1, k, t, n, m) + matrix_get(half, k + 1, t, n, m);
        d = fmin(d, fmin(x, y));
    }

    double x = matrix_get(half - 1, m - 1, t, n, m) + matrix_get(m - 1, half, t, n, m);
    d = fmin(d, x);

    double rez = d;
    free(t);

    return rez;
}
