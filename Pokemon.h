#ifndef POKEMON_H
#define POKEMON_H

#include <string>

// used for type effectiveness in battle
enum NATURE_TYPE {NORMAL = 1, FIRE = 2, WATER = 3, ELECTRIC = 4, GRASS = 5};

// determining catch chance
enum RARITY {COMMON = 1, UNCOMMON = 2, RARE = 3, LEGENDARY = 4};

// A single pokemon in the game

class Pokemon{
    
    private:
    
    std::string name;
    std::string baseAttackName;
    std::string heavyAttackName;
    
    int evoStage;
    int pokemonExp;
    int hp;
    int baseAttackDmg;
    int heavyAttackDmg;
    
    NATURE_TYPE type;
    RARITY rarity;

    public:

    // constructor
    Pokemon();
    // destructor
    ~Pokemon();


    // setters and getters

    // rarity
    void setRarity(int);
    RARITY getRarity();

    // name
    void setName(std::string);
    std::string getName();

    // type
    void setType(int);
    NATURE_TYPE getType();
    std::string getTypeAsString();

    // evolution stage
    void setEvoStage(int);
    int getEvoStage();

    // pokemon exp
    void setPokemonExp(int);
    int getPokemonExp();

    // health points
    void setHp(double);
    double getHp();

    // base attack name
    void setBaseAttackName(std::string);
    std::string getBaseAttackName();
   
    // base attack dmg
    void setBaseAttackDmg(double);
    double getBaseAttackDmg();

    // heavy attack name
    void setHeavyAttackName(std::string);
    std::string getHeavyAttackName();

    // heavy attack dmg
    void setHeavyAttackDmg(double);
    double getHeavyAttackDmg();

    // prints out the elements of a pokemon
    void showStats();

    void evolve();
};

#endif // POKEMON_H
