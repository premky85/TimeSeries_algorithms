//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NTHR 6

pthread_barrier_t   barrier;

pthread_t threads_diag_cache[NTHR];




typedef struct _thread_data_t_diag_cache {
    double *t;
    double *a;
    double *b;
    int id;
    int n;
    int m;
    int no;
} thread_data_t_diag_cache;

thread_data_t_diag_cache thr_struct_diag_cache[NTHR];

inline double matrix_get(int y_pos, int x_pos, double t[], int y_size, int x_size);
inline void matrix_put(double value, int y_pos, int x_pos, double t[], int y_size, int x_size);

void diag_thr_cache(void *args) {
    thread_data_t_diag_cache* threadData;
    threadData = (thread_data_t_diag_cache *) args;

    double *t = threadData->t;
    double *a = threadData->a;
    double *b = threadData->b;

    int id = threadData->id;
    int n = threadData->n;
    int m = threadData->m;
    int no = threadData->no;

    //Racunanje zacetnih vrednosti
    if (id == 0) {
        for (int i = 1; i < no; ++i) {
            double v = fabs(a[i] - b[0]) + matrix_get(i - 1, 0, t, n, m);
            matrix_put(v, i, 0, t, n, m);
        }
    } if(NTHR > 1)  {
        if (id == 1) {
            for (int j = 1; j < m; ++j) {
                double v = fabs(a[0] - b[j]) + matrix_get(j - 1, j - 1, t, n, m);
                matrix_put(v, j, j, t, n, m);
            }
        }

    }
    else {
        for (int j = 1; j < m; ++j) {
            double v = fabs(a[0] - b[j]) + matrix_get(j - 1, j - 1, t, n, m);
            matrix_put(v, j, j, t, n, m);
        }
    }


    // Zgornji trikotnik
    for (int i = 2; i < m + 1; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(i) / NTHR);
        int start = id * step + 1;
        for (int j = start; j < start + step && j < i; ++j) {
            double m1 = matrix_get(i - 1, j, t, n, m);
            double m2 = matrix_get(i - 1, j - 1, t, n, m);
            double m3 = matrix_get(i - 2, j - 1, t, n, m);
            double value = fabs(a[i - j] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
        }
    }


    // Srednji kvadrat
    for (int i = m + 1; i < no; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(m) / NTHR);

        int start = id * step + 1;
        for (int j = start; j < start + step && j < m; ++j) {
            double m1 = matrix_get(i - 1, j, t, n, m);
            double m2 = matrix_get(i - 1, j - 1, t, n, m);
            double m3 = matrix_get(i - 2, j - 1, t, n, m);
            double value = fabs(a[i - j] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
        }
    }

    //problem pri zamiku
    for (int i = no; i < no + 1; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(m - 1) / NTHR);

        int start = id * step;
        for (int j = start; j < start + step && j < m - 1; ++j) {
            double m1 = matrix_get(i - 1, j + 1, t, n, m);
            double m2 = matrix_get(i - 1, j, t, n, m);
            double m3 = matrix_get(i - 2, j, t, n, m);
            double value = fabs(a[i - j - 1] - b[j + 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
        }
    }


    //Spodnji trikotnik
    for (int i = no + 1; i < n ; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(no + m - i - 1) / NTHR);

        int start = id * step;
        for (int j = start; j < start + step && j < no + m - i - 1; ++j) {
            double m1 = matrix_get(i - 1, j, t, n, m);
            double m2 = matrix_get(i - 1, j + 1, t, n, m);
            double m3 = matrix_get(i - 2, j + 1, t, n, m);
            double value = fabs(a[no - j - 1] - b[j + 1 + i - no]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
        }
    }
    pthread_exit(NULL);
}

double dtw_diag_par_cache(double *a_, double *b_, int n, int m) {
    int no = n;
    n = m + n - 1;
    double *t_ = (double*)malloc(n * m * sizeof(double));



    pthread_barrier_init(&barrier, NULL, NTHR);
    matrix_put(fabs(a_[0] - b_[0]), 0, 0, t_, n, m);

    for (int i = 0; i < NTHR; ++i) {
        thr_struct_diag_cache[i].t = t_;
        thr_struct_diag_cache[i].a = a_;
        thr_struct_diag_cache[i].b = b_;
        thr_struct_diag_cache[i].id = i;
        thr_struct_diag_cache[i].n = n;
        thr_struct_diag_cache[i].m = m;
        thr_struct_diag_cache[i].no = no;
        pthread_create(&threads_diag_cache[i],
                       NULL,
                       (void *)diag_thr_cache,
                       &thr_struct_diag_cache[i]);
    }

    for (int i = 0; i < NTHR; ++i) {
        pthread_join(threads_diag_cache[i], NULL);
    }

    double rez = matrix_get(n - 1, 0, t_, n, m);
    free(t_);

    return rez;
}