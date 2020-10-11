#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include "algs/dtw_algs.c"

#include <string.h>


double *Random(int n, int seed);


int main(int argc, char *argv[]) {

    struct timespec start, stop;
    double time = INFINITY;
    double rez = INFINITY;


    //double a[] = {1, 3, 4, 9, 8, 2, 1, 5, 7, 3};
    //double b[] = {1, 6, 2, 3, 0, 9, 4, 3, 6, 3};
    if (argc != 5) {
        printf("4 arguments required but %d given.", argc - 1);
        return -1;
    }

    int seed1 = atoi(argv[3]);
    int seed2 = atoi(argv[4]);
    int n = atoi(argv[2]);
    int m = n - 2;
    FILE* fd;
    //double *t = calloc(n * m, sizeof(double));

    double *a = Random(n, seed1);
    sleep(1);
    double *b = Random(m, seed2);




    if (strcmp(argv[1], "dtw_fw") == 0) {
        fd = fopen("../../bench/results/dtw_fw.csv", "a+");
        //printf("dtw FW: =======================================================\n");

        clock_gettime(CLOCK_REALTIME, &start);
        rez = dtw_fw(a, b, n, m);
        clock_gettime(CLOCK_REALTIME, &stop);
        time = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;

    } else if (strcmp(argv[1], "dtw_bk") == 0) {
        fd = fopen("../../bench/results/dtw_bk.csv", "a+");
        //printf("dtw BK: =======================================================\n");

        clock_gettime(CLOCK_REALTIME, &start);
        rez = dtw_bk(a, b, n, m);
        clock_gettime(CLOCK_REALTIME, &stop);
        time = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;

    } else if (strcmp(argv[1], "dtw_diag") == 0) {
        fd = fopen("../../bench/results/dtw_diag.csv", "a+");
        //printf("dtw DIAG: =======================================================\n");

        clock_gettime(CLOCK_REALTIME, &start);
        rez = dtw_diag(a, b, n, m);
        clock_gettime(CLOCK_REALTIME, &stop);
        time = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;

    } else if (strcmp(argv[1], "dtw_diag_par") == 0) {
        fd = fopen("../../bench/results/dtw_diag_par.csv", "a+");
        //printf("dtw DIAG: =======================================================\n");

        clock_gettime(CLOCK_REALTIME, &start);
        rez = dtw_diag_par(a, b, n, m);
        clock_gettime(CLOCK_REALTIME, &stop);
        time = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;

    } else if (strcmp(argv[1], "dtw_fwbk") == 0) {
        fd = fopen("../../bench/results/dtw_fwbk.csv", "a+");
        //printf("dtw FW-BK: =======================================================\n");

        clock_gettime(CLOCK_REALTIME, &start);
        rez = dtw_fwbk(a, b, n, m);
        clock_gettime(CLOCK_REALTIME, &stop);
        time = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;

    } else if (strcmp(argv[1], "dtw_fwbk_par") == 0) {
        fd = fopen("../../bench/results/dtw_fwbk_par.csv", "a+");
        //printf("dtw PARALLEL: =======================================================\n");

        clock_gettime(CLOCK_REALTIME, &start);
        rez = dtw_fwbk_par(a, b, n, m);
        clock_gettime(CLOCK_REALTIME, &stop);
        time = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;


    }  else if (strcmp(argv[1], "dtw_pruned") == 0) {
        fd = fopen("../../bench/results/dtw_pruned.csv", "a+");
        //printf("dtw PARALLEL: =======================================================\n");

        clock_gettime(CLOCK_REALTIME, &start);
        rez = dtw_pruned(a, b, n, m);
        clock_gettime(CLOCK_REALTIME, &stop);
        time = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;
    } else if (strcmp(argv[1], "dtw_fw_mem") == 0) {
        fd = fopen("../../bench/results/dtw_fw_mem.csv", "a+");
        //printf("dtw PARALLEL: =======================================================\n");

        clock_gettime(CLOCK_REALTIME, &start);
        rez = dtw_fw_mem(a, b, n, m);
        clock_gettime(CLOCK_REALTIME, &stop);
        time = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;
    } else if (strcmp(argv[1], "dtw_bk_mem") == 0) {
        fd = fopen("../../bench/results/dtw_bk_mem.csv", "a+");
        //printf("dtw PARALLEL: =======================================================\n");

        clock_gettime(CLOCK_REALTIME, &start);
        rez = dtw_bk_mem(a, b, n, m);
        clock_gettime(CLOCK_REALTIME, &stop);
        time = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;
    } else if (strcmp(argv[1], "dtw_fwbk_par_mem") == 0) {
        fd = fopen("../../bench/results/dtw_fwbk_par_mem.csv", "a+");
        //printf("dtw PARALLEL: =======================================================\n");

        clock_gettime(CLOCK_REALTIME, &start);
        rez = dtw_fwbk_par_mem(a, b, n, m);
        clock_gettime(CLOCK_REALTIME, &stop);
        time = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;
    } else if (strcmp(argv[1], "dtw_diag_cache") == 0) {
        fd = fopen("../../bench/results/dtw_diag_cache.csv", "a+");
        //printf("dtw DIAG: =======================================================\n");

        clock_gettime(CLOCK_REALTIME, &start);
        rez = dtw_diag_cache(a, b, n, m);
        clock_gettime(CLOCK_REALTIME, &stop);
        time = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;

    } else if (strcmp(argv[1], "dtw_diag_cache_mem") == 0) {
        fd = fopen("../../bench/results/dtw_diag_cache_mem.csv", "a+");
        //printf("dtw DIAG: =======================================================\n");

        clock_gettime(CLOCK_REALTIME, &start);
        rez = dtw_diag_cache_mem(a, b, n, m);
        clock_gettime(CLOCK_REALTIME, &stop);
        time = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;

    } else if (strcmp(argv[1], "dtw_diag_par_cache") == 0) {
        fd = fopen("../../bench/results/dtw_diag_par_cache.csv", "a+");
        //printf("dtw DIAG: =======================================================\n");

        clock_gettime(CLOCK_REALTIME, &start);
        rez = dtw_diag_par_cache(a, b, n, m);
        clock_gettime(CLOCK_REALTIME, &stop);
        time = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;

    } else if (strcmp(argv[1], "dtw_diag_par_cache_mem") == 0) {
        fd = fopen("../../bench/results/dtw_diag_par_cache_mem.csv", "a+");
        //printf("dtw DIAG: =======================================================\n");

        clock_gettime(CLOCK_REALTIME, &start);
        rez = dtw_diag_par_cache_mem(a, b, n, m);
        clock_gettime(CLOCK_REALTIME, &stop);
        time = (double)(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)/1000000000;

    }/*else if (strcmp(argv[1], "dtw_fw") == 0) {

    }*/

    printf("rez: %f\n", rez);

    fprintf(fd, "%d,%f\n", n, time);

    printf("\nTIME: =======================================================\nTime: %fs\n", time);
    return 0;

}

