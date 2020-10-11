//
// Created by premk on 10. 06. 20.
//

#ifndef TIMESERIES_DTW_EUCLIDEAN_H
#define TIMESERIES_DTW_EUCLIDEAN_H

#endif //TIMESERIES_DTW_EUCLIDEAN_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

inline double matrix_get(int x_pos, int y_pos, double t[], int x_size, int y_size);
inline void matrix_put(double value, int x_pos, int y_pos, double t[], int x_size, int y_size);

double euclidean(double *a, double *b, int m, int n) {
    double rez = 0;
    if (m == n) {
        for (int i = 0; i < m; ++i) {
            rez += fabs(a[i] - b[i]);
        }
    } else {
        int large = fmax(m, n);
        if (large == m) {
            double *tmp = a;
            a = b;
            b = tmp;

            int tmp_ = m;
            m = n;
            n = tmp_;
        }
        for (int i = 0; i < m; ++i) {
            rez += fabs(a[i] - b[i]);
        }
        for (int j = m; j < n; ++j) {
            rez += fabs(a[m - 1] - b[j]);
        }
    }

    return rez;
}