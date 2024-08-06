#pragma once
#include <string> 
#ifndef POTIONS_H
#define POTIONS_H
#include "DynamicArray.h" 

using std::string;

class potions {
    string potionName;
    string potionDescription;
    string potionPotency;
    string potionCost;
public:
    potions();
    potions(string Name, string Description, string Potency, string Cost);
    potions& operator =(const potions& rhs);
    potions(const potions& other);
    ~potions();
    void setName(string Name);
    string getName();
    void setDescription(string Description);
    string getDescription();
    void setPotency(string Potency);
    string getPotency();
    void setCost(string Cost);
    string getCost() const;
    bool operator==(const potions& other)const
    {
        return (potionName == other.potionName &&
            potionDescription == other.potionDescription &&
            potionPotency == other.potionPotency &&
            potionCost == other.potionCost); 
    }

};
#endif 
