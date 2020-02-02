import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data_fw = pd.read_csv("results/dtw_fw.csv", index_col="size")
data_bk = pd.read_csv("results/dtw_bk.csv", index_col="size")
data_fwbk = pd.read_csv("results/dtw_fwbk.csv", index_col="size")
data_fwbk_par = pd.read_csv("results/dtw_fwbk_par.csv", index_col="size")

data = pd.concat([data_fw, data_bk, data_fwbk, data_fwbk_par], axis=1)
data.columns = ["time_fw", "time_bk", "time_fwbk", "time_fwbk_par"]

plt.figure()
data.plot()
plt.show()





