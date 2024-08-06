#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H 
#include <iostream> 
#include "DynamicArray.h"
#include "potions.h"
#include <iostream>
#include <fstream> 


using namespace std; 
#include <string>

class Backpack; 
class CoinPouch; 

class Character
{
protected: 
	Backpack* m_Backpack;
	CoinPouch* m_CoinPouch;
	string m_name; 
public:
	
	Character(): m_name(""), m_CoinPouch(nullptr), m_Backpack(nullptr)
	{}
	Character(const string& name, CoinPouch* coinpouch, Backpack* backpack): m_name(name), m_CoinPouch(coinpouch), m_Backpack(backpack)
	{}
	Character(const Character& OtherCharacter) : m_name(OtherCharacter.m_name), m_CoinPouch(OtherCharacter.m_CoinPouch), m_Backpack(OtherCharacter.m_Backpack)
	{}
	~Character()
	{}

	Character operator = (const Character& other_character)
	{
		if (this != &other_character)
		{
			m_name = other_character.m_name;
			m_CoinPouch = other_character.m_CoinPouch;
			m_Backpack = other_character.m_Backpack;
		}

		return *this;
	}

		
	string getName()const
	{
		return m_name; 
	}
	CoinPouch* getCoinPouch() const
	{
		return m_CoinPouch;
	}
	Backpack* getBackPack() const
	{
		return m_Backpack; 
	}
	void setName(const string name)
	{
		m_name = name; 
	}
	void setCoinPouch(CoinPouch* coinpouch)
	{
		m_CoinPouch = coinpouch; 
	}
	void setBackpack(Backpack* backpack)
	{
		m_Backpack = backpack; 
	}
	void displayCharacter() const
	{
		cout << "Character: " << m_name << endl; 
	}
	

};
#endif 

