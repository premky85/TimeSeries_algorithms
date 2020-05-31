import pandas as pd
import matplotlib
matplotlib.use('TkAgg')

import matplotlib.pyplot as plt




#plt.figure()
#data.plot()

#plt.show()
class Plotter():
    def __init__(self):
        data_fw = pd.read_csv("results_random_time_series/dtw_fw.csv", index_col="size")
        data_fw_mem = pd.read_csv("results_random_time_series/dtw_fw_mem.csv", index_col="size")

        data_bk = pd.read_csv("results_random_time_series/dtw_bk.csv", index_col="size")
        data_bk_mem = pd.read_csv("results_random_time_series/dtw_bk_mem.csv", index_col="size")

        data_diag = pd.read_csv("results_random_time_series/dtw_diag.csv", index_col="size")
        data_diag_cache = pd.read_csv("results_random_time_series/dtw_diag_cache.csv", index_col="size")
        data_diag_cache_mem = pd.read_csv("results_random_time_series/dtw_diag_cache_mem.csv", index_col="size")

        data_diag_par = pd.read_csv("results_random_time_series/dtw_diag_par.csv", index_col="size")
        data_diag_par_cache = pd.read_csv("results_random_time_series/dtw_diag_par_cache.csv", index_col="size")
        data_diag_par_cache_mem = pd.read_csv("results_random_time_series/dtw_diag_par_cache_mem.csv", index_col="size")
        data_fwbk = pd.read_csv("results_random_time_series/dtw_fwbk.csv", index_col="size")
        data_fwbk_par = pd.read_csv("results_random_time_series/dtw_fwbk_par.csv", index_col="size")
        data_fwbk_par_mem = pd.read_csv("results_random_time_series/dtw_fwbk_par_mem.csv", index_col="size")

        data_prunned = pd.read_csv("results_random_time_series/dtw_prunned.csv", index_col="size")

        self.data = pd.concat([data_fw, data_fw_mem, data_bk, data_bk_mem, data_diag, data_diag_cache, data_diag_cache_mem,
                          data_fwbk, data_fwbk_par, data_fwbk_par_mem, data_prunned, data_diag_par, data_diag_par_cache,
                          data_diag_par_cache_mem], axis=1)
        self.data.columns = ["time_fw", "time_fw_mem", "time_bk", "time_bk_mem", "time_diag", "time_diag_cache",
                        "time_diag_cache_mem",
                        "time_fwbk", "time_fwbk_par", "time_fwbk_par_mem", "time_prunned", "time_diag_par",
                        "time_diag_par_cache", "time_diag_par_cache_mem", ]

    def plotSmall(self):
        small = self.data.dropna()
        small.plot()
        plt.ylabel("sec")
        plt.grid()


    def plotBig(self):
        big = self.data.dropna(axis='columns')
        big.plot()
        plt.ylabel("sec")
        plt.grid()

plotter = Plotter()
plotter.plotBig()



