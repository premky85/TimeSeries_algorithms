//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NTHR 12

pthread_barrier_t   barrier;

pthread_t threads_diag_cache_mem[NTHR];

double *t_new [3];
double *t1;
double *t2;
double *t3;
double *a;
double *b;


typedef struct _thread_data_t_diag_cache_mem {
    int id;
    int n;
    int m;
    int mo;
    char cur;
    char prev;
    char prevprev;
} thread_data_t_diag_cache_mem;

thread_data_t_diag_cache_mem thr_struct_diag_cache_mem[NTHR];

void diag_thr_cache_mem(void *args) {
    thread_data_t_diag_cache_mem* threadData;
    threadData = (thread_data_t_diag_cache_mem *) args;

    int id = threadData->id;
    int n = threadData->n;
    int m = threadData->m;
    int mo = threadData->mo;
    char cur = threadData->cur;
    char prev = threadData->prev;
    char prevprev = threadData->prevprev;

    int nthr = NTHR;

    /*
    if (id == 0) {
        for (int i = 2; i < n; ++i) {
            for (int j = 1; j < i; ++j) {
                double m1 = t[prevprev][j - 1];
                double m2 = t[prev][j];
                double m3 = t[prev][j - 1];
                double m4 = a[j];
                double m5 = b[i - j];
                double value = fabs(a[j] - b[i - j]) + fmin(m1, fmin(m2, m3));
                t[cur][j] = value;
            }

            cur = (cur + 1) % 3;
            prev = (prev + 1) % 3;
            prevprev = (prevprev + 1) % 3;
            t[prev][0] = fabs(a[0] - b[i]) + t[prevprev][0];
            t[prev][i] = fabs(a[i] - b[0]) + t[prevprev][i - 1];
        }
    } if(nthr > 1)  {
        if (id == 1) {
            for (int i = n; i < (2 * mo - n + 1); ++i) {
                for (int j = 0; j < (2 * n - 1) - i; ++j) {
                    double m1 = t[prev][j + 1];
                    double m2 = t[prev][j];
                    double m3 = t[prevprev][j];
                    double m4 = a[j + 1];
                    double m5 = b[((2 * n - 1) - i) - j];
                    double value = fabs(a[j + 1] - b[((2 * n - 1) - i) - j]) + fmin(m1, fmin(m2, m3));
                    t[cur][j] = value;
                }
                cur = (cur + 1) % 3;
                prev = (prev + 1) % 3;
                prevprev = (prevprev + 1) % 3;
            }
        }

    }
    else {
        for (int i = n; i < (2 * mo - n + 1); ++i) {
            for (int j = 0; j < (2 * n - 1) - i; ++j) {
                double m1 = t[prev][j + 1];
                double m2 = t[prev][j];
                double m3 = t[prevprev][j];
                double m4 = a[j + 1];
                double m5 = b[((2 * n - 1) - i) - j];
                double value = fabs(a[j + 1] - b[((2 * n - 1) - i) - j]) + fmin(m1, fmin(m2, m3));
                t[cur][j] = value;
            }
            cur = (cur + 1) % 3;
            prev = (prev + 1) % 3;
            prevprev = (prevprev + 1) % 3;
        }
    }
     */

    for (int i = 2; i < n; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)(i - 1) / nthr);
        int start = id * step + 1;
        for (int j = start; j < start + step && j < i; ++j) {
            double m1 = t_new[prevprev][j - 1];
            double m2 = t_new[prev][j];
            double m3 = t_new[prev][j - 1];
            double m4 = a[j];
            double m5 = b[i - j];
            double value = fabs(a[j] - b[i - j]) + fmin(m1, fmin(m2, m3));
            t_new[cur][j] = value;
        }
        cur = (cur + 1) % 3;
        prev = (prev + 1) % 3;
        prevprev = (prevprev + 1) % 3;
        t_new[prev][0] = fabs(a[0] - b[i]) + t_new[prevprev][0];
        t_new[prev][i] = fabs(a[i] - b[0]) + t_new[prevprev][i - 1];
    }

    for (int i = n; i < (2 * mo - n + 1); ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)((2 * n - 1) - i - 1) / nthr);
        int start = id * step;
        for (int j = start; j < start + step && j < (2 * n - 1) - i; ++j) {
            double m1 = t_new[prev][j + 1];
            double m2 = t_new[prev][j];
            double m3 = t_new[prevprev][j];
            double m4 = a[j + 1];
            double m5 = b[((2 * n - 1) - i) - j];
            double value = fabs(a[j + 1] - b[((2 * n - 1) - i) - j]) + fmin(m1, fmin(m2, m3));
            t_new[cur][j] = value;
        }
        cur = (cur + 1) % 3;
        prev = (prev + 1) % 3;
        prevprev = (prevprev + 1) % 3;
    }

    for (int i = (2 * mo - n + 1); i < m ; ++i) {
        pthread_barrier_wait(&barrier);
        int step = ceil((double)((2 * n - 1) - i) / nthr);
        int start = id * step;
        for (int j = start; j < start + step && j < (2 * n - 1) - i; ++j) {
            double m1 = t_new[prev][j + 1];
            double m2 = t_new[prev][j];
            double m3 = t_new[prevprev][j + 1];
            double m4 = a[j + 1 + (i - n)];
            double m5 = b[((2 * n - 1) - i) - j + (i - n)];
            double value = fabs(a[j + 1 + (i - n)] - b[n - j - 1]) + fmin(m1, fmin(m2, m3));
            t_new[cur][j] = value;
        }
        cur = (cur + 1) % 3;
        prev = (prev + 1) % 3;
        prevprev = (prevprev + 1) % 3;
    }
    pthread_exit(NULL);
}

double dtw_diag_par_cache_mem(double *a_, double *b_, int n, int m) {
    int mo = m;
    m = n + m - 1;


    t1 = (double*)malloc(n * sizeof(double));
    t2 = (double*)malloc(n * sizeof(double));
    t3 = (double*)malloc(n * sizeof(double));

    char cur = 2;
    char prev = 1;
    char prevprev = 0;
    t_new[0] = t1;
    t_new[1] = t2;
    t_new[2] = t3;

    a = a_;
    b = b_;

    pthread_barrier_init(&barrier, NULL, NTHR);
    t_new[0][0] = fabs(a[0] - b[0]);
    t_new[1][0] = fabs(a[0] - b[1]) + t_new[0][0];
    t_new[1][1] = fabs(a[1] - b[0]) + t_new[0][0];

    for (int i = 0; i < NTHR; ++i) {
        thr_struct_diag_cache_mem[i].id = i;
        thr_struct_diag_cache_mem[i].n = n;
        thr_struct_diag_cache_mem[i].m = m;
        thr_struct_diag_cache_mem[i].mo = mo;
        thr_struct_diag_cache_mem[i].cur = cur;
        thr_struct_diag_cache_mem[i].prev = prev;
        thr_struct_diag_cache_mem[i].prevprev = prevprev;
        pthread_create(&threads_diag_cache_mem[i],
                       NULL,
                       diag_thr_cache_mem,
                       &thr_struct_diag_cache_mem[i]);
    }

    for (int i = 0; i < NTHR; ++i) {
        pthread_join(threads_diag_cache_mem[i], NULL);
    }

    //printf("cntDIAG: %d\n", cnt);
    double rez = t_new[(m - 1) % 3][0];
    //free(t);
    free(t1);
    free(t2);
    free(t3);
    return rez;
}