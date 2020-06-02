#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double dtw_diag_cache_mem(double *a, double *b, int m, int n) {
    int no = n;
    n = m + n - 1;
    double  *t [3];
    double *t1 = (double*)malloc(m * sizeof(double));
    double *t2 = (double*)malloc(m * sizeof(double));
    double *t3 = (double*)malloc(m * sizeof(double));
    char cur = 2;
    char prev = 1;
    char prevprev = 0;
    t[0] = t1;
    t[1] = t2;
    t[2] = t3;



    t[0][0] = fabs(a[0] - b[0]);
    t[1][0] = fabs(a[0] - b[1]) + t[0][0];
    t[1][1] = fabs(a[1] - b[0]) + t[0][0];

    for (int i = 2; i < m; ++i) {
        for (int j = 1; j < i; ++j) {
            double m1 = t[prevprev][j - 1];
            double m2 = t[prev][j];
            double m3 = t[prev][j - 1];
            double m4 = a[j];
            double m5 = b[i - j];
            double value = fabs(a[j] - b[i - j]) + fmin(m1, fmin(m2, m3));
            t[cur][j] = value;
        }

        cur = (cur + 1) % 3;
        prev = (prev + 1) % 3;
        prevprev = (prevprev + 1) % 3;
        t[prev][0] = fabs(a[0] - b[i]) + t[prevprev][0];
        t[prev][i] = fabs(a[i] - b[0]) + t[prevprev][i - 1];
    }

    for (int i = m; i < no; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            double m1 = t[prev][j + 1];
            double m2 = t[prev][j];
            double m3 = t[prevprev][j];
            double m4 = a[j + 1];
            double m5 = b[((2 * m - 1) - i) - j + 2*(i - m)];
            double value = fabs(a[j + 1] - b[((2 * m - 1) - i) - j + 2*(i - m)]) + fmin(m1, fmin(m2, m3));
            t[cur][j + 1] = value;
        }
        cur = (cur + 1) % 3;
        prev = (prev + 1) % 3;
        prevprev = (prevprev + 1) % 3;
    }

    for (int i = no; i < no + 1; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            double m1 = t[prev][j + 1];
            double m2 = t[prev][j];
            double m3 = t[prevprev][j];
            double m4 = a[j + 1];
            double m5 = b[no - j - 1];
            double value = fabs(a[j + 1] - b[no - j - 1]) + fmin(m1, fmin(m2, m3));
            t[cur][j] = value;
        }
        cur = (cur + 1) % 3;
        prev = (prev + 1) % 3;
        prevprev = (prevprev + 1) % 3;
    }


    for (int i = no + 1; i < n ; ++i) {
        for (int j = 0; j < m + no - i - 1; ++j) {
            double m1 = t[prev][j + 1];
            double m2 = t[prev][j];
            double m3 = t[prevprev][j + 1];
            double m4 = a[j + 1 + i - no];
            double m5 = b[no - j - 1];
            double value = fabs(a[j + 1 + i - no] - b[no - j - 1]) + fmin(m1, fmin(m2, m3));
            t[cur][j] = value;
        }
        cur = (cur + 1) % 3;
        prev = (prev + 1) % 3;
        prevprev = (prevprev + 1) % 3;
    }

    double rez = t[prev][0];
    free(t1);
    free(t2);
    free(t3);

    return rez;
}