//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double matrix_get(int y_pos, int x_pos, double t[], int y_size, int x_size);
void matrix_put(double value, int y_pos, int x_pos, double t[], int y_size, int x_size);

double dtw_pruned(double *a, double *b, int n, int m) {
    double cnt;

    int ws, sc, ec, beg, end, foundSC, ec_next;

    int large = fmax(m, n);
    if (large == m) {
        double *tmp = a;
        a = b;
        b = tmp;

        int tmp_ = m;
        m = n;
        n = tmp_;
    }

    double upper_bound;
    double *upper_bounds = calloc(large, sizeof(double));
    double *t = (double*)malloc(n * m * sizeof(double));
    memset(t, INFINITY, n * m *  sizeof(double));

    matrix_put(fabs(a[0] - b[0]), 0, 0, t, n, m);
    for (int i = 1; i < n; ++i) {
        double value = matrix_get(i - 1, 0, t, n, m) + fabs(a[i] - b[0]);
        matrix_put(value, i, 0, t, n, m);
    }
    for (int j = 1; j < m; ++j) {
        double value = matrix_get(0, j - 1, t, n, m) + fabs(a[0] - b[j]);
        matrix_put(value, 0, j, t, n, m);
    }



    //ws = (int)fmax(n, m);
    sc = 1;
    ec = 1;
    upper_bounds[n - 1] = fabs(a[n-1] - b[m-1]);
    //printf("%f\t", upper_bounds[n - 1]);



    for (int i = m - 2; i > n - 2 ; i--) {
        upper_bounds[i] = upper_bounds[i + 1] + fabs(a[i] - b[i]);
        //printf("%f\t", upper_bounds[j]);
    }

    for (int i = n - 2; i >=0 ; i--) {
        upper_bounds[i] = upper_bounds[i + 1] + fabs(a[i] - b[i]);
        //printf("%f\t", upper_bounds[j]);
    }

    for (int i = 1; i < n; ++i) {
        beg = sc;//fmax(sc, i - ws);
        end = m;//fmin(i + ws, n);
        foundSC = 0;
        ec_next = i;
        for (int j = beg; j < end; ++j) {

            double m1 = matrix_get(i - 1,  j - 1, t, n, m);
            double m2 = matrix_get(i - 1, j, t, n, m);
            double m3 = matrix_get(i, j - 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
            //cnt += 1;
            if (i == j) {
                upper_bound = upper_bounds[i + 1] + matrix_get(i, j, t, n, m);
            }


            if (matrix_get(i, j, t, n, m) > upper_bound) {
                if (foundSC == 0) {
                    sc = j + 1;
                }
                if (j >= ec) {
                    break;
                }
            } else {
                foundSC = 1;
                ec_next = j + 1;

            }


            /*
            if (foundSC == 0 && matrix_get(i, j, t, m, n) <= upper_bound) {
                sc = i;
                foundSC = 1;
            }

            if (matrix_get(i, j, t, m, n) > upper_bound) {
                if (i > ec) {
                    break;
                }
            } else {
                ec_next = i + 1;
            }
             */

        }

        ec = ec_next;

    }

    double rez = matrix_get(n - 1, m - 1, t, n, m);
    free(t);

    //printf("Pruned: %f\n", 1 - cnt/n/m);
    return rez;

}