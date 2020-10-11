from ctypes import *
import time
import numpy as np
import pandas as pd
from DTW.dtw import DTW
import itertools
from sktime.utils.load_data import load_from_tsfile_to_dataframe, load_from_arff_to_dataframe
import os


class kNN():
    def __init__(self, dtw):
        self.dtw = dtw


    def importDataArff(self, path):
        self.pathTrain = path + "_TRAIN"
        self.pathTest = path + "_TEST"
        self.dfTrain = load_from_arff_to_dataframe(path, replace_missing_vals_with='NaN')[0]
        self.format = "arff"
        return

    def importDataCsv(self, path, classRow=None, header=None, unknownLabel=np.NaN):
        self.path = path
        self.pathTrain = path + "_TRAIN"
        self.pathTest = path + "_TEST"
        self.dfTrain = pd.read_csv(self.pathTrain, header=header)
        self.dfTest = pd.read_csv(self.pathTest, header=header)
        self.dfTrain.replace(unknownLabel, np.NaN, inplace=True)
        self.dfTest.replace(unknownLabel, np.NaN, inplace=True)
        self.dfTrainClasses = self.dfTrain[classRow]
        self.dfTestClasses = self.dfTest[classRow]
        self.dfTrain = self.dfTrain.drop(columns=[classRow])
        self.dfTest = self.dfTest.drop(columns=[classRow])
        self.format = "csv"
        return

    def importFittedData(self, rPath, dPath=None, classRow=None, header=None, unknownLabel=np.NaN):
        if dPath:
            self.importDataCsv(dPath, classRow, header, unknownLabel)
        self.df = pd.read_csv(rPath)
        self.df = self.df.drop(columns=["time"])



    '''
    def calcPairs(self):
        self.pairs = list(itertools.combinations(self.df.index, 2))
        return

    
    def calcDistances(self, dtw_alg):
        if self.format == "arff":
            for a1, a2 in self.pairs:
                arr1 = self.df.loc[a1][0].dropna().tolist()
                arr2 = self.df.loc[a2][0].dropna().tolist()
                dtw.run(dtw_alg, arr1, arr2, True)
                print()
    '''

    def fit(self, dtw_algorithms=None, print_out=True):
        #self.calcPairs()
        data = self.path.split("/")[-1].split(".")[0]
        if dtw_algorithms:
            algs = dtw_algorithms
        else:
            algs = self.dtw.algs
        for alg in algs:
            f = open("results/" + data + "_" + alg + ".csv", "w")
            f.write("time_series_TEST,time_series_TRAIN,time,distance\n")
            f.close()
        i = 0
        n = self.dfTrain.shape[0] * self.dfTest.shape[0]
        if self.format == "csv":
            start = time.perf_counter()
            for a1 in self.dfTest.index:
                for a2 in self.dfTrain.index:
                    i += 1
                    arr1 = list(map(float, self.dfTest.loc[a1].dropna().tolist()))
                    arr2 = list(map(float, self.dfTrain.loc[a2].dropna().tolist()))
                    for alg in algs:
                        rez, tim = dtw.run(alg, arr1, arr2, print_out=False)
                        f = open("results/" + data + "_" + alg + ".csv", "a+")
                        f.write(str(a1) + "," + str(a2) + "," + str(tim) + "," + str(rez) + "\n")
                        f.close()
                    end = time.perf_counter()
                    tim = (end - start)
                    if print_out:
                        hour = tim // 3600
                        min = (tim % 3600) // 60
                        sec = tim - hour * 3600 - min * 60

                        tim2 = (n / i) * tim - tim
                        hour2 = tim2 // 3600
                        min2 = (tim2 % 3600) // 60
                        sec2 = tim2 - hour2 * 3600 - min2 * 60

                        print("\n##########\n{:.2f}% elapsed: {:.0f}h, {:.0f}min, {:.2f}s, remaining time: {:.0f}h, {:.0f}min, {:.2f}s\n##########\n".format((i / n) * 100, hour, min, sec, hour2, min2, sec2))
                '''
                if self.format == "arff":
                    start = time.perf_counter()
                    for a1, a2 in self.pairs:
                        i += 1
                        arr1 = self.df.loc[a1][0].dropna().tolist()
                        arr2 = self.df.loc[a2][0].dropna().tolist()
                        for alg in algs:
                            rez, tim = dtw.run(alg, arr1, arr2, print_out=True)
                            f = open("results/" + data + "_" + alg + ".csv", "a+")
                            f.write(str(a1) + "," + str(a2) + "," + str(tim) + "," + str(rez) + "\n")
                            f.close()
                        end = time.perf_counter()
                        tim = (end - start)
                        print("\n########## \n", (i / n) * 100,
                              "%\t elapsed: {}s, remaining time: {}s\n##########\n".format(tim, (n / i) * tim - tim))
                              
                '''
        self.importFittedData("results/" + data + "_" + algs[0] + ".csv")

    def predict(self, id):
        df_id = self.df.loc[self.df['time_series_TEST'] == id]
        df_id = df_id.sort_values(by=['distance'])
        neighbours = df_id.head(1)["time_series_TRAIN"]
        rez = self.dfTrainClasses.loc[neighbours].values
        rez = np.bincount(rez).argmax()
        return rez

    def buildConfusionMatrix(self):
        n = self.dfTrainClasses.nunique()
        self.confusionMatrix = np.zeros((n, n))
        for i in range(self.dfTest.shape[0]):
            pred = self.predict(i)
            real = self.dfTestClasses.loc[i]
            self.confusionMatrix[pred - 1, real - 1] += 1

        return self.confusionMatrix

    def precision(self, classId):
        TP = self.confusionMatrix[classId, classId]
        FP = np.sum(self.confusionMatrix[classId]) - TP
        return TP / (TP + FP)

    def precisionMean(self):
        s = 0
        for i in range(self.confusionMatrix.shape[0]):
            s += self.precision(i)
        return s/self.confusionMatrix.shape[0]

    def recall(self, classId):
        n =self.confusionMatrix.shape[0]
        s = np.sum([self.confusionMatrix[i][i] for i in range(n)])
        return self.confusionMatrix[classId, classId]/s

    def recallMean(self):
        s = 0
        for i in range(self.confusionMatrix.shape[0]):
            s += self.recall(i)
        return s/self.confusionMatrix.shape[0]

    def classificationAccuracy(self):
        n = self.confusionMatrix.shape[0]
        s = np.sum([self.confusionMatrix[i][i] for i in range(n)])
        return s/np.sum(self.confusionMatrix)

    def fScoreMean(self):
        p = self.precisionMean()
        r = self.recallMean()
        return 2 * ((p * r) / (p + r))





dtw = DTW()
knn = kNN(dtw)




'''
knn.importDataCsv("data/AllGestureWiimoteX", classRow="target", header=0, unknownLabel='?')
knn.fit(["dtw_fwbk_par", "dtw_pruned", "dtw_diag_par_cache", "dtw_fw", "euclidean"], print_out=True)
knn.importDataCsv("data/AllGestureWiimoteY", classRow="target", header=0, unknownLabel='?')
knn.fit(["dtw_fwbk_par", "dtw_pruned", "dtw_diag_par_cache", "dtw_fw", "euclidean"], print_out=True)
knn.importDataCsv("data/AllGestureWiimoteZ", classRow="target", header=0, unknownLabel='?')
knn.fit(["dtw_fwbk_par", "dtw_pruned", "dtw_diag_par_cache", "dtw_fw", "euclidean"], print_out=True)

knn.importDataCsv("data/Car")
knn.fit(["dtw_fwbk_par", "dtw_pruned", "dtw_diag_par_cache", "dtw_fw", "euclidean"])
knn.importDataCsv("data/HandOutlines")
knn.fit(["dtw_fwbk_par", "dtw_pruned", "dtw_diag_par_cache", "dtw_fw", "euclidean"])
knn.importDataCsv("data/InlineSkate")
knn.fit(["dtw_fwbk_par", "dtw_pruned", "dtw_diag_par_cache", "dtw_fw", "euclidean"])
knn.importDataCsv("data/MALLAT")
knn.fit(["dtw_fwbk_par", "dtw_pruned", "dtw_diag_par_cache", "dtw_fw", "euclidean"])
knn.importDataCsv("data/CinC_ECG_torso")
knn.fit(["dtw_fwbk_par", "dtw_pruned", "dtw_diag_par_cache", "dtw_fw", "euclidean"])
knn.importDataCsv("data/Symbols")
knn.fit(["dtw_fwbk_par", "dtw_pruned", "dtw_diag_par_cache", "dtw_fw", "euclidean"])
'''

knn.importFittedData("results/bk1/AllGestureWiimoteX_dtw_fw.csv", dPath="data/AllGestureWiimoteX", classRow="target", header=0, unknownLabel='?')
confusionMatrix_dtw = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(AllGestureWiimoteX) DTW => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))

knn.importFittedData("results/bk1/AllGestureWiimoteX_euclidean.csv", dPath="data/AllGestureWiimoteX", classRow="target", header=0, unknownLabel='?')
confusionMatrix_euclidean = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(AllGestureWiimoteX) Euclidean distance => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))
print()

knn.importFittedData("results/bk1/AllGestureWiimoteY_dtw_fw.csv", dPath="data/AllGestureWiimoteY", classRow="target", header=0, unknownLabel='?')
confusionMatrix_dtw = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(AllGestureWiimoteY) DTW => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))

knn.importFittedData("results/bk1/AllGestureWiimoteY_euclidean.csv", dPath="data/AllGestureWiimoteY", classRow="target", header=0, unknownLabel='?')
confusionMatrix_euclidean = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(AllGestureWiimoteY) Euclidean distance => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))
print()

knn.importFittedData("results/bk1/AllGestureWiimoteZ_dtw_fw.csv", dPath="data/AllGestureWiimoteZ", classRow="target", header=0, unknownLabel='?')
confusionMatrix_dtw = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(AllGestureWiimoteZ) DTW => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))

knn.importFittedData("results/bk1/AllGestureWiimoteZ_euclidean.csv", dPath="data/AllGestureWiimoteZ", classRow="target", header=0, unknownLabel='?')
confusionMatrix_euclidean = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(AllGestureWiimoteZ) Euclidean distance => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))
print()

knn.importFittedData("results/bk1/Car_dtw_fw.csv", dPath="data/Car", classRow=0)
confusionMatrix_dtw = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(Car) DTW => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))

knn.importFittedData("results/bk1/Car_euclidean.csv", dPath="data/Car", classRow=0)
confusionMatrix_euclidean = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(Car) Euclidean distance => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))
print()

knn.importFittedData("results/bk1/HandOutlines_dtw_fw.csv", dPath="data/HandOutlines", classRow=0)
confusionMatrix_dtw = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(HandOutlines) DTW => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))

knn.importFittedData("results/bk1/HandOutlines_euclidean.csv", dPath="data/HandOutlines", classRow=0)
confusionMatrix_euclidean = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(HandOutlines) Euclidean distance => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))
print()

knn.importFittedData("results/bk1/InlineSkate_dtw_fw.csv", dPath="data/InlineSkate", classRow=0)
confusionMatrix_dtw = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(InlineSkate) DTW => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))

knn.importFittedData("results/bk1/InlineSkate_euclidean.csv", dPath="data/InlineSkate", classRow=0)
confusionMatrix_euclidean = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(InlineSkate) Euclidean distance => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))
print()

knn.importFittedData("results/bk1/MALLAT_dtw_fw.csv", dPath="data/MALLAT", classRow=0)
confusionMatrix_dtw = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(MALLAT) DTW => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))

knn.importFittedData("results/bk1/MALLAT_euclidean.csv", dPath="data/MALLAT", classRow=0)
confusionMatrix_euclidean = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(MALLAT) Euclidean distance => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))
print()

knn.importFittedData("results/bk1/CinC_ECG_torso_dtw_fw.csv", dPath="data/CinC_ECG_torso", classRow=0)
confusionMatrix_dtw = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(CinC_ECG_torso) DTW => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))

knn.importFittedData("results/bk1/CinC_ECG_torso_euclidean.csv", dPath="data/CinC_ECG_torso", classRow=0)
confusionMatrix_euclidean = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(CinC_ECG_torso) Euclidean distance => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))
print()

knn.importFittedData("results/bk1/Symbols_dtw_fw.csv", dPath="data/Symbols", classRow=0)
confusionMatrix_dtw = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(Symbols) DTW => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))

knn.importFittedData("results/bk1/Symbols_euclidean.csv", dPath="data/Symbols", classRow=0)
confusionMatrix_euclidean = knn.buildConfusionMatrix()
CA = knn.classificationAccuracy()
p_mean = knn.precisionMean()
r_mean = knn.recallMean()
f_mean = knn.fScoreMean()
print("(Symbols) Euclidean distance => CA: {}, Precision_mean: {}, Recall_mean: {}, F-score_mean: {}".format(CA, p_mean, r_mean, f_mean))



'''
knn.importFittedData("results/bk1/Car_dtw_fw.csv", dPath="data/Car")
confusionMatrix_dtw = knn.buildConfusionMatrix()
knn.importFittedData("results/bk1/Car_euclidean.csv", dPath="data/Car")
confusionMatrix_euclidean = knn.buildConfusionMatrix()

knn.importFittedData("results/bk1/HandOutlines_dtw_fw.csv", dPath="data/HandOutlines")
confusionMatrix_dtw = knn.buildConfusionMatrix()
knn.importFittedData("results/bk1/HandOutlines_euclidean.csv", dPath="data/HandOutlines")
confusionMatrix_euclidean = knn.buildConfusionMatrix()

knn.importFittedData("results/bk1/InlineSkate_dtw_fw.csv", dPath="data/InlineSkate")
confusionMatrix_dtw = knn.buildConfusionMatrix()
knn.importFittedData("results/bk1/InlineSkate_euclidean.csv", dPath="data/InlineSkate")
confusionMatrix_euclidean = knn.buildConfusionMatrix()

knn.importFittedData("results/bk1/MALLAT_dtw_fw.csv", dPath="data/MALLAT")
confusionMatrix_dtw = knn.buildConfusionMatrix()
knn.importFittedData("results/bk1/MALLAT_euclidean.csv", dPath="data/MALLAT")
confusionMatrix_euclidean = knn.buildConfusionMatrix()

knn.importFittedData("results/bk1/CinC_ECG_torso_dtw_fw.csv", dPath="data/CinC_ECG_torso")
confusionMatrix_dtw = knn.buildConfusionMatrix()
knn.importFittedData("results/bk1/CinC_ECG_torso_euclidean.csv", dPath="data/CinC_ECG_torso")
confusionMatrix_euclidean = knn.buildConfusionMatrix()

knn.importFittedData("results/bk1/Symbols_dtw_fw.csv", dPath="data/Symbols")
confusionMatrix_dtw = knn.buildConfusionMatrix()
knn.importFittedData("results/bk1/Symbols_euclidean.csv", dPath="data/Symbols")
confusionMatrix_euclidean = knn.buildConfusionMatrix()
'''