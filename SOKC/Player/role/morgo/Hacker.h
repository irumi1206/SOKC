#ifndef HACKER_H
#define HACKER_H
#include "/home/ubuntu/GameProject/SOKC-branch/Player/Player.h"
#include "/home/ubuntu/GameProject/SOKC-branch/jsonParser/JsonParser.h"

class Hacker:public Player{
    
    void userAbility(Json::Value data);
};
#endif