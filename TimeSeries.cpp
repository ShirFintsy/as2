#include "TimeSeries.h"

TimeSeries::TimeSeries(const char* CSVfileName) : csvFname(CSVfileName){
    // open the file and check if valid:
    ifstream myFile(csvFname);
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");
    string stringHeadLine;
    // get the first line of the file (the headlines):
    getline(myFile, stringHeadLine);
    // convert the string to stream:
    istringstream streamHeadline(stringHeadLine);
    string item;
    // insert each headline to the corresponding column:
    while (getline(streamHeadline, item, ',')) {
        headLines.push_back(item);
    }
    unsigned int num_columns = headLines.size();
    string line;
    // create the specific number of columns:
    for (int i = 0; i < num_columns; i ++) {
        columns.emplace_back();
    }
    // read each line in the file:
    while (std::getline(myFile, line)) {
        istringstream streamLine(line);
        // check the line is valid:
        if(count(line.begin(), line.end(), ',') != num_columns - 1) {
            throw runtime_error("table is invalid");
        }
        // insert value to each column:
        for (int i = 0; i < num_columns; i++) {
            getline(streamLine, item, ',');
            float num = stof(item);
            columns[i].push_back(num);
        }
    }
}