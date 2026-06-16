#include "Game.h"
#include "Battle.h"
#include "Leaderboard.h"
#include "HelpFunctions.h"
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include "Potion.h"
#include "Blade.h"
#include "Mirror.h"
#include "Beam.h"
#include "Shield.h"
#include <filesystem>
#include <iostream>
#include <stdexcept>

namespace fs = std::filesystem;

Game::Game()
{
    fs::create_directories(DATA_DIR);
    loadAll();
}

void Game::loadAll()
{
    for (auto& entry : fs::directory_iterator(DATA_DIR))
    {
        if (entry.path().extension() == ".dat")
        {
            try
            {
                users.push_back(User::load(entry.path().string()));
            }
            catch (const std::exception& e)
            {
                std::cerr << "Warning: could not load " << entry.path() << ": " << e.what() << std::endl;
            }
        }
    }
    refreshLeaderboard();
}

void Game::saveAll() const
{
    for (auto& u : users)
    {
        u->save(DATA_DIR);
    }
}

User* Game::findUser(const std::string& username)
{
    for (auto& u : users)
        if (u->getUsername() == username) return u.get();
    return nullptr;
}

void Game::refreshLeaderboard()
{
    std::vector<User*> ptrs;
    for (auto& u : users) ptrs.push_back(u.get());
    Leaderboard::updateRanks(ptrs);
}

void Game::printLeaderboard() const
{
    std::vector<User*> ptrs;
    for (auto& u : users) ptrs.push_back(u.get());
    Leaderboard::print(ptrs);
}

void Game::registerUser()
{
    std::string username, password;
    std::cout << "Choose username: ";
    std::cin >> username;

    if (findUser(username))
    {
        std::cout << "Username already taken." << std::endl;
        return;
    }

    std::cout << "Choose password: ";
    std::cin >> password;

    auto newUser = std::make_unique<User>(username, password);

    std::cout << std::endl << "Choose your starting character type:" << std::endl
              << "1. Warrior (HP:" << CharConstants::WARRIOR_HP
              << " DMG:1-" << CharConstants::MAX_WARRIOR_DMG << ")" << std::endl
              << "2. Mage    (HP:" << CharConstants::MAGE_HP
              << " DMG:1-" << CharConstants::MAX_MAGE_DMG << ")" << std::endl
              << "3. Archer  (HP:" << CharConstants::ARCHER_HP
              << " DMG:1-" << CharConstants::MAX_ARCHER_DMG << ")" << std::endl;

    int charChoice = readInt();
    std::string charName;
    std::cout << "Enter character name: ";
    std::cin >> charName;

    switch (charChoice)
    {
        case 1: newUser->addCharacter(std::make_unique<Warrior>(charName, newUser.get())); break;
        case 2: newUser->addCharacter(std::make_unique<Mage>   (charName, newUser.get())); break;
        case 3: newUser->addCharacter(std::make_unique<Archer> (charName, newUser.get())); break;
        default:
            std::cout << "Invalid choice – defaulting to Warrior." << std::endl;
            newUser->addCharacter(std::make_unique<Warrior>(charName, newUser.get()));
    }

    std::cout << std::endl << "Choose your starting item:" << std::endl;
    for (int i = 0; i < ItemConstants::NUMBER_OF_ITEMS; ++i)
        std::cout << i + 1 << ". " << toString(static_cast<ItemType>(i))
                  << " (" << itemPrice(static_cast<ItemType>(i)) << " XP)" << std::endl;

    int itemChoice = readInt();
    ItemType startItem = ItemType::Potion;
    if (itemChoice >= 1 && itemChoice <= ItemConstants::NUMBER_OF_ITEMS)
        startItem = static_cast<ItemType>(itemChoice - 1);

    switch (startItem)
    {
        case ItemType::Potion: newUser->addItem(std::make_unique<Potion>()); break;
        case ItemType::Blade:  newUser->addItem(std::make_unique<Blade>());  break;
        case ItemType::Mirror: newUser->addItem(std::make_unique<Mirror>()); break;
        case ItemType::Beam:   newUser->addItem(std::make_unique<Beam>());   break;
        case ItemType::Shield: newUser->addItem(std::make_unique<Shield>()); break;
    }

    std::cout << std::endl << "Welcome, " << username << "! Your adventure begins." << std::endl;
    users.push_back(std::move(newUser));
    refreshLeaderboard();
    saveAll();
}

User* Game::loginUser()
{
    std::string username, password;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    User* u = findUser(username);
    if (!u || !u->checkPassword(password))
    {
        std::cout << "Invalid username or password." << std::endl;
        return nullptr;
    }
    std::cout << "Welcome back, " << username << "!" << std::endl;
    return u;
}

void Game::shopMenu(User& user)
{
    while (true)
    {
        std::cout << std::endl << "=== Shop === (Available XP: " << user.getAvailableXP() << ")" << std::endl
                  << "1. Buy item" << std::endl
                  << "2. Buy new character (50 XP)" << std::endl
                  << "3. Level up character (100 XP)" << std::endl
                  << "4. Back" << std::endl;

        int choice = readInt();
        if (choice == 4) break;

        if (choice == 1)
        {
            std::cout << "Choose item:" << std::endl;
            for (int i = 0; i < ItemConstants::NUMBER_OF_ITEMS; ++i)
                std::cout << i + 1 << ". " << toString(static_cast<ItemType>(i))
                          << " – " << itemPrice(static_cast<ItemType>(i)) << " XP" << std::endl;
            std::cout << "0. Cancel" << std::endl;
            int ic = readInt();
            if (ic < 1 || ic > ItemConstants::NUMBER_OF_ITEMS) continue;

            ItemType it = static_cast<ItemType>(ic - 1);
            if (!user.spendXP(itemPrice(it)))
            {
                std::cout << "Not enough XP." << std::endl; continue;
            }
            switch (it)
            {
                case ItemType::Potion: user.addItem(std::make_unique<Potion>()); break;
                case ItemType::Blade:  user.addItem(std::make_unique<Blade>());  break;
                case ItemType::Mirror: user.addItem(std::make_unique<Mirror>()); break;
                case ItemType::Beam:   user.addItem(std::make_unique<Beam>());   break;
                case ItemType::Shield: user.addItem(std::make_unique<Shield>()); break;
            }
            std::cout << "Purchased " << toString(it) << "!" << std::endl;
        }
        else if (choice == 2)
        {
            if (!user.spendXP(CharConstants::NEW_CHAR_COST))
            {
                std::cout << "Not enough XP (need " << CharConstants::NEW_CHAR_COST << ")." << std::endl;
                continue;
            }
            std::cout << "Choose type: 1.Warrior  2.Mage  3.Archer" << std::endl;
            int tc = readInt();
            std::string cname;
            std::cout << "Enter character name: ";
            std::cin >> cname;
            switch (tc)
            {
                case 1: user.addCharacter(std::make_unique<Warrior>(cname, &user)); break;
                case 2: user.addCharacter(std::make_unique<Mage>   (cname, &user)); break;
                case 3: user.addCharacter(std::make_unique<Archer> (cname, &user)); break;
                default:
                    std::cout << "Invalid – refunding XP." << std::endl;
                    user.addXP(CharConstants::NEW_CHAR_COST);
                    continue;
            }
            std::cout << "New character created!" << std::endl;
        }
        else if (choice == 3)
        {
            if (user.getCharacters().empty()) { std::cout << "No characters." << std::endl; continue; }
            if (!user.spendXP(CharConstants::LEVEL_UP_COST))
            {
                std::cout << "Not enough XP (need " << CharConstants::LEVEL_UP_COST << ")." << std::endl;
                continue;
            }
            user.printCharacters();
            std::cout << "Choose character to level up: ";
            int ci = readInt();
            if (ci < 1 || ci > static_cast<int>(user.getCharacters().size()))
            {
                std::cout << "Invalid – refunding XP." << std::endl;
                user.addXP(CharConstants::LEVEL_UP_COST);
                continue;
            }
            PlayerCharacter* ch = user.getCharacters()[ci - 1].get();
            std::cout << "Choose upgrade:" << std::endl
                      << "1. +2 Max HP" << std::endl
                      << "2. +1 Max Damage" << std::endl;
            int uc = readInt();
            if (uc == 1)      { ch->levelUpHP();  std::cout << "+2 Max HP applied." << std::endl; }
            else if (uc == 2) { ch->levelUpDMG(); std::cout << "+1 Max Damage applied." << std::endl; }
            else
            {
                std::cout << "Invalid – refunding XP." << std::endl;
                user.addXP(CharConstants::LEVEL_UP_COST);
            }
        }
        saveAll();
    }
}

void Game::battleMenu(User& user)
{
    if (users.size() < 2) { std::cout << "No other players to fight!" << std::endl; return; }

    std::cout << std::endl << "=== Choose Opponent ===" << std::endl;
    std::vector<User*> opponents;
    for (auto& u : users)
        if (u.get() != &user) opponents.push_back(u.get());

    for (size_t i = 0; i < opponents.size(); ++i)
        std::cout << i + 1 << ". " << opponents[i]->getUsername()
                  << "  (Rank " << opponents[i]->getRank() << ")" << std::endl;
    std::cout << "0. Cancel" << std::endl;

    int choice = readInt();
    if (choice < 1 || choice > static_cast<int>(opponents.size())) return;

    User* opponent = opponents[choice - 1];
    if (user.getCharacters().empty())     { std::cout << "You have no characters!" << std::endl; return; }
    if (opponent->getCharacters().empty()){ std::cout << "Opponent has no characters!" << std::endl; return; }

    Battle::run(user, *opponent);
    refreshLeaderboard();
    saveAll();
}

void Game::loggedInMenu(User& user)
{
    while (true)
    {
        std::cout << std::endl
                  << "=== " << user.getUsername()
                  << "  XP:" << user.getAvailableXP()
                  << "/" << user.getTotalXP()
                  << "  Battles:" << user.getBattlesWon()
                  << "W/" << user.getBattlesPlayed() << " ===" << std::endl
                  << "1. View characters" << std::endl
                  << "2. View items" << std::endl
                  << "3. Shop" << std::endl
                  << "4. Battle" << std::endl
                  << "5. Leaderboard" << std::endl
                  << "6. Logout" << std::endl;

        int choice = readInt();
        switch (choice)
        {
            case 1: user.printCharacters(); break;
            case 2: user.printItems();      break;
            case 3: shopMenu(user);         break;
            case 4: battleMenu(user);       break;
            case 5: printLeaderboard();     break;
            case 6: return;
            default: std::cout << "Invalid choice." << std::endl;
        }
    }
}

void Game::mainMenu()
{
    while (true)
    {
        std::cout << std::endl
                  << "=== RPG Battler ===" << std::endl
                  << "1. Register" << std::endl
                  << "2. Login" << std::endl
                  << "3. Leaderboard" << std::endl
                  << "4. Exit" << std::endl;

        int choice = readInt();
        switch (choice)
        {
            case 1: registerUser(); break;
            case 2:
            {
                User* u = loginUser();
                if (u) loggedInMenu(*u);
                break;
            }
            case 3: printLeaderboard(); break;
            case 4: return;
            default: std::cout << "Invalid choice." << std::endl;
        }
    }
}

void Game::run()
{
    mainMenu();
    saveAll();
}
