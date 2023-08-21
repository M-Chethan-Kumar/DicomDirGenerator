// DicomDirGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "generator.h"
#include <TraceWriter.h>
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
    std::filesystem::path path = Generator::getExecutingDirectory() / "Traces";
    Trace::TraceWriterFile	trace(path);
    Dicom::Merge::Library lib;
    std::cout << "------------------------------DicomDir and dicom files generator -------------!\n";
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


    const auto startTime = std::chrono::high_resolution_clock::now();
    const Generator generator(numberOfStudies, numberOfSeries);
    generator.create();

    const auto endTime = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    if(duration.count() != 0)
		std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
    else
    {
	    const auto timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        std::cout << "Time taken: " << timeTaken.count() << " milliseconds" << std::endl;
    }
    std::cout << "\rDone!        " << std::endl;
}