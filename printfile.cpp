#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <regex>


#include "globals.h"
#include "printfile.h"
#include "readFile.h"


// print the city location data grid
void printCityData(int minX, int maxX, int minY, int maxY)
{
    int gridRangeX = (maxX - minX) + 1; // 9
    int gridRangeY = (maxY - minY) + 1; // 9

    cout << "\nCity location data grid: " << endl;

    // Top border
    cout << " ";
    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#"; // 3 spaces for alignment
    }
    cout << endl;

    // Grid data
    for (int y = gridRangeY - 1; y >= 0; y--)
    {
        cout << setw(2) << setfill(' ') << y << " "; // Print Y-coordinate
        cout << "# ";                                // Left border

        for (int x = 0; x < gridRangeX; x++)
        {
            // Print city data or space if not greater than 0
            if (cityData[x][y] > 0)
            {
                cout << setw(2) << setfill(' ') << cityData[x][y];
            }
            else
            {
                cout << setw(2) << " "; // Empty space if value is 0 or less
            }
            cout << " "; // Space between grid values
        }

        cout << " #"; // Right border
        cout << endl;
    }

    // Bottom border
    cout << " ";
    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#"; // 3 spaces for alignment
    }
    cout << endl;

    // Print column numbers (y-axis labels at the bottom)
    cout << "    "; // Space before the labels
    for (int y = 0; y < gridRangeY; y++)
    {
        cout << setw(3) << setfill(' ') << y; // Print column numbers
    }
    cout << endl;
}

// print the cloud location data grid
void printcloudData(int minX, int maxX, int minY, int maxY)
{
    int gridRangeX = (maxX - minX) + 1; // 9
    int gridRangeY = (maxY - minY) + 1; // 9

    // print the cloud grid
    cout << "\nCloud data grid: " << endl;

    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    for (int y = gridRangeY - 1; y >= 0; y--)
    {
        cout << y << " ";
        cout << "# ";
        for (int x = 0; x < gridRangeX; x++)
        {
            int cloudValue = cloudData[x][y] / 10.0;
            cout << setw(2) << cloudValue << " ";
        }
        cout << " #";
        cout << endl;
    }

    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    cout << "    ";
    for (int y = 0; y < gridRangeY; y++)
    {
        cout << setw(2) << y << " ";
    }
    cout << endl;
}

// print the cloud location sysmbol data grid
void printcloudsysmbolData(int minX, int maxX, int minY, int maxY)
{
    int gridRangeX = (maxX - minX) + 1; // 9
    int gridRangeY = (maxY - minY) + 1; // 9

    // print the cloud grid
    cout << "\nCloud data symbol grid: " << endl;

    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    for (int y = gridRangeY - 1; y >= 0; y--)
    {
        cout << y << " ";
        cout << "# ";
        for (int x = 0; x < gridRangeX; x++)
        {
            int cloudValue = cloudData[x][y];

            char symbols;

            if (cloudValue < 35)
            {
                symbols = 'L';
            }
            else if (cloudValue < 66)
            {
                symbols = 'M';
            }
            else
            {
                symbols = 'H';
            }

            cout << setw(2) << symbols << " ";
        }
        cout << " #";
        cout << endl;
    }

    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    cout << "    ";
    for (int y = 0; y < gridRangeY; y++)
    {
        cout << setw(2) << y << " ";
    }
    cout << endl;
}

// print the pressure location data grid
void printPressureData(int minX, int maxX, int minY, int maxY)
{
    int gridRangeX = (maxX - minX) + 1; // 9
    int gridRangeY = (maxY - minY) + 1; // 9

    // print the cloud grid
    cout << "\nPressure data grid: " << endl;
    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    for (int y = gridRangeY - 1; y >= 0; y--)
    {
        cout << y << " ";
        cout << "# ";
        for (int x = 0; x < gridRangeX; x++)
        {
            int pressure = pressureData[x][y] / 10.0;
            cout << setw(2) << pressure << " ";
        }
        cout << " #";
        cout << endl;
    }

    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    cout << "    ";
    for (int y = 0; y < gridRangeY; y++)
    {
        cout << setw(2) << y << " ";
    }
    cout << endl;
}

// print the pressure location sysmbol data grid
void printPressuresymbolData(int minX, int maxX, int minY, int maxY)
{
    int gridRangeX = (maxX - minX) + 1; // 9
    int gridRangeY = (maxY - minY) + 1; // 9

    // print the cloud grid
    cout << "\nPressure symbol data grid: " << endl;
    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    for (int y = gridRangeY - 1; y >= 0; y--)
    {
        cout << y << " ";
        cout << "# ";
        for (int x = 0; x < gridRangeX; x++)
        {
            int pressure = pressureData[x][y];

            char pressuresymbols;

            if (pressure < 35)
            {
                pressuresymbols = 'L';
            }
            else if (pressure < 66)
            {
                pressuresymbols = 'M';
            }
            else
            {
                pressuresymbols = 'H';
            }

            cout << setw(2) << pressuresymbols << " ";
        }
        cout << " #";
        cout << endl;
    }

    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    cout << "    ";
    for (int y = 0; y < gridRangeY; y++)
    {
        cout << setw(2) << y << " ";
    }
    cout << endl;
}
