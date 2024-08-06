#include "potions.h"
#include <iostream>
#include "DynamicArray.h"
using std::string;

potions::potions()
{
    potionName = " ";
    potionDescription = " ";
    potionPotency = " ";
    potionCost = " ";
}


potions::potions(string Name, string Description, string Potency, string Cost) {
    potionName = Name;
    potionDescription = Description;
    potionPotency = Potency;
    potionCost = Cost;
}

potions::potions(const potions& other) {
    potionName = other.potionName;
    potionDescription = other.potionDescription;
    potionPotency = other.potionPotency;
    potionCost = other.potionCost;
}

potions& potions::operator=(const potions& rhs) {
    if (this != &rhs) {
        potionName = rhs.potionName;
        potionDescription = rhs.potionDescription;
        potionPotency = rhs.potionPotency;
        potionCost = rhs.potionCost;
    }
    return *this;
}

potions::~potions() {

}
void potions::setName(string Name) {
    potionName = Name;
}
string potions::getName() {
    return potionName;
}
void potions::setDescription(string Description) {
    potionDescription = Description;
}
string potions::getDescription() {
    return potionDescription;
}
void potions::setPotency(string Potency) {
    potionPotency = Potency;
}
string potions::getPotency() {
    return potionPotency;
}
void potions::setCost(string Cost) {
    potionCost = Cost;
}
string potions::getCost()const {
    return potionCost;
}