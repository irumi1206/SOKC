#include <iostream>
#include "Score.h"

PlayerScore::PlayerScore(){
    voting_valid=0;
    voting_invalid=0;
    killScore=0;
    missionScore=0;
    POTG=0;
    SOTG=0;
    benefitTaken=0;
};
PlayerScore::PlayerScore(const PlayerScore& other){
    this->voting_valid=other.voting_valid;
    this->voting_invalid=other.voting_invalid;
    this->killScore=other.killScore;
    this->missionScore=other.missionScore;
    this->POTG=other.POTG;
    this->SOTG=other.SOTG;
};
float PlayerScore::votingAccuracy(){
    if(voting_valid==0){
        return (float)0;
    }
    return (float)voting_valid/((float)voting_valid+(float)voting_invalid);
};
int PlayerScore::getKill(){
    return killScore;
};
int PlayerScore::getMission(){
    return missionScore;
};
void PlayerScore::addKill(int score){
    killScore+=score;
};
void PlayerScore::addMission(int score){
    missionScore+=score;
};
void PlayerScore::reset(){
    voting_valid=0;
    voting_invalid=0;
    killScore=0;
    missionScore=0;
    POTG=0;
    SOTG=0;
};
void PlayerScore::addVotingAc(int score){
    this->voting_valid+=score;
};
void PlayerScore::addVotingMi(int score){
    this->voting_invalid+=score;
};
void PlayerScore::addPOTG(int score){
    this->POTG+=score;
};
void PlayerScore::addSOTG(int score){
    this->SOTG+=score;
};
int PlayerScore::getPOTG(){
    return POTG;
};
int PlayerScore::getSOTG(){
    return SOTG;
};

float PlayerScore::averageMissionClear(){
    if(missionClearScore.size()==0){
        return 100;
    }
    int sum=0;
    std::for_each(missionClearScore.begin(),missionClearScore.end(),[&](int score){
        sum+=score;
    });
    return (float)sum/(float)missionClearScore.size();
}