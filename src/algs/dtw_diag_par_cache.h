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
    int no;
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
    int no = threadData->no;

    int dif = n == no ? 0 : 1;

    int nthr = NTHR;


    //Racunanje zacetnih vrednosti
    if (id == 0) {
        for (int i = 1; i < m; ++i) {
            double v = fabs(a[i] - b[0]) + matrix_get(i - 1, i - 1, t, m, n);
            matrix_put(v, i, i, t, m, n);
        }
    } if(nthr > 1)  {
        if (id == 1) {
            for (int j = 1; j < no; ++j) {
                double v = fabs(a[0] - b[j]) + matrix_get(0, j - 1, t, m, n);
                matrix_put(v, 0, j, t, m, n);
            }
        }

    }
    else {
        for (int j = 1; j < no; ++j) {
            double v = fabs(a[0] - b[j]) + matrix_get(0, j - 1, t, m, n);
            matrix_put(v, 0, j, t, m, n);
        }
    }


    // Zgornji trikotnik
    for (int i = 2; i < m + 1; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(i) / NTHR);
        int start = id * step + 1;
        for (int j = start; j < start + step && j < i; ++j) {
            double m1 = matrix_get(j, i - 1, t, m, n);
            double m2 = matrix_get(j - 1, i - 1, t, m, n);
            double m3 = matrix_get(j - 1, i - 2, t, m, n);
            double value = fabs(a[j] - b[i - j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, j, i, t, m, n);
        }
    }


    // Srednji kvadrat
    for (int i = m + 1; i < no; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(m - 1) / NTHR);

        int start = id * step;
        for (int j = start; j < start + step && j < m - 1; ++j) {
            double m1 = matrix_get(j + 1, i - 1, t, m, n);
            double m2 = matrix_get(j, i - 1, t, m, n);
            double m3 = matrix_get(j, i - 2, t, m, n);
            double value = fabs(a[j + 1] - b[i - (1 + j)]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, j + 1, i, t, m, n);
        }
    }

    //problem pri zamiku
    for (int i = no; i < no + 1; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(m - 1) / NTHR);

        int start = id * step;
        for (int j = start; j < start + step && j < m - 1; ++j) {
            double m1 = matrix_get(j + 1, i - 1, t, m, n);
            double m2 = matrix_get(j, i - 1, t, m, n);
            double m3 = matrix_get(j, i - 2, t, m, n);
            double value = fabs(a[j + 1] - b[i - (1 + j)]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, j, i, t, m, n);
        }
    }


    //Spodnji trikotnik
    for (int i = no + 1; i < n ; ++i) {
        pthread_barrier_wait(&barrier);
        //int step = ceil((double)((2 * n - 1) - i) / nthr);
        int step = ceil((double)(no + m - i - 1) / NTHR);

        int start = id * step;
        for (int j = start; j < start + step && j < no + m - i - 1; ++j) {
            double m1 = matrix_get(j + 1, i - 1, t, m, n);
            double m2 = matrix_get(j, i - 1, t, m, n);
            double m3 = matrix_get(j + 1, i - 2, t, m, n);
            double value = fabs(a[j + 1 + (i - no)] - b[no - j - 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, j, i, t, m, n);
        }
    }
    pthread_exit(NULL);
}

double dtw_diag_par_cache(double *a_, double *b_, int m, int n) {
    int no = n;
    n = m + n - 1;
    double *t_ = (double*)malloc(m * n * sizeof(double));

    t = t_;
    a = a_;
    b = b_;

    pthread_barrier_init(&barrier, NULL, NTHR);
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, m, n);

    for (int i = 0; i < NTHR; ++i) {
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

    //printf("cntDIAG: %d\n", cnt);
    double rez = matrix_get(0, n - 1, t, m, n);
    free(t_);

    return rez;
}