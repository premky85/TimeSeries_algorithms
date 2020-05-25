//
// Created by premk on 1. 03. 20.
//

//
// Created by premk on 2. 02. 20.
//

#include <pthread.h>

#include <math.h>
#include <stdlib.h>

pthread_t threads[2];

typedef struct _thread_data_t1 {
    double *prev;
    double *current;
    double *a;
    double *b;
    int n;
    int m;
} thread_data_t1;

thread_data_t1 thr_struct1[2];

void *dtw_upper_par_mem(void*);
void *dtw_lower_par_mem(void*);


double *mid1;
double *mid2;


double dtw_fwbk_par_mem(double *a, double *b, int n, int m) {
    double *t1 = (double*)malloc(n * sizeof(double));
    double *t2 = (double*)malloc(n * sizeof(double));
    double *t3 = (double*)malloc(n * sizeof(double));
    double *t4 = (double*)malloc(n * sizeof(double));



    thr_struct1[0].prev = t1;
    thr_struct1[0].current = t2;
    thr_struct1[0].a = a;
    thr_struct1[0].b = b;
    thr_struct1[0].n = n;
    thr_struct1[0].m = m;

    thr_struct1[1].prev = t3;
    thr_struct1[1].current = t4;
    thr_struct1[1].a = a;
    thr_struct1[1].b = b;
    thr_struct1[1].n = n;
    thr_struct1[1].m = m;


    pthread_create(&threads[0],
                   NULL,
                   dtw_upper_par_mem,
                   &thr_struct1[0]);

    pthread_create(&threads[1],
                   NULL,
                   dtw_lower_par_mem,
                   &thr_struct1[1]);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    double d = INFINITY;

    for (int k = 0; k < m - 1; ++k) {
        double x = mid1[k] + mid2[k];
        double y = mid1[k] + mid2[k + 1];
        d = fmin(d, fmin(x, y));
    }

    double x = mid1[m - 1] + mid2[m - 1];
    d = fmin(d, x);

    double rez = d;
    free(t1);
    free(t2);
    free(t3);
    free(t4);

    return rez;
}

void *dtw_upper_par_mem(void *args) {
    thread_data_t1* threadData;
    threadData = (thread_data_t1 *) args;
    double *t1 = threadData->prev;
    double *t2 = threadData->current;
    double *a = threadData->a;
    double *b = threadData->b;
    int n = threadData->n;
    int m = threadData->m;

    int half = floor((double)(n) / 2);

    char current = 0;

    t1[0] = fabs(a[0] - b[0]);
    for (int i = 1; i < n; ++i) {
        t1[i] = fabs(a[i] - b[0]) + t1[i - 1];
    }

    double *prev = t1;
    double *cur = t2;
    for (int j = 1; j < half; ++j) {
        cur[0] = fabs(a[0] - b[j]) + prev[0];
        for (int i = 1; i < n; ++i) {
            double m1 = prev[i];
            double m2 = prev[i - 1];
            double m3 = cur[i - 1];
            double tmp = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            cur[i] = tmp;//fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
        }



        current = 1 - current;
        prev = current == 0 ? t1 : t2;
        cur = current == 0 ? t2 : t1;

    }

    mid1 = prev;
    pthread_exit(NULL);
}

void *dtw_lower_par_mem(void *args) {
    thread_data_t1* threadData;
    threadData = (thread_data_t1 *) args;
    double *t1 = threadData->prev;
    double *t2 = threadData->current;
    double *a = threadData->a;
    double *b = threadData->b;
    int n = threadData->n;
    int m = threadData->m;
    char current = 0;

    int half = floor((double)(n) / 2);

    t1[n - 1] = fabs(a[n - 1] - b[m - 1]);
    for (int i = n - 2; i >= 0; --i) {

        t1[i] = fabs(a[i] - b[m - 1]) + t1[i + 1];
    }

    double *prev = t1;
    double *cur = t2;
    for (int j = m - 2; j >= half; --j) {
        cur[n - 1] = fabs(a[n - 1] - b[j]) + prev[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            double m1 = prev[i];
            double m2 = prev[i + 1];
            double m3 = cur[i + 1];
            double tmp = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            cur[i] = tmp;//fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
        }



        current = 1 - current;
        prev = current == 0 ? t1 : t2;
        cur = current == 0 ? t2 : t1;

    }
    mid2 = prev;
    pthread_exit(NULL);

}
