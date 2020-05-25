//
// Created by premk on 2. 02. 20.
//

#include <math.h>
#include <stdlib.h>
#include <time.h>


inline void matrix_put(double value, int x_pos, int y_pos, double t[], int x_size, int y_size) {
    t[y_pos * x_size + x_pos] = value;
}

inline double matrix_get(int x_pos, int y_pos, double t[], int x_size, int y_size) {
    return t[y_pos * x_size + x_pos];
}

inline double *Random(int n, int seed)
{
    int a = time(NULL);
    srand(seed);
    double * A;
    A = (double *)calloc(n,sizeof(double));
    printf("A: ");
    for (int i = 0; i < n; ++i) {
        A[i] = floor((( (double)rand() ) / (double)RAND_MAX) * 10);
        printf("%f\t", A[i]);
    }
    printf("\n");
    return A;
}