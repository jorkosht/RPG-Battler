#pragma once

namespace CharConstants {
    constexpr unsigned WARRIOR_HP = 20;
    constexpr unsigned MAGE_HP    = 12;
    constexpr unsigned ARCHER_HP  = 15;

    constexpr unsigned MAX_WARRIOR_DMG = 8;
    constexpr unsigned MAX_MAGE_DMG    = 12;
    constexpr unsigned MAX_ARCHER_DMG  = 8;

    constexpr unsigned WARRIOR_BLOCK = 4;
    constexpr unsigned WARRIOR_BLOCK_MIN = 1;

    constexpr unsigned ARCHER_DMG_THRESHOLD = 4;
    constexpr unsigned ARCHER_DMG_MULTIPLIER = 2;

    constexpr unsigned LEVEL_UP_COST    = 100;
    constexpr unsigned NEW_CHAR_COST    = 50;
    constexpr unsigned LEVEL_HP_BONUS   = 2;
    constexpr unsigned LEVEL_DMG_BONUS  = 1;
}

namespace ItemConstants {
    constexpr unsigned POTION_PRICE = 30;
    constexpr unsigned BLADE_PRICE  = 50;
    constexpr unsigned MIRROR_PRICE = 80;
    constexpr unsigned BEAM_PRICE   = 90;
    constexpr unsigned SHIELD_PRICE = 100;

    constexpr unsigned MIN_HEAL = 5;
    constexpr unsigned MAX_HEAL = 10;

    constexpr int NUMBER_OF_ITEMS = 5;
}

namespace BattleConstants {
    constexpr unsigned WIN_XP  = 10;
    constexpr unsigned LOSE_XP = 5;
}

enum class CharacterType { Warrior, Mage, Archer };
enum class ItemType { Potion = 0, Blade = 1, Mirror = 2, Beam = 3, Shield = 4 };
