#include "Archer.h"

Archer::Archer(const std::string& name, User* owner)
        : PlayerCharacter(name, CharConstants::ARCHER_HP, CharConstants::MAX_ARCHER_DMG, CharacterType::Archer, owner) {}

void Archer::ability(unsigned& dmg)
{
    dmg *= CharConstants::ARCHER_DMG_MULTIPLIER;
}
