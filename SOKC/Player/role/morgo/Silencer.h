#ifndef SILENCER_H
#define SILENCER_H
#include "/home/ubuntu/GameProject/SOKC-branch/Player/Player.h"
#include "/home/ubuntu/GameProject/SOKC-branch/jsonParser/JsonParser.h"

class Silencer:public Player{
    
    void userAbility(Json::Value data);
};
#endif