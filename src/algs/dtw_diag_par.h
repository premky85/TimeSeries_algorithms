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

inline double matrix_get(int y_pos, int x_pos, double t[], int y_size, int x_size);
inline void matrix_put(double value, int y_pos, int x_pos, double t[], int y_size, int x_size);

void diag_thr(void *args) {
    thread_data_t_diag* threadData;
    threadData = (thread_data_t_diag *) args;

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

    int i;
    for (int k = 1; k < n; k++) {
        pthread_barrier_wait(&barrier);
        i = k - id;
        for (int j = id + 1; j <= k; j = j + NTHR) {
            double m1 = matrix_get(i - 1, j, t, n, m);
            double m2 = matrix_get(i, j - 1, t, n, m);
            double m3 = matrix_get(i - 1, j - 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
            i = i - NTHR;
            //cnt++;
        }
    }


    for (int k = 1; k < n; k++) {
        pthread_barrier_wait(&barrier);
        i = k + id;
        for (int j = n - 1 - id; j >= k; j = j- NTHR) {
            double m1 = matrix_get(i - 1, j, t, n, m);
            double m2 = matrix_get(i, j - 1, t, n, m);
            double m3 = matrix_get(i - 1, j - 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
            i = i + NTHR;
            //cnt++;
        }
    }
    pthread_exit(NULL);
}

double dtw_diag_par(double *a_, double *b_, double *t_, int n, int m) {
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
    return rez;
}