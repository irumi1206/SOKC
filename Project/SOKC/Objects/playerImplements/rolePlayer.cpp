#include <iostream>

class CharacterRoleFlag
{
public:
    int role;
    CharacterRoleFlag(){
        role=0;
    }
    CharacterRoleFlag(const CharacterRoleFlag& other){
        this->role=other.role;
    }
};