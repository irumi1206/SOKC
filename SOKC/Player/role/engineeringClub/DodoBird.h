#ifndef DODOBIRD_H
#define DODOBIRD_H
#include "/home/ubuntu/GameProject/SOKC-branch/Player/Player.h"
#include "/home/ubuntu/GameProject/SOKC-branch/jsonParser/JsonParser.h"

class DodoBird:public Player{
    
    void userAbility(Json::Value data);
};
#endif