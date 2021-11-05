

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <string>
#include <vector>
using namespace std;

class TimeSeries{
    const char* fileName;
    vector<vector<string>> features;
public:
    TimeSeries(const char* CSVfileName){
        fileName = CSVfileName;
    }
    const char* get_file() {
        return fileName;
    }
    void add_vector(vector<string> f) {
        features.push_back(f);
    }
    vector<vector<string>> get_vector() {
        return features;
    }
    vector<string> get_vector_by_location(int vectorNum) {
        return features[vectorNum];
    }
    void set_vector(int vectorNum, string info){
        features[vectorNum].push_back(info);
    }
    void set_vector_by_location(int vectorNum, int timeIndex, string info) {
        features[vectorNum][timeIndex] = info;
    }

};

vector<std::string> splits_by_comma(string text);
void read_file(TimeSeries ts);

#endif /* TIMESERIES_H_ */