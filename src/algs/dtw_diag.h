//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>


inline double matrix_get(int y_pos, int x_pos, double t[], int y_size, int x_size);
inline void matrix_put(double value, int y_pos, int x_pos, double t[], int y_size, int x_size);

double dtw_diag(double *a, double *b, double *t, int n, int m) {
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, n, m);
    for (int i = 1; i < n; ++i) {
        double value = matrix_get(i - 1, 0, t, n, m) + fabs(a[i] - b[0]);
        matrix_put(value, i, 0, t, n, m);
    }
    for (int i = 1; i < m; ++i) {
        double value = matrix_get(0, i - 1, t, n, m) + fabs(a[0] - b[i]);
        matrix_put(value, 0, i, t, n, m);
    }
    //int cnt = 0;


    int i;
    int j;
    int upLim;
    for (int k = 1; k <= n + m - 2; ++k) {
        i = k < n ? k : n - 1;
        j = k < n ? 1 : k - n + 1;
        upLim = k < n ? k : n - 1;

        while (j <= upLim) {
            double m1 = matrix_get(i - 1, j, t, n, m);
            double m2 = matrix_get(i, j - 1, t, n, m);
            double m3 = matrix_get(i - 1, j - 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
            i--;
            j++;
        }

    }



/*
    for (int k = 1; k < n; k++) {
        i = k;
        for (int j = 1; j <= k; j++) {
            double m1 = matrix_get(i - 1, j, t, n, m);
            double m2 = matrix_get(i, j - 1, t, n, m);
            double m3 = matrix_get(i - 1, j - 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
            --i;
            //cnt++;
        }
    }

    for (int k = 1; k < n; k++) {
        i = k;
        for (int j = n - 1; j >= k; j--) {
            double m1 = matrix_get(i - 1, j, t, n, m);
            double m2 = matrix_get(i, j - 1, t, n, m);
            double m3 = matrix_get(i - 1, j - 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
            i++;
            //cnt++;
        }
    }

*/

/*
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            double m1 = matrix_get(i - j - 1, j, t, n, m);
            double m2 = matrix_get(i - j - 1, j + 1, t, n, m);
            double m3 = matrix_get(i - j, j, t, n, m);
            double value = fabs(a[i - j] - b[j + 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i - j, j + 1, t, n, m);
            //cnt++;
        }

    }



    for (int j = 2; j < m; ++j) {
        for (int i = 0; i < n - j; ++i) {
            double m1 = matrix_get(n - 1 - i - 1, j + i - 1, t, n, m);
            double m2 = matrix_get(n - 1 - i - 1, j + i, t, n, m);
            double m3 = matrix_get(n - 1 - i, j + i - 1, t, n, m);
            double value = fabs(a[n - 1 - i] - b[j + i]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, n - 1 - i, j + i, t, n, m);
            //cnt++;

        }
    }
     */



     

    //printf("cntDIAG: %d\n", cnt);
    double rez = matrix_get(n - 1, m - 1, t, n, m);
    return rez;
}