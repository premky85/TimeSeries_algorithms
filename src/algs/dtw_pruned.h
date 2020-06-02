//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double matrix_get(int x_pos, int y_pos, double t[], int x_size, int y_size);
void matrix_put(double value, int x_pos, int y_pos, double t[], int x_size, int y_size);

double dtw_pruned(double *a, double *b, int m, int n) {
    double cnt;

    int ws, sc, ec, beg, end, foundSC, ec_next;
    double upper_bound;
    double *upper_bounds = calloc(m, sizeof(double));
    double *t = (double*)malloc(n * m * sizeof(double));
    memset(t, INFINITY, n * m *  sizeof(double));

    matrix_put(fabs(a[0] - b[0]), 0, 0, t, m, n);
    for (int i = 1; i < m; ++i) {
        double value = matrix_get(i - 1, 0, t, m, n) + fabs(a[i] - b[0]);
        matrix_put(value, i, 0, t, m, n);
    }
    for (int j = 1; j < n; ++j) {
        double value = matrix_get(0, j - 1, t, m, n) + fabs(a[0] - b[j]);
        matrix_put(value, 0, j, t, m, n);
    }



    //ws = (int)fmax(n, m);
    sc = 1;
    ec = 1;
    upper_bounds[m - 1] = fabs(a[m-1] - b[n-1]);
    //printf("%f\t", upper_bounds[n - 1]);

    for (int i = m - 2; i >=0 ; i--) {
        upper_bounds[i] = upper_bounds[i + 1] + fabs(a[i] - b[i]);
        //printf("%f\t", upper_bounds[j]);
    }
    //cnt = n + m - 1;

    //printf("\n");
    //fflush(stdout);

    for (int j = 1; j < n; ++j) {


        beg = sc;//fmax(sc, i - ws);
        end = n;//fmin(i + ws, n);
        foundSC = 0;
        ec_next = j;
        for (int i = beg; i < end; ++i) {

            double m1 = matrix_get(i - 1,  j - 1, t, m, n);
            double m2 = matrix_get(i - 1, j, t, m, n);
            double m3 = matrix_get(i, j - 1, t, m, n);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, m, n);
            //cnt += 1;
            if (i == j) {
                upper_bound = upper_bounds[i + 1] + matrix_get(i, j, t, m, n);
            }


            if (matrix_get(i, j, t, m, n) > upper_bound) {
                if (foundSC == 0) {
                    sc = i + 1;
                }
                if (i >= ec) {
                    break;
                }
            } else {
                foundSC = 1;
                ec_next = i + 1;

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

    double rez = matrix_get(m - 1, n - 1, t, m, n);
    free(t);

    //printf("Pruned: %f\n", 1 - cnt/n/m);
    return rez;

}