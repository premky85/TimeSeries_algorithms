#include <stdio.h>
#include "dtw.c"

void main() {
    double a[] = {1, 3, 4, 9, 8, 2, 1, 5, 7, 3};
    double b[] = {1, 6, 2, 3, 0, 9, 4, 3, 6, 3};

    double a__[] = {1, 3, 4, 9, 8, 2, 1, 5, 7, 3};
    double b__[] = {1, 6, 2, 3, 0, 9, 4, 3, 6, 3};

    double a_[] = {3, 7, 5, 1, 2, 8, 9, 4, 3, 1};
    double b_[] = {3, 6, 3, 4, 9, 0, 3, 2, 6, 1};

    int n = sizeof(a)/ sizeof(a[0]);
    int m = sizeof(b)/ sizeof(b[0]);

    printf("dtw FW: =======================================================\n");

    double * dtwFw = dtw_fw(a, b, n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%2d ", (int)dtwFw[i * m + j]);
        }
        printf("\n");
    }
    //double s = construct_path_fw(dtwFw, n, m, n - 1, m - 1);
    //printf("sum: %d\n", (int)s);

    printf("dtw BK: =======================================================\n");

    double * dtwBk = dtw_bk(a, b, n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%2d ", (int)dtwBk[i * m + j]);
        }
        printf("\n");
    }
    //double s2 = construct_path_bk(dtwBk, n, m, 0, 0);
    //printf("sum: %2d\n", (int)s2);

    printf("dtw DIAG: =======================================================\n");

    double * dtwDiag = dtw_diag(a, b, n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%2d ", (int)dtwDiag[i * m + j]);
        }
        printf("\n");
    }

    printf("dtw FW-BK: =======================================================\n");

    double * dtwFwBk = dtw_fw_bk(a__, b__, n, m);


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%2d ", (int)dtwFwBk[i * m + j]);
        }
        printf("\n");
    }
    //double s3 = construct_path_fw(dtwFwBk, n, m, );
    //printf("sum: %d\n", (int)s3);

}

