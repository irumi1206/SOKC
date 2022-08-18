#include "GameSetting.h"
#include <vector>

std::vector<int> GameSetting::getPoolc(){
    return this->poolcAbility;
};

std::vector<int> GameSetting::getMorgo(){
    return this->morgoAbility;
};

std::vector<int> GameSetting::getMid(){
    return this->midAbility;
};

int GameSetting::getMorgoCount(){
    return this->morgoCount;
};

int GameSetting::getMidCount(){
    return this->midCount;
}

void GameSetting::setMorgoCount(int count){
    this->morgoCount=count;
}

void GameSetting::setMidCount(int count){
    this->midCount=count;
}