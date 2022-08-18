#include <iostream>
#include "Noob.h"

void Noob::userAbility(Json::Value data){
    cout<<"NOOOOOOOOOOOOOOOOOB"<<"\n";
};
Noob::Noob(int id, std::string name):Player(id,name){};
Noob::Noob():Player(-1,""){};