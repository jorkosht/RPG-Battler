#pragma once
#include "Items.h"
#include "User.h"

class Beam : public Items
{
public:
    Beam();
    
    void ability(User* attacker, User* defender);
};
