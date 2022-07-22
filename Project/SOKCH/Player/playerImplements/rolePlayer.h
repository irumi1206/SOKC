#ifndef ROLEPLAYER_H
#define ROLEPLAYER_H
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
    Team getTeam();
    void setRole(int role);
    int getRole();
};
#endif
// bitmasking?