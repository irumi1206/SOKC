#include <iostream>
#include "Role.h"

Team CharacterRoleFlag::getTeam(){
    return this->team;
}
void CharacterRoleFlag::setRole(int role){
    this->role=role;
}
int CharacterRoleFlag::getRole(){
    return this->role;
}

// bitmasking?