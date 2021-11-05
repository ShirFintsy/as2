

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

    // consturctor:
    TimeSeries(const char* CSVfileName);
    /**
     * this function return a specific column by its headline.
     * @param headLine.
     * @return specific column.
     */
    vector<float> get_column(string headLine);
    // the array with headlines of each column:
    vector<string> headLines;
    // 2D array of vectors (columns):
    vector<vector<float>> columns;

    unsigned int num_columns;
    /**
     * this function returns the number of columns in the table.
     * @return
     */
    unsigned int get_num_columns();
    /**
     * this function return a specific headline by its number.
     * @param num .
     * @return headline.
     */
    string get_head_line(int num);
    /**
     * this function return a specific column by its place.
     * @param headLine.
     * @return specific column.
     */
    vector<float> get_column(int num);
};



#endif /* TIMESERIES_H_ */