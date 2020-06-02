//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>

inline double matrix_get(int x_pos, int y_pos, double t[], int x_size, int y_size);
inline void matrix_put(double value, int x_pos, int y_pos, double t[], int x_size, int y_size);

double dtw_fwbk(double *a, double *b, int m, int n) {
    double *t = (double*)malloc(m * n * sizeof(double));


    int half = floor((double)(n) / 2);
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, m, n);
    matrix_put(fabs(a[m - 1] - b[n - 1]), m - 1, n - 1, t, m, n);
    for (int j = 1; j < half; ++j) {
        double value = matrix_get(0, j - 1, t, m, n) + fabs(a[0] - b[j]);
        matrix_put(value, 0, j, t, m, n);
    }
    for (int i = 1; i < m; ++i) {
        double value = matrix_get(i - 1, 0, t, n, m) + fabs(a[i] - b[0]);
        matrix_put(value, i, 0, t, m, n);
    }

    for (int j = 1; j < half; ++j) {
        for (int i = 1; i < m; ++i) {
            double m1 = matrix_get(i - 1, j - 1, t, m, n);
            double m2 = matrix_get(i - 1, j, t, m, n);
            double m3 = matrix_get(i, j - 1, t, m, n);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, m, n);
        }
    }

    for (int j = n - 2; j >= half; --j) {
        double value = matrix_get(m - 1, j + 1, t, m, n) + fabs(a[m - 1] - b[j]);
        matrix_put(value, m - 1, j, t, m, n);
    }
    for (int i = m - 2; i >= 0; --i) {
        double value = matrix_get(i + 1, n - 1, t, m, n) + fabs(a[i] - b[n - 1]);
        matrix_put(value, i, n - 1, t, m, n);
    }

    for (int j = n - 2; j >= half; --j) {
        for (int i = m - 2; i >= 0; --i) {
            double m1 = matrix_get(i + 1, j + 1, t, m, n);
            double m2 = matrix_get(i + 1, j, t, m, n);
            double m3 = matrix_get(i, j + 1, t, m, n);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, m, n);
        }

    }

    double d = INFINITY;
    //double down_start = INFINITY;
    //double up_start = INFINITY;
    for (int k = 0; k < m - 1; ++k) {
        double x = matrix_get(k, half - 1, t, m, n) + matrix_get(k, half, t, m, n);
        double y = matrix_get(k, half - 1, t, m, n) + matrix_get(k + 1, half, t, m, n);
        //double z = matrix_get(half - 1, k, t, n, m) + matrix_get(half, k + 1, t, n, m);
        d = fmin(d, fmin(x, y));
        /*
        if (d == x) {
            down_start = k;//matrix_get(half, k, t, n, m);
            up_start = k;//matrix_get(half - 1, k, t, n, m);
        } else if (d == y) {
            down_start = k + 1;//matrix_get(half, k + 1, t, n, m);
            up_start = k;//matrix_get(half - 1, k, t, n, m);
        }
         */
    }

    double x = matrix_get(m - 1, half - 1, t, m, n) + matrix_get(m - 1, half, t, m, n);
    //double z = matrix_get(half - 1, k, t, n, m) + matrix_get(half, k + 1, t, n, m);
    d = fmin(d, x);

    /*
    if (d == x) {
        down_start = m;//matrix_get(half, k, t, n, m);
        up_start = m;//matrix_get(half - 1, k, t, n, m);
    }
     */

    double rez = d;
    free(t);


    return rez;
}
