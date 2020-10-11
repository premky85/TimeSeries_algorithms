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
    double *t1 = (double*)malloc(m * sizeof(double));
    double *t2 = (double*)malloc(m * sizeof(double));
    char current = 0;

    t1[0] = fabs(a[0] - b[0]);
    for (int j = 1; j < m; ++j) {
        t1[j] = fabs(a[0] - b[j]) + t1[j - 1];
    }

    double *prev = t1;
    double *cur = t2;
    for (int i = 1; i < n; ++i) {
        cur[0] = fabs(a[i] - b[0]) + prev[0];
        for (int j = 1; j < m; ++j) {
            double m1 = prev[j];
            double m2 = prev[j - 1];
            double m3 = cur[j - 1];
            double tmp = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            cur[j] = tmp;//fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
        }



        current = 1 - current;
        prev = current == 0 ? t1 : t2;
        cur = current == 0 ? t2 : t1;

    }

    double rez = prev[m - 1];
    free(t1);
    free(t2);

    return rez;
}