#pragma once
#include <iostream>
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"

unsigned calculateDMG(unsigned dmg, std::function<unsigned (unsigned)> ability1,
                      std::function<unsigned (unsigned)> ability2);

unsigned noAbility(unsigned dmg);

unsigned abilities(CharacterType& type, unsigned dmg);

bool ask();
