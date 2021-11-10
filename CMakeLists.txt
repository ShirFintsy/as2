cmake_minimum_required(VERSION 3.20)
project(advEx2)

set(CMAKE_CXX_STANDARD 14)

add_executable(advEx2 anomaly_detection_util.cpp anomaly_detection_util.h timeseries.cpp SimpleAnomalyDetector.cpp
        SimpleAnomalyDetector.h timeseries.h MainTrain.cpp AnomalyDetector.h)
