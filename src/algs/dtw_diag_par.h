//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NTHR 6

pthread_barrier_t   barrier;

pthread_t threads_diag[NTHR];

typedef struct thread_data_t_diag {
    double *t;
    double *a;
    double *b;
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


    double *t = threadData->t;
    double *a = threadData->a;
    double *b = threadData->b;

    int id = threadData->id;
    int n = threadData->n;
    int m = threadData->m;

    if (id == 0) {
        for (int i = 1; i < n; ++i) {
            double value = matrix_get(i - 1, 0, t, n, m) + fabs(a[i] - b[0]);
            matrix_put(value, i, 0, t, n, m);
        }
    } if(NTHR > 1)  {
        if (id == 1) {
            for (int j = 1; j < m; ++j) {
                double value = matrix_get(0, j - 1, t, m, n) + fabs(a[0] - b[j]);
                matrix_put(value, 0, j, t, n, m);
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
    for (int i = 1; i < m; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(i) / NTHR);
        int start = id * step;

        for (int j = start; j < start + step && j < i; ++j) {
            double m1 = matrix_get(i - j - 1, j, t, n, m);
            double m2 = matrix_get(i - j - 1, j + 1, t, n, m);
            double m3 = matrix_get(i - j, j, t, n, m);
            double value = fabs(a[i - j] - b[j + 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i - j, j + 1, t, n, m);
        }
    }

    for (int i = m; i < n; i++) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(m - 1) / NTHR);
        int start = id * step;

        for (int j = start; j < start + step && j < m - 1; ++j) {
            double m1 = matrix_get(i - j, j, t, n, m);
            double m2 = matrix_get(i - j - 1, j, t, n, m);
            double m3 = matrix_get(i - j - 1, j + 1, t, n, m);
            double value = fabs(a[i - j] - b[j + 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i - j, j + 1, t, n, m);
        }
    }


    for (int i = n; i < n + m - 1; i++) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(n + m - i - 1) / NTHR);
        int start = id * step;
        for (int j = start; j < start + step && j < n + m - i - 2; ++j) {
            double m1 = matrix_get(n - 1 - j, j + 1 + i - n, t, n, m);
            double m2 = matrix_get(n - 2 - j, j + 1 + i - n, t, n, m);
            double m3 = matrix_get(n - 2 - j, j + 2 + i - n, t, n, m);
            double value = fabs(a[n - 1 - j] - b[j + 2 + i - n]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, n - 1 - j, j + 2 + i - n, t, n, m);
        }
    }
    pthread_exit(NULL);
}

double dtw_diag_par(double *a_, double *b_, int n, int m) {
    double *t_ = (double*)malloc(m * n * sizeof(double));
    pthread_barrier_init(&barrier, NULL, NTHR);
    matrix_put(fabs(a_[0] - b_[0]), 0, 0, t_, n, m);
    for (int i = 0; i < NTHR; ++i) {

        thr_struct_diag[i].t = t_;
        thr_struct_diag[i].a = a_;
        thr_struct_diag[i].b = b_;
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

    double rez = matrix_get(n - 1, m - 1, t_, n, m);
    free(t_);

    return rez;
}