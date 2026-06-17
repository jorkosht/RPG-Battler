#pragma once
#include "Items.h"
#include "User.h"

class Blade : public Items
{
    
public:
    Blade();
    unsigned ability(User* user, unsigned dmg);
};
