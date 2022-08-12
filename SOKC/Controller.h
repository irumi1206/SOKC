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
    Json::Value control(std::string in);
    Json::Value positions();
    Json::Value playerInfo();
    int roomCheck(int roomId);
    Json::Value getMission(Player& player);
    Json::Value gameEnd(Team team,int id);
    Json::Value teamPlayers(Team team);
    //투표
    Json::Value voteResult();
    Json::Value deadList();
    Json::Value death(int id);
};

#endif