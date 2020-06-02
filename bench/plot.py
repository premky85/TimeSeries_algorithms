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

        data_pruned = pd.read_csv("results_random_time_series/dtw_pruned.csv", index_col="size")

        self.data = pd.concat([data_fw, data_fw_mem, data_bk, data_bk_mem, data_diag, data_diag_cache, data_diag_cache_mem,
                          data_fwbk, data_fwbk_par, data_fwbk_par_mem, data_pruned, data_diag_par, data_diag_par_cache,
                          data_diag_par_cache_mem], axis=1)
        self.data.columns = ["time_fw", "time_fw_mem", "time_bk", "time_bk_mem", "time_diag", "time_diag_cache",
                        "time_diag_cache_mem",
                        "time_fwbk", "time_fwbk_par", "time_fwbk_par_mem", "time_pruned", "time_diag_par",
                        "time_diag_par_cache", "time_diag_par_cache_mem", ]

    def plotSmall(self, save=False):
        small = self.data.dropna()
        small.plot()
        plt.ylabel("sec")
        plt.grid()
        if save:
            plt.savefig("graphs/small.png", dpi=400)
        else:
            plt.show()


    def plotBig(self, save=False):
        big = self.data.dropna(axis='columns')
        big.plot()
        plt.ylabel("sec")
        plt.grid()
        if save:
            plt.savefig("graphs/big.png", dpi=400)
        else:
            plt.show()

    def plotAll(self):
        self.plot(["time_fw", "time_fw_mem"], save=True)
        self.plot(["time_bk", "time_bk_mem"], save=True)
        self.plot(["time_fw", "time_diag"], save=True)
        self.plot(["time_fw", "time_bk"], save=True)
        self.plot(["time_diag", "time_diag_cache", "time_diag_cache_mem"], save=True)
        self.plot(["time_fw", "time_fwbk"], save=True)
        self.plot(["time_fw", "time_pruned"], save=True)
        self.plot(["time_fw", "time_fwbk_par"], save=True)
        self.plot(["time_fwbk_par", "time_fwbk_par_mem"], save=True)
        self.plot(["time_fwbk_par", "time_diag_par"], save=True)
        self.plot(["time_diag_par", "time_diag_par_cache", "time_diag_par_cache_mem"], save=True)
        self.plot(["time_fwbk_par_mem", "time_diag_par_cache_mem"], save=True)
        self.plotSmall(save=True)
        self.plotBig(save=True)


    def plot(self, times, save=False):
        df = self.data[times].dropna(axis=0)
        df.plot()
        plt.ylabel("sec")
        plt.grid()
        if save:
            n = [x.strip("time_") for x in times]
            name = "_vs_".join(n)
            plt.savefig("graphs/{}.png".format(name), dpi=400)
        else:
            plt.show()




plotter = Plotter()
#plotter.plotBig()
#plotter.plotSmall()
#plotter.plot(["time_fwbk_par_mem", "time_diag_par_cache_mem"], save=True)
plotter.plotAll()



