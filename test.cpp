// Function to clean up dynamically allocated memory
/*void cleanup()
{
    if (cityData != nullptr)
    {
        for (int x = 0; x < (maxX - minX + 1); x++)
        {
            delete[] cityData[x];
        }
        delete[] cityData; 
        cityData = nullptr; 
    }

    if (cloudData != nullptr)
    {
        for (int x = 0; x < (maxX - minX + 1); x++)
        {
            delete[] cloudData[x]; 
        }
        delete[] cloudData; 
        cloudData = nullptr; 
    }

    if (pressureData != nullptr)
    {
        for (int x = 0; x < (maxX - minX + 1); x++)
        {
            delete[] pressureData[x]; 
        }
        delete[] pressureData; 
        pressureData = nullptr; 
    }
}*/





/* #include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

// Initialize pointers to dynamic 2D arrays for storing
//int **cityData = nullptr;
int **cloudData = nullptr;
int **pressureData = nullptr;

string *citynamearray = nullptr;
string *cloudarray = nullptr;
string *pressurearray = nullptr;

int minX = 0, minY = 0, maxX = 0, maxY = 0;

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

struct Pressure
{
  int x, y, value;
};

// Array to store city locations (assuming a max size of 100 for example)
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
    // Find positions of brackets and dashes
    size_t cityopenBracket = line.find('[');
    size_t citycloseBracket = line.find(']');
    size_t citydashPos = line.find('-', citycloseBracket);
    size_t citysecondDash = line.find('-', citydashPos + 1);

    // Check if the expected parts are found
    if (cityopenBracket == string::npos || citycloseBracket == string::npos || citydashPos == string::npos || citysecondDash == string::npos)
    {
      // Don't print the error, just skip this line
      continue;
    }

    // Extract coordinates (x, y)
    string citycoordinates = line.substr(cityopenBracket + 1, citycloseBracket - cityopenBracket - 1);
    size_t commaPos = citycoordinates.find(',');
    int x = stoi(citycoordinates.substr(0, commaPos));
    int y = stoi(citycoordinates.substr(commaPos + 1));

    // Extract value after the first dash
    int value = stoi(line.substr(citycloseBracket + 2, citydashPos - citycloseBracket - 2));

    // Extract city name after the second dash
    string cityname = line.substr(citysecondDash + 1);

    // Add to the array for storage without printing to the console
    initialiseCityLocation(x, y, value, cityname);
  }
  inputfile.close();
}

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

// Function to print the city locations stored in the array
void printdataLocations()
{
  cout << "city data:" << endl;
  for (int i = 0; i < cityLocationCount; i++)
  {
    const CityLocation &city = cityLocations_Array[i];
    cout << city.x << ", " << city.y << "-" << city.value << "-" << city.cityName << endl;
  }
  cout << endl;

  cout << "cloud data: " << endl;
  for (int i = 0; i < cloudLocationCount; ++i)
  {
    const CloudLocation &cloud = cloudLocation_Array[i];

    cout << cloud.x << "," << cloud.y << "-" << cloud.value << endl;
  }

  cout << endl;

  cout << "pressure data: " << endl;
  for (int i = 0; i < Pressure_Count; ++i)
  {
    const Pressure &pressure = Pressure_Array[i];

    cout << pressure.x << "," << pressure.y << "-" << pressure.value << endl;
  }
} */

/*int main()
{
  // Process the data from the file

  processCitylocationData("citylocation.txt");

  processCloudlocationData("cloudcover.txt");

  processPressureData("pressure.txt");

  // Optionally, print all city locations after processing
  printdataLocations();

  return 0;
}*/

// using void to create function then print out in the main
/*void processCustomData(const string &filename)
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
    size_t openBracket = line.find('[');
    size_t closeBracket = line.find(']');
    size_t dashPos = line.find('-', closeBracket);
    size_t secondDash = line.find('-', dashPos + 1);

    if (openBracket == string::npos || closeBracket == string::npos || dashPos == string::npos || secondDash == string::npos)
    {
      cerr << "Error: invalid data format" << endl;
      continue;
    }

    string coordinates = line.substr(openBracket + 1, closeBracket - openBracket - 1);
    size_t commaPos = coordinates.find(',');
    int x = stoi(coordinates.substr(0, commaPos));
    int y = stoi(coordinates.substr(commaPos + 1));

    int value = stoi(line.substr(closeBracket + 2, dashPos - closeBracket - 2));

    string cityname = line.substr(secondDash + 1);

    cout << "Coordinates: (" << x << ", " << y << ")\n";
    cout << "Value: " << value << "\n";
    cout << "City Name: " << cityname << "\n";
    cout << "---------------------------\n";
  }
  inputfile.close();
}

int main(){
  processCustomData("citylocation.txt");
}*/

// Functiom read text file, the use delim and new array to print a new statement
/*int main(){

  ifstream inputfile("data.txt");

  if (!inputfile){
    cerr << "Error: file cannot open" << endl;
    return 1;
  }

  string data;

  getline(inputfile,data);
  inputfile.close();

  char delim = ',';

  int count = 1;

  for (char ch:data){
    if (ch == delim) ++count;
  }

  int* arr = new int[count];

  stringstream ss(data);
  string item;
  int index = 0;

  while (getline(ss,item,delim))
  {
    arr[index++] = stoi(item);
  }

  cout << "array elements: " << endl;
  for (int i = 0; i < count; i++)
  {
    cout << arr[i] << " ";
  }
  cout << endl;

  delete[]arr;

  return 0;
}*/

// using delim and new array and delete[]

/*int main() {
    // Input string with data separated by a delimiter
    string data = "10,20,30,40,50";
    char delim = ','; // Define the delimiter

    // Count the number of elements based on the delimiter
    int count = 1; // At least one element exists
    for (char ch : data) {
        if (ch == delim) ++count;
    }

    // Create a dynamic array to store the values
    int* arr = new int[count];

    // Split the string and populate the array
    stringstream ss(data);
    string item;
    int index = 0;

    while (getline(ss, item, delim)) {
        arr[index++] = stoi(item); // Convert string to integer and store it
    }

    // Display the array elements
    cout << "Array elements:" << endl;
    for (int i = 0; i < count; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Deallocate the memory
    delete[] arr;

    return 0;
}*/

// new array and delete[]

/*int main(){

  int* arr = new int[10];

  for (int i = 0; i < 5; ++i){
    arr [i] = i * 100;
  }

  cout << "Array elements: ";
  for (int i = 0; i < 5; ++i){
    cout << arr [i] << " ";
  }

  delete[] arr;

  return 0;

}*/

/*#include <iostream>
#include <sstream>
#include <iomanip>

#include "readFile.h"

using namespace std;*/

/*void weathersummaryreport()
{
  string divides = "-------------------------------";

  cout << "Weather Forecast Summary Report" << endl;
  cout << divides << endl;
  for (size_t i = 0; i < cities.size(); ++i)
  {
    cout << "City Name: " << endl;
    cout << "City ID: " << endl;

    cout << "Ave. Cloud Cover (ACC)" << "    " << " :" << endl;
    cout << "Ave. Pressure    (AP) " << "    " << " :" << endl;
    cout << "Probability of Rain (%)" << "    " << ":" << endl;

    cout << endl;
  }
}*/

/*void ProbabilityofRainsummary()
{
}*/

/*int main()
{
  weathersummaryreport();
  return 0;
}*/

// Probability of rain (%)

// char ACC = "clouddata"
// char AP = "pressureData"

/*if (AP == "L" && ACC == "H")
{
  double rainProbability = 90.00;
  cout << rainProbability << endl;
  cout << "~~~~" << endl;
  cout << "~~~~~" << endl;
  cout << "\\\\\" << endl;
}
else if (AP == "L" && ACC == "M")
{
  double rainProbability = 80.00;
  cout << rainProbability << endl;
  cout << "~~~~" << endl;
  cout << "~~~~~" << endl;
  cout << " \\\\" << endl;
}
else if (AP == "L" && ACC == "L")
{
  double rainProbability = 70.00;
  cout << rainProbability << endl;
  cout << "~~~~" << endl;
  cout << "~~~~~" << endl;
  cout << "  \\\" << endl;
}

else if (AP == "M" && ACC == "H")
{
  double rainProbability = 60.00;
  cout << rainProbability << endl;
  cout << "~~~~" << endl;
  cout << "~~~~~" << endl;
  cout << "    \\" << endl;
}
else if (AP == "M" && ACC == "M")
{
  double rainProbability = 50.00;
  cout << rainProbability << endl;
  cout << "~~~~" << endl;
  cout << "~~~~~" << endl;
  cout << " \" << endl;
}

else if (AP == "M" && ACC == "L")
{
  double rainProbability = 40.00;
  cout << rainProbability << endl;
  cout << "~~~~" << endl;
  cout << "~~~~~" << endl;

}
else if (AP == "H" && ACC == "H")
{
  double rainProbability = 30.00;
  cout << rainProbability << endl;
  cout << "~~~" << endl;
  cout << "~~~~" << endl;

}else if (AP == "H" && ACC == "M")
{
  double rainProbability = 20.00;
  cout << rainProbability << endl;
  cout << "~~" << endl;
  cout << "~~~" << endl;

}else if (AP == "H" && ACC == "L")
{
  double rainProbability = 10.00;
  cout << rainProbability << endl;
  cout << "~" << endl;
  cout << "~~" << endl;

}*/
