#ifndef SMARTSTRATEGY_H
#define SMARTSTRATEGY_H

#include "Strategy.h"
#include <unordered_map>
#include <string>

class SmartStrategy : public Strategy
{
private:
    std::unordered_map<std::string, int> frequencyMap;
    int N;

public:
    SmartStrategy(int n);
    virtual char chooseNext(const std::vector<char> &history) override;
    void updateFrequencies(const std::vector<char> &history, char humanChoice, char computerChoice);
    void readFrequenciesFromFile(const std::string &filename);
    void writeFrequenciesToFile(const std::string &filename);
};

#endif /* SMARTSTRATEGY_H */
