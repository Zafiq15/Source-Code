#include <iostream>
#include <limits>
#include <fstream>

#include "globals.h"
#include "readFile.h"
#include "printfile.h"
#include "weatherreport.h"

using namespace std;

// Divider string to visually separate sections in the output
const string divider = "-------------------------------------------------\n";

// information for displaying student details in the program
const string STUDENT_INFORMATION[] = {
    "Student ID: 8496481", "Student Name: Muhammad Zafiq"};

// Menu options available to the user to interact with the program
const string OPTIONS[] = {
    "1) Read in and process a configuration file",
    "2) Display city map",
    "3) Display cloud coverage map (cloudiness index)",
    "4) Display cloud coverage map (LMH symbols)",
    "5) Display atmospheric pressure map (pressure index)",
    "6) Display atmospheric pressure map (LMH symbols)",
    "7) Show weather forecast summary report",
    "8) Quit"};

// Function when user select 2 to 7 press enter to return main menu
void promptUserToPressEnterToContinue()
{
  // Clears any previous input from the input buffer
  cin.ignore(1000, '\n');
  string userInput = "";

  // Continuously prompts user to press Enter until a valid input is given
  do
  {
    cout << "\nPress <Enter> to go back to main menu";
    getline(cin, userInput);
  } while (userInput.length() != 0);
  cout << endl;
}

// Function to clean up dynamically allocated memory
void cleanup()
{
  // Check if cityData is not null before attempting to delete it
  if (cityData != nullptr)
  {
    for (int x = 0; x < (maxX - minX + 1); x++)
    {
      delete[] cityData[x];
    }
    delete[] cityData;
    cityData = nullptr;
  }
  // Check if cloudData is not null before attempting to delete it
  if (cloudData != nullptr)
  {
    for (int x = 0; x < (maxX - minX + 1); x++)
    {
      delete[] cloudData[x];
    }
    delete[] cloudData;
    cloudData = nullptr;
  }
  // Check if pressureData is not null before attempting to delete it
  if (pressureData != nullptr)
  {
    for (int x = 0; x < (maxX - minX + 1); x++)
    {
      delete[] pressureData[x];
    }
    delete[] pressureData;
    pressureData = nullptr;
  }
}

int main()
{
  // Display student information
  for (const string &info : STUDENT_INFORMATION)
  {
    cout << info << endl;
  }
  cout << divider;

  // Print a welcoming message to the user at the beginning of the program.
  cout << "Welcome to Weather Information Processing System!" << endl
       << endl;

  // Loop through the OPTIONS array and print each menu option to the console.
  for (const string &option : OPTIONS)
  {
    cout << option << endl;
  }

  // Select and validate user input
  int input = 0;
  // Start an infinite loop that will keep asking the user for input until a valid choice is made.
  while (true)
  {
    // Prompt the user to enter their choice (between 1 and 8).
    cout << "\nPlease enter your choice (1-8): ";
    cin >> input;

    // Check if the input is valid (within range 1-8 and not an invalid input).
    if (cin.fail() || input < 1 || input > 8)
    {
      // If input is invalid, clear the error state and ignore the invalid input.
      cin.clear();

      // Ignore the rest of the invalid input until the next newline character.
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      cout << "Error: Invalid input. Please enter a number between 1 and 8." << endl;
    }
    else
    {
      // Process the valid input based on the user's choice.
      switch (input)
      {
      case 1:
      {
        // Prompt the user to enter the configuration filename
        cout << "Please enter config filename: ";
        string filename;
        cin >> filename;
        cout << endl;
        storeConfigFileInfo(filename);
      }
      break;

      case 2:
      {
        // Display the city map based on the processed data.
        printCityData(minX, maxX, minY, maxY);

        // Prompt user to press <enter> to go back to the main menu after viewing the output.
        promptUserToPressEnterToContinue();
        break;
      }

      case 3:
      {
        // Display the cloud coverage map (cloudiness index) based on the processed data.
        printcloudData(minX, maxX, minY, maxY);

        // Prompt user to press <enter> to go back to the main menu after viewing the output.
        promptUserToPressEnterToContinue();
        break;
      }
      case 4:
      {
        // Display the cloud coverage map (LMH symbols) based on the processed data.
        printcloudsysmbolData(minX, maxX, minY, maxY);

        // Prompt user to press <enter> to go back to the main menu after viewing the output.
        promptUserToPressEnterToContinue();
        break;
      }
      case 5:
      {
        // Display the atmospheric pressure map (pressure index) based on the processed data.
        printPressureData(minX, maxX, minY, maxY);

        // Prompt user to press <enter> to go back to the main menu after viewing the output.
        promptUserToPressEnterToContinue();
        break;
      }
      case 6:
      {
        // Display the atmospheric pressure map (LMH symbols) based on the processed data.
        printPressuresymbolData(minX, maxX, minY, maxY);

        // Prompt user to press <enter> to go back to the main menu after viewing the output.
        promptUserToPressEnterToContinue();
        break;
      }
      case 7:
        // Print a summary report of the weather forecast based on the processed data.
        weathersummaryreport();

        // Prompt user to press <enter> to go back to the main menu after viewing the output.
        promptUserToPressEnterToContinue();
        break;

      case 8:
        // Print a message to the user indicating that the program is exiting.
        cout << "Exiting the program." << endl;
        return 0;
      default:
        // Print an error message if the input doesn't match any valid case.
        cout << "Invalid choice." << endl;
        break;
      }
    }
  }
  // Clean up dynamically allocated memory before exiting the program.
  cleanup();
  return 0;
}
