#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>

class Strategy
{
public:
    virtual char chooseNext(const std::vector<char> &history = {}) = 0;
    virtual ~Strategy() {}
};

#endif /* STRATEGY_H */
