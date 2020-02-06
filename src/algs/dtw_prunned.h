//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double matrix_get(int y_pos, int x_pos, double t[], int y_size, int x_size);
void matrix_put(double value, int y_pos, int x_pos, double t[], int y_size, int x_size);

double dtw_prunned(double *a, double *b, double *t, int n, int m) {
    int ws, sc, ec, beg, end, foundSC, ec_next;
    double upper_bound;
    double *upper_bounds = calloc(n, sizeof(double));
    
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, n, m);
    for (int i = 1; i < n; ++i) {
        double value = matrix_get(i - 1, 0, t, n, m) + fabs(a[i] - b[0]);
        matrix_put(value, i, 0, t, n, m);
    }
    for (int i = 1; i < m; ++i) {
        double value = matrix_get(0, i - 1, t, n, m) + fabs(a[0] - b[i]);
        matrix_put(value, 0, i, t, n, m);
    }
    
    ws = (int)fmax(n, m);
    sc = 1;
    ec = 1;
    upper_bounds[n - 1] = fabs(a[n-1] - b[n-1]);
    //printf("%f\t", upper_bounds[n - 1]);
    for (int j = n - 2; j >=0 ; j--) {
        upper_bounds[j] = upper_bounds[j + 1] + fabs(a[j-1] - b[j - 1]);
        //printf("%f\t", upper_bounds[j]);
    }
    //printf("\n");
    //fflush(stdout);

    for (int i = 1; i < n; ++i) {
        upper_bound = upper_bounds[i] + matrix_get(i - 1, i - 1, t, n, m);
        beg = fmax(sc, i - ws);
        end = fmin(i + ws, m);
        foundSC = 0;
        ec_next = i;
        for (int j = beg; j < end; ++j) {
            double m1 = matrix_get(i - 1,  j - 1, t, n, m);
            double m2 = matrix_get(i - 1, j, t, n, m);
            double m3 = matrix_get(i, j - 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);

            if (foundSC == 0 && matrix_get(i, j, t, n, m) <= upper_bound) {
                sc = j;
                foundSC = 1;
            }

            if (matrix_get(i, j, t, n, m) > upper_bound) {
                if (j > ec) {
                    break;
                }
            } else {
                ec_next = j + 1;
            }
        }
        ec = ec_next;
    }

    double rez = matrix_get(n - 1, m - 1, t, n, m);
    return rez;
}