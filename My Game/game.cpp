using namespace std; 

#include "potions.h"
#include "DynamicArray.h" 
#include "Character.h" 
#include "CoinPouch.h"
#include "Backpack.h"
#include "Dice.h" 
#include <string>
#include <sstream> 
#include <fstream> 
#include <iostream>

void coinConversion(int& copper, int& silver, int& gold, int& electrum, int& platinum);
void usersPotions(DynamicArray<potions>& potionArray);
void costCoins( DynamicArray<potions>& potionArray, int& copper, int& silver, int& gold, int& electrum, int& platinum);
void buyPotions(Character* characters[], int numCharacters, DynamicArray<potions>& potionArray, int& copper, int& silver, int& gold, int& electrum, int& platinum);
void writeToFile(Character* characters[], int numCharacters, const string& filename);
void inputCoins(Character* characters[], int numCharacters); 
void rollDiceAndWeapon(Character* characters[], int numCharacters, Dice& dice);

int main()
{
    const int MAXPOTIONS = 10;
    const int MAXCHARACTERS = 3; 

    int copper = 0;
    int silver = 0;
    int gold = 0;
    int electrum = 0;
    int platinum = 0;

    
    DynamicArray<potions> potionArray; 
    Character* characters[MAXCHARACTERS] = { nullptr };
    Dice dice; 
    
    usersPotions(potionArray);
    costCoins(potionArray, copper, silver, gold, electrum, platinum);
    coinConversion(copper, silver, gold, electrum, platinum);
    

    cout << "Enter the names of up to" << MAXCHARACTERS << " characters ( Amy enter enter enter = 1 name) " << endl;
    for (int i = 0; i < MAXCHARACTERS; ++i) 
    {
        string name; 
        cout << "Character  " << i + 1 << ": ";
        getline(cin, name);

        CoinPouch* coinPouch = new CoinPouch(0,0,0,0,0, nullptr);
        Backpack* backpack = new Backpack(nullptr); 


        characters[i] = new Character(name, coinPouch, backpack); 

        coinPouch->setOwner(characters[i]); 
        backpack->setOwner(characters[i]); 

     
    }
    inputCoins(characters, MAXCHARACTERS); 
    rollDiceAndWeapon(characters, MAXCHARACTERS, dice); 

    cout << "Characters added:" << endl; 
    for (int i = 0; i < MAXCHARACTERS; ++i)
    {
        cout << " Character" << i + 1 << ":" << characters[i]->getName() << endl; 

    }

    cout << " the total cost for these potions will be " << copper << " copper " << silver << " silver " << gold << " gold " << electrum << " electrum " << platinum << " platinum " << endl;
    
    buyPotions(characters, MAXCHARACTERS, potionArray, copper, silver, gold, electrum, platinum); 

    writeToFile(characters, MAXCHARACTERS, "characters.txt");

    for (int i = 0; i < MAXCHARACTERS; ++i)
    {
        delete characters[i]->getCoinPouch(); 
        delete characters[i]->getBackPack();
        delete characters[i]; 
    }
    
    return 0;
}
//if there is time make a subclass for rarity that calculates the cost of the potion for them 
// it can use the potency and type to determine a random dice roll based on the perameters 
//if there is time make a seperate ability to say they have more than one of the same kind of potion- so they dont have to retype it


void inputCoins(Character* characters[], int numCharacters) {
    for (int i = 0; i < numCharacters; ++i) {
        int copper, silver, gold, electrum, platinum;
        cout << "Enter the number of coins for " << characters[i]->getName() << ":" << endl;

        cout << "Copper: ";
        cin >> copper;

        cout << "Silver: ";
        cin >> silver;

        cout << "Gold: ";
        cin >> gold;

        cout << "Electrum: ";
        cin >> electrum;

        cout << "Platinum: ";
        cin >> platinum;

        characters[i]->getCoinPouch()->addCoins(copper, silver, gold, electrum, platinum);
    }
}

void rollDiceAndWeapon(Character* characters[], int numCharacters, Dice& dice)
{
    for (int i = 0; i < numCharacters; ++i)
    {
        auto rollResult = dice.roll();
        int number = rollResult.first;
        string weapon = rollResult.second;

        cout << "Character " << characters[i]->getName() << " rolled a " << number << " and got a " << weapon << " starter weapon." << endl;

        potions weaponPotion(weapon, "Weapon", "Standard", "0.0.0.0.0");
        characters[i]->getBackPack()->addItem(weaponPotion);
    }
}

void buyPotions(Character* characters[], int numCharacters, DynamicArray<potions>& potionArray, int& copper, int& silver, int& gold, int& electrum, int& platinum)
{
    char buyChoice;
    cout << "Do you want to buy these potions? (Y/N):";
    cin >> buyChoice;

    if (toupper(buyChoice) == 'Y')
    {
        int characterChoice; 
        cout << " Which character wants to buy these potions? (Enter character number 1, 2, or 3 )";
            cin >> characterChoice; 
            cin.ignore(); 

            if (characterChoice >= 1 && characterChoice <= numCharacters)
            {
                int characterIndex = characterChoice - 1;
                if (characters[characterIndex]->getCoinPouch()->hasEnoughCoins(copper, silver, gold, electrum, platinum))
                {
                    for (int j = 0; j < potionArray.GetElements(); ++j)
                    {
                        characters[characterIndex]->getBackPack()->addItem(potionArray[j]);
                    }

                    characters[characterIndex]->getCoinPouch()->removeCoins(copper, silver, gold, electrum, platinum);
                    cout << "Potions bought and added to " << characters[characterIndex]->getName() << "'s backpack." << endl;
                }
                else
                {
                    cout << characters[characterIndex]->getName() << " does not have enough coins to buy these potions." << endl;
                }
            }
            else
            {
                cout << "Invalid character choice. No potions bought." << endl;
            }
    }
    else
    {
        cout << "No potions bought." << endl;
    }
}
void writeToFile(Character* characters[], int numCharacters, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    for (int i = 0; i < numCharacters; ++i) {
        if (characters[i] != nullptr) {
            outFile << "Character: " << characters[i]->getName() << std::endl;

            CoinPouch* coinPouch = characters[i]->getCoinPouch();
            if (coinPouch) {
                outFile << "Coins: " << coinPouch->getCoins() << std::endl;
            }

            Backpack* backpack = characters[i]->getBackPack();
            if (backpack) {
                outFile << "Backpack items:" << std::endl;
                for (int j = 0; j < backpack->numItems(); ++j) {
                    potions potion = backpack->getItem(j);  
                    outFile << "  - " << potion.getName() << ", "
                        << potion.getDescription() << ", "
                        << potion.getPotency() << ", "
                        << potion.getCost() << std::endl;
                }
            }
        }
    }

    outFile.close();
}


void usersPotions(DynamicArray<potions>& potionArray){
    string potionName;
    string potionDescription;
    string potionPotency;
    string potionCost;
    int numPotions; 

    cout << " How many potions do you have? ";
    cin >> numPotions;
    cin.ignore();
    for (int i = 0; i < numPotions; ++i) {
        cout << " What is the name of your " << i + 1 << " potion? : ";
        getline(cin, potionName);

        cout << " What type of potion is that? : ";
        getline(cin, potionDescription);

        cout << " What is the potency of that potion? : ";
        getline(cin, potionPotency);

        cout << " What is the cost of that potion in this order copper.silver.gold.electrum.platinum (please place 0. for none) : ";
        getline(cin, potionCost);

     

        potions newPotion(potionName, potionDescription, potionPotency, potionCost); 
        potionArray.Insert(newPotion); 
      
    }
}

void costCoins( DynamicArray<potions>& potionArray, int& copper, int& silver, int& gold, int& electrum, int& platinum) {
    int numPotions = potionArray.GetElements(); 
    for (int i = 0; i < numPotions; ++i) {
        string strCost = potionArray[i].getCost();
        istringstream ss(strCost);
        string token;
        int coinQuantity = 0;
        while (getline(ss, token, '.')) {
            int coin = stoi(token);
            switch (coinQuantity) {
            case 0:
                copper += coin;
                break;
            case 1:
                silver += coin;
                break;
            case 2:
                gold += coin;
                break;
            case 3:
                electrum += coin;
                break;
            case 4:
                platinum += coin;
                break;
            }
            ++coinQuantity;
        }
    }

}

void coinConversion(int& copper, int& silver, int& gold, int& electrum, int& platinum) {
    const int silverToCopper = 10;
    const int goldToSilver = 10;
    const int electrumToGold = 5;
    const int platinumToElectrum = 10;

    if (silver >= silverToCopper) {
        copper += silver / silverToCopper;
        silver %= silverToCopper;
    }


    if (gold >= goldToSilver) {
        silver += gold / goldToSilver;
        gold %= goldToSilver;
    }


    if (electrum >= electrumToGold) {
        gold += electrum / electrumToGold;
        electrum %= electrumToGold;
    }


    if (platinum >= platinumToElectrum) {
        electrum += platinum / platinumToElectrum;
        platinum %= platinumToElectrum;
    }
}



