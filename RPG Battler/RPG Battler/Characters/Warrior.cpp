#include "Warrior.h"

Warrior::Warrior(const std::string& name, User* owner)
        : PlayerCharacter(name, CharConstants::WARRIOR_HP, CharConstants::MAX_WARRIOR_DMG, CharacterType::Warrior, owner) {}

void Warrior::ability(unsigned& dmg)
{
    int block = rand() % CharConstants::WARRIOR_BLOCK;
    if (dmg < block) dmg = 0;
    dmg -= block;
}
