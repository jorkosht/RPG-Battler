#include "Warrior.h"

unsigned Warrior::ability(unsigned dmg)
{
    int block = rand() % Constants::WARRIOR_BLOCK;
    if (dmg < block) return 0;
    return dmg - block;
}
