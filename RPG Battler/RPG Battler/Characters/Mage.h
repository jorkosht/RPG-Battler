#pragma once
#include "PlayerCharacter.h"

class Mage : public PlayerCharacter
{
    
public:
    unsigned ability(unsigned dmg) override;
};
