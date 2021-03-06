//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NTHR 6

pthread_barrier_t   barrier;

pthread_t threads_diag_cache_mem[NTHR];

typedef struct _thread_data_t_diag_cache_mem {
    double **t_new;
    double *a;
    double *b;
    int id;
    int n;
    int m;
    int no;
    char cur;
    char prev;
    char prevprev;

} thread_data_t_diag_cache_mem;

thread_data_t_diag_cache_mem thr_struct_diag_cache_mem[NTHR];

void diag_thr_cache_mem(void *args) {
    thread_data_t_diag_cache_mem* threadData;
    threadData = (thread_data_t_diag_cache_mem *) args;

    double **t_new = threadData->t_new;
    double *a = threadData->a;
    double *b = threadData->b;

    int id = threadData->id;
    int n = threadData->n;
    int m = threadData->m;
    int no = threadData->no;
    char cur = threadData->cur;
    char prev = threadData->prev;
    char prevprev = threadData->prevprev;

    for (int i = 2; i < m + 1; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(i) / NTHR);
        int start = id * step + 1;
        for (int j = start; j < start + step && j < i; ++j) {
            double m1 = t_new[prevprev][j - 1];
            double m2 = t_new[prev][j];
            double m3 = t_new[prev][j - 1];
            double value = fabs(a[i - j] - b[j]) + fmin(m1, fmin(m2, m3));
            t_new[cur][j] = value;
        }
        cur = (cur + 1) % 3;
        prev = (prev + 1) % 3;
        prevprev = (prevprev + 1) % 3;
        t_new[prev][0] = fabs(a[i] - b[0]) + t_new[prevprev][0];
        t_new[prev][i] = fabs(a[0] - b[i]) + t_new[prevprev][i - 1];
    }

    for (int i = m + 1; i < no; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(m) / NTHR);
        int start = id * step + 1;
        for (int j = start; j < start + step && j < m; ++j) {
            double m1 = t_new[prev][j];
            double m2 = t_new[prev][j - 1];
            double m3 = t_new[prevprev][j - 1];
            double value = fabs(a[i - j] - b[j]) + fmin(m1, fmin(m2, m3));
            t_new[cur][j] = value;
        }
        cur = (cur + 1) % 3;
        prev = (prev + 1) % 3;
        prevprev = (prevprev + 1) % 3;
    }

    for (int i = no; i < no + 1; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(m - 1) / NTHR);
        int start = id * step;
        for (int j = start; j < start + step && j < m - 1; ++j) {
            double m1 = t_new[prev][j + 1];
            double m2 = t_new[prev][j];
            double m3 = t_new[prevprev][j];
            double value = fabs(a[i - j - 1] - b[j + 1]) + fmin(m1, fmin(m2, m3));
            t_new[cur][j] = value;
        }
        cur = (cur + 1) % 3;
        prev = (prev + 1) % 3;
        prevprev = (prevprev + 1) % 3;
    }


    for (int i = no + 1; i < n ; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(no + m - i - 1) / NTHR);
        int start = id * step;
        for (int j = start; j < start + step && j < no + m - i - 1; ++j) {
            double m1 = t_new[prev][j + 1];
            double m2 = t_new[prev][j];
            double m3 = t_new[prevprev][j + 1];
            double value = fabs(a[no - j - 1] - b[j + 1 + (i - no)]) + fmin(m1, fmin(m2, m3));
            t_new[cur][j] = value;
        }
        cur = (cur + 1) % 3;
        prev = (prev + 1) % 3;
        prevprev = (prevprev + 1) % 3;
    }

    pthread_exit(NULL);
}

double dtw_diag_par_cache_mem(double *a_, double *b_, int n, int m) {
    int no = n;
    n = m + n - 1;

    double **t_new;
    double *t1;
    double *t2;
    double *t3;

    t_new = (double**)malloc(3 * sizeof(double*));
    t1 = (double*)malloc(m * sizeof(double));
    t2 = (double*)malloc(m * sizeof(double));
    t3 = (double*)malloc(m * sizeof(double));

    char cur = 2;
    char prev = 1;
    char prevprev = 0;
    t_new[0] = t1;
    t_new[1] = t2;
    t_new[2] = t3;


    pthread_barrier_init(&barrier, NULL, NTHR);
    t_new[0][0] = fabs(a_[0] - b_[0]);
    t_new[1][0] = fabs(a_[1] - b_[0]) + t_new[0][0];
    t_new[1][1] = fabs(a_[0] - b_[1]) + t_new[0][0];

    for (int i = 0; i < NTHR; ++i) {
        thr_struct_diag_cache_mem[i].t_new = t_new;
        thr_struct_diag_cache_mem[i].a = a_;
        thr_struct_diag_cache_mem[i].b = b_;
        thr_struct_diag_cache_mem[i].id = i;
        thr_struct_diag_cache_mem[i].n = n;
        thr_struct_diag_cache_mem[i].m = m;
        thr_struct_diag_cache_mem[i].no = no;
        thr_struct_diag_cache_mem[i].cur = cur;
        thr_struct_diag_cache_mem[i].prev = prev;
        thr_struct_diag_cache_mem[i].prevprev = prevprev;
        pthread_create(&threads_diag_cache_mem[i],
                       NULL,
                       (void *)diag_thr_cache_mem,
                       &thr_struct_diag_cache_mem[i]);
    }

    for (int i = 0; i < NTHR; ++i) {
        pthread_join(threads_diag_cache_mem[i], NULL);
    }

    double rez = t_new[prev][0];
    free(t_new);
    free(t1);
    free(t2);
    free(t3);
    return rez;
}