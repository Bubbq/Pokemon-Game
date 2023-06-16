#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <string>

enum natureType {NORMAL = 1, FIRE = 2, WATER = 3, ELECTRIC = 4, GRASS = 5};
enum RARITY {COMMON = 1, UNCOMMON = 2, RARE = 3, LEGENDARY = 4};

class Pokemon
{
    private:
    std::string name;
    int evoStage;
    int pokemonXp;
    int hp;
    std::string base_attack_name;
    int base_attack_dmg;
    std::string heavy_attack_name;
    int heavy_attack_dmg;
    natureType type;
    RARITY rarity;

    public:

    Pokemon();
    ~Pokemon();


    void setRarity(int val);
    RARITY getRarity();


    std::string Getname();
    void Setname(std::string val);

    natureType GetType();
    void SetType(int val);
    std::string GetTypeAsString(natureType val);

    int GetevoStage();
    void SetevoStage(int val);

    int GetPokemonXp();
    void SetPokemonXp(int val);

    double Gethp();
    void Sethp(int val);

    std::string Getbase_attack_name();
    void Setbase_attack_name(std::string val);

    double Getbase_attack_dmg();
    void Setbase_attack_dmg(double val);

    std::string Getheavy_attack_name();
    void Setheavy_attack_name(std::string val);

    double Getheavy_attack_dmg();
    void Setheavy_attack_dmg(double val);

    void printPokemon();
};

#endif // POKEMON_H
