#ifndef FREQUENCY_FILE_MANAGER_H
#define FREQUENCY_FILE_MANAGER_H

#include <unordered_map>
#include <string>

class FrequencyFileManager
{
public:
    static void readFrequenciesFromFile(const std::string &filename, std::unordered_map<std::string, int> &frequencyMap);
    static void writeFrequenciesToFile(const std::string &filename, const std::unordered_map<std::string, int> &frequencyMap);
};

#endif /* FREQUENCY_FILE_MANAGER_H */
