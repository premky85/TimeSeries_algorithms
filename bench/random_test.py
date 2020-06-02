import gc

import numpy as np
from ctypes import *
import time

small = [x for x in range(100, 1000, 100)]
medium = [x for x in range(1000, 10000, 1000)]
large = [x for x in range(10000, 20000, 10000)]
xlarge = [x for x in range(20000, 100000, 10000)]
xxlarge = [x for x in range(100000, 1000000, 100000)]

repnum = 3


so_file = "../src/cmake-build-debug/libtimeseries_dtw.so"
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


algs = [#(dtw.dtw_fw, "dtw_fw"),
        (dtw.dtw_pruned, "dtw_pruned"),
        #(dtw.dtw_bk, "dtw_bk"),
        #(dtw.dtw_diag, "dtw_diag"),
        #(dtw.dtw_diag_cache, "dtw_diag_cache"),
        #(dtw.dtw_diag_par, "dtw_diag_par"),
        #(dtw.dtw_diag_par_cache, "dtw_diag_par_cache"),
        #(dtw.dtw_fwbk, "dtw_fwbk"),
        #(dtw.dtw_fwbk_par, "dtw_fwbk_par"),
        ]

algs_mem = [
    #(dtw.dtw_fw_mem, "dtw_fw_mem"),
    #(dtw.dtw_bk_mem, "dtw_bk_mem"),
    #(dtw.dtw_diag_cache_mem, "dtw_diag_cache_mem"),
    #(dtw.dtw_diag_par_cache_mem, "dtw_diag_par_cache_mem"),
    #(dtw.dtw_fwbk_par_mem, "dtw_fwbk_par_mem"),

]

for alg in algs + algs_mem:
    f = open("results_random_time_series/" + alg[1] + ".csv", "w")
    f.write("size,time\n")
    f.close()

for x in small:
    arr1 = np.rint(np.random.rand(x) * 10).ctypes.data_as(POINTER(c_int))
    arr2 = np.rint(np.random.rand(x) * 10).ctypes.data_as(POINTER(c_int))

    print("n: " + str(x))
    for alg in algs + algs_mem:
        gc.collect()
        tim = 0
        for i in range(repnum):
            #gc.collect()
            start = time.perf_counter()
            rez = alg[0](arr1, arr2, x, x)
            end = time.perf_counter()
            tim += (end - start)
        print(alg[1] + ": " + str(rez))
        rez = dtw.dtw_fw(arr1, arr2, x, x)
        print("dtw_fw: " + str(rez))

        f = open("results_random_time_series/" + alg[1] + ".csv", "a+")
        f.write(str(x) + "," + str(tim / repnum) + "\n")
        f.close()

    print()

for x in medium:
    arr1 = np.rint(np.random.rand(x) * 10).ctypes.data_as(POINTER(c_int))
    arr2 = np.rint(np.random.rand(x) * 10).ctypes.data_as(POINTER(c_int))

    print("n: " + str(x))

    for alg in algs + algs_mem:
        gc.collect()
        tim = 0
        for i in range(repnum):
            #gc.collect()
            start = time.perf_counter()
            rez = alg[0](arr1, arr2, x, x)
            end = time.perf_counter()
            tim += (end - start)
        print(alg[1] + ": " + str(rez))
        rez = dtw.dtw_fw(arr1, arr2, x, x)
        print("dtw_fw: " + str(rez))

        f = open("results_random_time_series/" + alg[1] + ".csv", "a+")
        f.write(str(x) + "," + str(tim / repnum) + "\n")
        f.close()

    print()

for x in large:
    arr1 = np.rint(np.random.rand(x) * 10).ctypes.data_as(POINTER(c_int))
    arr2 = np.rint(np.random.rand(x) * 10).ctypes.data_as(POINTER(c_int))

    print("n: " + str(x))

    for alg in algs + algs_mem:
        gc.collect()
        tim = 0
        for i in range(repnum):
            #gc.collect()
            start = time.perf_counter()
            rez = alg[0](arr1, arr2, x, x)
            end = time.perf_counter()
            tim += (end - start)
        print(alg[1] + ": " + str(rez))
        rez = dtw.dtw_fw(arr1, arr2, x, x)
        print("dtw_fw: " + str(rez))

        f = open("results_random_time_series/" + alg[1] + ".csv", "a+")
        f.write(str(x) + "," + str(tim / repnum) + "\n")
        f.close()

    print()

for x in xlarge:
    arr1 = np.rint(np.random.rand(x) * 10).ctypes.data_as(POINTER(c_int))
    arr2 = np.rint(np.random.rand(x) * 10).ctypes.data_as(POINTER(c_int))

    print("n: " + str(x))
    for alg in algs_mem:
        gc.collect()
        tim = 0
        for i in range(repnum):
            #gc.collect()
            start = time.perf_counter()
            rez = alg[0](arr1, arr2, x, x)
            end = time.perf_counter()
            tim += (end - start)
        print(alg[1] + ": " + str(rez))

        f = open("results_random_time_series/" + alg[1] + ".csv", "a+")
        f.write(str(x) + "," + str(tim / repnum) + "\n")
        f.close()

    print()
for x in xxlarge:
    arr1 = np.rint(np.random.rand(x) * 10).ctypes.data_as(POINTER(c_int))
    arr2 = np.rint(np.random.rand(x) * 10).ctypes.data_as(POINTER(c_int))

    print("n: " + str(x))
    for alg in algs_mem:
        gc.collect()
        tim = 0
        for i in range(repnum):
            #gc.collect()
            start = time.perf_counter()
            rez = alg[0](arr1, arr2, x, x)
            end = time.perf_counter()
            tim += (end - start)
        print(alg[1] + ": " + str(rez))

        f = open("results_random_time_series/" + alg[1] + ".csv", "a+")
        f.write(str(x) + "," + str(tim / repnum) + "\n")
        f.close()

    print()







