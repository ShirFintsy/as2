#include <fstream>
#include <iostream>
#include "TimeSeries.h"

void read_file(TimeSeries ts) {
    const char* fileName = ts.get_file();
    // Read from the text file
    std::fstream fs;
    fs.open (fileName, std::fstream::in | std::fstream::out | std::fstream::app);
    if (!fs) {
        cout << "Unable to open file";
    }
    std::string myLine;
    int lineNum = 1;
    int numOfFeatures = 0;
    // Use a while loop together with the getline() function to read the file line by line
    while (getline (fs, myLine)) {
        vector<string> features;
        if (lineNum == 1) { //the first line
            //names of the featurs???
            features = splits_by_comma(myLine);
            numOfFeatures = (int)features.size();
            for (int i = 0; i < numOfFeatures; ++i) {
                ts.add_vector(vector<string>(1));
                ts.set_vector_by_location(i, 0, features[i]);
            }
        } else {
            vector<string> allInfo = splits_by_comma(myLine);

            for(int i = 0; i < numOfFeatures; i++) {
                ts.set_vector(i, allInfo[i]);
            }
        } lineNum++;
    }
    fs.close();
}
/*
 * This function splits the text given by commas in the text.
 * Return a vector of all the parts of the text without the commas.
 * ###########need to check it###################
 */
vector<std::string> splits_by_comma(string text) {
    string temp = "";
    vector<string> splits;

    for(int i=0; i<(int)text.size(); i++){
        // If cur char is not del, then append it to the cur "word", otherwise
        // you have completed the word, print it, and start a new word.
        if(text[i] != ','){
            temp += text[i];
        }
        else{
            splits.push_back(temp);
            temp = "";
        }
    }
    splits.push_back(temp);
    return splits;
}
