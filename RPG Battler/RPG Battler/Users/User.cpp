#include "User.h"
#include "PlayerCharacter.h"
#include "HelpFunctions.h"
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include "Potion.h"
#include "Blade.h"
#include "Mirror.h"
#include "Beam.h"
#include "Shield.h"
#include <fstream>
#include <stdexcept>
#include <iomanip>

User::User() = default;
User::User(const std::string& username, const std::string& password)
    : username(username), password(password) {}
User::~User() = default;

const std::string& User::getUsername() const
{
    return username;
}
unsigned User::getTotalXP() const
{
    return totalXP;
}
unsigned User::getAvailableXP() const
{
    return availableXP;
}
unsigned User::getBattlesPlayed() const
{
    return battlesPlayed;
}
unsigned User::getBattlesWon() const
{
    return battlesWon;
}
int User::getRank() const
{
    return rank;
}
double User::getWinRate() const
{
    return battlesPlayed == 0 ? 0.0
        : static_cast<double>(battlesWon) / battlesPlayed * 100.0;
}

void User::setRank(int r)
{
    rank = r;
}
bool User::checkPassword(const std::string& pw) const
{
    return password == pw;
}
void User::addXP(unsigned amount)
{
    totalXP += amount;
    availableXP += amount;
}
bool User::spendXP(unsigned amount)
{
    if (availableXP < amount) return false;
    availableXP -= amount;
    return true;
}

void User::addCharacter(std::unique_ptr<PlayerCharacter> ch)
{
    characters.push_back(std::move(ch));
}
const std::vector<std::unique_ptr<PlayerCharacter>>& User::getCharacters() const
{
    return characters;
}

void User::printCharacters() const
{
    std::cout << std::endl << "=== Your Characters ===" << std::endl;
    for (size_t i = 0; i < characters.size(); ++i)
    {
        auto& c = characters[i];
        std::cout << i + 1 << ". " << c->getName()
                  << " [" << toString(c->getType()) << "]"
                  << "  HP: " << c->getCurrHP() << "/" << c->getMaxHP()
                  << "  DMG: 1-" << (c->getMaxDMG() + c->getDmgUpgrades())
                  << "  Level: " << c->getLevel() << std::endl;
    }
}

PlayerCharacter* User::chooseCharacter()
{
    if (characters.empty()) {
        std::cout << "You have no characters!" << std::endl;
        return nullptr;
    }
    printCharacters();
    std::cout << "Choose character (number): ";
    int choice = readInt();
    if (choice < 1 || choice > static_cast<int>(characters.size()))
    {
        std::cout << "Invalid choice." << std::endl;
        return nullptr;
    }
    return characters[choice - 1].get();
}

void User::addItem(std::unique_ptr<Items> item)
{
    items.push_back(std::move(item));
}
const std::vector<std::unique_ptr<Items>>& User::getItems() const
{
    return items;
}

void User::printItems() const
{
    if (items.empty())
    {
        std::cout << "  (no items)" << std::endl;
        return;
    }
    int counts[ItemConstants::NUMBER_OF_ITEMS] = {};
    for (auto& i : items) counts[static_cast<int>(i->getType())]++;
    std::cout << std::endl << "=== Your Items ===" << std::endl;
    for (int i = 0; i < ItemConstants::NUMBER_OF_ITEMS; ++i)
    {
        if (counts[i] > 0)
            std::cout << "  " << toString(static_cast<ItemType>(i))
            << " x" << counts[i]
            << "  (" << itemPrice(static_cast<ItemType>(i)) << " XP)" << std::endl;
    }
}

int User::findItem(ItemType type) const
{
    for (int i = 0; i < static_cast<int>(items.size()); ++i)
    {
        if (items[i]->getType() == type) return i;
    }
    return -1;
}

void User::eraseItemAt(int index)
{
    items.erase(items.begin() + index);
}

bool User::consumeItem(ItemType type)
{
    int idx = findItem(type);
    if (idx == -1) return false;
    eraseItemAt(idx);
    return true;
}

bool User::hasMirror() const
{
    return findItem(ItemType::Mirror) != -1;
}
bool User::consumeMirror()
{
    return consumeItem(ItemType::Mirror);
}
bool User::hasShield() const
{
    return findItem(ItemType::Shield) != -1;
}
bool User::consumeShield()
{
    return consumeItem(ItemType::Shield);
}
bool User::hasBlade() const
{
    return findItem(ItemType::Blade)  != -1;
}
bool User::consumeBlade()
{
    return consumeItem(ItemType::Blade);
}

void User::recordWin()
{
    ++battlesPlayed;
    ++battlesWon;
}
void User::recordLoss()
{
    ++battlesPlayed;
}

void User::save(const std::string& dir) const
{
    std::string path = dir + "/" + username + ".dat";
    std::ofstream out(path);
    if (!out) throw std::runtime_error("Cannot open save file: " + path);

    out << username << std::endl
        << password << std::endl
        << totalXP << std::endl
        << availableXP << std::endl
        << battlesPlayed << std::endl
        << battlesWon << std::endl
        << rank << std::endl;

    out << items.size() << std::endl;
    for (auto& item : items)
        out << static_cast<int>(item->getType()) << std::endl;

    out << characters.size() << std::endl;
    for (auto& ch : characters)
        ch->saveBase(out);
}

std::unique_ptr<User> User::load(const std::string& filepath)
{
    std::ifstream in(filepath);
    if (!in) throw std::runtime_error("Cannot open: " + filepath);

    auto u = std::make_unique<User>();
    in >> u->username >> u->password >> u->totalXP >> u->availableXP
       >> u->battlesPlayed >> u->battlesWon >> u->rank;

    size_t itemCount;
    in >> itemCount;
    for (size_t i = 0; i < itemCount; ++i)
    {
        int t; in >> t;
        switch (static_cast<ItemType>(t))
        {
            case ItemType::Potion: u->items.push_back(std::make_unique<Potion>());
                break;
            case ItemType::Blade: u->items.push_back(std::make_unique<Blade>());
                break;
            case ItemType::Mirror: u->items.push_back(std::make_unique<Mirror>());
                break;
            case ItemType::Beam: u->items.push_back(std::make_unique<Beam>());
                break;
            case ItemType::Shield: u->items.push_back(std::make_unique<Shield>());
                break;
            default: break;
        }
    }

    size_t charCount;
    in >> charCount;
    for (size_t i = 0; i < charCount; ++i)
    {
        std::string cname; int ctype;
        unsigned maxHP, currHP, maxDMG, level, hpUp, dmgUp;
        in >> cname >> ctype >> maxHP >> currHP >> maxDMG >> level >> hpUp >> dmgUp;

        std::unique_ptr<PlayerCharacter> ch;
        switch (static_cast<CharacterType>(ctype))
        {
            case CharacterType::Warrior: ch = std::make_unique<Warrior>(cname, u.get()); break;
            case CharacterType::Mage:    ch = std::make_unique<Mage>   (cname, u.get()); break;
            case CharacterType::Archer:  ch = std::make_unique<Archer> (cname, u.get()); break;
            default: continue;
        }
        ch->restoreFields(maxHP, currHP, maxDMG, level, hpUp, dmgUp);
        u->characters.push_back(std::move(ch));
    }
    return u;
}
