#pragma once
#include <iostream>
#include "Constants.h"

class User;

class Items
{
    ItemType type;
    unsigned price;
    bool isActive = false;
public:
    Items();
    Items(ItemType type, unsigned price);
    virtual ~Items();
    
    ItemType getType() const;
    
    void setPrice(unsigned price);
    
    unsigned getPrice() const;
};

