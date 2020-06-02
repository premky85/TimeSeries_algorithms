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


double dtw_fwbk_par(double *a, double *b, int m, int n) {
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
        double x = matrix_get(k, half - 1, t, m, n) + matrix_get(k, half, t, m, n);
        double y = matrix_get(k, half - 1, t, m, n) + matrix_get(k + 1, half, t, m, n);
        d = fmin(d, fmin(x, y));
    }

    double x = matrix_get(m - 1, half - 1, t, m, n) + matrix_get(m - 1, half, t, m, n);
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
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, m, n);
    for (int j = 1; j < half; ++j) {
        double value = matrix_get(0, j - 1, t, m, n) + fabs(a[0] - b[j]);
        matrix_put(value, 0, j, t, m, n);
    }
    for (int i = 1; i < m; ++i) {
        double value = matrix_get(i - 1, 0, t, n, m) + fabs(a[i] - b[0]);
        matrix_put(value, i, 0, t, m, n);
    }

    for (int j = 1; j < half; ++j) {
        for (int i = 1; i < m; ++i) {
            double m1 = matrix_get(i - 1, j - 1, t, m, n);
            double m2 = matrix_get(i - 1, j, t, m, n);
            double m3 = matrix_get(i, j - 1, t, m, n);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, m, n);
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
    matrix_put(fabs(a[m - 1] - b[n - 1]), m - 1, n - 1, t, m, n);
    for (int j = n - 2; j >= half; --j) {
        double value = matrix_get(m - 1, j + 1, t, m, n) + fabs(a[m - 1] - b[j]);
        matrix_put(value, m - 1, j, t, m, n);
    }
    for (int i = m - 2; i >= 0; --i) {
        double value = matrix_get(i + 1, n - 1, t, m, n) + fabs(a[i] - b[n - 1]);
        matrix_put(value, i, n - 1, t, m, n);
    }

    for (int j = n - 2; j >= half; --j) {
        for (int i = m - 2; i >= 0; --i) {
            double m1 = matrix_get(i + 1, j + 1, t, m, n);
            double m2 = matrix_get(i + 1, j, t, m, n);
            double m3 = matrix_get(i, j + 1, t, m, n);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, m, n);
        }

    }
    pthread_exit(NULL);

}