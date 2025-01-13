#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <regex>

#include "globals.h"
#include "readFile.h"
#include "weatherreport.h"

using namespace std;

// function for the rain probability summary
double ProbabilityofRainsummary(string ACC, string AP)
{
  // Declare rainProbability outside the if-else blocks
  double rainProbability = 0.0;

  if (AP == "L" && ACC == "H")
  {
    rainProbability = 90.00;
    cout << "Probability of Rain (%)" << "   : " << rainProbability << endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "\\\\\\\\\\\\" << endl;
  }
  else if (AP == "L" && ACC == "M")
  {
    rainProbability = 80.00;
    cout << "Probability of Rain (%)" << "   : " << rainProbability << endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << " \\\\\\\\" << endl;
  }
  else if (AP == "L" && ACC == "L")
  {
    rainProbability = 70.00;
    cout << "Probability of Rain (%)" << "   : " << rainProbability << endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "  \\\\\\" << endl;
  }
  else if (AP == "M" && ACC == "H")
  {
    rainProbability = 60.00;
    cout << "Probability of Rain (%)" << "   : " << rainProbability << endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "   \\\\" << endl;
  }
  else if (AP == "M" && ACC == "M")
  {
    rainProbability = 50.00;
    cout << "Probability of Rain (%)" << "   : " << rainProbability << endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "    \\" << endl;
  }
  else if (AP == "M" && ACC == "L")
  {
    rainProbability = 40.00;
    cout << "Probability of Rain (%)" << "   : " << rainProbability << endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
  }
  else if (AP == "H" && ACC == "H")
  {
    rainProbability = 30.00;
    cout << "Probability of Rain (%)" << "   : " << rainProbability << endl;
    cout << "~~~" << endl;
    cout << "~~~~" << endl;
  }
  else if (AP == "H" && ACC == "M")
  {
    rainProbability = 20.00;
    cout << "Probability of Rain (%)" << "   : " << rainProbability << endl;
    cout << "~~" << endl;
    cout << "~~~" << endl;
  }
  else if (AP == "H" && ACC == "L")
  {
    rainProbability = 10.00;
    cout << "Probability of Rain (%)" << "   : " << rainProbability << endl;
    cout << "~" << endl;
    cout << "~~" << endl;
  }
  else
  {
    cout << "Invalid data for ACC or AP." << endl;
  }

  return rainProbability;
}

// print the city data type for each city and ID
void displaycitydata(int cityId)
{
  int cityMinX = 1000, cityMinY = 1000, cityMaxX = -1000, cityMaxY = -1000;
  for (size_t i = 0; i < static_cast<size_t>(cityLocationCount); ++i)
  {
    if (cityLocations_Array[i].value == cityId)
    {
      cityMinX = min(cityMinX, cityLocations_Array[i].x);
      cityMinY = min(cityMinY, cityLocations_Array[i].y);
      cityMaxX = max(cityMaxX, cityLocations_Array[i].x);
      cityMaxY = max(cityMaxY, cityLocations_Array[i].y);
    }
  }
  cityMinX = std::max(minX, cityMinX - 1);
  cityMinY = std::max(minY, cityMinY - 1);
  cityMaxX = std::min(maxX, cityMaxX + 1);
  cityMaxY = std::min(maxY, cityMaxY + 1);

  double pressureSum = 0, cloudSum = 0;
  int numValues = 0;
  for (int y = cityMaxY; y >= cityMinY; --y)
  {
    for (int x = cityMinX; x <= cityMaxX; ++x)
    {
      pressureSum += pressureData[x][y];
      cloudSum += cloudData[x][y];
      ++numValues;
    }
  }

  double pressureAverage = pressureSum / numValues;
  double cloudAverage = cloudSum / numValues;

  cout << "City Name: " << citynamearray[cityId] << endl;
  cout << "City ID: " << cityId << endl;

  cout << "Ave. Cloud Cover (ACC)    : " << cloudAverage << " (" << (cloudAverage >= 65 ? "H" : (cloudAverage >= 35 ? "M" : "L")) << ")" << endl;

  cout << "Ave. Pressure (AP)        : " << pressureAverage << " (" << (pressureAverage >= 65 ? "H" : (pressureAverage >= 35 ? "M" : "L")) << ")" << endl;

  ProbabilityofRainsummary(
      cloudAverage >= 65 ? "H" : (cloudAverage >= 35 ? "M" : "L"),
      pressureAverage >= 65 ? "H" : (pressureAverage >= 35 ? "M" : "L"));
}

// print the summary report for the weather forecast
void weathersummaryreport()
{
  string divides = "-------------------------------";

  cout << "\nWeather Forecast Summary Report" << endl;
  cout << divides << endl;

  cout << fixed << setprecision(2);

  for (int i = 99; i >= 0; i--)
  {
    string cityName = citynamearray[i];
    if (cityName.empty())
    {
      continue;
    }
    displaycitydata(i);
    cout << endl;
  }
}