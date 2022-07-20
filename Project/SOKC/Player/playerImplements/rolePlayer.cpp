#include <iostream>

enum Team{
    PoolC,
    Morgo,
    Mid
};

class CharacterRoleFlag
{
public:
    int role;
    Team team;
    Team getTeam(){
        return this->team;
    }
    void setRole(int role){
        this->role=role;
    }
    int getRole(){
        return this->role;
    }
};

// bitmasking?