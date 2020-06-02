//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>


inline double matrix_get(int x_pos, int y_pos, double t[], int x_size, int y_size);
inline void matrix_put(double value, int x_pos, int y_pos, double t[], int x_size, int y_size);

double dtw_diag_cache(double *a, double *b, int m, int n) {
    int no = n;
    n = m + n - 1;
    double *t = (double*)malloc(n * m * sizeof(double));
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, m, n);
    for (int i = 1; i < m; ++i) {
        double m1 = matrix_get(i - 1, i - 1, t, m, n);
        double m2 = a[i];
        double m3 = b[0];

        double v = fabs(a[i] - b[0]) + matrix_get(i - 1, i - 1, t, m, n);
        matrix_put(v, i, i, t, m, n);
    }
    for (int i = 1; i < no; ++i) {
        double m5 = matrix_get(0, i - 1, t, m, n);
        double m2 = a[0];
        double m3 = b[i];


        double v = fabs(a[0] - b[i]) + matrix_get(0, i - 1, t, m, n);
        matrix_put(v, 0, i, t, m, n);
    }

    for (int i = 2; i < m; ++i) {
        for (int j = 1; j < i; ++j) {
            double m1 = matrix_get(j, i - 1, t, m, n);
            double m2 = matrix_get(j - 1, i - 1, t, m, n);
            double m3 = matrix_get(j - 1, i - 2, t, m, n);
            double m4 = a[j];
            double m5 = b[i - j];
            double value = fabs(a[j] - b[i - j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, j, i, t, m, n);
        }
    }

    for (int i = m; i < no; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            double m1 = matrix_get(j + 1, i - 1, t, m, n);
            double m2 = matrix_get(j, i - 1, t, m, n);
            double m3 = matrix_get(j, i - 2, t, m, n);
            double m4 = a[j + 1];
            double m5 = b[((2 * m - 1) - i) - j + 2*(i - m)];
            double value = fabs(a[j + 1] - b[((2 * m - 1) - i) - j + 2*(i - m)]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, j + 1, i, t, m, n);
        }
    }

    for (int i = no; i < no + 1; ++i) {
        for (int j = 0; j < m + no - i - 1; ++j) {
            double m1 = matrix_get(j + 1, i - 1, t, m, n);
            double m2 = matrix_get(j, i - 1, t, m, n);
            double m3 = matrix_get(j , i - 2, t, m, n);
            double m4 = a[j + 1];
            double m5 = b[no - j - 1];
            double value = fabs(a[j + 1] - b[no - j - 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, j, i, t, m, n);
        }
    }

    for (int i = no + 1; i < n ; ++i) {
        for (int j = 0; j < m + no - i - 1; ++j) {
            double m1 = matrix_get(j, i - 1, t, m, n);
            double m2 = matrix_get(j + 1, i - 1, t, m, n);
            double m3 = matrix_get(j + 1, i - 2, t, m, n);
            double m4 = a[j + 1 + i - no];
            double m5 = b[no - j - 1];
            double value = fabs(a[j + 1 + i - no] - b[no - j - 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, j, i, t, m, n);
        }
    }

    double rez = matrix_get(0, n - 1, t, m, n);

    free(t);
    return rez;
}