#ifndef SNIPER_H
#define SNIPER_H
#include "/home/ubuntu/GameProject/SOKC-branch/Player/Player.h"
#include "/home/ubuntu/GameProject/SOKC-branch/jsonParser/JsonParser.h"

class Sniper:public Player{
    
    void userAbility(Json::Value data);
};
#endif