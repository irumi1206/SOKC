#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>
#include <vector>
#include <algorithm>
#include "jsonParser/JsonParser.h"
#include "Player/Game.h"
#include <map>

class Controller
{
public:
    Game game;
    const Json::Value null;
    const std::string Header="Header";
    const std::string Content="Content";
    Controller();
    Json::Value control(std::string in, int clientIndex);
    Json::Value positions();
    Json::Value playerInfo();
    int roomCheck(int roomId);
    Json::Value getMission(Player& player);
    //Header 7
    Json::Value setHost(int id);
    //Header 11
    Json::Value roundStart();
    //Header 33
    Json::Value death(int id);
    //Header 35
    Json::Value benefitTaken(int id);
    //Header 100
    Json::Value gameEnd(Team team,int id);
    Json::Value teamPlayers(Team team);
    //투표
    Json::Value voteResult();
    Json::Value deadList();
    //투표 끝났는지 확인
    Json::Value votingCheck();
    Json::Value roleSetting();

    
    
};

#endif