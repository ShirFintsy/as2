cmake_minimum_required(VERSION 3.20)
project(advEx2)

set(CMAKE_CXX_STANDARD 14)

add_executable(advEx2 SimpleAnomalyDetector.cpp SimpleAnomalyDetector.h timeseries.cpp TimeSeries.h MainTrain.cpp AnomalyDetector.h)
