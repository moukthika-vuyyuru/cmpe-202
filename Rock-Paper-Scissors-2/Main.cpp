#include "Game.h"
#include "RandomStrategy.h"
#include "SmartStrategy.h"
#include "FrequencyFileManager.h"
#include <iostream>
#include <ctime>

Strategy *selectStrategy()
{
    int strategyChoice;
    std::cout << "Choose computer strategy (1 for random, 2 for smart): ";
    std::cin >> strategyChoice;

    if (strategyChoice == 1)
    {
        return new RandomStrategy();
    }
    else if (strategyChoice == 2)
    {
        SmartStrategy *smartStrategy = new SmartStrategy(5); // N = 5
        std::unordered_map<std::string, int> frequencyMap;
        FrequencyFileManager::readFrequenciesFromFile("/Users/moukthika/Desktop/cmpe-202/Code/Rock-Paper-Scissors-2/freq.txt", frequencyMap);
        smartStrategy->setFrequencyMap(frequencyMap);
        return smartStrategy;
    }
    else
    {
        std::cerr << "Invalid strategy choice! Defaulting to random." << std::endl;
        return new RandomStrategy();
    }
}

int main()
{
    srand(time(nullptr));

    // Select strategy
    Strategy *computerStrategy = selectStrategy();

    // Play game
    Game game(computerStrategy);
    game.playGame();

    return 0;
}