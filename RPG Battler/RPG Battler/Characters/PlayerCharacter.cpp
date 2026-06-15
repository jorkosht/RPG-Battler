#include "PlayerCharacter.h"
#include "User.h"
#include "HelpFunctions.h"
#include <cstdlib>

PlayerCharacter::PlayerCharacter(const std::string& name, unsigned maxHP,
                                 unsigned maxDMG, CharacterType type, User* owner)
    : name(name), maxHP(maxHP), currHP(maxHP), maxDMG(maxDMG), type(type), owner(owner) {}

PlayerCharacter::~PlayerCharacter() = default;

void PlayerCharacter::ability(unsigned& dmg) {}

const std::string& PlayerCharacter::getName() const { return name; }
unsigned PlayerCharacter::getMaxHP() const { return maxHP + hpUpgrades * CharConstants::LEVEL_HP_BONUS; }
unsigned PlayerCharacter::getCurrHP() const { return currHP; }
unsigned PlayerCharacter::getMaxDMG() const { return maxDMG; }
CharacterType PlayerCharacter::getType() const { return type; }
User* PlayerCharacter::getOwner() const { return owner; }
unsigned PlayerCharacter::getLevel() const { return level; }
unsigned PlayerCharacter::getDmgUpgrades() const { return dmgUpgrades; }
unsigned PlayerCharacter::getHPUpgrades() const { return hpUpgrades; }

void PlayerCharacter::setCurrHP(unsigned hp) { currHP = hp; }
void PlayerCharacter::resetHP() { currHP = getMaxHP(); }
void PlayerCharacter::levelUpHP() { ++hpUpgrades; ++level; currHP = getMaxHP(); }
void PlayerCharacter::levelUpDMG() { ++dmgUpgrades; ++level; }

void PlayerCharacter::attack(PlayerCharacter& defender)
{
    unsigned effectiveMax = maxDMG + dmgUpgrades;
    unsigned dmg = rand() % effectiveMax + 1;

    std::cout << std::endl << "[" << name << "] rolls " << dmg << " DMG";

    if (type != CharacterType::Warrior)
    {
        bool canActivate = true;

        if (type == CharacterType::Archer && dmg > CharConstants::ARCHER_DMG_THRESHOLD)
            canActivate = false;

        if (canActivate)
        {
            std::cout << std::endl << "Activate your special ability? (y/n): ";
            if (ask())
            {
                if (defender.getOwner()->consumeMirror())
                    std::cout << "[Mirror] Defender's Mirror blocked your ability!\n";
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

    if (defender.getType() == CharacterType::Warrior)
    {
        if (owner->consumeMirror())
        {
            std::cout << "[Mirror] Attacker's Mirror blocked Warrior's block ability!\n";
        }
        else
        {
            unsigned block = CharConstants::WARRIOR_BLOCK_MIN
                           + rand() % CharConstants::WARRIOR_BLOCK;
            std::cout << "[Warrior Block] " << defender.getName()
                      << " blocks " << block << " DMG" << std::endl;
            dmg = (dmg > block) ? dmg - block : 0;
        }
    }

    if (dmg > 0 && defender.getOwner()->hasShield())
    {
        std::cout << defender.getOwner()->getUsername()
                  << ", use your Shield to block " << dmg << " DMG? (y/n): ";
        if (ask())
        {
            if (defender.getOwner()->consumeShield())
            {
                std::cout << "[Shield] Damage blocked!" << std::endl;
                dmg = 0;
            }
        }
    }

    std::cout << "[" << name << "] deals " << dmg
              << " DMG to [" << defender.getName() << "]" << std::endl;

    unsigned newHP = (defender.currHP > dmg) ? defender.currHP - dmg : 0;
    defender.currHP = newHP;
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

void PlayerCharacter::loadBase(std::istream& in)
{
    int t;
    in >> name >> t >> maxHP >> currHP >> maxDMG >> level >> hpUpgrades >> dmgUpgrades;
    type = static_cast<CharacterType>(t);
}
