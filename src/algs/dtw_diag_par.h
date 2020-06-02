//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NTHR 8

pthread_barrier_t   barrier;

pthread_t threads_diag[NTHR];

double *t;
double *a;
double *b;


typedef struct _thread_data_t_diag {
    int id;
    int n;
    int m;
} thread_data_t_diag;

thread_data_t_diag thr_struct_diag[NTHR];

inline double matrix_get(int x_pos, int y_pos, double t[], int x_size, int y_size);
inline void matrix_put(double value, int x_pos, int y_pos, double t[], int x_size, int y_size);

void diag_thr(void *args) {
    thread_data_t_diag* threadData;
    threadData = (thread_data_t_diag *) args;

    int id = threadData->id;
    int n = threadData->n;
    int m = threadData->m;

    int dif = n == m ? 0 : 1;


    if (id == 0) {
        for (int i = 1; i < m; ++i) {
            double value = matrix_get(i - 1, 0, t, m, n) + fabs(a[i] - b[0]);
            matrix_put(value, i, 0, t, m, n);
        }
    } if(NTHR > 1)  {
        if (id == 1) {
            for (int j = 1; j < n; ++j) {
                double value = matrix_get(0, j - 1, t, m, n) + fabs(a[0] - b[j]);
                matrix_put(value, 0, j, t, m, n);
            }
        }
    } else {
        for (int j = 1; j < n; ++j) {
            double value = matrix_get(0, j - 1, t, m, n) + fabs(a[0] - b[j]);
            matrix_put(value, 0, j, t, m, n);
        }
    }
    pthread_barrier_wait(&barrier);
    if (id == 0) {
        double m5 = matrix_get(0, 0, t, m, n);
        double m2 = matrix_get(0, 1, t, m, n);
        double m3 = matrix_get(1, 0, t, m, n);


        double v = fabs(a[1] - b[1]) + fmin(m5, fmin(m2, m3));
        matrix_put(v, 1, 1, t, m, n);
    }

    //
    for (int i = 2; i < m; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(i) / NTHR);
        int start = id * step;

        for (int j = start; j < start + step && j < i; ++j) {
            double m1 = matrix_get(i - j - 1, j, t, m, n);
            double m2 = matrix_get(i - j - 1, j + 1, t, m, n);
            double m3 = matrix_get(i - j, j, t, m, n);
            double value = fabs(a[i - j] - b[j + 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i - j, j + 1, t, m, n);

            //cnt++;
        }
    }

    for (int i = m; i < n; i++) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(m - 1) / NTHR);
        int start = id * step;


        for (int j = start; j < start + step && j < m - 1; ++j) {
            double m1 = matrix_get(m - j - 1, j + 1 + i - m, t, m, n);
            double m2 = matrix_get(m - j - 2, j + 1 + i - m, t, m, n);
            double m3 = matrix_get(m - j - 2, j + 2 + i - m, t, m, n);
            double value = fabs(a[m - 1 - j] - b[j + 2 + i - m]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, m - j - 1, j + 2 + i - m, t, m, n);

            //cnt++;
        }
    }


    for (int i = n; i < n + m - 1; i++) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(n + m - i - 1) / NTHR);
        int start = id * step;


        for (int j = start; j < start + step && j < n + m - i - 1 - dif; ++j) {
            double m1 = matrix_get(n - 2 - j, i - m + 1 + j, t, m, n);
            double m2 = matrix_get(n - 3 - j, i - m + 1 + j, t, m, n);
            double m3 = matrix_get(n - 3 - j, i - m + 2 + j, t, m, n);
            double value = fabs(a[m - 1 - j] - b[j + 1 + i - m + dif]) + fmin(m1, fmin(m2, m3));

            matrix_put(value, m - 1 - j, j + 1 + i - m + dif, t, m, n);
        }
    }
    pthread_exit(NULL);
}

double dtw_diag_par(double *a_, double *b_, int m, int n) {
    double *t_ = (double*)malloc(m * n * sizeof(double));

    t = t_;
    a = a_;
    b = b_;

    pthread_barrier_init(&barrier, NULL, NTHR);
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, m, n);
    for (int i = 0; i < NTHR; ++i) {
        thr_struct_diag[i].id = i;
        thr_struct_diag[i].n = n;
        thr_struct_diag[i].m = m;
        pthread_create(&threads_diag[i],
                       NULL,
                       (void *)diag_thr,
                       &thr_struct_diag[i]);
    }

    for (int i = 0; i < NTHR; ++i) {
        pthread_join(threads_diag[i], NULL);
    }

    //printf("cntDIAG: %d\n", cnt);
    double rez = matrix_get(m - 1, n - 1, t, m, n);
    free(t_);

    return rez;
}