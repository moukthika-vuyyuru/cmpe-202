#include "Game.h"
#include "SmartStrategy.h"
#include "FrequencyFileManager.h"

Game::Game(Strategy *strategy) : computerStrategy(strategy) {}

Game::~Game()
{
    delete computerStrategy;
}

void Game::playGame()
{
    std::vector<char> history;

    for (int round = 0; round < 20; ++round)
    {
        // Display round number
        playerInteraction.displayRoundNumber(round + 1);

        // Human player's choice
        char humanChoice = playerInteraction.getHumanChoice();
        history.push_back(humanChoice);

        // Computer player's choice
        char computerChoice = computerStrategy->chooseNext(history);
        history.push_back(computerChoice);

        // Determine winner and update scores
        ScoreKeeper::Result result = scoreKeeper.updateScore(humanChoice, computerChoice);

        // Display round result
        playerInteraction.displayRoundResult(humanChoice, computerChoice, result);

        // Update the frequencies for the smart strategy
        if (dynamic_cast<SmartStrategy *>(computerStrategy))
        {
            dynamic_cast<SmartStrategy *>(computerStrategy)->updateFrequencies(history, humanChoice, computerChoice);
        }
        if (history.size() > 5)
            history.erase(history.begin(), history.begin() + 2);
    }

    // Display final score
    playerInteraction.displayFinalScore(scoreKeeper.getHumanScore(), scoreKeeper.getComputerScore());

    // Write the frequencies to a file for the smart strategy
    if (dynamic_cast<SmartStrategy *>(computerStrategy))
    {
        FrequencyFileManager frequencyFileManager;
        frequencyFileManager.writeFrequenciesToFile("/Users/moukthika/Desktop/cmpe-202/Code/Rock-Paper-Scissors-2/freq.txt", dynamic_cast<SmartStrategy *>(computerStrategy)->getFrequencyMap());
    }
}