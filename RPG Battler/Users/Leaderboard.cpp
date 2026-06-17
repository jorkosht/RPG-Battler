#include "Leaderboard.h"
#include "User.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

void Leaderboard::updateRanks(std::vector<User*>& users)
{
    std::sort(users.begin(), users.end(), [](const User* a, const User* b)
    {
        if (a->getBattlesWon() != b->getBattlesWon())
            return a->getBattlesWon() > b->getBattlesWon();
        if (a->getTotalXP() != b->getTotalXP())
            return a->getTotalXP() > b->getTotalXP();
        return a->getWinRate() > b->getWinRate();
    });
    for (int i = 0; i < static_cast<int>(users.size()); ++i)
        users[i]->setRank(i + 1);
}

void Leaderboard::print(const std::vector<User*>& users)
{
    std::cout << std::endl << "========== LEADERBOARD ==========" << std::endl;
    std::cout << std::left
              << std::setw(5)  << "Rank"
              << std::setw(18) << "Username"
              << std::setw(8)  << "Wins"
              << std::setw(10) << "Total XP"
              << std::setw(10) << "Win Rate"
              << std::endl;
    std::cout << std::string(51, '-') << std::endl;

    for (auto* u : users)
    {
        std::cout << std::left
                  << std::setw(5)  << u->getRank()
                  << std::setw(18) << u->getUsername()
                  << std::setw(8)  << u->getBattlesWon()
                  << std::setw(10) << u->getTotalXP()
                  << std::fixed << std::setprecision(1)
                  << u->getWinRate() << "%" << std::endl;
    }
    std::cout << "=================================" << std::endl;
}
