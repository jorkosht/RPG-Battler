#pragma once
#include "PlayerCharacter.h"

class Warrior : public PlayerCharacter
{
public:
    unsigned ability(unsigned dmg) override;
};
