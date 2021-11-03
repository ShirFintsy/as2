

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;

class TimeSeries{
    const char* fileName;
public:
    TimeSeries(const char* CSVfileName){
        fileName = CSVfileName;
    }
    const char* get_file() {
        return fileName;
    }

};



#endif /* TIMESERIES_H_ */