#include <iostream>

class CharacterRoleFlag
{
public:
    std::string role;
    CharacterRoleFlag(){
        role="temp!";
    }
    CharacterRoleFlag(const CharacterRoleFlag& other){
        this->role=other.role;
    }
};