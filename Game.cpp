#include "Game.h"
#include "SmartStrategy.h"
#include <iostream>

Game::Game(Strategy *strategy) : computerStrategy(strategy), humanScore(0), computerScore(0) {}

void Game::playRound(char humanChoice)
{
    history.push_back(humanChoice);
    char computerChoice = computerStrategy->chooseNext(history);
    history.push_back(computerChoice);

    // Display the choices made by both players
    std::cout << "  HUMAN chose ";
    switch (humanChoice)
    {
    case 'R':
        std::cout << "ROCK" << std::endl;
        break;
    case 'P':
        std::cout << "PAPER" << std::endl;
        break;
    case 'S':
        std::cout << "SCISSORS" << std::endl;
        break;
    default:
        break;
    }
    std::cout << "  COMPUTER chose ";
    switch (computerChoice)
    {
    case 'R':
        std::cout << "ROCK" << std::endl;
        break;
    case 'P':
        std::cout << "PAPER" << std::endl;
        break;
    case 'S':
        std::cout << "SCISSORS" << std::endl;
        break;
    default:
        break;
    }

    // Determine the winner of the round
    if (humanChoice == computerChoice)
    {
        std::cout << "  The winner is: TIE" << std::endl;
    }
    else if ((humanChoice == 'R' && computerChoice == 'S') ||
             (humanChoice == 'P' && computerChoice == 'R') ||
             (humanChoice == 'S' && computerChoice == 'P'))
    {
        std::cout << "  The winner is: HUMAN" << std::endl;
        humanScore++;
    }
    else
    {
        std::cout << "  The winner is: COMPUTER" << std::endl;
        computerScore++;
    }

    // Update the frequencies for the smart strategy
    if (dynamic_cast<SmartStrategy *>(computerStrategy))
    {
        dynamic_cast<SmartStrategy *>(computerStrategy)->updateFrequencies(history, humanChoice, computerChoice);
    }
    if (history.size() > N)
        history.erase(history.begin(), history.begin() + 2);
}

void Game::playGame()
{
    // Play 20 rounds of the game
    for (int i = 0; i < 20; ++i)
    {
        std::cout << "\nRound " << i + 1 << std::endl;
        char humanChoice;
        std::cout << "  HUMAN's choice? ";
        std::cin >> humanChoice;

        // Check if the human's choice is valid
        if (humanChoice != 'R' && humanChoice != 'P' && humanChoice != 'S')
        {
            std::cerr << "Invalid choice! Please choose R, P, or S." << std::endl;
            continue;
        }

        // Play the round with the human's choice
        playRound(humanChoice);
    }

    // Display the final score of the game
    std::cout << "\nFinal Score:" << std::endl;
    std::cout << "  HUMAN: " << humanScore << std::endl;
    std::cout << "  COMPUTER: " << computerScore << std::endl;

    // Write the frequencies to a file for the smart strategy
    if (dynamic_cast<SmartStrategy *>(computerStrategy))
    {
        dynamic_cast<SmartStrategy *>(computerStrategy)->writeFrequenciesToFile("/Users/moukthika/Desktop/cmpe-202/Code/Rock-Paper-Scissors/freq.txt");
    }
}

Game::~Game()
{
    delete computerStrategy;
}
