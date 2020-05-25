//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NTHR 12

pthread_barrier_t   barrier;

pthread_t threads_diag_cache[NTHR];

double *t;
double *a;
double *b;


typedef struct _thread_data_t_diag_cache {
    int id;
    int n;
    int m;
    int mo;
} thread_data_t_diag_cache;

thread_data_t_diag_cache thr_struct_diag_cache[NTHR];

inline double matrix_get(int x_pos, int y_pos, double t[], int x_size, int y_size);
inline void matrix_put(double value, int x_pos, int y_pos, double t[], int x_size, int y_size);

void diag_thr_cache(void *args) {
    thread_data_t_diag_cache* threadData;
    threadData = (thread_data_t_diag_cache *) args;

    int id = threadData->id;
    int n = threadData->n;
    int m = threadData->m;
    int mo = threadData->mo;

    int nthr = NTHR;


    if (id == 0) {
        for (int i = 1; i < n; ++i) {
            double m1 = matrix_get(i - 1, i - 1, t, n, m);
            double m2 = a[i];
            double m3 = b[0];

            double v = fabs(a[i] - b[0]) + matrix_get(i - 1, i - 1, t, n, m);
            matrix_put(v, i, i, t, n, m);
        }
    } if(nthr > 1)  {
        if (id == 1) {
            for (int i = 1; i < mo; ++i) {
                double m5 = matrix_get(0, i - 1, t, n, m);
                double m2 = a[0];
                double m3 = b[i];


                double v = fabs(a[0] - b[i]) + matrix_get(0, i - 1, t, n, m);
                matrix_put(v, 0, i, t, n, m);
            }
        }

    }
    else {
        for (int i = 1; i < mo; ++i) {
            double m5 = matrix_get(0, i - 1, t, n, m);
            double m2 = a[0];
            double m3 = b[i];


            double v = fabs(a[0] - b[i]) + matrix_get(0, i - 1, t, n, m);
            matrix_put(v, 0, i, t, n, m);
        }
    }

    for (int i = 2; i < n; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(i - 1) / nthr);
        int start = id * step + 1;
        for (int j = start; j < start + step && j < i; ++j) {
            double m1 = matrix_get(j, i - 1, t, n, m);
            double m2 = matrix_get(j - 1, i - 1, t, n, m);
            double m3 = matrix_get(j - 1, i - 2, t, n, m);
            double m4 = a[j];
            double m5 = b[i - j];
            double value = fabs(a[j] - b[i - j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, j, i, t, n, m);
        }
    }

    for (int i = n; i < (2 * mo - n + 1); ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)((2 * n - 1) - i - 1) / nthr);
        int start = id * step;
        for (int j = start; j < start + step && j < (2 * n - 1) - i; ++j) {
            double m1 = matrix_get(j + 1, i - 1, t, n, m);
            double m2 = matrix_get(j, i - 1, t, n, m);
            double m3 = matrix_get(j, i - 2, t, n, m);
            double m4 = a[j + 1];
            double m5 = b[((2 * n - 1) - i) - j];
            double value = fabs(a[j + 1] - b[((2 * n - 1) - i) - j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, j, i, t, n, m);
        }
    }

    for (int i = (2 * mo - n + 1); i < m ; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)((2 * n - 1) - i) / nthr);
        int start = id * step;
        for (int j = start; j < start + step && j < (2 * n - 1) - i; ++j) {
            double m1 = matrix_get(j + 1, i - 1, t, n, m);
            double m2 = matrix_get(j, i - 1, t, n, m);
            double m3 = matrix_get(j + 1, i - 2, t, n, m);
            double m4 = a[j + 1 + (i - n)];
            double m5 = b[((2 * n - 1) - i) - j + (i - n)];
            double value = fabs(a[j + 1 + (i - n)] - b[n - j - 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, j, i, t, n, m);
        }
    }
    pthread_exit(NULL);
}

double dtw_diag_par_cache(double *a_, double *b_, int n, int m) {
    int mo = m;
    m = n + m - 1;
    double *t_ = (double*)malloc(m * n * sizeof(double));

    t = t_;
    a = a_;
    b = b_;

    pthread_barrier_init(&barrier, NULL, NTHR);
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, n, m);

    for (int i = 0; i < NTHR; ++i) {
        thr_struct_diag_cache[i].id = i;
        thr_struct_diag_cache[i].n = n;
        thr_struct_diag_cache[i].m = m;
        thr_struct_diag_cache[i].mo = mo;
        pthread_create(&threads_diag_cache[i],
                       NULL,
                       diag_thr_cache,
                       &thr_struct_diag_cache[i]);
    }

    for (int i = 0; i < NTHR; ++i) {
        pthread_join(threads_diag_cache[i], NULL);
    }

    //printf("cntDIAG: %d\n", cnt);
    double rez = matrix_get(0, m - 1, t, n, m);
    free(t_);

    return rez;
}