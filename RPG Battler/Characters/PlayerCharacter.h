#pragma once
#include "Constants.h"
#include <string>
#include <iostream>

class User;

class PlayerCharacter {
public:
    PlayerCharacter(const std::string& name, unsigned maxHP, unsigned maxDMG,
                    CharacterType type, User* owner);
    virtual ~PlayerCharacter();

    virtual void ability(unsigned& dmg);
    void attack(PlayerCharacter& defender);

    const std::string& getName() const;
    unsigned getMaxHP() const;
    unsigned getCurrHP() const;
    unsigned getMaxDMG() const;
    CharacterType getType() const;
    User* getOwner() const;
    unsigned getLevel() const;
    unsigned getDmgUpgrades() const;
    unsigned getHPUpgrades() const;

    void setCurrHP(unsigned hp);
    void resetHP();
    void levelUpHP();
    void levelUpDMG();

    void saveBase(std::ostream& out) const;
    void loadBase(std::istream& in);

    void restoreFields(unsigned maxHP, unsigned currHP, unsigned maxDMG,
                       unsigned level, unsigned hpUpgrades, unsigned dmgUpgrades);

protected:
    std::string name;
    unsigned maxHP;
    unsigned currHP;
    unsigned maxDMG;
    CharacterType type;
    User* owner;
    unsigned level = 1;
    unsigned hpUpgrades = 0;
    unsigned dmgUpgrades = 0;
};
