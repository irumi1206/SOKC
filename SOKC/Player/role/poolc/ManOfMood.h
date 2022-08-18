#ifndef MANOFMOOD_H
#define MANOFMOOD_H
#include "/home/ubuntu/GameProject/SOKC-branch/Player/Player.h"
#include "/home/ubuntu/GameProject/SOKC-branch/jsonParser/JsonParser.h"

class ManOdMood:public Player{
    
    void userAbility(Json::Value data);
};
#endif