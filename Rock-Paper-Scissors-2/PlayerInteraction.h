#ifndef PLAYERINTERACTION_H
#define PLAYERINTERACTION_H

#include <iostream>
#include "ScoreKeeper.h"

class PlayerInteraction
{
public:
    char getHumanChoice();
    void displayRoundNumber(int roundNumber);
    void displayRoundResult(char humanChoice, char computerChoice, ScoreKeeper::Result result);
    void displayFinalScore(int humanScore, int computerScore);
};

#endif /* PLAYERINTERACTION_H */