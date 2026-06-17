#include "PlayerCharacter.h"
#include "User.h"
#include "HelpFunctions.h"
#include <cstdlib>

PlayerCharacter::PlayerCharacter(const std::string& name, unsigned maxHP,
                                 unsigned maxDMG, CharacterType type, User* owner)
    : name(name), maxHP(maxHP), currHP(maxHP), maxDMG(maxDMG), type(type), owner(owner) {}

PlayerCharacter::~PlayerCharacter() = default;

void PlayerCharacter::ability(unsigned& dmg) {}

const std::string& PlayerCharacter::getName() const
{
    return name;
}

unsigned PlayerCharacter::getCurrHP() const
{
    return currHP;
}

CharacterType      PlayerCharacter::getType() const
{
    return type;
}

User* PlayerCharacter::getOwner() const
{
    return owner;
}

unsigned PlayerCharacter::getLevel() const
{
    return level;
}

unsigned PlayerCharacter::getDmgUpgrades() const
{
    return dmgUpgrades;
}

unsigned PlayerCharacter::getHPUpgrades() const
{
    return hpUpgrades;
}

unsigned PlayerCharacter::getMaxHP() const
{
    return maxHP + hpUpgrades * CharConstants::LEVEL_HP_BONUS;
}

unsigned PlayerCharacter::getMaxDMG() const
{
    return maxDMG;
}

void PlayerCharacter::setCurrHP(unsigned hp)
{
    currHP = hp;
}

void PlayerCharacter::resetHP()
{
    currHP = getMaxHP();
}

void PlayerCharacter::levelUpHP()
{
    ++hpUpgrades;
    ++level;
    currHP = getMaxHP();
}

void PlayerCharacter::levelUpDMG()
{
    ++dmgUpgrades;
    ++level;
}

void PlayerCharacter::attack(PlayerCharacter& defender)
{
    unsigned effectiveMax = maxDMG + dmgUpgrades;
    unsigned dmg = rand() % effectiveMax + 1;

    std::cout << std::endl << "[" << name << "] rolls " << dmg << " DMG" << std::endl;

    if (type == CharacterType::Mage || type == CharacterType::Archer)
    {
        bool offerAbility = true;
        if (type == CharacterType::Archer)
            offerAbility = true;

        if (offerAbility)
        {
            std::cout << "Activate your special ability? (y/n): ";
            if (ask())
            {
                if (defender.owner->consumeMirror())
                    std::cout << "[Mirror] Opponent's Mirror blocked your ability!" << std::endl;
                else
                    ability(dmg);
            }
        }
    }

    if (owner->consumeBlade())
    {
        std::cout << "[Blade] Damage doubled: " << dmg << " -> " << dmg * 2 << std::endl;
        dmg *= 2;
    }

    if (defender.type == CharacterType::Warrior)
    {
        if (owner->consumeMirror())
            std::cout << "[Mirror] Attacker's Mirror blocked Warrior's block!" << std::endl;
        else
            defender.ability(dmg);
    }

    if (dmg > 0 && defender.owner->hasShield())
    {
        std::cout << defender.owner->getUsername()
                  << ", use your Shield to block " << dmg << " DMG? (y/n): ";
        if (ask() && defender.owner->consumeShield())
        {
            std::cout << "[Shield] Damage blocked!" << std::endl;
            dmg = 0;
        }
    }

    std::cout << "[" << name << "] deals " << dmg
              << " DMG to [" << defender.getName() << "]" << std::endl;

    defender.currHP = (defender.currHP > dmg) ? defender.currHP - dmg : 0;
}

void PlayerCharacter::saveBase(std::ostream& out) const
{
    out << name << std::endl
        << static_cast<int>(type) << std::endl
        << maxHP << std::endl
        << currHP << std::endl
        << maxDMG << std::endl
        << level << std::endl
        << hpUpgrades << std::endl
        << dmgUpgrades << std::endl;
}

void PlayerCharacter::restoreFields(unsigned maxHP, unsigned currHP, unsigned maxDMG,
                                    unsigned level, unsigned hpUp, unsigned dmgUp)
{
    this->maxHP = maxHP;
    this->currHP = currHP;
    this->maxDMG = maxDMG;
    this->level = level;
    hpUpgrades = hpUp;
    dmgUpgrades = dmgUp;
}
