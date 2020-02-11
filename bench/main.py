import matplotlib.pyplot as plt
import numpy as np
import os
import subprocess
from ctypes import *
import random
import time
import gc

small = [x for x in range(100, 1000, 100)]
medium = [x for x in range(1000, 10000, 1000)]
large = [x for x in range(10000, 100000, 10000)]


so_file = "../src/cmake-build-debug/libtimeseries_dtw.so"
dtw = CDLL(so_file)
dtw.dtw_fw.restype = c_double
dtw.dtw_bk.restype = c_double
dtw.dtw_prunned.restype = c_double
dtw.dtw_diag.restype = c_double
dtw.dtw_fwbk.restype = c_double
dtw.dtw_fwbk_par.restype = c_double

algs = [(dtw.dtw_fw, "dtw_fw"),
        (dtw.dtw_prunned, "dtw_prunned"),
        (dtw.dtw_bk, "dtw_bk"),
        (dtw.dtw_diag, "dtw_diag"),

        (dtw.dtw_fwbk, "dtw_fwbk"),
        (dtw.dtw_fwbk_par, "dtw_fwbk_par"),
        ]

for alg in algs:
    f = open("results/" + alg[1] + ".csv", "w")
    f.write("size,time\n")
    f.close()



for x in small:
    arr1 = np.rint(np.random.rand(x) * 10).ctypes.data_as(POINTER(c_int))
    arr2 = np.rint(np.random.rand(x) * 10).ctypes.data_as(POINTER(c_int))
    arrt = np.zeros(x*x).ctypes.data_as(POINTER(c_double))
    gc.collect()

    dtw.dtw_fw(arr1, arr2, arrt, x, x)
    print("n: " + str(x))
    for alg in algs:
        start = time.perf_counter()
        rez = alg[0](arr1, arr2, arrt, x, x)
        end = time.perf_counter()
        print(rez)

        f = open("results/" + alg[1] + ".csv", "a+")
        f.write(str(x) + "," + str(end-start) + "\n")
        f.close()
    print()

for x in medium:
    arr1 = np.rint(np.random.rand(x) * 10).ctypes.data_as(POINTER(c_int))
    arr2 = np.rint(np.random.rand(x) * 10).ctypes.data_as(POINTER(c_int))
    arrt = np.zeros(x * x).ctypes.data_as(POINTER(c_double))
    gc.collect()

    dtw.dtw_fw(arr1, arr2, arrt, x, x)
    print("n: " + str(x))

    for alg in algs:
        start = time.perf_counter()
        rez = alg[0](arr1, arr2, arrt, x, x)
        end = time.perf_counter()
        print(rez)

        f = open("results/" + alg[1] + ".csv", "a+")
        f.write(str(x) + "," + str(end - start) + "\n")
        f.close()
    print()

for x in large:
    arr1 = np.rint(np.random.rand(x) * 10).ctypes.data_as(POINTER(c_int))
    arr2 = np.rint(np.random.rand(x) * 10).ctypes.data_as(POINTER(c_int))
    arrt = np.zeros(x * x).ctypes.data_as(POINTER(c_double))
    gc.collect()

    dtw.dtw_fw(arr1, arr2, arrt, x, x)
    print("n: " + str(x))

    for alg in algs:
        start = time.perf_counter()
        rez = alg[0](arr1, arr2, arrt, x, x)
        end = time.perf_counter()
        print(rez)

        f = open("results/" + alg[1] + ".csv", "a+")
        f.write(str(x) + "," + str(end - start) + "\n")
        f.close()
    print()








