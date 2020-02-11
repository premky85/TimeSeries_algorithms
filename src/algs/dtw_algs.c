//
// Created by premk on 2. 02. 20.
//

#include "dtw_fw.h"
#include "dtw_bk.h"
#include "dtw_fwbk.h"
#include "dtw_fwbk_par.h"
#include "dtw_prunned.h"
#include "dtw_diag.h"
#include "dtw_diag_par.h"
#include "helpers.h"


double dtw_fw(double *a, double *b, double *t, int n, int m);

double dtw_bk(double *a, double *b, double *t, int n, int m);

double dtw_diag(double *a, double *b, double *t, int n, int m);

double dtw_fwbk(double *a, double *b, double *t, int n, int m);

double dtw_fwbk_par(double *a, double *b, double *t, int n, int m);

double dtw_prunned(double *a, double *b, double *t, int n, int m);

double dtw_diag_par(double *a, double *b, double *t, int n, int m);


