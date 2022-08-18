#include "Politician.h"

Politician::Politician(int id, std::string name):public Player(id, name){
    this->voteCount=2;
}

void Politician::benefit(){
    this->voteCount+=1;
}