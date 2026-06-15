#include "Mage.h"

Mage::Mage(const std::string& name, User* owner)
        : PlayerCharacter(name, CharConstants::MAGE_HP, CharConstants::MAX_MAGE_DMG, CharacterType::Mage, owner) {}

void Mage::ability(unsigned& dmg)
{
    dmg = CharConstants::MAX_MAGE_DMG + getDmgUpgrades() - dmg;
}
