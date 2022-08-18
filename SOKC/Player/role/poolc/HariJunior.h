#ifndef HARIJUNIOR_H
#define HARIJUNIOR_H
#include "/home/ubuntu/GameProject/SOKC-branch/Player/Player.h"
#include "/home/ubuntu/GameProject/SOKC-branch/jsonParser/JsonParser.h"

class HariJunior:public Player{
    
    Json::Value userAbility(Json::Value data); 
};
#endif