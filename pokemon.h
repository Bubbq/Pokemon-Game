#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>

enum natureType {NORMAL = 1, FIRE = 2, WATER = 3, ELECTRIC = 4, GRASS = 5};

class Pokemon
{
    private:
    std::string name;
    int evoStage;
    int hp;
    std::string base_attack_name;
    int base_attack_dmg;
    std::string heavy_attack_name;
    int heavy_attack_dmg;
    natureType type;

    public:
    
    Pokemon();
    ~Pokemon();
    
    std::string Getname();
    void Setname(std::string val);
    
    natureType GetType();
    void SetType(int val);
    
    int GetevoStage();
    void SetevoStage(int val);
    
    int Gethp();
    void Sethp(int val);
    
    std::string Getbase_attack_name();
    void Setbase_attack_name(std::string val);
    
    int Getbase_attack_dmg();
    void Setbase_attack_dmg(int val);
    
    std::string Getheavy_attack_name();
    void Setheavy_attack_name(std::string val);
    
    int Getheavy_attack_dmg();
    void Setheavy_attack_dmg(int val);
    
    void print();
};

#endif // POKEMON_H
