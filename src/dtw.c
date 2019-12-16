#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double construct_path_fw(double *t, int n, int m, int a, int b);

double construct_path_bk(double *t, int n, int m, int a, int b);

void matrix_put(double value, int y_pos, int x_pos, double t[], int y_size, int x_size) {
    t[y_pos * x_size + x_pos] = value;
}

double matrix_get(int y_pos, int x_pos, double t[], int y_size, int x_size) {
    return t[y_pos * x_size + x_pos];
}

/*
double dist(double a, double b){
    return sqrt()
}
 */

double *dtw_fw(double a[], double b[], int n, int m) {
    //int n = sizeof(a)/ sizeof(a[0]);
    //int m = sizeof(b)/ sizeof(b[0]);
    double *t = malloc(n * m * sizeof(a[0]));
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, n, m);
    for (int i = 1; i < n; ++i) {
        double value = matrix_get(i - 1, 0, t, n, m) + fabs(a[i] - b[0]);
        matrix_put(value, i, 0, t, n, m);
        //t[i * m] =  t[i * m - 1] + fabs(a[i] - b[0]);
    }
    for (int i = 1; i < m; ++i) {
        double value = matrix_get(0, i - 1, t, n, m) + fabs(a[0] - b[i]);
        matrix_put(value, 0, i, t, n, m);
        //t[i] =  t[i - 1] + fabs(a[0] - b[i]);
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            double m1 = matrix_get(i - 1, j - 1, t, n, m);
            double m2 = matrix_get(i - 1, j, t, n, m);
            double m3 = matrix_get(i, j - 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
            //printf("%d ", (int)round(value));
            //t[i * j] = fabs(a[i] - b[j]) + fmin()
        }
        //printf("\n");

    }
    double rez = matrix_get(n - 1, m - 1, t, n, m);
    printf("rez: %f\n", rez);
    fflush(stdout);
    return t;
}

double *dtw_bk(double *a, double *b, int n, int m) {
    //int n = sizeof(a)/ sizeof(a[0]);
    //int m = sizeof(b)/ sizeof(b[0]);
    double *t = malloc(n * m * sizeof(a[0]));
    matrix_put(fabs(a[n - 1] - b[m - 1]), n - 1, m - 1, t, n, m);
    for (int i = n - 2; i >= 0; --i) {
        double value = matrix_get(i + 1, m - 1, t, n, m) + fabs(a[i] - b[m - 1]);
        matrix_put(value, i, m - 1, t, n, m);
        //t[i * m] =  t[i * m - 1] + fabs(a[i] - b[0]);
    }
    for (int i = m - 2; i >= 0; --i) {
        double value = matrix_get(n - 1, i + 1, t, n, m) + fabs(a[n - 1] - b[i]);
        matrix_put(value, n - 1, i, t, n, m);
        //t[i] =  t[i - 1] + fabs(a[0] - b[i]);
    }
    for (int i = n - 2; i >= 0; --i) {
        for (int j = m - 2; j >= 0; --j) {
            double m1 = matrix_get(i + 1, j + 1, t, n, m);
            double m2 = matrix_get(i + 1, j, t, n, m);
            double m3 = matrix_get(i, j + 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
            //t[i * j] = fabs(a[i] - b[j]) + fmin()
        }

    }
    double rez = matrix_get(0, 0, t, n, m);
    printf("rez: %f\n", rez);
    fflush(stdout);
    return t;
}

double *dtw_diag(double *a, double *b, int n, int m) {
    double *t = malloc(n * m * sizeof(a[0]));
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, n, m);

    for (int i = 1; i < n; ++i) {
        double value = fabs(a[i] - b[0]);
        matrix_put(value, i, 0, t, n, m);
        //t[i * m] =  t[i * m - 1] + fabs(a[i] - b[0]);
    }
    for (int i = 1; i < m; ++i) {
        double value = fabs(a[0] - b[i]);
        matrix_put(value, 0, i, t, n, m);
        //t[i] =  t[i - 1] + fabs(a[0] - b[i]);
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            double m1 = matrix_get(i - j - 1, j, t, n, m);
            double m2 = matrix_get(i - j - 1, j + 1, t, n, m);
            double m3 = matrix_get(i - j, j, t, n, m);
            double value = fabs(a[i - j] - b[j + 1]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i - j, j + 1, t, n, m);
            //printf("%d ", (int)round(value));
            //t[i * j] = fabs(a[i] - b[j]) + fmin()
        }
        //printf("\n");

    }
    for (int j = 2; j < m; ++j) {
        for (int i = 0; i < n - j; ++i) {
            double m1 = matrix_get(n - 1 - i - 1, j + i - 1, t, n, m);
            double m2 = matrix_get(n - 1 - i - 1, j + i, t, n, m);
            double m3 = matrix_get(n - 1 - i, j + i - 1, t, n, m);
            double value = fabs(a[n - 1 - i] - b[j + i]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, n - 1 - i, j + i, t, n, m);
            //printf("%d ", (int)round(value));
            //t[i * j] = fabs(a[i] - b[j]) + fmin()
        }
        //printf("\n");

    }

    double rez = matrix_get(n - 1, m - 1, t, n, m);
    printf("rez: %f\n", rez);
    fflush(stdout);
    return t;


}

/*
double *dtw_fw_bk(double *a, double *b, int n, int m) {
    double *t = malloc((n + 1)* (m + 1) * sizeof(a[0]));
    for (int i = 1; i < n; ++i) {
        matrix_put(INFINITY, i, 0, t, n, m);
        //t[i * m] =  t[i * m - 1] + fabs(a[i] - b[0]);
    }
    for (int i = 1; i < m; ++i) {
        matrix_put(INFINITY, 0, i, t, n, m);
        //t[i] =  t[i - 1] + fabs(a[0] - b[i]);
    }
    matrix_put(0, 0, 0, t, n, m);
    matrix_put(0, n, m, t, n, m);
    int half = floor((double)(n + 1) / 2);
    for (int i = 1; i < half; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            double value = fabs(a[i - 1] - b[j - 1]) + fmin(fmin(matrix_get(i - 1, j, t, n, m), matrix_get(i, j - 1, t, n, m)), matrix_get(i - 1, j - 1, t, n, m));
            matrix_put(value, i, j, t, n, m);
        }
    }
    for (int i = n + 1; i > half; --i) {
        for (int j = m; j > -1; --j) {
            double value = fabs(a[i] - b[j]) + fmin(fmin(matrix_get(i + 1, j, t, n, m), matrix_get(i, j + 1, t, n, m)), matrix_get(i + 1, j + 1, t, n, m));
            matrix_put(value, i, j, t, n, m);
        }
    }
    //double d = INFINITY;


    return t;
}

 */

double *dtw_fw_bk(double *a, double *b, int n, int m) {
    int half = floor((double)(n) / 2);
    double *t = (double *)calloc((n)* (m), sizeof(a[0]));
    matrix_put(fabs(a[0] - b[0]), 0, 0, t, n, m);
    matrix_put(fabs(a[n - 1] - b[m - 1]), n + 1, m + 1, t, n, m);
    for (int i = 1; i < half; ++i) {
        double value = matrix_get(i - 1, 0, t, n, m) + fabs(a[i] - b[0]);
        matrix_put(value, i, 0, t, n, m);
        //t[i * m] =  t[i * m - 1] + fabs(a[i] - b[0]);
    }
    for (int i = 1; i < m; ++i) {
        double value = matrix_get(0, i - 1, t, n, m) + fabs(a[0] - b[i]);
        matrix_put(value, 0, i, t, n, m);
        //t[i] =  t[i - 1] + fabs(a[0] - b[i]);
    }

    for (int i = 1; i < half; ++i) {
        for (int j = 1; j < m; ++j) {
            double m1 = matrix_get(i - 1, j - 1, t, n, m);
            double m2 = matrix_get(i - 1, j, t, n, m);
            double m3 = matrix_get(i, j - 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
            //printf("%d ", (int)round(value));
            //t[i * j] = fabs(a[i] - b[j]) + fmin()
        }
        //printf("\n");

    }

    for (int i = n - 2; i >= half; --i) {
        double value = matrix_get(i + 1, m - 1, t, n, m) + fabs(a[i] - b[m - 1]);
        matrix_put(value, i, m - 1, t, n, m);
        //t[i * m] =  t[i * m - 1] + fabs(a[i] - b[0]);
    }
    for (int i = m - 2; i >= 0; --i) {
        double value = matrix_get(n - 1, i + 1, t, n, m) + fabs(a[n - 1] - b[i]);
        matrix_put(value, n - 1, i, t, n, m);
        //t[i] =  t[i - 1] + fabs(a[0] - b[i]);
    }

    for (int i = n - 2; i >= half; --i) {
        for (int j = m - 2; j >= 0; --j) {
            double m1 = matrix_get(i + 1, j + 1, t, n, m);
            double m2 = matrix_get(i + 1, j, t, n, m);
            double m3 = matrix_get(i, j + 1, t, n, m);
            double value = fabs(a[i] - b[j]) + fmin(m1, fmin(m2, m3));
            matrix_put(value, i, j, t, n, m);
            //t[i * j] = fabs(a[i] - b[j]) + fmin()
        }

    }

    /*

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%2d ", (int)t[i * m + j]);
        }
        printf("\n");
    }
     */

    double d = INFINITY;
    double down_start = INFINITY;
    double up_start = INFINITY;
    for (int k = 1; k < m; ++k) {
        double x = matrix_get(half - 1, k, t, n, m) + matrix_get(half, k, t, n, m);
        double y = matrix_get(half - 1, k, t, n, m) + matrix_get(half, k + 1, t, n, m);
        //double z = matrix_get(half - 1, k, t, n, m) + matrix_get(half, k + 1, t, n, m);
        d = fmin(d, fmin(x, y));
        if (d == x) {
            down_start = k;//matrix_get(half, k, t, n, m);
            up_start = k;//matrix_get(half - 1, k, t, n, m);
        } else if (d == y) {
            down_start = k + 1;//matrix_get(half, k + 1, t, n, m);
            up_start = k;//matrix_get(half - 1, k, t, n, m);
        }
    }
    double rez = d;


    //double p1 = construct_path_fw(t, n, m, half - 1, (int)up_start);
    //double p2 = construct_path_bk(t, n, m, half, (int)down_start);

    printf("upStart = %f, downStart = %f | rez: %f\n", up_start, down_start, rez);
    fflush(stdout);

    return t;
}

// Assisting functions

double construct_path_fw(double *t, int n, int m, int a, int b) {
    double sum;
    sum = matrix_get(a, b, t, n, m); // choose starting point
    while (a > 0 || b > 0) {
        double min = INFINITY;
        int tmp_a;
        int tmp_b;
        double m1 = (a - 1 >= 0 && b - 1 >= 0) ? matrix_get(a - 1, b - 1, t, n, m) : INFINITY;
        double m2 = (a - 1 >= 0 && b >= 0) ? matrix_get(a - 1, b, t, n, m) : INFINITY;
        double m3 = (a >= 0 && b - 1 >= 0) ? matrix_get(a, b - 1, t, n, m) : INFINITY;
        if(m1 < m2) {
            min = m1;
            tmp_a = a - 1;
            tmp_b = b - 1;
        } else {
            min = m2;
            tmp_a = a - 1;
            tmp_b = b;
        }
        if(m3 < min) {
            min = m3;
            tmp_a = a;
            tmp_b = b - 1;
        }
        a = tmp_a;
        b = tmp_b;
        sum += min;
    }

    return sum;
}

double construct_path_bk(double *t, int n, int m, int a, int b) {
    double sum;
    sum = matrix_get(a, b, t, n, m); // choose starting point
    while (a < n - 1 || b < m - 1) {
        double min = INFINITY;
        int tmp_a;
        int tmp_b;
        double m1 = (a + 1 <= n && b + 1 <= m) ? matrix_get(a + 1, b + 1, t, n, m) : INFINITY;
        double m2 = (a + 1 <= n && b <= m) ? matrix_get(a + 1, b, t, n, m) : INFINITY;
        double m3 = (a <= n && b + 1 <= m) ? matrix_get(a, b + 1, t, n, m) : INFINITY;
        if (m1 < m2) {
            min = m1;
            tmp_a = a + 1;
            tmp_b = b + 1;
        } else {
            min = m2;
            tmp_a = a + 1;
            tmp_b = b;
        }
        if (m3 < min) {
            min = m3;
            tmp_a = a;
            tmp_b = b + 1;
        }
        a = tmp_a;
        b = tmp_b;
        sum += min;
    }

    return sum;
}