#include <iostream>
#include "playerObject.cpp"
#include <vector>
#include <ctime>
#include <unistd.h>

class Vote{
private:
    std::vector<Player> voterList;
    std::vector<int> voteCount;
    int startTime;
    int endTime;
    bool voteEnd=false;
public:
    Vote(std::vector<Player>& playerList){
        for(int i=0;i<playerList.size();i++){
            if(!playerList[i].isDie()){
                voterList.push_back(playerList[i]);
                voteCount.push_back(0);
            }
        }
    }
    Vote(){

    }
    void voteStart(int second){
        this->startTime=time(NULL);
        this->endTime=startTime+second;
    }
    void vote(Player voter,Player voted){
        
    }
    int voteTime(){
        return this->endTime-time(NULL);
    }
    
};