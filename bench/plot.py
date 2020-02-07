import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data_fw = pd.read_csv("results/dtw_fw.csv", index_col="size")
data_bk = pd.read_csv("results/dtw_bk.csv", index_col="size")
data_diag = pd.read_csv("results/dtw_diag.csv", index_col="size")
data_fwbk = pd.read_csv("results/dtw_fwbk.csv", index_col="size")
data_fwbk_par = pd.read_csv("results/dtw_fwbk_par.csv", index_col="size")
data_prunned = pd.read_csv("results/dtw_prunned.csv", index_col="size")

data = pd.concat([data_fw, data_bk, data_diag, data_fwbk, data_fwbk_par, data_prunned], axis=1)
data.columns = ["time_fw", "time_bk", "time_diag", "time_fwbk", "time_fwbk_par", "time_prunned"]

plt.figure()
data.plot()
plt.ylabel("sec")
plt.grid()
plt.show()





