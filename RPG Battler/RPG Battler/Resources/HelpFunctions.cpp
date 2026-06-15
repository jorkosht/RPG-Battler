#include "HelpFunctions.h"

bool ask()
{
    char answer = ' ';
    while (answer != 'y' && answer != 'n')
    {
        std::cin >> answer;
        if (answer != 'y' && answer != 'n')
            std::cout << "Invalid answer. Please enter y or n: ";
    }
    return answer == 'y';
}

std::string toString(ItemType type)
{
    switch (type)
    {
        case ItemType::Potion: return "Potion";
        case ItemType::Blade: return "Blade";
        case ItemType::Mirror: return "Mirror";
        case ItemType::Beam: return "Beam";
        case ItemType::Shield: return "Shield";
        default: return "Unknown";
    }
}

std::string toString(CharacterType type)
{
    switch (type)
    {
        case CharacterType::Warrior: return "Warrior";
        case CharacterType::Mage: return "Mage";
        case CharacterType::Archer: return "Archer";
        default: return "Unknown";
    }
}

unsigned itemPrice(ItemType type)
{
    switch (type)
    {
        case ItemType::Potion: return ItemConstants::POTION_PRICE;
        case ItemType::Blade: return ItemConstants::BLADE_PRICE;
        case ItemType::Mirror: return ItemConstants::MIRROR_PRICE;
        case ItemType::Beam: return ItemConstants::BEAM_PRICE;
        case ItemType::Shield: return ItemConstants::SHIELD_PRICE;
        default: return 0;
    }
}

ItemType itemTypeFromInt(int i)
{
    if (i < 0 || i >= ItemConstants::NUMBER_OF_ITEMS)
        throw std::invalid_argument("Invalid item index");
    return static_cast<ItemType>(i);
}

CharacterType charTypeFromInt(int i)
{
    if (i < 0 || i > 2)
        throw std::invalid_argument("Invalid character type index");
    return static_cast<CharacterType>(i);
}

int readInt()
{
    int v;
    while (!(std::cin >> v))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number: ";
    }
    return v;
}
