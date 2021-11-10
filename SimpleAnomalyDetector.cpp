
#include "SimpleAnomalyDetector.h"


SimpleAnomalyDetector::SimpleAnomalyDetector() {}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
    /*
     * find the correlated features in the time series- checking every couple of features.
     */
    int flag = 0; //flag to check if there is any correlated features.
    for (int i = 0; i < ts.get_num_columns(); ++i) {
        float m = 0.99;
        int c = -1;
        float pear;
        float* arrayI = from_vector_to_array(ts.get_column_by_loc(i)); // create array from info in feature 1
        for (int j = i + 1; j < ts.get_num_columns(); ++j) {
            float* arrayJ = from_vector_to_array(ts.get_column_by_loc(j)); // create array from info in feature 2
            pear = abs(pearson(arrayI, arrayJ, (int)ts.get_num_columns())); // find the pearson of the features togther
            if (pear > m) {
                m = pear;
                c = j;
                if (c != -1) {
                    /*
                     * add the correlated feature we found to the vector of correlated features of the time series
                     */
                    struct correlatedFeatures cor;
                    create_cor_feature(cor, ts, pear, i ,c);
                    cf.push_back(cor);
                    flag = 1;
                }
            }
        }
    }
    if (flag == 0) {
        cout << "There is no correlated features at all.";
        exit;
    }
    //debug:
//    cout << "features: " << cf[0].feature1 << cf[0].feature2 << endl;
//    cout << "threshold :" << cf[0].threshold << endl;
//    cout << "corralation :" << cf[0].corrlation;
}
/**
 * This function return the linear reg of the points of the correlated features.
 * @param c - the correlatedFeatures contain the info about the features
 * @param ts - time series
 * @return line return from linear_reg
 */
Line find_linear_reg (struct correlatedFeatures c, TimeSeries ts) {
    int sizeOfFeature = ts.get_column_by_head(c.feature1).size();
    Point** pointsArray = find_points_of_correlated_features(c, ts);
    Line l = linear_reg(pointsArray, sizeOfFeature);
    return l;
}
/**
 * This function convert vector to array (so we can use it in "pearson")
 * @param feature - the vector that contains the feature info
 * @return array
 */
float* from_vector_to_array(vector<float> feature) {
    float* array = new float[feature.size()];
    for (int i = 0; i < feature.size();i++) {
        array[i] = feature[i];
    }
    return array;
}
/**
 * This function create the points from the info in the correlated features.
 * @param c  - the correlatedFeatures contain the info about the features
 * @param ts - time series
 * @return array of pointer to points
 */
Point** find_points_of_correlated_features (struct correlatedFeatures c, TimeSeries ts) {
    int sizeOfFeature = ts.get_column_by_head(c.feature1).size();
    Point** pointsArray = new Point*[sizeOfFeature];
    for (int i = 0; i < sizeOfFeature; i++) {
        // create point from line i in feature 1 and line i in feature 2.
        Point *p = new Point(ts.get_column_by_head(c.feature1)[i],
                             ts.get_column_by_head(c.feature2)[i]);
        pointsArray[i] = p;
    }
    return pointsArray;
}
/**
 * This function return the maximum threshold.
 * @param points - the points in the graph of the correlated features.
 * @param line - the linear reg of the graph.
 * @param size - the size of the points array.
 * @return maximum threshold value
 */
float max_threshold (Point** points, Line line, int size) {
    float maxThreshold = 0;
    int currLine = 0;
    for (int i = 0; i < size; ++i) {
        float d = dev(*points[i], line);
        if (d > maxThreshold) {
            maxThreshold = d;
            currLine = i + 1;
        }
    }
    return 1.1 * maxThreshold;

}

int return_timeStep(Point** points, Line line, int size) {
    float maxThreshold = 0;
    int currLine = 0;
    for (int i = 0; i < size; ++i) {
        float d = dev(*points[i], line);
        if (d > maxThreshold) {
            maxThreshold = d;
            currLine = i + 1;
        }
    }
    return currLine;
}

void create_cor_feature (struct correlatedFeatures& cor, TimeSeries ts, float pear, int i, int c) {
    if (i != -1 && c != -1) {
        cor.feature1 = ts.get_head_line_by_loc(i);
        cor.feature2 = ts.get_head_line_by_loc(c);
    }
    cor.corrlation = pear;
    cor.lin_reg = find_linear_reg(cor, ts);
    Point** p = find_points_of_correlated_features(cor, ts);
    cor.threshold = max_threshold(p, cor.lin_reg,ts.get_column_by_head(cor.feature1).size());
    cor.line = return_timeStep(p, cor.lin_reg,ts.get_column_by_head(cor.feature1).size());
}


vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> reports;
    for (correlatedFeatures i : this->cf) {
        correlatedFeatures testedCor;
        testedCor.feature1 = i.feature1;
        testedCor.feature2 = i.feature2;
        float* arrayI = from_vector_to_array(ts.get_column_by_head(i.feature1));
        float* arrayJ = from_vector_to_array(ts.get_column_by_head(i.feature2));
        float pear = abs(pearson(arrayI, arrayJ, (int)ts.get_num_columns()));
        create_cor_feature(testedCor, ts, pear, -1, -1);
        if (testedCor.threshold > i.threshold) {
            AnomalyReport singleReport(testedCor.feature1 + "-" + testedCor.feature2,testedCor.line);
            reports.push_back(singleReport);

        }
    }
    return reports;
}
