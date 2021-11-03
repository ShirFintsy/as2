cmake_minimum_required(VERSION 3.20)
project(advEx2)

set(CMAKE_CXX_STANDARD 14)

add_executable(advEx2 MainTrain.cpp AnomalyDetector.h SimpleAnomalyDetector.h SimpleAnomalyDetector.cpp TimeSeries.h
        TimeSeries.cpp anomaly_detection_util.h anomaly_detection_util.cpp)
