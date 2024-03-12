#ifndef SCOREKEEPER_H
#define SCOREKEEPER_H

class ScoreKeeper
{
public:
    enum class Result
    {
        WIN,
        LOSS,
        TIE
    };

private:
    int humanScore;
    int computerScore;

public:
    ScoreKeeper() : humanScore(0), computerScore(0) {}

    Result updateScore(char humanChoice, char computerChoice);

    int getHumanScore() const { return humanScore; }
    int getComputerScore() const { return computerScore; }
};

#endif /* SCOREKEEPER_H */
