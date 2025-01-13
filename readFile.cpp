#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <regex>

#include "printfile.h"
#include "globals.h"
#include "readFile.h"

int **cityData = nullptr;
int **cloudData = nullptr;
int **pressureData = nullptr;
int minX = 0, maxX = 0, minY = 0, maxY = 0;

string citynamearray[100];

// Array to store city locations
CityLocation cityLocations_Array[100];
int cityLocationCount = 0;

// // Array to cloud locations
CloudLocation cloudLocation_Array[100];
int cloudLocationCount = 0;

// // Array to store Pressure locations
Pressure Pressure_Array[100];
int Pressure_Count = 0;

// Function to initialize the city location data and add it to the array
void initialiseCityLocation(int x, int y, int value, const string &cityName)
{
    if (cityLocationCount < 100)
    {
        cityLocations_Array[cityLocationCount] = {x, y, value, cityName};
        cityLocationCount++;
    }
    else
    {
        cerr << "Error: City location data array is full!" << endl;
    }
}

// Function to initialize the cloud location data and add it to the array
void initialiseCloudLocation(int x, int y, int value)
{
    // Ensure we don't exceed the array size
    if (cloudLocationCount < 100)
    {
        cloudLocation_Array[cloudLocationCount] = {x, y, value};
        cloudLocationCount++;
    }
    else
    {
        cerr << "Error: Cloud location data array is full!" << endl;
    }
}

// Function to initialize the pressure location data and add it to the array
void initialisePressure(int x, int y, int value)
{
    // Ensure we don't exceed the array size
    if (Pressure_Count < 100)
    {
        Pressure_Array[Pressure_Count] = {x, y, value};
        Pressure_Count++;
    }
    else
    {
        cerr << "Error: Pressure data array is full!" << endl;
    }
}

// Function to process the city location data from the file
void processCitylocationData(const string &filename)
{
    ifstream inputfile(filename);

    if (!inputfile)
    {
        cerr << "Error: file cannot open" << endl;
        return;
    }

    string line;
    while (getline(inputfile, line))
    {
        size_t cityopenBracket = line.find('[');
        size_t citycloseBracket = line.find(']');
        size_t citydashPos = line.find('-', citycloseBracket);
        size_t citysecondDash = line.find('-', citydashPos + 1);

        if (cityopenBracket == string::npos || citycloseBracket == string::npos || citydashPos == string::npos || citysecondDash == string::npos)
        {
            continue;
        }

        string citycoordinates = line.substr(cityopenBracket + 1, citycloseBracket - cityopenBracket - 1);
        size_t commaPos = citycoordinates.find(',');
        int x = stoi(citycoordinates.substr(0, commaPos));
        int y = stoi(citycoordinates.substr(commaPos + 1));
        int value = stoi(line.substr(citycloseBracket + 2, citydashPos - citycloseBracket - 2));
        string cityname = line.substr(citysecondDash + 1);

        initialiseCityLocation(x, y, value, cityname);
    }
    inputfile.close();
}

// Function to process the cloud location data from the file
void processCloudlocationData(const string &filename)
{
    ifstream inputfile(filename);

    if (!inputfile)
    {
        cerr << "Error: file cannot open" << filename << endl;
        return;
    }

    string line;
    while (getline(inputfile, line))
    {

        size_t cloudopenBracket = line.find('[');
        size_t cloudcloseBracket = line.find(']');
        size_t clouddash = line.find('-');

        if (cloudopenBracket == string ::npos || cloudcloseBracket == string ::npos || clouddash == string ::npos)
        {
            continue;
        }

        string cloudcoordinates = line.substr(cloudopenBracket + 1, cloudcloseBracket - cloudopenBracket - 1);

        size_t commaPos = cloudcoordinates.find(',');
        int x = stoi(cloudcoordinates.substr(0, commaPos));
        int y = stoi(cloudcoordinates.substr(commaPos + 1));

        int value = stoi(line.substr(cloudcloseBracket + 2));

        initialiseCloudLocation(x, y, value);
    }
    inputfile.close();
}

// Function to process the pressure location data from the file
void processPressureData(const string &filename)
{
    ifstream inputfile(filename);

    if (!inputfile)
    {
        cerr << "Error: file cannot be open " << filename << endl;
        return;
    }

    string line;
    while (getline(inputfile, line))
    {

        size_t pressureOpenBracket = line.find('[');
        size_t pressureCloseBracket = line.find(']');
        size_t pressureDash = line.find('-');

        if (pressureOpenBracket == string::npos || pressureCloseBracket == string::npos || pressureDash == string::npos)
        {
            continue;
        }

        string pressurecoordinates = line.substr(pressureOpenBracket + 1, pressureCloseBracket - pressureOpenBracket);
        size_t commaPos = pressurecoordinates.find(',');

        int x = stoi(pressurecoordinates.substr(0, commaPos));
        int y = stoi(pressurecoordinates.substr(commaPos + 1));
        int value = stoi(line.substr(pressureCloseBracket + 2));

        initialisePressure(x, y, value);
    }
    inputfile.close();
}

// Function to process the grid range line and extract X and Y ranges
void processGridRangeLine(const string &line, int &minX, int &maxX, int &minY, int &maxY)
{
    size_t equalPos = line.find("=");
    string beforeEquals = line.substr(0, equalPos);
    string afterEquals = line.substr(equalPos + 1);

    size_t dashPos = afterEquals.find("-");
    string beforeDash = afterEquals.substr(0, dashPos);
    string afterDash = afterEquals.substr(dashPos + 1);

    int min = stoi(beforeDash);
    int max = stoi(afterDash);

    if (beforeEquals == "GridX_IdxRange")
    {
        minX = min;
        maxX = max;
        cout << "Reading in GridX_IdxRange: " << min << "-" << max << ".....done!" << endl;
        cout << endl;
    }
    else if (beforeEquals == "GridY_IdxRange")
    {
        minY = min;
        maxY = max;
        cout << "Reading in GridY_IdxRange: " << min << "-" << max << ".....done!" << endl;
        cout << endl;
    }
}

// Function to store configuration file info and print out the data
void storeConfigFileInfo(const string &filename)
{
    fstream inputConfigFile(filename.c_str(), fstream::in);
    if (!inputConfigFile.is_open())
    {
        cout << "Failed to open file: " << filename << endl;
        return;
    }

    string readConfigFile;
    int storing_gridXandY = 0;
    bool isInitialized = false;

    while (getline(inputConfigFile, readConfigFile))
    {
        size_t found_Xrange = readConfigFile.find("Grid");

        if (found_Xrange != string::npos)
        {
            processGridRangeLine(readConfigFile, minX, maxX, minY, maxY);
            storing_gridXandY++;
        }

        if (storing_gridXandY == 2 && !isInitialized)
        {
            int gridRangeX = (maxX - minX) + 1;
            int gridRangeY = (maxY - minY) + 1;

            // Dynamically allocate cityData based on grid range
            cityData = new int *[gridRangeX];
            for (int x = 0; x < gridRangeX; x++)
            {
                cityData[x] = new int[gridRangeY];
                for (int y = 0; y < gridRangeY; y++)
                {
                    cityData[x][y] = 0;
                }
            }
            isInitialized = true;

            cloudData = new int *[gridRangeX];
            for (int x = 0; x < gridRangeX; x++)
            {
                cloudData[x] = new int[gridRangeY];
                for (int y = 0; y < gridRangeY; y++)
                {
                    cloudData[x][y] = 0;
                }
            }
            isInitialized = true;

            pressureData = new int *[gridRangeX];
            for (int x = 0; x < gridRangeX; x++)
            {
                pressureData[x] = new int[gridRangeY];
                for (int y = 0; y < gridRangeY; y++)
                {
                    pressureData[x][y] = 0;
                }
            }
            isInitialized = true;
        }
        if (storing_gridXandY == 2 && isInitialized)
        {
            size_t found_txt = readConfigFile.find("citylocation.txt");
            size_t cloud_txt = readConfigFile.find("cloudcover.txt");
            size_t pressure_txt = readConfigFile.find("pressure.txt");

            if (found_txt != string::npos)
            {
                cout << "Storing Data from input file: \n"
                     << endl;

                processCitylocationData(readConfigFile);

                cout << "citylocation.txt" << "...done!" << endl;

                // Populate cityData array with values from cityLocations_Array
                for (int i = 0; i < cityLocationCount; i++)
                {
                    int x = cityLocations_Array[i].x - minX;       // Adjust coordinates based on minX
                    int y = cityLocations_Array[i].y - minY;       // Adjust coordinates based on minY
                    int cityID = cityLocations_Array[i].value;     // Get city value
                    cityData[x][y] = cityLocations_Array[i].value; // Assign city value to the grid
                    citynamearray[cityID] = cityLocations_Array[i].cityName;
                }
            }
            else if (cloud_txt != string ::npos)
            {
                processCloudlocationData(readConfigFile);

                cout << "cloudcover.txt" << "...done!" << endl;

                for (int i = 0; i < cloudLocationCount; i++)
                {
                    int x = cloudLocation_Array[i].x - minX;        // Adjust coordinates based on minX
                    int y = cloudLocation_Array[i].y - minY;        // Adjust coordinates based on minY
                    cloudData[x][y] = cloudLocation_Array[i].value; // Assign city value to the grid
                }
            }
            else if (pressure_txt != string::npos)
            {
                processPressureData(readConfigFile);

                cout << "pressure.txt" << "...done!" << endl;

                for (int i = 0; i < Pressure_Count; i++)
                {
                    int x = Pressure_Array[i].x - minX;           // Adjust coordinates based on minX
                    int y = Pressure_Array[i].y - minY;           // Adjust coordinates based on minY
                    pressureData[x][y] = Pressure_Array[i].value; // Assign pressure value to the grid
                }
            }
        }
    }

    cout << "\nAll records successfully store. Going back to main menu ..." << endl;
    inputConfigFile.close();
}

