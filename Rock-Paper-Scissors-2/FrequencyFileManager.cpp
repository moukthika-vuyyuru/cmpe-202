#include "FrequencyFileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

void FrequencyFileManager::readFrequenciesFromFile(const std::string &filename, std::unordered_map<std::string, int> &frequencyMap)
{
    std::ifstream inFile(filename);
    if (!inFile)
    {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }

    // Read each line from the file and extract sequence and frequency
    std::string line;
    while (std::getline(inFile, line))
    {
        // Find the position of the separator character ":"
        size_t separatorPos = line.find(":");
        if (separatorPos == std::string::npos)
        {
            std::cerr << "Error parsing line from file: " << line << std::endl;
            continue; // Skip this line if separator ":" is not found
        }

        // Extract sequence and frequency parts
        std::string sequence = line.substr(0, separatorPos);
        std::string frequencyStr = line.substr(separatorPos + 1);

        // Convert frequency string to integer
        int frequency;
        try
        {
            frequency = std::stoi(frequencyStr);
        }
        catch (const std::invalid_argument &ia)
        {
            std::cerr << "Invalid frequency value: " << frequencyStr << std::endl;
            continue; // Skip this line if frequency value is invalid
        }

        // Trim leading and trailing whitespace from sequence
        sequence.erase(0, sequence.find_first_not_of(" \t")); // Trim leading whitespace
        sequence.erase(sequence.find_last_not_of(" \t") + 1); // Trim trailing whitespace

        // Update the frequency map with the values read from the file
        frequencyMap[sequence] = frequency;
    }

    inFile.close();
}

void FrequencyFileManager::writeFrequenciesToFile(const std::string &filename, const std::unordered_map<std::string, int> &frequencyMap)
{
    // Open the file for writing
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    // // Iterate over the frequencies map and update the file content
    for (const auto &entry : frequencyMap)
    {
        outFile << entry.first << ":" << entry.second << std::endl;
    }
    // remove last newline
    outFile.seekp(-1, std::ios_base::end);
    outFile << std::flush;
    outFile.close();
}