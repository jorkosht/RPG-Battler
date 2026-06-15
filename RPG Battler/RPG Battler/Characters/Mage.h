#pragma once
#include "PlayerCharacter.h"

class Mage : public PlayerCharacter
{
    
public:
    Mage(const std::string& name, User* owner);
    void ability(unsigned& dmg) override;
};
