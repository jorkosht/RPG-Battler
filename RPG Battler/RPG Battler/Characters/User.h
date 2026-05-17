#pragma once
#include <iostream>
#include <memory>
#include "PlayerCharacter.h"
#include "Items.h"

class User
{
    std::string username;
    std::string password;
    
    unsigned totalXP;
    unsigned unspentXP;
    unsigned totalBattles;
    unsigned wonBattles;
    unsigned rank;
    
    std::vector<std::unique_ptr<PlayerCharacter>> characters;
    std::vector<std::unique_ptr<Items>> items;
    
    
public:
    
};
