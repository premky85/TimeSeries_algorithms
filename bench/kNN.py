from ctypes import *
import time
import numpy as np
import pandas as pd
from dtw import DTW
import itertools
from sktime.utils.load_data import load_from_tsfile_to_dataframe, load_from_arff_to_dataframe


class kNN():
    def __init__(self, dtw):
        self.dtw = dtw

    def importData(self, path):
        self.df = load_from_arff_to_dataframe(path, replace_missing_vals_with='NaN')[0]
        return

    def calcPairs(self):
        self.pairs = list(itertools.combinations(self.df.index, 2))
        return

    def calcDistances(self, dtw_alg):
        for a1, a2 in self.pairs:
            arr1 = self.df.loc[a1][0].dropna().tolist()
            arr2 = self.df.loc[a2][0].dropna().tolist()
            dtw.run(dtw_alg, arr1, arr2, True)
            dtw.run("dtw_prunned", arr1, arr2, True)
            dtw.run("dtw_diag_par_cache", arr1, arr2, True)
            print()



dtw = DTW()
knn = kNN(dtw)

knn.importData("data/EigenWormsDimension1_TRAIN.arff")
knn.calcPairs()
knn.calcDistances("dtw_fw")