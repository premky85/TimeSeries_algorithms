//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>


inline double matrix_get(int x_pos, int y_pos, double t[], int x_size, int y_size);
inline void matrix_put(double value, int x_pos, int y_pos, double t[], int x_size, int y_size);

double dtw_diag(double *a, double *b, int m, int n) {
    double *t = (double*)malloc(n * m * sizeof(double));
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, m, n);
    for (int i = 1; i < m; ++i) {
        double value = matrix_get(i - 1, 0, t, m, n) + fabs(a[i] - b[0]);
        matrix_put(value, i, 0, t, m, n);
    }
    for (int j = 1; j < n; ++j) {
        double value = matrix_get(0, j - 1, t, m, n) + fabs(a[0] - b[j]);
        matrix_put(value, 0, j, t, m, n);
    }


    for (int i = 1; i < m; ++i) {
        for (int j = 0; j < i; ++j) {
            double m1 = matrix_get(i - j - 1, j, t, m, n);
            double m2 = matrix_get(i - j - 1, j + 1, t, m, n);
            double m3 = matrix_get(i - j, j, t, m, n);
            double value = fabs(a[i - j] - b[j + 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i - j, j + 1, t, m, n);
            //cnt++;
        }

    }


    for (int i = m; i < n; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            double m1 = matrix_get(m - j - 1, j + 1 + i - m, t, m, n);
            double m2 = matrix_get(m - j - 2, j + 1 + i - m, t, m, n);
            double m3 = matrix_get(m - j - 2, j + 2 + i - m, t, m, n);
            double value = fabs(a[m - 1 - j] - b[j + 2 + i - m]) + fmin(m1, fmin(m2, m3));
            double minmin = fmin(m1, fmin(m2, m3));
            double ababababa = fabs(a[n - 1 - j] - b[j + 2 + i - n]);
            double lala = a[n - 1 - j];
            double blala = b[j + 2 + i - n];
            matrix_put(value, m - j - 1, j + 2 + i - m, t, m, n);
            //cnt++;
        }

    }


    for (int i = n; i < m + n - 1; ++i) {
        for (int j = 0; j < n + m - i - 2; ++j) {
            double m1 = matrix_get(m - 1 - j, i - m + 1 + j, t, m, n);
            double m2 = matrix_get(m - 2 - j, i - m + 1 + j, t, m, n);
            double m3 = matrix_get(m - 2 - j, i - m + 2 + j, t, m, n);
            double value = fabs(a[m - 1 - j] - b[j + 2 + i - m]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, m - 1 - j, j + 2 + i - m, t, m, n);
            //cnt++;

        }
    }




     

    //printf("cntDIAG: %d\n", cnt);
    double rez = matrix_get(m - 1, n - 1, t, m, n);
    free(t);
    return rez;
}