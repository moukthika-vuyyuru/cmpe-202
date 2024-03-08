#ifndef GAME_H
#define GAME_H

#include "Strategy.h"

class Game {
private:
    Strategy* computerStrategy;
    int humanScore;
    int computerScore;
    std::vector<char> history;
    static const int N = 5;

public:
    Game(Strategy* strategy);
    ~Game();
    void playRound(char humanChoice);
    void playGame();
};

#endif /* GAME_H */
