#include "SmartStrategy.h"
#include <fstream>
#include <iostream>
#include <initializer_list>
#include <sstream>
#include <map> // Include the map header

SmartStrategy::SmartStrategy(int n) : N(n) {}

char SmartStrategy::chooseNext(const std::vector<char> &history)
{
    // If history size is less than N, choose randomly
    if (history.size() < N)
    {
        char moves[] = {'R', 'P', 'S'};
        return moves[rand() % 3];
    }

    // Form the sequence from the last N-1 moves (excluding the last computer choice)
    std::string sequence;
    for (size_t i = history.size() - N; i < history.size() - 1; ++i)
    {
        sequence += history[i];
    }

    // Log the sequence before looking it up in the frequency map
    std::cout << "Sequence before lookup: " << sequence << std::endl;

    // Find the most frequent move for the sequence
    int maxFreq = 0;
    // Randomly choose between R, P, or S
    char moves[] = {'R', 'P', 'S'};
    char nextMove = moves[rand() % 3];
    std::string maxSequence;
    for (const auto &entry : frequencyMap)
    {
        // Check if the key starts with the current sequence
        if (entry.first.find(sequence) == 0)
        {
            // Counter the human's predicted move
            if (entry.second > maxFreq)
            {
                maxFreq = entry.second;
                maxSequence = entry.first;
                // Get the next move in the sequence
                nextMove = entry.first[N - 1]; // N - 1 is the length of the current sequence
            }
        }
    }

    // Log the sequence found with max frequency and the corresponding next move
    std::cout << "Sequence found with max frequency: " << maxSequence << std::endl;
    std::cout << "Next move based on sequence: " << nextMove << std::endl;

    // Counter the human's predicted move
    if (nextMove == 'R')
    {
        std::cout << "Counter move: P (Paper)" << std::endl;
        return 'P'; // Counter rock with paper
    }
    else if (nextMove == 'P')
    {
        std::cout << "Counter move: S (Scissors)" << std::endl;
        return 'S'; // Counter paper with scissors
    }
    else
    {
        std::cout << "Counter move: R (Rock)" << std::endl;
        return 'R'; // Counter scissors with rock
    }
}

void SmartStrategy::updateFrequencies(const std::vector<char> &history, char humanChoice, char computerChoice)
{
    if (history.size() < N)
    {
        return;
    }
    // Iterate through the history to extract sequences starting from human moves
    for (size_t i = 0; i <= history.size() - N; i += 2)
    {
        std::string sequence;
        // Extract the sequence of length N starting from index i
        for (size_t j = i; j < i + N; ++j)
        {
            sequence += history[j];
        }

        // Update the frequency map with the extracted sequence
        frequencyMap[sequence]++;
    }
}

void SmartStrategy::readFrequenciesFromFile(const std::string &filename)
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
    std::cout << "Frequency Map count: " << frequencyMap.size() << std::endl;
    inFile.close();
}

void SmartStrategy::writeFrequenciesToFile(const std::string &filename)
{
    // Open the file for reading
    std::ifstream inFile(filename);
    if (!inFile)
    {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }

    // Read the entire file into memory
    std::stringstream buffer;
    buffer << inFile.rdbuf();

    // Close the input file
    inFile.close();

    // Process the buffer
    std::string fileContent = buffer.str();

    // Iterate over the frequencies map and update the file content
    for (const auto &entry : frequencyMap)
    {
        // Construct the new line to append or update
        std::string newLine = entry.first + ":" + std::to_string(entry.second);

        // Search for the sequence in the file content
        size_t found = fileContent.find(entry.first + ":");

        if (found != std::string::npos)
        {
            // Sequence found, update its frequency
            size_t endOfLine = fileContent.find("\n", found);
            fileContent.replace(found, endOfLine - found, newLine);
        }
        else
        {
            // Sequence not found, append it to the end of the file content
            fileContent += "\n" + newLine;
        }
    }

    // Open the file for writing
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    // Write the modified content back to the file
    outFile << fileContent;
    outFile.close();
}
