#pragma once
#include "PlayerCharacter.h"

class Archer : public PlayerCharacter
{
    
public:
    unsigned ability(unsigned dmg) override;
};
