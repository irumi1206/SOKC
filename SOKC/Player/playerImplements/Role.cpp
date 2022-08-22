#include <iostream>
#include "Role.h"

Team CharacterRoleFlag::getTeam(){
    return this->team;
}
void CharacterRoleFlag::setRole(int role){
    this->role=role;
    if(role<20){
        this->team=PoolC;
        switch(role){
            case 2:
            {
                this->abilityCount=1;
                break;
            }
            case 3:
            {
                this->abilityCount=2;
                break;
            }
            default:
            break;
        }
    }else if(role<40){
        this->team=Morgo;
        switch(role){
            case 21:
            {
                this->abilityCount=1;
                break;
            }
            case 22:
            {
                this->abilityCount=1;//매 라운드 초기화
                break;
            }
            case 24:
            {
                this->abilityCount=1;//매 라운드 초기화
                break;
            }
            default:
            break;
        }
    }
    else{
        this->team=Mid;
    }
}
int CharacterRoleFlag::getRole(){
    return this->role;
}