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
    // Calculate the range of the grid based on the provided min and max coordinates
    int gridRangeX = (maxX - minX) + 1;
    int gridRangeY = (maxY - minY) + 1;

    cout << "\nCity location data grid: " << endl;

    // Print the top border of the grid
    cout << " ";
    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    // Print the city grid data
    for (int y = gridRangeY - 1; y >= 0; y--)
    {
        cout << setw(2) << setfill(' ') << y << " ";
        cout << "# ";

        for (int x = 0; x < gridRangeX; x++)
        {
            // Print city data or space if not greater than 0
            if (cityData[x][y] > 0)
            {
                cout << setw(2) << setfill(' ') << cityData[x][y];
            }
            else
            {
                cout << setw(2) << " ";
            }
            cout << " ";
        }

        cout << " #";
        cout << endl;
    }

    // Print the bottom border of the grid
    cout << " ";
    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    // Print column numbers (y-axis labels at the bottom)
    cout << "    ";
    for (int y = 0; y < gridRangeY; y++)
    {
        cout << setw(3) << setfill(' ') << y;
    }
    cout << endl;
}

// Function to print the cloud location data grid
void printcloudData(int minX, int maxX, int minY, int maxY)
{
    // Calculate the range of the grid based on the provided min and max coordinates
    int gridRangeX = (maxX - minX) + 1;
    int gridRangeY = (maxY - minY) + 1;

    cout << "\nCloud data grid: " << endl;

    // Print the top border of the grid
    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    // print the cloud grid data
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

    // Print the bottom border of the grid
    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    // Print the column labels (x-coordinates) at the bottom
    cout << "    ";
    for (int y = 0; y < gridRangeY; y++)
    {
        cout << setw(2) << y << " ";
    }
    cout << endl;
}

// Function to print the cloud location symbol data grid
void printcloudsysmbolData(int minX, int maxX, int minY, int maxY)
{
    // Calculate the range of the grid based on the provided min and max coordinates
    int gridRangeX = (maxX - minX) + 1;
    int gridRangeY = (maxY - minY) + 1;

    cout << "\nCloud data symbol grid: " << endl;

    // Print the top border of the grid
    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    // print the cloud symbol grid data
    for (int y = gridRangeY - 1; y >= 0; y--)
    {
        cout << y << " ";
        cout << "# ";
        for (int x = 0; x < gridRangeX; x++)
        {
            // Get the cloud value for the current cell
            int cloudValue = cloudData[x][y];

            // Determine the symbol based on cloud value
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

    // Print the bottom border of the grid
    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    // Print the column labels (x-coordinates) at the bottom
    cout << "    ";
    for (int y = 0; y < gridRangeY; y++)
    {
        cout << setw(2) << y << " ";
    }
    cout << endl;
}

// Function to print the pressure location data grid
void printPressureData(int minX, int maxX, int minY, int maxY)
{
    // Calculate the range of the grid based on the provided min and max coordinates
    int gridRangeX = (maxX - minX) + 1;
    int gridRangeY = (maxY - minY) + 1;

    // Print the top border of the grid
    cout << "\nPressure data grid: " << endl;
    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    // print the pressure grid data
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

    // Print the bottom border of the grid
    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    // Print the column labels (x-coordinates) at the bottom
    cout << "    ";
    for (int y = 0; y < gridRangeY; y++)
    {
        cout << setw(2) << y << " ";
    }
    cout << endl;
}

// Function to print the pressure location sysmbol data grid
void printPressuresymbolData(int minX, int maxX, int minY, int maxY)
{
    // Calculate the range of the grid based on the provided min and max coordinates
    int gridRangeX = (maxX - minX) + 1;
    int gridRangeY = (maxY - minY) + 1;

    cout << "\nPressure symbol data grid: " << endl;

    // Print the top border of the grid
    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    // print the cloud grid data
    for (int y = gridRangeY - 1; y >= 0; y--)
    {
        cout << y << " ";
        cout << "# ";

        // print the pressure symbol grid data
        for (int x = 0; x < gridRangeX; x++)
        {
            // Get the pressure value for the current cell
            int pressure = pressureData[x][y];

            // Determine the symbol based on pressure value
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

    // Print the bottom border of the grid
    for (int x = 0; x < gridRangeX + 2; x++)
    {
        cout << setw(3) << setfill(' ') << "#";
    }
    cout << endl;

    // Print the column labels (x-coordinates) at the bottom
    cout << "    ";
    for (int y = 0; y < gridRangeY; y++)
    {
        cout << setw(2) << y << " ";
    }
    cout << endl;
}
