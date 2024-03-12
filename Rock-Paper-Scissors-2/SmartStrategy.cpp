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
    // std::cout << "Sequence before lookup: " << sequence << std::endl;

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
    // std::cout << "Sequence found with max frequency: " << maxSequence << std::endl;
    // std::cout << "Next move based on sequence: " << nextMove << std::endl;

    // Counter the human's predicted move
    if (nextMove == 'R')
    {
        // std::cout << "Counter move: P (Paper)" << std::endl;
        return 'P'; // Counter rock with paper
    }
    else if (nextMove == 'P')
    {
        // std::cout << "Counter move: S (Scissors)" << std::endl;
        return 'S'; // Counter paper with scissors
    }
    else
    {
        // std::cout << "Counter move: R (Rock)" << std::endl;
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

const std::unordered_map<std::string, int> &SmartStrategy::getFrequencyMap() const
{
    return frequencyMap;
}

void SmartStrategy::setFrequencyMap(const std::unordered_map<std::string, int> &map)
{
    frequencyMap = map;
}
