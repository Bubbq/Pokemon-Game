#ifndef POKEMON_H
#define POKEMON_H



enum natureType {NORMAL = 1, FIRE = 2, WATER = 3, ELECTRIC = 4, GRASS = 5};

class Pokemon
{
    private:
        char* name;
        int evoStage;
        int hp;
        char* base_attack_name;
        int base_attack_dmg;
        char* heavy_attack_name;
        int heavy_attack_dmg;
        natureType type;



    public:

        Pokemon();
        ~Pokemon();

        void copyString(const char* src, char*& dst);


        char* Getname();
        void Setname(char* val);

        natureType GetType();
        void SetType(int val);

        int GetevoStage();
        void SetevoStage(int val);

        int Gethp();
        void Sethp(int val);

        char* Getbase_attack_name();
        void Setbase_attack_name(char* val);

        int Getbase_attack_dmg();
        void Setbase_attack_dmg(int val);

        char* Getheavy_attack_name();
        void Setheavy_attack_name(char* val);

        int Getheavy_attack_dmg();
        void Setheavy_attack_dmg(int val);

        void print();
};

#endif // POKEMON_H
