#pragma once
#include "Items.h"
#include "Constants.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>

class PlayerCharacter;

class User {
public:
    User();
    User(const std::string& username, const std::string& password);
    User(User&&) = default;
    User& operator=(User&&) = default;
    User(const User&) = delete;
    User& operator=(const User&) = delete;
    ~User();

    const std::string& getUsername() const;
    unsigned getTotalXP() const;
    unsigned getAvailableXP() const;
    unsigned getBattlesPlayed() const;
    unsigned getBattlesWon() const;
    int getRank() const;
    double getWinRate() const;

    void setRank(int rank);
    void addXP(unsigned amount);
    bool spendXP(unsigned amount);

    void addCharacter(std::unique_ptr<PlayerCharacter> character);
    const std::vector<std::unique_ptr<PlayerCharacter>>& getCharacters() const;
    void printCharacters() const;
    PlayerCharacter* chooseCharacter();

    void addItem(std::unique_ptr<Items> item);
    const std::vector<std::unique_ptr<Items>>& getItems() const;
    void printItems() const;
    bool consumeItem(ItemType type);

    bool hasMirror() const;
    bool consumeMirror();
    bool hasShield() const;
    bool consumeShield();
    bool hasBlade() const;
    bool consumeBlade();

    void recordWin();
    void recordLoss();

    void save(const std::string& dir) const;
    static std::unique_ptr<User> load(const std::string& filepath);

    bool checkPassword(const std::string& pw) const;

private:
    std::string username;
    std::string password;
    unsigned totalXP = 0;
    unsigned availableXP = 0;
    unsigned battlesPlayed = 0;
    unsigned battlesWon = 0;
    int rank = 0;

    std::vector<std::unique_ptr<Items>> items;
    std::vector<std::unique_ptr<PlayerCharacter>> characters;

    int findItem(ItemType type) const;
    void eraseItemAt(int index);
};
