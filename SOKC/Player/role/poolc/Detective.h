#ifndef DETECTIVE_H
#define DETECTIVE_H
#include "/home/ubuntu/GameProject/SOKC-branch/Player/Player.h"
#include "/home/ubuntu/GameProject/SOKC-branch/jsonParser/JsonParser.h"

class Detective:public Player{
    int abilityCount=1;
    void userAbility(Json::Value data);
    int getAbilityCount();
    void setAbilityCount(int count);
};
#endif