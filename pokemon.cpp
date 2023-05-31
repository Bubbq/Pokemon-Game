#include "pokemon.h"

Pokemon::Pokemon(){

    name = "";
    base_attack_name = "";
    heavy_attack_name = "";

    evoStage = 0;
    hp = 0;
    base_attack_dmg = 0;
    heavy_attack_dmg = 0;

    type = NORMAL;
}

Pokemon::~Pokemon(){}

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

int Pokemon::GetevoStage() { return evoStage; }
void Pokemon::SetevoStage(int val) { evoStage = val; }

int Pokemon::Gethp() { return hp; }
void Pokemon::Sethp(int val) { hp = val; }

std::string Pokemon::Getbase_attack_name() { return base_attack_name; }
void Pokemon::Setbase_attack_name(std::string val) { base_attack_name = val; }

int Pokemon::Getbase_attack_dmg() { return base_attack_dmg; }
void Pokemon::Setbase_attack_dmg(int val) { base_attack_dmg = val; }

std::string Pokemon::Getheavy_attack_name() { return heavy_attack_name; }
void Pokemon::Setheavy_attack_name(std::string val) { heavy_attack_name = val; }

int Pokemon::Getheavy_attack_dmg() { return heavy_attack_dmg; }
void Pokemon::Setheavy_attack_dmg(int val) { heavy_attack_dmg = val; }

void Pokemon::printPokemon(){
    std::cout <<
        "Name: " << name << '\n' <<
        "Type: " << GetTypeAsString(type) << '\n' <<
       // "Evol: " << evoStage << '\n' <<
        "HP: " << hp << '\n' <<
        "Base_Attack: " << base_attack_name << ", " << base_attack_dmg << " dmg\n" <<
        "Heavy_Attack: " << heavy_attack_name << ", " << heavy_attack_dmg << " dmg\n" <<
        '\n';
}
