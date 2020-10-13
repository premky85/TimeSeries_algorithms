# Optimization of dynamic time warping algorithm
## Description

Dynamic time warping (DTW) is one of the algorithms used for calculating distance between time series with different lenghts.
It's computational time and space complexity equal <img src="https://render.githubusercontent.com/render/math?math=O(n \times m)"> where *n* and *m* are
lengths of first and second time series. Main purpose of this project is to optimize computational complexity of DTW algorithm by parallelizing it.

## Installation and usage

Clone repository to your computer. Folder <code>src/algs/</code> contains DTW algorithms written in C language. If you change them you need to compile them using CMake. And copy newly compiled <code>libtimeseries_dtw.so</code> file to <code>bench/DTW/lib/</code>
Folder "bench" includes Python scripts for benchmarking DTW algorithms. Main DTW class is contained in <code>bench/DTW/dtw.py</code> file.

If you wish to use DTW to calculate distance between two time series you can do it like this

```
dtw = DTW()
distance, time = dtw.run(dtw_algorithm, time_series_1, time_series_2)
```

First argument <code>dtw_algorithm</code> represents algorithm used to calculate DTW distance. Available options are:
<code>"dtw_fw", "dtw_bk", "dtw_fwbk", "dtw_diag", "dtw_pruned", "dtw_fwbk_par", "dtw_diag_cache", "dtw_diag_par", "dtw_diag_par_cache", "dtw_fw_mem", "dtw_bk_mem", "dtw_fwbk_par_mem", "dtw_diag_cache_mem", "dtw_diag_par_cache_mem"</code>.
Second and third arguments are arrays representing two time series.

Function returns calculated distance and elapsed time.
