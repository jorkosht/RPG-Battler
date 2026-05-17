#include "Archer.h"

unsigned Archer::ability(unsigned dmg)
{
    return dmg * Constants::ARCHER_DMG_MULTIPLIER;
}
