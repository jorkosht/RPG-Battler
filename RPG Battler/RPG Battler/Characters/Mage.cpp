#include "Mage.h"

unsigned Mage::ability(unsigned dmg) 
{
    int newDmg = Constants::MAX_MAGE_DMG + getDmgUpgrades() - dmg;
    return newDmg;
}
