//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

inline double matrix_get(int x_pos, int y_pos, double t[], int x_size, int y_size);
inline void matrix_put(double value, int x_pos, int y_pos, double t[], int x_size, int y_size);

double dtw_fw(double *a, double *b, int m, int n) {
    double *t = (double*)malloc(n * m * sizeof(double));


    matrix_put(fabs(a[0] - b[0]), 0, 0, t, m, n);
    for (int i = 1; i < m; ++i) {
        double value = matrix_get(i - 1, 0, t, n, m) + fabs(a[i] - b[0]);
        matrix_put(value, i, 0, t, m, n);
    }
    for (int j = 1; j < n; ++j) {
        double value = matrix_get(0, j - 1, t, m, n) + fabs(a[0] - b[j]);
        matrix_put(value, 0, j, t, m, n);
    }

    //int cnt = 0;
    for (int j = 1; j < n; ++j) {       // po y
        for (int i = 1; i < m; ++i) {   // po x
            double m1 = matrix_get(i - 1, j - 1, t, m, n);
            double m2 = matrix_get(i - 1, j, t, m, n);
            double m3 = matrix_get(i, j - 1, t, m, n);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, m, n);
            //cnt++;
        }
    }

    //printf("cntFW: %d\n", cnt);

    double rez = matrix_get(m - 1, n - 1, t, m, n);
    free(t);

    return rez;
}
