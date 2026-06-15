#pragma once
#include "Constants.h"
#include <iostream>
#include <string>
#include <limits>

bool ask();
std::string toString(ItemType type);
std::string toString(CharacterType type);
unsigned itemPrice(ItemType type);
ItemType itemTypeFromInt(int i);
CharacterType charTypeFromInt(int i);
int readInt();
