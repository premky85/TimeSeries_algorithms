//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <time.h>


inline void matrix_put(double value, int y_pos, int x_pos, double t[], int y_size, int x_size) {
    t[y_pos * x_size + x_pos] = value;
}

inline double matrix_get(int y_pos, int x_pos, double t[], int y_size, int x_size) {
    return t[y_pos * x_size + x_pos];
}

inline double *Random(int n, int seed)
{
    int a = time(NULL);
    srand(seed);
    double * A;
    A = (double *)calloc(n,sizeof(double));
    //printf("A: ");
    for (int i = 0; i < n; ++i) {
        A[i] = floor((( (double)rand() ) / (double)RAND_MAX) * 10);
        printf("%.0f ", A[i]);
    }
    printf("\n");
    return A;
}