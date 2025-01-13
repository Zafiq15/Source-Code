#include <iostream>
#include <limits>
#include <fstream>

#include "globals.h"
#include "readFile.h"
#include "printfile.h"
#include "weatherreport.h"

// Heloo there

using namespace std;

const string divider = "-------------------------------------------------\n";

const string STUDENT_INFORMATION[] = {
    "Student ID: 8496481", "Student Name: Muhammad Zafiq"};

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
  cin.ignore(1000, '\n');
  string userInput = "";
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
}

int main()
{
  // Display student information
  // Iterate through each element in the STUDENT_INFORMATION array and print it to the console.
  for (const string &info : STUDENT_INFORMATION)
  {
    cout << info << endl; // Print the student information (ID and Name) to the console.
  }
  cout << divider; // Print the divider line after displaying student information.

  // Display welcome message
  // Print a welcoming message to the user at the beginning of the program.
  cout << "Welcome to Weather Information Processing System!" << endl
       << endl;

  // Display options
  // Loop through the OPTIONS array and print each menu option to the console.
  for (const string &option : OPTIONS)
  {
    cout << option << endl; // Print each available option to the user.
  }

  // Select and validate user input
  // Initialize 'input' to store the user's choice.
  int input = 0;
  while (true) // Start an infinite loop that will keep asking the user for input until a valid choice is made.
  {
    // Prompt the user to enter their choice (between 1 and 8).
    cout << "\nPlease enter your choice (1-8): ";
    cin >> input; // Read the user input into the 'input' variable.

    // Check if the input is valid (within range 1-8 and not an invalid input).
    if (cin.fail() || input < 1 || input > 8)
    {
      // If input is invalid, clear the error state and ignore the invalid input.
      cin.clear(); // Clear the error state of the input stream.

      // Ignore the rest of the invalid input until the next newline character.
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Error: Invalid input. Please enter a number between 1 and 8." << endl; // Inform the user about the invalid input.
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
        cin >> filename; // Accept filename from the user
        cout << endl;
        storeConfigFileInfo(filename);
      }
      break;

      case 2:
      {
        printCityData(minX, maxX, minY, maxY);
        promptUserToPressEnterToContinue(); // Prompt user to press <enter> to go back to the main menu after viewing the output.
        break;
      }

      case 3:
      {

        printcloudData(minX, maxX, minY, maxY);
        promptUserToPressEnterToContinue(); // Prompt user to press <enter> to go back to the main menu after viewing the output.
        break;
      }
      case 4:
      {
        printcloudsysmbolData(minX, maxX, minY, maxY);
        promptUserToPressEnterToContinue(); // Prompt user to press <enter> to go back to the main menu after viewing the output.
        break;
      }
      case 5:
      {
        printPressureData(minX, maxX, minY, maxY);
        promptUserToPressEnterToContinue(); // Prompt user to press <enter> to go back to the main menu after viewing the output.
        break;
      }
      case 6:
      {
        printPressuresymbolData(minX, maxX, minY, maxY);
        promptUserToPressEnterToContinue(); // Prompt user to press <enter> to go back to the main menu after viewing the output.
        break;
      }
      case 7:
        weathersummaryreport();             // Call the function to display the weather forecast summary report.
        promptUserToPressEnterToContinue(); // Prompt user to press <enter> to go back to the main menu after viewing the output.
        break;

      case 8:
        cout << "Exiting the program." << endl; // Display message to indicate the program is exiting.
        cleanup();
        return 0; // Exit the program.
      default:
        cout << "Invalid choice." << endl; // If the input doesn't match any valid case, print an error message.
        break;
      }
    }
  }
  cleanup(); // Clean up dynamically allocated memory before exiting the program.
  return 0;
}
