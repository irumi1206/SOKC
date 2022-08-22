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
    std::map<int,std::tuple<float,float>> positionVector;
    Controller();
    Json::Value control1(std::string in, int clientId);
    Json::Value control(Json::Value data, int clientId);
    Json::Value playerInfo();
    int roomCheck(int roomId);
    // Json::Value getMission(Player& player);
    int getMission(Player& player);
    //Header 7
    Json::Value setHost(int id);
    //Header 16
    Json::Value roundStartData();
    //Header 22
    Json::Value voteEnd();
    //Header 31
    Json::Value positions();
    //Header 35
    Json::Value benefitTaken(int id);
    //Header 100
    Json::Value gameEnd(Team team);
    Json::Value teamPlayers(Team team);
    //투표
    Json::Value voteResult(std::map<int,int> storage);
    Json::Value deadList();
    Json::Value roleSetting();
    //투표 끝났는지 확인
    bool isVoteEnd();
    void startVote();
    bool enterAllow=true;

    Json::Value useAbility(int roleFlag, Json::Value data);
    Json::Value survivors();
};

#endif