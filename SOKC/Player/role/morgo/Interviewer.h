#ifndef INTERVIEWER_H
#define INTERVIEWER_H
#include "/home/ubuntu/GameProject/SOKC-branch/Player/Player.h"
#include "/home/ubuntu/GameProject/SOKC-branch/jsonParser/JsonParser.h"

class Interviewer:public Player{
    
    void userAbility(Json::Value data);
};
#endif