

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
using namespace std;

class TimeSeries{
private:
    string csvFname;
public:

    TimeSeries(const char* CSVfileName);

// the array with headlines of each column:
vector<string> headLines;
    vector<vector<float>> columns;
};



#endif /* TIMESERIES_H_ */