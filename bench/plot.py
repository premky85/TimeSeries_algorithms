import pandas as pd
import numpy as np
import matplotlib
matplotlib.use('TkAgg')

import matplotlib.pyplot as plt


data_fw = pd.read_csv("results/dtw_fw.csv", index_col="size")
data_fw_mem = pd.read_csv("results/dtw_fw_mem.csv", index_col="size")

data_bk = pd.read_csv("results/dtw_bk.csv", index_col="size")
data_bk_mem = pd.read_csv("results/dtw_bk_mem.csv", index_col="size")

data_diag = pd.read_csv("results/dtw_diag.csv", index_col="size")
data_diag_cache = pd.read_csv("results/dtw_diag_cache.csv", index_col="size")
data_diag_cache_mem = pd.read_csv("results/dtw_diag_cache_mem.csv", index_col="size")

data_diag_par = pd.read_csv("results/dtw_diag_par.csv", index_col="size")
data_diag_par_cache = pd.read_csv("results/dtw_diag_par_cache.csv", index_col="size")
data_diag_par_cache_mem = pd.read_csv("results/dtw_diag_par_cache_mem.csv", index_col="size")
data_fwbk = pd.read_csv("results/dtw_fwbk.csv", index_col="size")
data_fwbk_par = pd.read_csv("results/dtw_fwbk_par.csv", index_col="size")
data_fwbk_par_mem = pd.read_csv("results/dtw_fwbk_par_mem.csv", index_col="size")

data_prunned = pd.read_csv("results/dtw_prunned.csv", index_col="size")

data = pd.concat([data_fw, data_fw_mem, data_bk, data_bk_mem, data_diag, data_diag_cache, data_diag_cache_mem,
                  data_fwbk, data_fwbk_par, data_fwbk_par_mem, data_prunned, data_diag_par, data_diag_par_cache, data_diag_par_cache_mem], axis=1)
data.columns = ["time_fw", "time_fw_mem", "time_bk", "time_bk_mem", "time_diag", "time_diag_cache", "time_diag_cache_mem",
                "time_fwbk", "time_fwbk_par", "time_fwbk_par_mem", "time_prunned", "time_diag_par", "time_diag_par_cache", "time_diag_par_cache_mem", ]

#plt.figure()
#data.plot()

#plt.show()

small = data.dropna()
small.plot()
plt.ylabel("sec")
plt.grid()

big = data.dropna(axis='columns')
big.plot()
plt.ylabel("sec")
plt.grid()




