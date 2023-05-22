#include<fstream>
#include<iostream>
#include "Pokemon.h"

    Pokemon::Pokemon(){

        name = nullptr;
        base_attack_name = nullptr;
        heavy_attack_name = nullptr;

        evoStage = 0;
        hp = 0;
        base_attack_dmg = 0;
        heavy_attack_dmg = 0;


        type = NORMAL;

}

    Pokemon::~Pokemon(){

        if(name!=nullptr){
            delete [] name;
        }

         if(base_attack_name!=nullptr){
            delete [] base_attack_name;
        }

         if(heavy_attack_name!=nullptr){
            delete [] heavy_attack_name;
        }

    }

    void Pokemon::copyString(const char* src, char*& dst) {//GIVEN
		//First determine the length of the src
		int len =0;
		int index =0;
		while(src[index]!='\0'){
			len++;
			index++;
		}

		//Dynamically allocate memory for the dst.
		// Remember: the length does not include the '\0'
		dst = new char[len + 1];
		//Go through all the elements of the src, till '\0' is found
		int i = 0;
		while (src[i] != '\0') {
			//At each step, create a copy of src[i] into dst[i]
			dst[i] = src[i];
			//Move to the next element
			i++;
		}
		//Do not forget to add the string termination character in the
		//dst c string
		dst[i] = '\0';
	}

    char* Pokemon::Getname() { return name; }
    void Pokemon::Setname(char* val) { copyString(val, name); }

    natureType Pokemon::GetType(){return type;}
    void Pokemon::SetType(int val){type = (natureType)val;}

    int Pokemon::GetevoStage() { return evoStage; }
    void Pokemon::SetevoStage(int val) { evoStage = val; }

    int Pokemon::Gethp() { return hp; }
    void Pokemon::Sethp(int val) { hp = val; }

    char* Pokemon::Getbase_attack_name() { return base_attack_name; }
    void Pokemon::Setbase_attack_name(char* val) { copyString(val, base_attack_name); }

    int Pokemon::Getbase_attack_dmg() { return base_attack_dmg; }
    void Pokemon::Setbase_attack_dmg(int val) { base_attack_dmg = val; }

    char* Pokemon::Getheavy_attack_name() { return heavy_attack_name; }
    void Pokemon::Setheavy_attack_name(char* val) { copyString(val, heavy_attack_name); }

    int Pokemon::Getheavy_attack_dmg() { return heavy_attack_dmg; }
    void Pokemon::Setheavy_attack_dmg(int val) { heavy_attack_dmg = val; }

   void Pokemon::print(){

        std::cout << hp << std::endl;

   }
