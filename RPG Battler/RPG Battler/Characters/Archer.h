#pragma once
#include "PlayerCharacter.h"

class Archer : public PlayerCharacter
{
public:
    Archer(const std::string& name, User* owner);
    void ability(unsigned& dmg) override;
};
