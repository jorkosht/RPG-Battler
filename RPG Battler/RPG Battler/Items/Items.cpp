#include "Items.h"

Items::Items() = default;
Items::Items(ItemType type, unsigned price) : type(type), price(price) {}
Items::~Items() = default;

void Items::setPrice(unsigned price) { this->price = price; }
const ItemType Items::getType() const { return type; }
unsigned Items::getPrice() const { return price; }
