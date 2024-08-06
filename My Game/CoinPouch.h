#pragma once
#ifndef COINPOUCH_H
#define COINPOUCH_H
#include "Character.h"
#include <fstream> 



class CoinPouch : public Character
{
private:
    int m_copper;
    int m_silver;
    int m_gold;
    int m_electrum;
    int m_platinum;
    Character* m_owner; 
public:
    CoinPouch() : m_copper(0), m_silver(0), m_gold(0), m_electrum(0), m_platinum(0), m_owner(nullptr)
    {
    }
    CoinPouch(int copper, int silver, int gold, int electrum, int platinum, Character* owner)
        : m_copper(copper), m_silver(silver), m_gold(gold), m_electrum(electrum), m_platinum(platinum), m_owner(owner) {}

    string getCoins() const
    {
        return "Copper: " + to_string(m_copper) + ", Silver: " + to_string(m_silver) + ", Gold: " + to_string(m_gold) +
            ", Electrum: " + to_string(m_electrum) + ", Platinum: " + to_string(m_platinum);
    }
    void addCoins(int copper, int silver, int gold, int electrum, int platinum)
    {
        m_copper += copper;
        m_silver += silver;
        m_gold += gold;
        m_electrum += electrum;
        m_platinum += platinum;
    }
    bool hasEnoughCoins(int copper, int silver, int gold, int electrum, int platinum)
    {
        return m_copper >= copper && m_silver >= silver && m_gold >= gold && m_electrum >= electrum && m_platinum >= platinum;
    }

    bool removeCoins(int copper, int silver, int gold, int electrum, int platinum)
    {
        if (hasEnoughCoins(copper, silver, gold, electrum, platinum))
        {
            m_copper -= copper;
            m_silver -= silver;
            m_gold -= gold;
            m_electrum -= electrum;
            m_platinum -= platinum;
            return true;
        }
        else
        {
            return false;
        }
    }

    void displayCoins() const
    {
        std::cout << "Copper: " << m_copper << ", Silver: " << m_silver << ", Gold: " << m_gold << ", Electrum: " << m_electrum << ", Platinum: " << m_platinum << std::endl;
    }
   
    void setOwner(Character* owner)
    {
        m_owner = owner; 
    }
    Character* getOwner()const
    {
        return m_owner; 
    }
   
};

#endif



