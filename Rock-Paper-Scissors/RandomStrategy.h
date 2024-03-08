#ifndef RANDOMSTRATEGY_H
#define RANDOMSTRATEGY_H

#include "Strategy.h"

class RandomStrategy : public Strategy {
public:
    char chooseNext(const std::vector<char>& history) override;
};

#endif /* RANDOMSTRATEGY_H */
