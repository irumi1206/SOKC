#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include <map>

//생성자, id는 임시적으로 100할당
Game::Game(){
    this->id=100;
}
//생성자, id를 받아 저장
Game::Game(int i){
    this->id=i;
}
//방의 id값을 가져오는 getter
int Game::getId(){
    return this->id;
}

int Game::getHost(){
    return hostId;
}

void Game::setHost(int id){
    this->hostId=id;
}

//roop문으로 플레이어 찾은 후 레퍼런스로 가져오기
Player& Game::findPlayer(int playerId){
    for(int i=0; i<playerList.size();i++){
        if(playerList[i].getId()==playerId){
            return playerList[i];
        }
    }
    Player temp=Player();
    Player& resultTemp=temp;
    return resultTemp;
}
//roop문으로 플레이어 찾은 후 제거
int Game::deletePlayer(int playerId){
    for(int i=0; i<playerList.size();i++){
        if(playerList[i].getId()==playerId){
            playerList.erase(playerList.begin()+i);
            return 1;
        }
    }
    return 0;
}
//플레이어 참가, 아이디는 tcp의 index로 지정해줌
int Game::joinPlayer(std::string name,int clientIndex){
    int result=1;
    int id=10000+clientIndex;
    // std::for_each(playerList.begin(), playerList.end(), [&](Player& player){
    //     if(player.getId()==id){
    //         result=0;
    //     }
    // });
    Player tempPlayer=Player(id,name);
    tempPlayer.setColor(emptyColor());
    if(playerList.size()==0){
        hostId=id;
    }
    playerList.push_back(tempPlayer);
    return id;
}
//플레이어 참가, input을 player로 받을 경우(사용하지 않음)
int Game::joinPlayer(Player playerIn){
    int tempId=playerIn.getId();
    int result=1;
    std::for_each(playerList.begin(), playerList.end(), [&](Player& player){
        if(player.getId()==tempId){
            result= 0;
        }
    });
    if(result==1){
        playerList.push_back(playerIn);
    }
    return result;
}
//플레이어 수
int Game::countPlayers(){
    return playerList.size();
}
//플레이어 리스트를 벡터로 받아오는 함수
std::vector<Player> Game::getPlayers(){
    return playerList;
}

void Game::assignRole(){

    int playercount=countPlayers();
    int poolcCount=playercount-molgoCount-midCount;
    std::vector<int> poolcAbility={1,2,3,4,5,6,7,8,9,10};
    std::vector<int> molgoAbility={20,21,22,23,24,25,26,27};
    std::vector<int> midAbility={40,41,42,43,44,45};
    
    srand(time(NULL));
    int i=0;
    while(playercount){
        int temp=rand()%playercount;
        int temp2;
        if(temp<poolcCount){
            int poolcAbilitySize=poolcAbility.size();
            temp2=rand()%poolcAbilitySize;
            playerList[i].setRole(poolcAbility[temp2]);
            poolcAbility.erase(poolcAbility.begin()+temp2);
            poolcCount-=1;
        }else if(temp<poolcCount+molgoCount){
            int molgoAbilitySize=molgoAbility.size();
            temp2=rand()%molgoAbilitySize;
            playerList[i].setRole(molgoAbility[temp2]);
            molgoAbility.erase(molgoAbility.begin()+temp2);
            molgoCount-=1;
        }else{
            int midAbilitySize=midAbility.size();
            temp2=rand()%midAbilitySize;
            playerList[i].setRole(midAbility[temp2]);
            midAbility.erase(midAbility.begin()+temp2);
            midCount-=1;
        }
        playercount-=1;
        i++;
    }
}

void Game::setMolgoCount(int molgo){
    this->molgoCount=molgo;
}
void Game::setMidCount(int mid){
    this->midCount=mid;
}
int Game::getMolgoCount(){
    return this->molgoCount;
}
int Game::getMidCount(){
    return this->midCount;
}
int Game::emptyColor(){
    int result=1;
    int i=1;
    while(result==1){
        result=0;
        i++;
        std::for_each(playerList.begin(), playerList.end(), [&](Player& player){
            if(player.getColor()==i){
                result=1;
            }
        });
    }
    return i;
}

void Game::setMissionCount(int missionCount){
    this->missionCount=missionCount;
}
int Game::getMissionCount(){
    return this->missionCount;
}

void Game::gameStart(){
    assignRole();
    std::for_each(playerList.begin(),playerList.end(),[&](Player& player){
        player.live();
        player.setStatus(Gaming);
        player.assignMission(missionCount);
    });
}
//투표
void Game::clearVoteStorage(){
    this->voteStorage.clear();
}

void Game::putVote(int votingPlayerId,int votedPlayerId){
    this->voteStorage.push_back(VotingStatus(votingPlayerId,votedPlayerId));
    Player& votingPlayer=findPlayer(votingPlayerId);
    Player& votedPlayer=findPlayer(votedPlayerId);
    if(votingPlayer.getTeam()!=votedPlayer.getTeam()){
        votingPlayer.addVotingAc(1);
    }else{
        votingPlayer.addVotingMi(1);
    }
}
std::map<int,int> Game::voteInfo(){
    std::map<int,int> storage;
    for(VotingStatus currentVote:voteStorage){
        storage[currentVote.votedPlayerId]++;
    };
    return storage;
}

int Game::calculateVoteDead(){
    std::map<int,int> storage=voteInfo();

    int id=-1;
    int count=0;
    for(auto current=storage.begin();current!=storage.end();current++){
        if(current->second==count) id=-1;
        else if(current->second>count){
            id=current->first;
            count=current->second;
        }
    }

    return id;
}

bool Game::checkEnd(){
    return false;
    //추가 해야 함.
}