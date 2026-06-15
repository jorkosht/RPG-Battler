#pragma once
#include "User.h"
#include "PlayerCharacter.h"

class Battle {
public:
    static User* run(User& u1, User& u2);

private:
    static void doTurn(User& attacker, PlayerCharacter& atkChar,
                       User& defender, PlayerCharacter& defChar);
    static void applyAttack(User& attacker, PlayerCharacter& atkChar,
                            User& defender, PlayerCharacter& defChar);
    static bool tryUseItem(User& user, PlayerCharacter& userChar,
                           User& opponent, PlayerCharacter& oppChar);
    static void printStatus(const PlayerCharacter& a, const PlayerCharacter& b);
};
