cmake_minimum_required(VERSION 3.15)
project(timeseries_dtw)
set(CMAKE_C_STANDARD 11)

#set(SOURCE_FILES main.c)
#add_executable(timeseries_dtw ${SOURCE_FILES})
find_package(Threads REQUIRED)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")

include_directories(algs)



add_library(${PROJECT_NAME} SHARED
        algs/dtw_bk.h
        algs/dtw_diag.h
        algs/dtw_fwbk.h
        algs/dtw_fwbk_par.h
        algs/dtw_fw.h
        algs/helpers.h
        algs/dtw_algs.c
        algs/dtw_prunned.h)

#add_executable(${PROJECT_NAME} main.c)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(${PROJECT_NAME} m Threads::Threads)