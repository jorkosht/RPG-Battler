#pragma once
#include "CharacterType.h"
#include "CharacterConstants.h"
#include <iostream>

class User;

class PlayerCharacter
{
    std::string name;
    User* owner;
    CharacterType type;
    
    unsigned currHP;
    unsigned maxHP;
    unsigned maxDMG;
    unsigned level = Constants::STARTING_LEVEL;
    unsigned dmgUpgrades = 0;
    unsigned hpUpgrades = 0;
    
public:
    void attack(PlayerCharacter& defender);
    const unsigned getDmgUpgrades() const;
    virtual unsigned ability(unsigned dmg) = 0;
};
