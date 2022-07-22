#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <iostream>
#include "jsonparser/jsonparser.h"
#include "Player/playerRepository.h"
#include <vector>
#include <algorithm>

class Controller
{
public:
    Game game;
    Controller();
    Json::Value control(std::string in);
    Json::Value positions();
};

#endif