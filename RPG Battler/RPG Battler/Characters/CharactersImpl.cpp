#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include "HelpFunctions.h"
#include <cstdlib>
#include <iostream>

Warrior::Warrior(const std::string& name, User* owner)
    : PlayerCharacter(name, CharConstants::WARRIOR_HP, CharConstants::MAX_WARRIOR_DMG,
                      CharacterType::Warrior, owner) {}

void Warrior::ability(unsigned& dmg)
{
    unsigned block = CharConstants::WARRIOR_BLOCK_MIN
                   + rand() % CharConstants::WARRIOR_BLOCK;
    std::cout << "[Warrior Block] " << name << " blocks " << block << " DMG\n";
    dmg = (dmg > block) ? dmg - block : 0;
}

Mage::Mage(const std::string& name, User* owner)
    : PlayerCharacter(name, CharConstants::MAGE_HP, CharConstants::MAX_MAGE_DMG,
                      CharacterType::Mage, owner) {}

void Mage::ability(unsigned& dmg)
{
    unsigned flipped = (CharConstants::MAX_MAGE_DMG + dmgUpgrades) - dmg;
    std::cout << "[Mage Flip] " << dmg << " -> " << flipped << " DMG\n";
    dmg = flipped;
}

Archer::Archer(const std::string& name, User* owner)
    : PlayerCharacter(name, CharConstants::ARCHER_HP, CharConstants::MAX_ARCHER_DMG,
                      CharacterType::Archer, owner) {}

void Archer::ability(unsigned& dmg)
{
    if (dmg <= CharConstants::ARCHER_DMG_THRESHOLD)
    {
        std::cout << "[Archer Double] " << dmg << " -> "
                  << dmg * CharConstants::ARCHER_DMG_MULTIPLIER << " DMG\n";
        dmg *= CharConstants::ARCHER_DMG_MULTIPLIER;
    }
    else
    {
        std::cout << "[Archer Double] Damage too high to double (" << dmg << ").\n";
    }
}
