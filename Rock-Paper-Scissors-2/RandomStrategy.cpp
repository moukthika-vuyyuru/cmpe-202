#include "RandomStrategy.h"
#include <cstdlib>

char RandomStrategy::chooseNext(const std::vector<char> &history)
{
    // Randomly choose between R, P, or S
    char choices[3] = {'R', 'P', 'S'};
    return choices[rand() % 3];
}
