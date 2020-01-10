#include <stdio.h>
#include "dtw.c"
#include <time.h>
#include <math.h>
#include <unistd.h>

double *Random(int n)
{
    srand(time(NULL));
    double * A;
    A = (double *)calloc(n,sizeof(double));
    for (int i = 0; i < n; ++i) {
        A[i] = floor((( (double)rand() ) / (double)RAND_MAX) * 10);
    }
    return A;
}


void main() {

    struct timespec start, stop;
    double time_fw;
    double time_bk;
    double time_fw_bk;
    double time_par;

    //double a[] = {1, 3, 4, 9, 8, 2, 1, 5, 7, 3};
    //double b[] = {1, 6, 2, 3, 0, 9, 4, 3, 6, 3};

    int n = 10000;
    int m = 10000;
    double *a = Random(n);
    sleep(1);
    double *b = Random(m);

    /*
    for (int k = 0; k < n; ++k) {
        printf("%f ", a[k]);
    }
    printf("\n");
    for (int k = 0; k < m; ++k) {
        printf("%f ", b[k]);
    }
    printf("\n");
    */


    //int n = sizeof(a)/ sizeof(a[0]);
    //int m = sizeof(b)/ sizeof(b[0]);



    printf("dtw FW: =======================================================\n");

    clock_gettime(CLOCK_REALTIME, &start);
    double dtwFw = dtw_fw(a, b, n, m);
    clock_gettime(CLOCK_REALTIME, &stop);
    time_fw = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;
    printf("rez: %f\n", dtwFw);


    /*
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%2d ", (int)dtwFw[i * m + j]);
        }
        printf("\n");
    }
     */


    printf("dtw BK: =======================================================\n");

    clock_gettime(CLOCK_REALTIME, &start);
    double dtwBk = dtw_bk(a, b, n, m);
    clock_gettime(CLOCK_REALTIME, &stop);
    time_bk = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;
    printf("rez: %f\n", dtwBk);

    /*
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%2d ", (int)dtwBk[i * m + j]);
        }
        printf("\n");
    }
     */


    /*
    printf("dtw DIAG: =======================================================\n");

    double * dtwDiag = dtw_diag(a, b, n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%2d ", (int)dtwDiag[i * m + j]);
        }
        printf("\n");
    }
     */

    printf("dtw FW-BK: =======================================================\n");

    clock_gettime(CLOCK_REALTIME, &start);
    double dtwFwBk = dtw_fw_bk(a, b, n, m);
    clock_gettime(CLOCK_REALTIME, &stop);
    time_fw_bk = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;
    printf("rez: %f\n", dtwFwBk);

    /*
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%2d ", (int)dtwFwBk[i * m + j]);
        }
        printf("\n");
    }
    */

    printf("dtw PARALLEL: =======================================================\n");

    clock_gettime(CLOCK_REALTIME, &start);
    double dtwPar = dtw_parallel(a, b, n, m);
    clock_gettime(CLOCK_REALTIME, &stop);
    time_par = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;
    printf("rez: %f\n", dtwPar);

    /*
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%2d ", (int)dtwPar[i * m + j]);
        }
        printf("\n");
    }
    */

    printf("\nTIME: =======================================================\nTime FW: %fs, Time BK: %fs, Time FWBK: %fs, Time PARALLEL: %fs", time_fw, time_bk, time_fw_bk, time_par);

}

