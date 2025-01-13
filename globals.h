#ifndef globals_h
#define globals_h

#include <string>

using namespace std;

// Structure to store the parsed city location data
struct CityLocation
{
  int x, y, value;
  string cityName;
};

// Structure to store the parsed cloud location data
struct CloudLocation
{
  int x, y, value;
};

// Structure to store the parsed pressure location data
struct Pressure
{
  int x, y, value;
};

// Global variables
extern int **cityData;
extern int **cloudData;
extern int **pressureData;
extern int minX, maxX, minY, maxY;

extern string citynamearray[100];
extern string *cloudarray;
extern string *pressurearray;

// Array to store city locations
extern CityLocation cityLocations_Array[100];
extern int cityLocationCount;

// Array to cloud locations
extern CloudLocation cloudLocation_Array[100];
extern int cloudLocationCount;

// Array to store Pressure locations
extern Pressure Pressure_Array[100];
extern int Pressure_Count;

#endif