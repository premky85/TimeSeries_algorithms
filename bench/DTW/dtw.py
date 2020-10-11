from ctypes import *
import time
import numpy as np
import pandas as pd

class DTW:
    def __init__(self):
        so_file = "bench/DTW/lib/libtimeseries_dtw.so" 
        dtw = CDLL(so_file)
        dtw.dtw_fw.restype = c_double
        dtw.dtw_fw_mem.restype = c_double
        dtw.dtw_bk.restype = c_double
        dtw.dtw_bk_mem.restype = c_double

        dtw.dtw_pruned.restype = c_double
        dtw.dtw_diag.restype = c_double
        dtw.dtw_diag_cache.restype = c_double
        dtw.dtw_diag_cache_mem.restype = c_double


        dtw.dtw_fwbk.restype = c_double
        dtw.dtw_fwbk_par.restype = c_double
        dtw.dtw_fwbk_par_mem.restype = c_double

        dtw.dtw_diag_par.restype = c_double
        dtw.dtw_diag_par_cache.restype = c_double
        dtw.dtw_diag_par_cache_mem.restype = c_double

        dtw.euclidean.restype = c_double

        self.algs = {
                "dtw_fw": dtw.dtw_fw,
                "dtw_pruned": dtw.dtw_pruned,
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

    def run(self, dtw_alg, time_series1, time_series2, print_out=False, write_csv=None):
        ysize = len(time_series1)
        xsize = len(time_series2)

        time_series_1 = np.array(time_series1).astype(float).ctypes.data_as(POINTER(c_double))
        time_series_2 = np.array(time_series2).astype(float).ctypes.data_as(POINTER(c_double))
        start = time.perf_counter()
        rez = self.algs[dtw_alg](time_series_1, time_series_2, xsize, ysize)
        end = time.perf_counter()
        tim = (end - start)

        if write_csv:
            f = open(write_csv + ".csv", "a+")
            f.write(str(ysize) + ',' + str(xsize) + ',' + str(tim) + "\n")
            f.close()

        if print_out:
            print("{} | result: {} | time: {}".format(dtw_alg, rez, tim))

        return (rez, tim)
