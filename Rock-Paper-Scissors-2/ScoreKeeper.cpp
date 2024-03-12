#include "ScoreKeeper.h"

ScoreKeeper::Result ScoreKeeper::updateScore(char humanChoice, char computerChoice)
{
    if (humanChoice == computerChoice)
    {
        // It's a tie
        return Result::TIE;
    }
    else if ((humanChoice == 'R' && computerChoice == 'S') ||
             (humanChoice == 'P' && computerChoice == 'R') ||
             (humanChoice == 'S' && computerChoice == 'P'))
    {
        // Human wins
        humanScore++;
        return Result::WIN;
    }
    else
    {
        // Computer wins
        computerScore++;
        return Result::LOSS;
    }
}
