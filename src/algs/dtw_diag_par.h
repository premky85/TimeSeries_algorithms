//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NTHR 12

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
        for (int i = 1; i < n; ++i) {
            double value = matrix_get(i - 1, 0, t, n, m) + fabs(a[i] - b[0]);
            matrix_put(value, i, 0, t, n, m);
        }
    } if(NTHR > 1)  {
        if (id == 1) {
            for (int i = 1; i < m; ++i) {
                double value = matrix_get(0, i - 1, t, n, m) + fabs(a[0] - b[i]);
                matrix_put(value, 0, i, t, n, m);
            }
        }
    } else {
        for (int i = 1; i < m; ++i) {
            double value = matrix_get(0, i - 1, t, n, m) + fabs(a[0] - b[i]);
            matrix_put(value, 0, i, t, n, m);
        }
    }
    pthread_barrier_wait(&barrier);
    if (id == 0) {
        double m5 = matrix_get(0, 0, t, n, m);
        double m2 = matrix_get(0, 1, t, n, m);
        double m3 = matrix_get(1, 0, t, n, m);


        double v = fabs(a[1] - b[1]) + fmin(m5, fmin(m2, m3));
        matrix_put(v, 1, 1, t, n, m);
    }

    //
    for (int i = 2; i < n; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(i) / NTHR);
        int start = id * step;

        for (int j = start; j < start + step && j < i; ++j) {
            double m1 = matrix_get(i - j - 1, j, t, n, m);
            double m2 = matrix_get(i - j - 1, j + 1, t, n, m);
            double m3 = matrix_get(i - j, j, t, n, m);
            double value = fabs(a[i - j] - b[j + 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i - j, j + 1, t, n, m);

            //cnt++;
        }
    }

    for (int i = n; i < m; i++) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(n - 1) / NTHR);
        int start = id * step;


        for (int j = start; j < start + step && j < n - 1; ++j) {
            double m1 = matrix_get(n - j - 1, j + 1 + i - n, t, n, m);
            double m2 = matrix_get(n - j - 2, j + 1 + i - n, t, n, m);
            double m3 = matrix_get(n - j - 2, j + 2 + i - n, t, n, m);
            double value = fabs(a[n - 1 - j] - b[j + 2 + i - n]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, n - j - 1, j + 2 + i - n, t, n, m);

            //cnt++;
        }
    }


    for (int i = m; i < m + n - 1; i++) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(m + n - i - 1) / NTHR);
        int start = id * step;


        for (int j = start; j < start + step && j < m + n - i - 1 - dif; ++j) {
            double m1 = matrix_get(m - n - 1 - j, i - n + 1 + j, t, n, m);
            double m2 = matrix_get(m - n - 2 - j, i - n + 1 + j, t, n, m);
            double m3 = matrix_get(m - n - 2 - j, i - n + 2 + j, t, n, m);
            double value = fabs(a[n - 1 - j] - b[j + 1 + i - n + dif]) + fmin(m1, fmin(m2, m3));

            matrix_put(value, n - 1 - j, j + 1 + i - n + dif, t, n, m);
        }
    }
    pthread_exit(NULL);
}

double dtw_diag_par(double *a_, double *b_, int n, int m) {
    double *t_ = (double*)malloc(m * n * sizeof(double));

    t = t_;
    a = a_;
    b = b_;

    pthread_barrier_init(&barrier, NULL, NTHR);
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, n, m);
    for (int i = 0; i < NTHR; ++i) {
        thr_struct_diag[i].id = i;
        thr_struct_diag[i].n = n;
        thr_struct_diag[i].m = m;
        pthread_create(&threads_diag[i],
                       NULL,
                       diag_thr,
                       &thr_struct_diag[i]);
    }

    for (int i = 0; i < NTHR; ++i) {
        pthread_join(threads_diag[i], NULL);
    }

    //printf("cntDIAG: %d\n", cnt);
    double rez = matrix_get(n - 1, m - 1, t, n, m);
    free(t_);

    return rez;
}