//
// Created by premk on 1. 03. 20.
//

#ifndef TIMESERIES_DTW_DTW_FW_MEM_H
#define TIMESERIES_DTW_DTW_FW_MEM_H

#endif //TIMESERIES_DTW_DTW_FW_MEM_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double dtw_fw_mem(double *a, double *b, int n, int m) {
    double *t1 = (double*)malloc(n * sizeof(double));
    double *t2 = (double*)malloc(n * sizeof(double));
    char current = 0;

    t1[0] = fabs(a[0] - b[0]);
    for (int i = 1; i < n; ++i) {
        t1[i] = fabs(a[i] - b[0]) + t1[i - 1];
    }

    double *prev = t1;
    double *cur = t2;
    for (int j = 1; j < m; ++j) {
        cur[0] = fabs(a[0] - b[j]) + prev[0];
        for (int i = 1; i < n; ++i) {
            double m1 = prev[i];
            double m2 = prev[i - 1];
            double m3 = cur[i - 1];
            double tmp = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            cur[i] = tmp;//fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
        }



        current = 1 - current;
        prev = current == 0 ? t1 : t2;
        cur = current == 0 ? t2 : t1;

    }

    //printf("cntFW: %d\n", cnt);

    double rez = prev[n - 1];
    free(t1);
    free(t2);

    return rez;
}