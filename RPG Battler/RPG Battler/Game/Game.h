
#pragma once
#include "User.h"
#include <vector>
#include <memory>
#include <string>

class Game {
public:
    Game();
    void run();

private:
    static constexpr const char* DATA_DIR = "data";
    void loadAll();
    void saveAll() const;

    void mainMenu();
    void loggedInMenu(User& user);
    void shopMenu(User& user);
    void battleMenu(User& user);

    void registerUser();
    User* loginUser();

    User* findUser(const std::string& username);
    void refreshLeaderboard();
    void printLeaderboard() const;

    std::vector<std::unique_ptr<User>> users;
    User* loggedIn = nullptr;
};
