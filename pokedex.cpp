#include "pokedex.h"
#include "pokemon.h"

#include<iostream>

void Pokedex::printCurrPokemon(){

    int pokemonCount = 1;
    node * tmp = new node();
    tmp = head;

    while(tmp->next!=nullptr){

        std::cout  << pokemonCount << ".) " << tmp->pokemonInfo->Getname() << std::endl;
        tmp = tmp->next;
        pokemonCount++;
    }
}

void Pokedex::printPokemon(){

    node * tmp = new node();
    tmp = head;

    while(tmp->next != nullptr){

        std::cout <<  "General Stats: " << std::endl << std::endl;

        std::cout << "Name: " << tmp->pokemonInfo->Getname() << std::endl;
        std::cout << "Type: " << tmp->pokemonInfo->GetTypeAsString(tmp->pokemonInfo->GetType()) << std::endl << std::endl;

        std::cout << "Attack Statistics: " << std::endl << std::endl;

        std::cout << "Current Health: " << tmp->pokemonInfo->Gethp() << std::endl;
        std::cout << "Base: " << tmp->pokemonInfo->Getbase_attack_name() << ", " << tmp->pokemonInfo->Getbase_attack_dmg() << "dmg" << std::endl;
        std::cout << "Heavy: " << tmp->pokemonInfo->Getheavy_attack_name() << ", " << tmp->pokemonInfo->Getheavy_attack_dmg() << "dmg" << std::endl << std::endl;

        tmp = tmp->next;
    }
}

void Pokedex::appendPokemon(Pokemon * data){

    node *nn = new node();
    nn->pokemonInfo = data;

    // Assign to head, if the current linked list is empty
    if (head == nullptr) {
        head = nn;
        return;
    }

    // Traverse until the end of the list
    else {
        node *tmp = new node();
        tmp = head;

        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }

        // Insert at the end
        tmp->next = nn;
        nn->next = nullptr;
    }
}

bool Pokedex::removePokemonByName(char* name){

    node * desiredNode = new node();
    desiredNode = head;

    node * prevNode = new node();
    prevNode = nullptr;

    //if the first node is the desired node
    if(desiredNode->pokemonInfo->Getname() == name){

        head = head->next;
        delete desiredNode;
        return true;

    }

    while(desiredNode->next!=nullptr){

        prevNode = desiredNode;
        desiredNode = desiredNode->next;

        if(desiredNode->pokemonInfo->Getname() == name){
            prevNode->next = desiredNode->next;
            delete desiredNode;
            return true;
        }
    }

    return false;
}

int Pokedex::findNodeSize() {
	int c = 0;
	node *tmp = new node();
	tmp = head;

	while (tmp->next!=nullptr) {//if were not at the end, increment
		c++;
		tmp = tmp->next;
	}
	return c;
}

Pokemon * Pokedex::findPokemonAtIndex(int val){

    node * tmp = new node();
    tmp = head;
    int index = 0;

    while(tmp->next!=nullptr){
        index++;
        tmp = tmp->next;
        if(index == val){
            return tmp->pokemonInfo;
        }

    }
    return nullptr;
}

Pokedex::Pokedex(){

    head = nullptr;

}

Pokedex::~Pokedex(){

    node * temp = head;
    node* tempCopy = head;

    while(temp!=nullptr){
        tempCopy = temp->next;//makes a copy so we dont remove the  info for the location of the next node
        delete temp;
        temp = tempCopy;
    }
}
