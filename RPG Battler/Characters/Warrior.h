#pragma once
#include "PlayerCharacter.h"

class Warrior : public PlayerCharacter
{
public:
    Warrior(const std::string& name, User* owner);
    void ability(unsigned& dmg) override;
};
