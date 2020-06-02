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


    def importDataArff(self, path):
        self.df = load_from_arff_to_dataframe(path, replace_missing_vals_with='NaN')[0]
        self.format = "arff"
        return

    def importDataCsv(self, path):
        self.df = pd.read_csv(path, header=None)
        self.df = self.df.drop(columns=[0])
        self.format = "csv"
        return

    def calcPairs(self):
        self.pairs = list(itertools.combinations(self.df.index, 2))
        return

    def calcDistances(self, dtw_alg):
        if self.format == "arff":
            for a1, a2 in self.pairs:
                arr1 = self.df.loc[a1][0].dropna().tolist()
                arr2 = self.df.loc[a2][0].dropna().tolist()
                dtw.run(dtw_alg, arr1, arr2, True)
                dtw.run("dtw_prunned", arr1, arr2, True)
                dtw.run("dtw_diag_par_cache", arr1, arr2, True)
                dtw.run("dtw_fwbk_par", arr1, arr2, True)
                print()

        elif self.format == "csv":
            for a1, a2 in self.pairs:
                arr1 = self.df.loc[a1].tolist()
                arr2 = self.df.loc[a2].tolist()
                for alg in dtw_alg:
                    dtw.run(alg, arr1, arr2, True)

                print()



dtw = DTW()
knn = kNN(dtw)

#knn.importData("data/EigenWormsDimension1_TRAIN.arff")
knn.importDataCsv("data/HandOutlines_TRAIN")
knn.calcPairs()
knn.calcDistances("dtw_fw")