#pragma once
#include <vector>
#include <string>

class User;

class Leaderboard {
public:
    static void print(const std::vector<User*>& users);
    static void updateRanks(std::vector<User*>& users);
};
