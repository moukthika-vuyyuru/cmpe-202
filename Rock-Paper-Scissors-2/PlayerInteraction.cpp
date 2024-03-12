#include "PlayerInteraction.h"
#include "ScoreKeeper.h"

char PlayerInteraction::getHumanChoice()
{
    char choice;
    std::cout << "Your choice (R/P/S): ";
    std::cin >> choice;
    return choice;
}

void PlayerInteraction::displayRoundNumber(int roundNumber)
{
    std::cout << "\nRound " << roundNumber << std::endl;
}

void PlayerInteraction::displayRoundResult(char humanChoice, char computerChoice, ScoreKeeper::Result result)
{
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

    // Display the winner
    if (result == ScoreKeeper::Result::TIE)
    {
        std::cout << "  The winner is: TIE" << std::endl;
    }
    else if (result == ScoreKeeper::Result::WIN)
    {
        std::cout << "  The winner is: HUMAN" << std::endl;
    }
    else
    {
        std::cout << "  The winner is: COMPUTER" << std::endl;
    }
}

void PlayerInteraction::displayFinalScore(int humanScore, int computerScore)
{
    // Display final score
    std::cout << "\nFinal Score:" << std::endl;
    std::cout << "  HUMAN: " << humanScore << std::endl;
    std::cout << "  COMPUTER: " << computerScore << std::endl;
}
