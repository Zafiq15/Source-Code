#ifndef readFile_h
#define readFile_h

#include <string>

using namespace std;

// Function to store the configuration file information (e.g., print or log data)
void storeConfigFileInfo(const std::string &filename);

// Helper function to process grid range lines from the configuration file
void processGridRangeLine(const std::string &line, int &minX, int &maxX, int &minY, int &maxY);

// Initializes a city's location with the specified coordinates (x, y), value, and city name.
void initialiseCityLocation(int x, int y, int value, const std::string &cityName);

// Initializes a cloud's location with the specified coordinates (x, y) and value.
void initialiseCloudLocation(int x, int y, int value);

// Initializes the pressure value at the specified coordinates (x, y).
void initialisePressure(int x, int y, int value);

// Processes city location data from the specified configuration file.
void processCitylocationData(const std::string &filename);

// Processes cloud location data from the specified configuration file.
void processCloudlocationData(const std::string &filename);

// Processes pressure data from the specified configuration file.
void processPressureData(const std::string &filename);

#endif