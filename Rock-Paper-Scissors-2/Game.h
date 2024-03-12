// Game.h
#ifndef GAME_H
#define GAME_H

#include "Strategy.h"
#include "ScoreKeeper.h"
#include "PlayerInteraction.h"

class Game
{
private:
    Strategy *computerStrategy;
    ScoreKeeper scoreKeeper;
    PlayerInteraction playerInteraction;
    std::vector<char> history;
    int humanScore;
    int computerScore;

public:
    Game(Strategy *strategy);
    ~Game();
    void playGame();
    void playRound(char humanChoice);
};

#endif // GAME_H
