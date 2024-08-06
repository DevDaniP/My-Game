#pragma once
#ifndef BACKPACK_H
#define BACKPACK_H 
#include "DynamicArray.h"
#include "Character.h"
#include <fstream>

class Backpack : public Character

{
private:
    DynamicArray<potions> m_items;
    Character* m_owner;
public:
    Backpack(Character* owner = nullptr) : m_items(), m_owner(owner)
    {

    }

    ~Backpack() {}

    void setOwner(Character* owner)
    {
        m_owner = owner;
    }

    Character* getOwner() const
    {
        return m_owner;
    }

    int numItems() const
    {
        return m_items.GetElements();
    }

    void addItem(const potions& item)
    {
        m_items.Insert(item);
    }

    void removeItem(const potions& item)
    {
        m_items.Delete(item);
    }
    potions getItem(int index) const 
    {
        return m_items[index];
    }
};
#endif
  






