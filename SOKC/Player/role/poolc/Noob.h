#ifndef NOOB_H
#define NOOB_H
#include "/home/ubuntu/GameProject/SOKC-branch/Player/Player.h"
#include "/home/ubuntu/GameProject/SOKC-branch/jsonParser/JsonParser.h"


class Noob:public Player{
public:
    Noob(int id, std::string name);
    Noob();
    void userAbility(Json::Value data);
};

#endif
