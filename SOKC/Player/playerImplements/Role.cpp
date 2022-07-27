#include <iostream>
#include "Role.h"

Team CharacterRoleFlag::getTeam(){
    return this->team;
}
void CharacterRoleFlag::setRole(int role){
    this->role=role;
    if(role<20){
        this->team=PoolC;
    }else if(role<40){
        this->team=Morgo;
    }
    else{
        this->team=Mid;
    }
}
int CharacterRoleFlag::getRole(){
    return this->role;
}

// bitmasking?