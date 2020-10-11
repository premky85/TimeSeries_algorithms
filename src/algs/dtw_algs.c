//
// Created by premk on 2. 02. 20.
//

#include "dtw_fw.h"
#include "dtw_fw_mem.h"
#include "dtw_bk.h"
#include "dtw_bk_mem.h"
#include "dtw_fwbk.h"
#include "dtw_fwbk_par.h"
#include "dtw_fwbk_par_mem.h"
#include "dtw_pruned.h"
#include "dtw_diag.h"
#include "dtw_diag_cache.h"
#include "dtw_diag_cache_mem.h"
#include "dtw_diag_par.h"
#include "euclidean.h"
#include "dtw_diag_par_cache.h"
#include "dtw_diag_par_cache_mem.h"

#include "helpers.h"


double dtw_fw(double *a, double *b, int n, int m);

double dtw_bk(double *a, double *b, int m, int n);

double dtw_diag(double *a, double *b, int n, int m);

double dtw_fwbk(double *a, double *b, int n, int m);

double dtw_fwbk_par(double *a, double *b, int n, int m);

double dtw_pruned(double *a, double *b, int n, int m);

double dtw_diag_par(double *a, double *b, int n, int m);

double dtw_fw_mem(double *a, double *b, int n, int m);

double dtw_bk_mem(double *a, double *b, int n, int m);

double dtw_fwbk_par_mem(double *a, double *b, int n, int m);

double dtw_diag_cache(double *a, double *b, int n, int m);

double dtw_diag_cache_mem(double *a, double *b, int n, int m);

double dtw_diag_par_cache(double *a_, double *b_, int n, int m);

double dtw_diag_par_cache_mem(double *a_, double *b_, int n, int m);

double euclidean(double *a_, double *b_, int n, int m);



