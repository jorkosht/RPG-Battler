#pragma once
#include "Items.h"
#include "User.h"

class Potion : public Items
{
public:
    Potion();
    unsigned ability(unsigned currHP, unsigned maxHP);
};
