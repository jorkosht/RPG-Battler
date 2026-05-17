#include "PlayerCharacter.h"
#include "User.h"
#include "HelpFunctions.h"
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include <ctime>
#include <cstdlib>

const unsigned PlayerCharacter::getDmgUpgrades() const
{
    return dmgUpgrades;
}

void PlayerCharacter::attack(PlayerCharacter& defender)
{
    unsigned dmg = rand() % (maxDMG + dmgUpgrades);

    if (type != CharacterType::Warrior)
    {
        std::cout << dmg << " DMG" << std::endl << "Do you want to activate your ability? y/n" << std::endl;
        if (ask()) dmg = ability(dmg);
    }

    if (defender.type == CharacterType::Warrior)
        dmg = defender.ability(dmg);

    std::cout << dmg << " DMG" << std::endl;
    defender.currHP = (defender.currHP < dmg) ? 0 : defender.currHP - dmg;
}
