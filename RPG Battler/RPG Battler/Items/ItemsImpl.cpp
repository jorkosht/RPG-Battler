#include "Potion.h"
#include "Blade.h"
#include "Mirror.h"
#include "Beam.h"
#include "Shield.h"
#include <cstdlib>

Potion::Potion() : Items(ItemType::Potion, ItemConstants::POTION_PRICE) {}

unsigned Potion::ability(unsigned currHP, unsigned maxHP)
{
    unsigned heal = ItemConstants::MIN_HEAL
                  + rand() % (ItemConstants::MAX_HEAL - ItemConstants::MIN_HEAL + 1);
    unsigned newHP = currHP + heal;
    return (newHP > maxHP) ? maxHP : newHP;
}

Blade::Blade()  : Items(ItemType::Blade,  ItemConstants::BLADE_PRICE)  {}

Mirror::Mirror(): Items(ItemType::Mirror, ItemConstants::MIRROR_PRICE) {}

Beam::Beam()    : Items(ItemType::Beam,   ItemConstants::BEAM_PRICE)   {}

Shield::Shield(): Items(ItemType::Shield, ItemConstants::SHIELD_PRICE) {}
