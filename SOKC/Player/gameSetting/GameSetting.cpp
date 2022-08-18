#include "GameSetting.h"
#include <vector>

std::vector<int> GameSetting::getPoolc(){
    std::vector<int> poolcAbilityList;
    for(auto it = poolcAbility.begin();it!=poolcAbility.end();++it){
        if(it->second){
            poolcAbilityList.push_back(it->first);
        }
    }
    return poolcAbilityList;
};

std::vector<int> GameSetting::getMorgo(){
    std::vector<int> morgoAbilityList;
    for(auto it = morgoAbility.begin();it!=morgoAbility.end();++it){
        if(it->second){
            morgoAbilityList.push_back(it->first);
        }
    }
    return morgoAbilityList;
};

std::vector<int> GameSetting::getMid(){
    std::vector<int> midAbilityList;
    for(auto it = midAbility.begin();it!=midAbility.end();++it){
        if(it->second){
            midAbilityList.push_back(it->first);
        }
    }
    return midAbilityList;
};

int GameSetting::getMorgoCount(){
    return this->morgoCount;
};

int GameSetting::getMidCount(){
    return this->midCount;
}

int GameSetting::getMissionCount(){
    return this->missionCount;
}

int GameSetting::getPoolcCount(){
    return this->poolcCount;
}

void GameSetting::setMorgoCount(int count){
    this->morgoCount=count;
}

void GameSetting::setMidCount(int count){
    this->midCount=count;
}

// void GameSetting::setMissionCount(int count){
//     this->missionCount = count;
// }

void GameSetting::setPoolcCount(int count){
    this->poolcCount=count;
}

void GameSetting::setKillCoolTime(int time){
    this->killCoolTime=time;
}
void GameSetting::setConferenceCoolTime(int time){
    this->conferenceCoolTime=time;
}
void GameSetting::setVotingTime(int time){
    this->votingTime = time;
}
void GameSetting::setDiscussionTime(int time){
    this->discussionTime = time;
}

int GameSetting::getKillCoolTime(){
    return this->killCoolTime;
}
int GameSetting::getConferenceCoolTime(){
    return this->conferenceCoolTime;
}
int GameSetting::getVotingTime(){
    return this->votingTime;
}
int GameSetting::getDiscussionTime(){
    return this->discussionTime;
}

void GameSetting::setRoleSetting(int id, bool setting){
    if(id<20){
        poolcAbility[id]=setting;
    }else if(id<40){
        morgoAbility[id]=setting;
    }else{
        midAbility[id]=setting;
    }
}
std::vector<std::map<int,bool>> GameSetting::getRoleSetting(){
    return {poolcAbility, morgoAbility, midAbility};
}

GameSetting::GameSetting(){
    this->poolcAbility.insert(std::make_pair(1,true));
    this->poolcAbility.insert(std::make_pair(2,true));
    this->poolcAbility.insert(std::make_pair(3,true));
    this->poolcAbility.insert(std::make_pair(4,true));
    this->poolcAbility.insert(std::make_pair(5,true));
    this->poolcAbility.insert(std::make_pair(6,true));
    this->poolcAbility.insert(std::make_pair(7,true));

    this->morgoAbility.insert(std::make_pair(21,true));
    this->morgoAbility.insert(std::make_pair(22,true));
    this->morgoAbility.insert(std::make_pair(23,true));
    this->morgoAbility.insert(std::make_pair(24,true));

    this->midAbility.insert(std::make_pair(41,true));
}