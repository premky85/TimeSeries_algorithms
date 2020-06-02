//
// Created by premk on 1. 03. 20.
//

#include <math.h>
#include <stdlib.h>

double dtw_bk_mem(double *a, double *b, int m, int n) {
    double *t1 = (double*)malloc(m * sizeof(double));
    double *t2 = (double*)malloc(m * sizeof(double));
    char current = 0;

    t1[m - 1] = fabs(a[m - 1] - b[n - 1]);
    for (int i = m - 2; i >= 0; --i) {
        double x = fabs(a[i] - b[n - 1]) + t1[i + 1];
        t1[i] = x;
    }

    double *prev = t1;
    double *cur = t2;
    for (int j = n - 2; j >= 0; --j) {
        cur[m - 1] = fabs(a[m - 1] - b[j]) + prev[m - 1];
        for (int i = m - 2; i >= 0; --i) {
            double m1 = prev[i];
            double m2 = prev[i + 1];
            double m3 = cur[i + 1];
            double tmp = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            cur[i] = tmp;//fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
        }



        current = 1 - current;
        prev = current == 0 ? t1 : t2;
        cur = current == 0 ? t2 : t1;

    }

    //printf("cntFW: %d\n", cnt);

    double rez = prev[0];
    free(t1);
    free(t2);

    return rez;


}
