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
    Controller();
    Json::Value control(std::string in);
    Json::Value positions();
    std::string playerInfo();
    int roomCheck(int roomId);
};

#endif