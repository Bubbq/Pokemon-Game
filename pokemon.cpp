#include "pokemon.h"

Pokemon::Pokemon(){

    name = "";
    base_attack_name = "";
    heavy_attack_name = "";

    evoStage = 1;
    pokemonXp = 0;
    hp = 0;
    base_attack_dmg = 0;
    heavy_attack_dmg = 0;

    type = NORMAL;
}

Pokemon::~Pokemon(){}

void Pokemon::setRarity(int val){rarity = (RARITY)val;}
RARITY Pokemon::getRarity(){return rarity;}

std::string Pokemon::Getname() { return name; }
void Pokemon::Setname(std::string val) { name = val; }

natureType Pokemon::GetType(){return type;}
void Pokemon::SetType(int val){type = (natureType)val;}
std::string Pokemon::GetTypeAsString(natureType val){

    switch(val){
    case 1: return "Normal";
        break;
    case 2: return "Fire";
        break;
    case 3: return "Water";
        break;
    case 4: return "Electric";
        break;
    default: return "Grass";
        break;
    }
}

int Pokemon::GetevoStage(){return evoStage;}
void Pokemon::SetevoStage(int val){evoStage = val;}

int Pokemon::GetPokemonXp() { return pokemonXp; }
void Pokemon::SetPokemonXp(int val) { pokemonXp = val; }

double Pokemon::Gethp() { return hp; }
void Pokemon::Sethp(double val) { hp = val; }

std::string Pokemon::Getbase_attack_name() { return base_attack_name; }
void Pokemon::Setbase_attack_name(std::string val) { base_attack_name = val; }

double Pokemon::Getbase_attack_dmg() { return base_attack_dmg; }
void Pokemon::Setbase_attack_dmg(double val) { base_attack_dmg = val; }

std::string Pokemon::Getheavy_attack_name() { return heavy_attack_name; }
void Pokemon::Setheavy_attack_name(std::string val) { heavy_attack_name = val; }

double Pokemon::Getheavy_attack_dmg() { return heavy_attack_dmg; }
void Pokemon::Setheavy_attack_dmg(double val) { heavy_attack_dmg = val; }

void Pokemon::printPokemon(){
    std::cout <<name;
    if(hp <=0){
        std::cout << "(*FAINTED*)" << std::endl;
    }
    else{
        std::cout << std::endl <<
        // "\t\tEvol: " << evoStage << std::endl <<
        "\tHP: " << hp << std::endl <<
        "\tType: " << GetTypeAsString(type) << std::endl <<
        "\tRarity: " << rarity << std::endl <<
        std::endl <<
        "\tNormal Attack: " << base_attack_name << ", " << base_attack_dmg << " dmg" << std::endl <<
        "\tHeavy Attack: " << heavy_attack_name << ", " << heavy_attack_dmg << " dmg" << std::endl <<
        std::endl;
            }

}
