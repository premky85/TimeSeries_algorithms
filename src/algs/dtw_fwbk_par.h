//
// Created by premk on 2. 02. 20.
//

#include <pthread.h>

#include <math.h>
#include <stdlib.h>

pthread_t threads[2];

typedef struct _thread_data_t {
    double *t;
    double *a;
    double *b;
    int n;
    int m;
} thread_data_t;

thread_data_t thr_struct[2];

void *dtw_upper_par(void*);
void *dtw_lower_par(void*);
inline double matrix_get(int x_pos, int y_pos, double t[], int x_size, int y_size);
inline void matrix_put(double value, int x_pos, int y_pos, double t[], int x_size, int y_size);


double dtw_fwbk_par(double *a, double *b, int n, int m) {
    double *t = (double*)malloc(n * m * sizeof(double));


    thr_struct[0].t = t;
    thr_struct[0].a = a;
    thr_struct[0].b = b;
    thr_struct[0].n = n;
    thr_struct[0].m = m;


    pthread_create(&threads[0],
                   NULL,
                   dtw_upper_par,
                   &thr_struct[0]);

    pthread_create(&threads[1],
                   NULL,
                   dtw_lower_par,
                   &thr_struct[0]);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);


    int half = floor((double)(n) / 2);
    double d = INFINITY;

    for (int k = 0; k < m - 1; ++k) {
        double x = matrix_get(half - 1, k, t, n, m) + matrix_get(half, k, t, n, m);
        double y = matrix_get(half - 1, k, t, n, m) + matrix_get(half, k + 1, t, n, m);
        d = fmin(d, fmin(x, y));
    }

    double x = matrix_get(half - 1, m - 1, t, n, m) + matrix_get(half, m - 1, t, n, m);
    d = fmin(d, x);

    double rez = d;
    free(t);

    return rez;
}

void *dtw_upper_par(void *args) {
    thread_data_t* threadData;
    threadData = (thread_data_t *) args;
    double *t = threadData->t;
    double *a = threadData->a;
    double *b = threadData->b;
    int n = threadData->n;
    int m = threadData->m;

    int half = floor((double)(n) / 2);
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, n, m);
    for (int i = 1; i < half; ++i) {
        double value = matrix_get(i - 1, 0, t, n, m) + fabs(a[i] - b[0]);
        matrix_put(value, i, 0, t, n, m);
    }
    for (int i = 1; i < m; ++i) {
        double value = matrix_get(0, i - 1, t, n, m) + fabs(a[0] - b[i]);
        matrix_put(value, 0, i, t, n, m);
    }
    for (int i = 1; i < half; ++i) {
        for (int j = 1; j < m; ++j) {
            double m1 = matrix_get(i - 1, j - 1, t, n, m);
            double m2 = matrix_get(i - 1, j, t, n, m);
            double m3 = matrix_get(i, j - 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
        }
    }
    pthread_exit(NULL);
}

void *dtw_lower_par(void *args) {
    thread_data_t* threadData;
    threadData = (thread_data_t *) args;
    double *t = threadData->t;
    double *a = threadData->a;
    double *b = threadData->b;
    int n = threadData->n;
    int m = threadData->m;

    int half = floor((double)(n) / 2);
    matrix_put(fabs(a[n - 1] - b[m - 1]), n - 1, m - 1, t, n, m);
    for (int i = n - 2; i >= half; --i) {
        double value = matrix_get(i + 1, m - 1, t, n, m) + fabs(a[i] - b[m - 1]);
        matrix_put(value, i, m - 1, t, n, m);
    }
    for (int i = m - 2; i >= 0; --i) {
        double value = matrix_get(n - 1, i + 1, t, n, m) + fabs(a[n - 1] - b[i]);
        matrix_put(value, n - 1, i, t, n, m);
    }
    for (int i = n - 2; i >= half; --i) {
        for (int j = m - 2; j >= 0; --j) {
            double m1 = matrix_get(i + 1, j + 1, t, n, m);
            double m2 = matrix_get(i + 1, j, t, n, m);
            double m3 = matrix_get(i, j + 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
        }
    }
    pthread_exit(NULL);

}