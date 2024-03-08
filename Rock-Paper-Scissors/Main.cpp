#include "Game.h"
#include "RandomStrategy.h"
#include "SmartStrategy.h"
#include <iostream>
#include <ctime>
#include <string>
int main()
{
    srand(time(nullptr));

    // Determine strategy
    Strategy *computerStrategy;
    int strategyChoice;
    std::cout << "Choose computer strategy (1 for random, 2 for smart): ";
    std::cin >> strategyChoice;

    if (strategyChoice == 1)
    {
        computerStrategy = new RandomStrategy();
    }
    else if (strategyChoice == 2)
    {
        SmartStrategy *smartStrategy = new SmartStrategy(5); // N = 5
        smartStrategy->readFrequenciesFromFile("/Users/moukthika/Desktop/cmpe-202/Code/Rock-Paper-Scissors/freq.txt");
        computerStrategy = smartStrategy;
    }
    else
    {
        std::cerr << "Invalid strategy choice! Defaulting to random." << std::endl;
        computerStrategy = new RandomStrategy();
    }

    // Play game
    Game game(computerStrategy);
    game.playGame();

    return 0;
}