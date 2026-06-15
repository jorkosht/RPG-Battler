#include "Battle.h"
#include "HelpFunctions.h"
#include "Potion.h"
#include "Beam.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>

void Battle::printStatus(const PlayerCharacter& a, const PlayerCharacter& b)
{
    std::cout << std::endl << "--- Battle Status ---" << std::endl;
    std::cout << std::left << std::setw(20) << a.getName()
              << " HP: " << a.getCurrHP() << "/" << a.getMaxHP() << std::endl;
    std::cout << std::left << std::setw(20) << b.getName()
              << " HP: " << b.getCurrHP() << "/" << b.getMaxHP() << std::endl;
    std::cout << "---------------------\n";
}

bool Battle::tryUseItem(User& user, PlayerCharacter& userChar,
                        User& opponent, PlayerCharacter& oppChar)
{
    user.printItems();
    if (user.getItems().empty())
    {
        std::cout << "No items in inventory.\n";
        return false;
    }

    std::cout << "Choose item to use:\n";
    for (int i = 0; i < ItemConstants::NUMBER_OF_ITEMS; ++i)
        std::cout << i + 1 << ". " << toString(static_cast<ItemType>(i)) << std::endl;
    std::cout << "0. Cancel" << std::endl;

    int choice = readInt();
    if (choice == 0) return false;
    if (choice < 1 || choice > ItemConstants::NUMBER_OF_ITEMS)
    {
        std::cout << "Invalid choice." << std::endl;
        return false;
    }

    ItemType chosen = static_cast<ItemType>(choice - 1);

    bool found = false;
    for (auto& it : user.getItems())
        if (it->getType() == chosen) { found = true; break; }

    if (!found)
    {
        std::cout << "You don't have that item." << std::endl;
        return false;
    }

    switch (chosen)
    {
        case ItemType::Potion:
        {
            int idx = -1;
            for (int i = 0; i < (int)user.getItems().size(); ++i)
                if (user.getItems()[i]->getType() == ItemType::Potion) { idx = i; break; }
            Potion p;
            unsigned newHP = p.ability(userChar.getCurrHP(), userChar.getMaxHP());
            std::cout << "[Potion] Healed! HP: " << userChar.getCurrHP()
                      << " -> " << newHP << std::endl;
            userChar.setCurrHP(newHP);
            const_cast<std::vector<std::unique_ptr<Items>>&>(user.getItems())
                .erase(user.getItems().begin() + idx);
            return true;
        }
        case ItemType::Blade:
        {
            std::cout << "[Blade] Armed! Your next attack will deal double damage." << std::endl;
            return true;
        }
        case ItemType::Mirror:
        {
            std::cout << "[Mirror] Active! The opponent's next special ability will be blocked." << std::endl;
            return true;
        }
        case ItemType::Beam:
        {
            if (!opponent.hasMirror())
            {
                std::cout << "[Beam] Opponent has no active Mirror to remove." << std::endl;
                return false;
            }
            int idx = -1;
            for (int i = 0; i < (int)user.getItems().size(); ++i)
                if (user.getItems()[i]->getType() == ItemType::Beam) { idx = i; break; }
            const_cast<std::vector<std::unique_ptr<Items>>&>(user.getItems())
                .erase(user.getItems().begin() + idx);

            opponent.consumeMirror();
            std::cout << "[Beam] Removed opponent's Mirror!" << std::endl;
            return true;
        }
        case ItemType::Shield:
        {
            std::cout << "[Shield] Your Shield is ready. It will automatically prompt "
                         "when you take damage." << std::endl;
            return true;
        }
    }
    return false;
}

void Battle::doTurn(User& attacker, PlayerCharacter& atkChar,
                    User& defender,  PlayerCharacter& defChar)
{
    std::cout << "\n=== " << attacker.getUsername()
              << "'s turn [" << atkChar.getName() << "] ===" << std::endl;
    printStatus(atkChar, defChar);

    std::cout << "1. Attack\n2. Use item" << std::endl;
    int choice = readInt();

    if (choice == 1)
    {
        atkChar.attack(defChar);
    }
    else if (choice == 2)
    {
        bool turnUsed = tryUseItem(attacker, atkChar, defender, defChar);
        if (!turnUsed)
        {
            std::cout << "Falling back to attack." << std::endl;
            atkChar.attack(defChar);
        }
    }
    else
    {
        std::cout << "Invalid choice – attacking by default." << std::endl;
        atkChar.attack(defChar);
    }
}

User* Battle::run(User& u1, User& u2)
{
    std::cout << std::endl << "============================" << std::endl;
    std::cout << "   BATTLE: " << u1.getUsername() << " vs " << u2.getUsername() << std::endl;
    std::cout << "============================" << std::endl;

    std::cout << u1.getUsername() << ", choose your character:" << std::endl;
    PlayerCharacter* c1 = u1.chooseCharacter();
    if (!c1)
    {
        std::cout << "No character selected." << std::endl;
        return nullptr;
    }

    std::cout << u2.getUsername() << ", choose your character:" << std::endl;
    PlayerCharacter* c2 = u2.chooseCharacter();
    if (!c2)
    {
        std::cout << "No character selected." << std::endl;
        return nullptr;
    }

    c1->resetHP();
    c2->resetHP();

    bool u1First = rand() % 2 == 0;
    User* curAttacker  = u1First ? &u1 : &u2;
    User* curDefender  = u1First ? &u2 : &u1;
    PlayerCharacter* curAtkChar = u1First ? c1 : c2;
    PlayerCharacter* curDefChar = u1First ? c2 : c1;

    std::cout << std::endl << "[Coin toss] " << curAttacker->getUsername() << " goes first!" << std::endl;

    while (c1->getCurrHP() > 0 && c2->getCurrHP() > 0)
    {
        doTurn(*curAttacker, *curAtkChar, *curDefender, *curDefChar);

        if (curDefChar->getCurrHP() == 0) break;

        std::swap(curAttacker,  curDefender);
        std::swap(curAtkChar,   curDefChar);
    }

    User* winner = (c1->getCurrHP() > 0) ? &u1 : &u2;
    User* loser  = (winner == &u1) ? &u2 : &u1;

    std::cout << std::endl << "*** " << winner->getUsername() << " WINS! ***" << std::endl;

    winner->addXP(BattleConstants::WIN_XP);
    loser->addXP(BattleConstants::LOSE_XP);
    winner->recordWin();
    loser->recordLoss();

    std::cout << winner->getUsername() << " earned " << BattleConstants::WIN_XP << " XP" << std::endl;
    std::cout << loser->getUsername()  << " earned " << BattleConstants::LOSE_XP  << " XP" << std::endl;

    c1->resetHP();
    c2->resetHP();

    return winner;
}
