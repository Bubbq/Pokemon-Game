#include <iostream>

#include "Pokedex.h"
#include "Pokemon.h"

void Pokedex::printCurrPokemon(){
    
    node * tmp = new node();
    tmp = head;
    
    while(tmp->next!=nullptr){
        std::cout << tmp->pokemonInfo->Getname() << "\t" << tmp->pokemonInfo->Gethp() << std::endl;
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
        node *tmp = head;
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
