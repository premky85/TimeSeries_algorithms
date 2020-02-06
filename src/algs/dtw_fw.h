//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double matrix_get(int y_pos, int x_pos, double t[], int y_size, int x_size);
void matrix_put(double value, int y_pos, int x_pos, double t[], int y_size, int x_size);

double dtw_fw(double *a, double *b, double *t, int n, int m) {
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, n, m);
    for (int i = 1; i < n; ++i) {
        double value = matrix_get(i - 1, 0, t, n, m) + fabs(a[i] - b[0]);
        matrix_put(value, i, 0, t, n, m);
    }
    for (int i = 1; i < m; ++i) {
        double value = matrix_get(0, i - 1, t, n, m) + fabs(a[0] - b[i]);
        matrix_put(value, 0, i, t, n, m);
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            double m1 = matrix_get(i - 1, j - 1, t, n, m);
            double m2 = matrix_get(i - 1, j, t, n, m);
            double m3 = matrix_get(i, j - 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);

        }
    }
    double rez = matrix_get(n - 1, m - 1, t, n, m);
    return rez;
}
