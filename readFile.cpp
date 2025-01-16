#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <regex>

#include "printfile.h"
#include "globals.h"
#include "readFile.h"

// Pointers to dynamically allocate memory for city, cloud, and pressure data grids
int **cityData = nullptr;
int **cloudData = nullptr;
int **pressureData = nullptr;
int minX = 0, maxX = 0, minY = 0, maxY = 0;

// Array to store city names
string citynamearray[100];

// Array to store city locations
CityLocation cityLocations_Array[100];
int cityLocationCount = 0;

// Array to cloud locations
CloudLocation cloudLocation_Array[100];
int cloudLocationCount = 0;

// Array to store Pressure locations
Pressure Pressure_Array[100];
int Pressure_Count = 0;

// Function to initialize the city location data and add it to the array
void initialiseCityLocation(int x, int y, int value, const string &cityName)
{
    // Ensure we don't exceed the array size
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

    // Check if the file opened successfully
    if (!inputfile)
    {
        cerr << "Error: file cannot open" << endl;
        return;
    }

    string line;
    while (getline(inputfile, line))
    {
        // Find the positions of specific characters in the line
        size_t cityopenBracket = line.find('[');
        size_t citycloseBracket = line.find(']');
        size_t citydashPos = line.find('-', citycloseBracket);
        size_t citysecondDash = line.find('-', citydashPos + 1);

        // Skip the line if any required character is not found
        if (cityopenBracket == string::npos || citycloseBracket == string::npos || citydashPos == string::npos || citysecondDash == string::npos)
        {
            continue;
        }

        // Extract the city coordinates string between '[' and ']'
        string citycoordinates = line.substr(cityopenBracket + 1, citycloseBracket - cityopenBracket - 1);

        // Find the position of the comma in the coordinates
        size_t commaPos = citycoordinates.find(',');

        // Extract the X and Y coordinates
        int x = stoi(citycoordinates.substr(0, commaPos));
        int y = stoi(citycoordinates.substr(commaPos + 1));

        // Extract the value between ']' and the first '-'
        int value = stoi(line.substr(citycloseBracket + 2, citydashPos - citycloseBracket - 2));

        // Extract the city name after the second '-'
        string cityname = line.substr(citysecondDash + 1);

        // Initialize the city location with the extracted data
        initialiseCityLocation(x, y, value, cityname);
    }
    inputfile.close();
}

// Function to process the cloud location data from the file
void processCloudlocationData(const string &filename)
{
    ifstream inputfile(filename);

    // Check if the file opened successfully
    if (!inputfile)
    {
        cerr << "Error: file cannot open" << filename << endl;
        return;
    }

    string line;
    while (getline(inputfile, line))
    {
        // Find the positions of specific characters in the line
        size_t cloudopenBracket = line.find('[');
        size_t cloudcloseBracket = line.find(']');
        size_t clouddash = line.find('-');

        // Skip the line if any required character is not found
        if (cloudopenBracket == string ::npos || cloudcloseBracket == string ::npos || clouddash == string ::npos)
        {
            continue;
        }

        // Extract the cloud coordinates string between '[' and ']'
        string cloudcoordinates = line.substr(cloudopenBracket + 1, cloudcloseBracket - cloudopenBracket - 1);

        // Find the position of the comma in the coordinates
        size_t commaPos = cloudcoordinates.find(',');

        // Extract the X and Y coordinates
        int x = stoi(cloudcoordinates.substr(0, commaPos));
        int y = stoi(cloudcoordinates.substr(commaPos + 1));

        // Extract the cloud value after the ']'
        int value = stoi(line.substr(cloudcloseBracket + 2));

        // Initialize the cloud location with the extracted data
        initialiseCloudLocation(x, y, value);
    }
    inputfile.close();
}

// Function to process the pressure location data from the file
void processPressureData(const string &filename)
{
    ifstream inputfile(filename);

    // Check if the file opened successfully
    if (!inputfile)
    {
        cerr << "Error: file cannot be open " << filename << endl;
        return;
    }

    string line;
    while (getline(inputfile, line))
    {
        // Find the positions of specific characters in the line
        size_t pressureOpenBracket = line.find('[');
        size_t pressureCloseBracket = line.find(']');
        size_t pressureDash = line.find('-');

        // Skip the line if any required character is not found
        if (pressureOpenBracket == string::npos || pressureCloseBracket == string::npos || pressureDash == string::npos)
        {
            continue;
        }

        // Extract the pressure coordinates string between '[' and ']'
        string pressurecoordinates = line.substr(pressureOpenBracket + 1, pressureCloseBracket - pressureOpenBracket);

        // Find the position of the comma in the coordinates
        size_t commaPos = pressurecoordinates.find(',');

        // Extract the X and Y coordinates
        int x = stoi(pressurecoordinates.substr(0, commaPos));
        int y = stoi(pressurecoordinates.substr(commaPos + 1));

        // Extract the value after the ']'
        int value = stoi(line.substr(pressureCloseBracket + 2));

        // Initialize the pressure location with the extracted data
        initialisePressure(x, y, value);
    }
    inputfile.close();
}

// Function to process the grid range line and extract X and Y ranges
void processGridRangeLine(const string &line, int &minX, int &maxX, int &minY, int &maxY)
{
    // Find the position of '=' in the line to split the string
    size_t equalPos = line.find("=");

    // Extract the part before '=' and after '='
    string beforeEquals = line.substr(0, equalPos);
    string afterEquals = line.substr(equalPos + 1);

    // Find the position of '-' to separate the min and max values
    size_t dashPos = afterEquals.find("-");

    // Extract the min and max values by splitting the string at the dash
    string beforeDash = afterEquals.substr(0, dashPos);
    string afterDash = afterEquals.substr(dashPos + 1);

    // Convert the min and max values from string to integer
    int min = stoi(beforeDash);
    int max = stoi(afterDash);

    // Process the X range
    if (beforeEquals == "GridX_IdxRange")
    {
        minX = min;
        maxX = max;
        cout << "Reading in GridX_IdxRange: " << min << "-" << max << ".....done!" << endl;
        cout << endl;
    }
    // Process the Y range
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

    // Check if the file was successfully opened
    if (!inputConfigFile.is_open())
    {
        cout << "Failed to open file: " << filename << endl;
        return;
    }

    string readConfigFile;
    int lineCount = 0;

    // Read the configuration file line by line
    while (getline(inputConfigFile, readConfigFile))
    {
        if (readConfigFile.empty())
        {
            continue;
        }
        if (readConfigFile.find("//") != string::npos)
        {
            continue;
        }
        lineCount++;

        // If "Grid" is found, process the grid range
        if (lineCount == 1 || lineCount == 2)
        {
            processGridRangeLine(readConfigFile, minX, maxX, minY, maxY);
        }

        // Once both GridX and GridY ranges are found, initialize the grid data
        if (lineCount == 3)
        {
            // Calculate grid range for X-axis and Y-axis
            int gridRangeX = (maxX - minX) + 1;
            int gridRangeY = (maxY - minY) + 1;

            // Dynamically allocate cityData based on grid range
            cityData = new int *[gridRangeX];
            for (int x = 0; x < gridRangeX; x++)
            {
                // Allocate memory for each row
                cityData[x] = new int[gridRangeY];
                for (int y = 0; y < gridRangeY; y++)
                {
                    // Initialize grid values to 0
                    cityData[x][y] = 0;
                }
            }

            // Dynamically allocate memory for cloudData array based on grid range
            cloudData = new int *[gridRangeX];
            for (int x = 0; x < gridRangeX; x++)
            {
                // Allocate memory for each row
                cloudData[x] = new int[gridRangeY];
                for (int y = 0; y < gridRangeY; y++)
                {
                    // Initialize grid values to 0
                    cloudData[x][y] = 0;
                }
            }

            // Dynamically allocate memory for pressureData array based on grid range
            pressureData = new int *[gridRangeX];
            for (int x = 0; x < gridRangeX; x++)
            {
                // Allocate memory for each row
                pressureData[x] = new int[gridRangeY];
                for (int y = 0; y < gridRangeY; y++)
                {
                    // Initialize grid values to 0
                    pressureData[x][y] = 0;
                }
            }

            processCitylocationData(readConfigFile);

            cout << readConfigFile << "...done!" << endl;

            // Populate cityData array with values from cityLocations_Array
            for (int i = 0; i < cityLocationCount; i++)
            {
                int x = cityLocations_Array[i].x - minX;
                int y = cityLocations_Array[i].y - minY;
                int cityID = cityLocations_Array[i].value;
                cityData[x][y] = cityLocations_Array[i].value;
                citynamearray[cityID] = cityLocations_Array[i].cityName;
            }
        }
        if (lineCount == 4)
        {
            processCloudlocationData(readConfigFile);

            cout << readConfigFile << "...done!" << endl;

            // Populate cloudData array with values from cloudLocation_Array
            for (int i = 0; i < cloudLocationCount; i++)
            {
                int x = cloudLocation_Array[i].x - minX;
                int y = cloudLocation_Array[i].y - minY;
                cloudData[x][y] = cloudLocation_Array[i].value;
            }
        }
        if (lineCount == 5)
        {
            processPressureData(readConfigFile);

            cout << readConfigFile << "...done!" << endl;

            // Populate pressureData array with values from Pressure_Array
            for (int i = 0; i < Pressure_Count; i++)
            {
                int x = Pressure_Array[i].x - minX;
                int y = Pressure_Array[i].y - minY;
                pressureData[x][y] = Pressure_Array[i].value;
            }
        }
    }

    // clear city location array and cloud location array and pressure location array
    cityLocationCount = 0;
    cloudLocationCount = 0;
    Pressure_Count = 0;

    cout << "\nAll records successfully store. Going back to main menu ..." << endl;
    inputConfigFile.close();
}
