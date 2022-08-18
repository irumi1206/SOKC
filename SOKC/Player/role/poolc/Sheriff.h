#ifndef SHERIFF_H
#define SHERIFF_H
#include "/home/ubuntu/GameProject/SOKC-branch/Player/Player.h"
#include "/home/ubuntu/GameProject/SOKC-branch/jsonParser/JsonParser.h"

class Sheriff:public Player{
    
    void userAbility(Json::Value data);
};
#endif