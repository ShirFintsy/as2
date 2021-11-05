#include "TimeSeries.h"

int main() {
    char* name= "table.txt";
    TimeSeries* ts = new TimeSeries(name);
    read_file(*ts);
}
