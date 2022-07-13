#include <iostream>

class PlayerScore
{
public:
    int voting_valid;
    int voting_invalid;
    int killScore;
    int missionScore;
    int POTG;
    int SOTG;
    PlayerScore(){
        voting_valid=0;
        voting_invalid=0;
        killScore=0;
        missionScore=0;
        POTG=0;
        SOTG=0;
    }
    PlayerScore(const PlayerScore& other){
        this->voting_valid=other.voting_valid;
        this->voting_invalid=other.voting_invalid;
        this->killScore=other.killScore;
        this->missionScore=other.missionScore;
        this->POTG=other.POTG;
        this->SOTG=other.SOTG;
    }
    float votingAccuracy(){
        if(voting_valid==0){
            return (float)0;
        }
        return (float)voting_valid/((float)voting_valid+(float)voting_invalid);
    }
    int getKill(){
        return killScore;
    }
    int getMission(){
        return missionScore;
    }
    void addKill(int score){
        killScore+=score;
    }
    void addMission(int score){
        missionScore+=score;
    }
    void reset(){
        voting_valid=0;
        voting_invalid=0;
        killScore=0;
        missionScore=0;
        POTG=0;
        SOTG=0;
    }
    void addVotingAc(int score){
        this->voting_valid+=score;
    }
    void addVotingMi(int score){
        this->voting_invalid+=score;
    }
    void addPOTG(int score){
        this->POTG+=score;
    }
    void addSOTG(int score){
        this->SOTG+=score;
    }
    int getPOTG(){
        return POTG;
    }
    int getSOTG(){
        return SOTG;
    }
};