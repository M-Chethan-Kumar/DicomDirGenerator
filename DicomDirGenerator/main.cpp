// DicomDirGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>

bool isValidInteger(const std::string& str) {
    std::istringstream ss(str);
    int num;
    if (ss >> num) {
        char remaining;
        if (ss >> remaining) {
            return false;
        }
        return true;
    }
    return false;
}

int main()
{
    std::cout << "Hello World!\n";
    std::string input;

    // Input and validation for the first integer
    do {
        std::cout << "Enter number of studies: ";
        std::cin >> input;
        if (!isValidInteger(input)) {
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
        }
    } while (!isValidInteger(input));

    const int numberOfStudies = std::stoi(input);

    // Input and validation for the second integer
    do {
        std::cout << "Enter number of series per study: ";
        std::cin >> input;
        if (!isValidInteger(input)) {
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
        }
    } while (!isValidInteger(input));

    const int numberOfSeries = std::stoi(input);

    std::cout << "Studies : " << numberOfStudies << std::endl;
    std::cout << "Series : " << numberOfSeries << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
