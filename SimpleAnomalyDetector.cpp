
#include "SimpleAnomalyDetector.h"
#include "TimeSeries.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    read_file(ts);
    for (int i = 0; i < ts.getFeatureSize(); ++i) {
        int m = 0;
        int c = -1;
        for (int j = i + 1; j < ts.getFeatureSize(); ++j) {
            if (pearson, ))///////////////////////i stoped in the middle.
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    // TODO Auto-generated destructor stub
}
