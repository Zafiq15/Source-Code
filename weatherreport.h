#ifndef weatherreport_h
#define weatherreport_h

using namespace std;

#include <string>

// Function to calculate the probability of rain based on the ACC and AP values.
double ProbabilityofRainsummary(string ACC, string AP);

// Displays the city map based on the processed data.
void displaycitydata(int cityId);

// Prints a summary report of the weather forecast based on the processed data.
void weathersummaryreport();

#endif