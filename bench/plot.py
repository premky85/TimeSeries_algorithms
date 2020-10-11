import pandas as pd
import matplotlib
matplotlib.use('TkAgg')
import numpy as np

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

        data_diag_par_cache_mem_1 = pd.read_csv("results_random_time_series/dtw_diag_par_cache_mem_NTHR1.csv", index_col="size")
        data_diag_par_cache_mem_2 = pd.read_csv("results_random_time_series/dtw_diag_par_cache_mem_NTHR2.csv", index_col="size")
        data_diag_par_cache_mem_3 = pd.read_csv("results_random_time_series/dtw_diag_par_cache_mem_NTHR3.csv", index_col="size")
        data_diag_par_cache_mem_4 = pd.read_csv("results_random_time_series/dtw_diag_par_cache_mem_NTHR4.csv", index_col="size")
        data_diag_par_cache_mem_5 = pd.read_csv("results_random_time_series/dtw_diag_par_cache_mem_NTHR5.csv", index_col="size")
        data_diag_par_cache_mem_6 = pd.read_csv("results_random_time_series/dtw_diag_par_cache_mem_NTHR6.csv", index_col="size")
        data_diag_par_cache_mem_7 = pd.read_csv("results_random_time_series/dtw_diag_par_cache_mem_NTHR7.csv", index_col="size")
        data_diag_par_cache_mem_8 = pd.read_csv("results_random_time_series/dtw_diag_par_cache_mem_NTHR8.csv", index_col="size")
        data_diag_par_cache_mem_9 = pd.read_csv("results_random_time_series/dtw_diag_par_cache_mem_NTHR9.csv", index_col="size")
        data_diag_par_cache_mem_10 = pd.read_csv("results_random_time_series/dtw_diag_par_cache_mem_NTHR10.csv", index_col="size")
        data_diag_par_cache_mem_11 = pd.read_csv("results_random_time_series/dtw_diag_par_cache_mem_NTHR11.csv", index_col="size")
        data_diag_par_cache_mem_12 = pd.read_csv("results_random_time_series/dtw_diag_par_cache_mem_NTHR12.csv", index_col="size")




        data_pruned = pd.read_csv("results_random_time_series/dtw_pruned.csv", index_col="size")

        self.data = pd.concat([data_fw, data_fw_mem, data_bk, data_bk_mem, data_diag, data_diag_cache, data_diag_cache_mem,
                          data_fwbk, data_fwbk_par, data_fwbk_par_mem, data_pruned, data_diag_par, data_diag_par_cache,
                          data_diag_par_cache_mem,
                               # data_diag_par_cache_mem_1, data_diag_par_cache_mem_2, data_diag_par_cache_mem_3, data_diag_par_cache_mem_4, data_diag_par_cache_mem_5, data_diag_par_cache_mem_6, data_diag_par_cache_mem_7, data_diag_par_cache_mem_8, data_diag_par_cache_mem_9, data_diag_par_cache_mem_10, data_diag_par_cache_mem_11, data_diag_par_cache_mem_12
                               ], axis=1)
        self.data.columns = ["fw", "fw_mem", "bk", "bk_mem", "diag", "diag_cache",
                        "diag_cache_mem",
                        "fwbk", "fwbk_par", "fwbk_par_mem", "pruned", "diag_par",
                        "diag_par_cache", "diag_par_cache_mem",
                             # "diag_par_cache_mem_1",
                             # "diag_par_cache_mem_2",
                             # "diag_par_cache_mem_3",
                             # "diag_par_cache_mem_4",
                             # "diag_par_cache_mem_5",
                             # "diag_par_cache_mem_6",
                             # "diag_par_cache_mem_7",
                             # "diag_par_cache_mem_8",
                             # "diag_par_cache_mem_9",
                             # "diag_par_cache_mem_10",
                             # "diag_par_cache_mem_11",
                             # "diag_par_cache_mem_12"
            ]

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
        self.plot(["fw", "fw_mem"], save=True)
        self.plot(["bk", "bk_mem"], save=True)
        self.plot(["fw", "diag_par"], save=True)
        self.plot(["fw", "diag_par_cache"], save=True)
        self.plot(["diag", "diag_cache", "diag_cache_mem"], save=True)
        self.plot(["fw", "pruned"], save=True)
        self.plot(["fw", "fwbk_par"], save=True)
        self.plot(["fwbk_par", "fwbk_par_mem"], save=True)
        self.plot(["fwbk_par", "diag_par"], save=True)
        self.plot(["diag_par", "diag_par_cache", "diag_par_cache_mem"], save=True)
        self.plot(["fwbk_par_mem", "diag_par_cache_mem"], save=True)
        self.plot(["fw", "bk", "fwbk", "diag", "diag_cache"], save=True)
        self.plot(["fw", "bk", "diag_cache", "fw_mem", "bk_mem", "diag_cache_mem"], save=True)
        self.plot(["fwbk_par", "diag_par_cache"], save=True)

        self.plotSmall(save=True)
        self.plotBig(save=True)

    def plotThreads(self, save=False):
        threads = self.data[["diag_par_cache_mem_1",
                             "diag_par_cache_mem_2",
                             "diag_par_cache_mem_3",
                             "diag_par_cache_mem_4",
                             "diag_par_cache_mem_5",
                             "diag_par_cache_mem_6",
                             "diag_par_cache_mem_7",
                             "diag_par_cache_mem_8",
                             "diag_par_cache_mem_9",
                             "diag_par_cache_mem_10",
                             "diag_par_cache_mem_11",
                             "diag_par_cache_mem_12"]]

        threads.columns = ["1 Thread", "2 Threads", "3 Threads", "4 Threads", "5 Threads", "6 Threads", "7 Threads", "8 Threads", "9 Threads", "10 Threads", "11 Threads", "12 Threads"]

        threads.plot()
        plt.ylabel("sec")
        plt.grid()
        if save:
            plt.savefig("graphs/threads.png", dpi=400)
        else:
            plt.show()

    def plotRealData(self, path, algs, save=False):
        realdf = pd.DataFrame()
        for alg in algs:
            tmpdf = pd.read_csv(path + "_dtw_" + alg + ".csv")
            a = tmpdf["time"].sum()
            realdf[alg] = [tmpdf["time"].sum()]

        a = realdf.columns.tolist()
        realdf = realdf.T
        realdf["names"] = a
        realdf.plot.bar(legend=None)
        plt.ylabel("sec")
        plt.xticks(rotation=10)
        plt.grid()
        if save:
            name = path.split("/")[-1].split(".")[0]
            plt.savefig("graphs/{}.png".format(name), dpi=400)
        else:
            plt.show()

    def plotSpeedUps(self):
        algs = self.data.columns[1:]








    def plot(self, times, save=False):
        df = self.data[times].dropna(axis=0)
        df.plot()
        plt.ylabel("sec")
        plt.grid()
        if save:
            n = [x for x in times]
            name = "_vs_".join(n)
            plt.savefig("graphs/{}.png".format(name), dpi=400)
        else:
            plt.show()




plotter = Plotter()
#plotter.plotBig()
#plotter.plotSmall()
#plotter.plot([], save=True)
plotter.plotAll()
#plotter.plotThreads(save=True)



# plotter.plotRealData("results/bk1/AllGestureWiimoteX", ["fw", "fwbk_par", "diag_par_cache", "pruned"], save=True)
# plotter.plotRealData("results/bk1/AllGestureWiimoteY", ["fw", "fwbk_par", "diag_par_cache", "pruned"], save=True)
# plotter.plotRealData("results/bk1/AllGestureWiimoteZ", ["fw", "fwbk_par", "diag_par_cache", "pruned"], save=True)
# plotter.plotRealData("results/bk1/Car", ["fw", "fwbk_par", "diag_par_cache", "pruned"], save=True)
# plotter.plotRealData("results/bk1/CinC_ECG_torso", ["fw", "fwbk_par", "diag_par_cache", "pruned"], save=True)
# plotter.plotRealData("results/bk1/HandOutlines", ["fw", "fwbk_par", "diag_par_cache", "pruned"], save=True)
# plotter.plotRealData("results/bk1/InlineSkate", ["fw", "fwbk_par", "diag_par_cache", "pruned"], save=True)
# plotter.plotRealData("results/bk1/MALLAT", ["fw", "fwbk_par", "diag_par_cache", "pruned"], save=True)
# plotter.plotRealData("results/bk1/Symbols", ["fw", "fwbk_par", "diag_par_cache", "pruned"], save=True)





