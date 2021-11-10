

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <iostream>

struct correlatedFeatures{
    string feature1,feature2;  // names of the correlated features
    float corrlation; // correlation > 0.9
    Line lin_reg;
    float threshold; //היסט max
    int line;
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
    vector<correlatedFeatures> cf;
public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const timeseries& ts);
    virtual vector<AnomalyReport> detect(const timeseries& ts);

    vector<correlatedFeatures> getNormalModel(){
        return cf;
    }

};
Point** find_points_of_correlated_features (struct correlatedFeatures c, timeseries ts);
float* from_vector_to_array(vector<float> feature);
Line find_linear_reg (struct correlatedFeatures c, timeseries ts);
float max_threshold (Point** points, Line line, int size);
int return_timeStep(Point** points, Line line, int size);

void create_cor_feature(struct correlatedFeatures& cor, timeseries ts, float pear, int i, int c);
#endif /* SIMPLEANOMALYDETECTOR_H_ */