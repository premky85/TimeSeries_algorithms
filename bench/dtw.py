from ctypes import *
import time
import numpy as np
import pandas as pd


class DTW:
    def __init__(self):
        so_file = "../src/cmake-build-debug/libtimeseries_dtw.so"
        dtw = CDLL(so_file)
        dtw.dtw_fw.restype = c_double
        dtw.dtw_fw_mem.restype = c_double
        dtw.dtw_bk.restype = c_double
        dtw.dtw_bk_mem.restype = c_double

        dtw.dtw_prunned.restype = c_double
        dtw.dtw_diag.restype = c_double
        dtw.dtw_diag_cache.restype = c_double
        dtw.dtw_diag_cache_mem.restype = c_double


        dtw.dtw_fwbk.restype = c_double
        dtw.dtw_fwbk_par.restype = c_double
        dtw.dtw_fwbk_par_mem.restype = c_double

        dtw.dtw_diag_par.restype = c_double
        dtw.dtw_diag_par_cache.restype = c_double
        dtw.dtw_diag_par_cache_mem.restype = c_double

        self.algs = {
                "dtw_fw": dtw.dtw_fw,
                "dtw_prunned": dtw.dtw_prunned,
                "dtw_bk": dtw.dtw_bk,
                "dtw_diag": dtw.dtw_diag,
                "dtw_diag_cache": dtw.dtw_diag_cache,
                "dtw_diag_par": dtw.dtw_diag_par,
                "dtw_diag_par_cache": dtw.dtw_diag_par_cache,
                "dtw_fwbk": dtw.dtw_fwbk,
                "dtw_fwbk_par": dtw.dtw_fwbk_par,
                "dtw_fw_mem": dtw.dtw_fw_mem,
                "dtw_bk_mem": dtw.dtw_bk_mem,
                "dtw_diag_cache_mem": dtw.dtw_diag_cache_mem,
                "dtw_diag_par_cache_mem": dtw.dtw_diag_par_cache_mem,
                "dtw_fwbk_par_mem": dtw.dtw_fwbk_par_mem,
                }

    def run(self, dtw_alg, time_series1, time_series2, out=False):
        xsize = len(time_series1)
        ysize = len(time_series2)

        time_series1 = (np.rint(time_series1) * 1.0).ctypes.data_as(POINTER(c_int))
        time_series2 = (np.rint(time_series2) * 1.0).ctypes.data_as(POINTER(c_int))
        start = time.perf_counter()
        rez = self.algs[dtw_alg](time_series1, time_series2, xsize, ysize)
        end = time.perf_counter()
        tim = (end - start)

        if out:
            print("{} | result: {} | time: {}".format(dtw_alg, rez, tim))

        return rez


dtw = DTW()

dtw.run("dtw_diag_par_cache", range(30000), range(30000), True)
#dtw.run("dtw_fw_mem", range(100000), range(100000), True)

