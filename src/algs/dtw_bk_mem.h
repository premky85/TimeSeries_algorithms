//
// Created by premk on 1. 03. 20.
//

#include <math.h>
#include <stdlib.h>

double dtw_bk_mem(double *a, double *b, int n, int m) {
    double *t1 = (double*)malloc(m * sizeof(double));
    double *t2 = (double*)malloc(m * sizeof(double));
    char current = 0;

    t1[m - 1] = fabs(a[n - 1] - b[m - 1]);
    for (int j = m - 2; j >= 0; --j) {
        double x = fabs(a[n - 1] - b[j]) + t1[j + 1];
        t1[j] = x;
    }

    double *prev = t1;
    double *cur = t2;
    for (int i = n - 2; i >= 0; --i) {
        cur[m - 1] = fabs(a[i] - b[m - 1]) + prev[m - 1];
        for (int  j = m - 2; j >= 0; --j) {
            double m1 = prev[j];
            double m2 = prev[j + 1];
            double m3 = cur[j + 1];
            double tmp = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            cur[j] = tmp;
        }

        current = 1 - current;
        prev = current == 0 ? t1 : t2;
        cur = current == 0 ? t2 : t1;

    }

    double rez = prev[0];
    free(t1);
    free(t2);

    return rez;


}
