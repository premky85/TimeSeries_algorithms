import gc
import numpy as np
from ctypes import *
import time
from DTW.dtw import DTW

small = [x for x in range(100, 1000, 100)]
medium = [x for x in range(1000, 10000, 1000)]
large = [x for x in range(10000, 20000, 10000)]
xlarge = [x for x in range(20000, 100000, 10000)]
xxlarge = [x for x in range(100000, 1000000, 100000)]

algs = [
        "dtw_fw",
        "dtw_pruned",
        "dtw_bk",
        "dtw_diag",
        "dtw_diag_cache",
        "dtw_diag_par",
        "dtw_diag_par_cache",
        "dtw_fwbk",
        "dtw_fwbk_par",
        ]

algs_mem = [
    "dtw_fw_mem",
    "dtw_bk_mem",
    "dtw_diag_cache_mem",
    "dtw_diag_par_cache_mem",
    "dtw_fwbk_par_mem",

]

dtw = DTW()

for alg in algs + algs_mem:
    f = open("bench/results/syntetic_data/" + alg + ".csv", "w")
    f.write("size_1,size_2,time\n")
    f.close()

for x in small + medium + large:
    arr1 = np.rint(np.random.rand(x) * 10)
    arr2 = np.rint(np.random.rand(x) * 10)

    print("n: " + str(x))
    for alg in algs + algs_mem:
        rez, time = dtw.run(alg, arr1, arr2, True, "bench/results/syntetic_data/" + alg)
    print()


for x in xlarge + xxlarge:
    arr1 = np.rint(np.random.rand(x) * 10)
    arr2 = np.rint(np.random.rand(x) * 10)

    print("n: " + str(x))
    for alg in algs_mem:
        rez, time = dtw.run(alg, arr1, arr2, True, "bench/results/syntetic_data/" + alg)
    print()







