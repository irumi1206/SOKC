#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>
#include <vector>
#include <algorithm>
#include "jsonParser/JsonParser.h"
#include "Player/Game.h"

class Controller
{
public:
    Game game;
    const Json::Value null;
    Controller();
    Json::Value control(std::string in);
    Json::Value positions();
    std::string playerInfo();
    int roomCheck(int roomId);
    std::string getMission(Player& player);
};

#endif