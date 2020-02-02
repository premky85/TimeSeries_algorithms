#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "helpers.h"
#include <math.h>






double construct_path_fw(double *t, int n, int m, int a, int b);

double construct_path_bk(double *t, int n, int m, int a, int b);



/*
double dist(double a, double b){
    return sqrt()
}
 */







/*
double *dtw_fw_bk(double *a, double *b, int n, int m) {
    double *t = malloc((n + 1)* (m + 1) * sizeof(a[0]));
    for (int i = 1; i < n; ++i) {
        matrix_put(INFINITY, i, 0, t, n, m);
        //t[i * m] =  t[i * m - 1] + fabs(a[i] - b[0]);
    }
    for (int i = 1; i < m; ++i) {
        matrix_put(INFINITY, 0, i, t, n, m);
        //t[i] =  t[i - 1] + fabs(a[0] - b[i]);
    }
    matrix_put(0, 0, 0, t, n, m);
    matrix_put(0, n, m, t, n, m);
    int half = floor((double)(n + 1) / 2);
    for (int i = 1; i < half; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            double value = fabs(a[i - 1] - b[j - 1]) + fmin(fmin(matrix_get(i - 1, j, t, n, m), matrix_get(i, j - 1, t, n, m)), matrix_get(i - 1, j - 1, t, n, m));
            matrix_put(value, i, j, t, n, m);
        }
    }
    for (int i = n + 1; i > half; --i) {
        for (int j = m; j > -1; --j) {
            double value = fabs(a[i] - b[j]) + fmin(fmin(matrix_get(i + 1, j, t, n, m), matrix_get(i, j + 1, t, n, m)), matrix_get(i + 1, j + 1, t, n, m));
            matrix_put(value, i, j, t, n, m);
        }
    }
    //double d = INFINITY;


    return t;
}

 */





// Assisting functions

double construct_path_fw(double *t, int n, int m, int a, int b) {
    double sum;
    sum = matrix_get(a, b, t, n, m); // choose starting point
    while (a > 0 || b > 0) {
        double min = INFINITY;
        int tmp_a;
        int tmp_b;
        double m1 = (a - 1 >= 0 && b - 1 >= 0) ? matrix_get(a - 1, b - 1, t, n, m) : INFINITY;
        double m2 = (a - 1 >= 0 && b >= 0) ? matrix_get(a - 1, b, t, n, m) : INFINITY;
        double m3 = (a >= 0 && b - 1 >= 0) ? matrix_get(a, b - 1, t, n, m) : INFINITY;
        if(m1 < m2) {
            min = m1;
            tmp_a = a - 1;
            tmp_b = b - 1;
        } else {
            min = m2;
            tmp_a = a - 1;
            tmp_b = b;
        }
        if(m3 < min) {
            min = m3;
            tmp_a = a;
            tmp_b = b - 1;
        }
        a = tmp_a;
        b = tmp_b;
        sum += min;
    }

    return sum;
}

double construct_path_bk(double *t, int n, int m, int a, int b) {
    double sum;
    sum = matrix_get(a, b, t, n, m); // choose starting point
    while (a < n - 1 || b < m - 1) {
        double min = INFINITY;
        int tmp_a;
        int tmp_b;
        double m1 = (a + 1 <= n && b + 1 <= m) ? matrix_get(a + 1, b + 1, t, n, m) : INFINITY;
        double m2 = (a + 1 <= n && b <= m) ? matrix_get(a + 1, b, t, n, m) : INFINITY;
        double m3 = (a <= n && b + 1 <= m) ? matrix_get(a, b + 1, t, n, m) : INFINITY;
        if (m1 < m2) {
            min = m1;
            tmp_a = a + 1;
            tmp_b = b + 1;
        } else {
            min = m2;
            tmp_a = a + 1;
            tmp_b = b;
        }
        if (m3 < min) {
            min = m3;
            tmp_a = a;
            tmp_b = b + 1;
        }
        a = tmp_a;
        b = tmp_b;
        sum += min;
    }

    return sum;
}

