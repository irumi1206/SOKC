#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "Game.h"

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
//플레이어 참가, 아이디는 랜덤으로 배정해줌
int Game::joinPlayer(std::string name){
    int result=1;
    int id;
    while(result){
        result=0;
        id=this->id*100+rand()%100;
        std::for_each(playerList.begin(), playerList.end(), [&](Player& player){
            if(player.getId()==id){
                result=1;
            }
        });
    }
    playerList.push_back(Player(id,name));
    
    return id;
}
//플레이어 참가, id를 임의적으로 할당할 때 사용
int Game::joinPlayer(int id,std::string name){
    int result=1;
    std::for_each(playerList.begin(), playerList.end(), [&](Player& player){
        if(player.getId()==id){
            result=0;
        }
    });
    if(result){
        playerList.push_back(Player(id,name));
    }
    return result;
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
            poolcList.push_back(playerList[i].getId());
            poolcCount-=1;
        }else if(temp<poolcCount+molgoCount){
            int molgoAbilitySize=molgoAbility.size();
            temp2=rand()%molgoAbilitySize;
            playerList[i].setRole(molgoAbility[temp2]);
            molgoAbility.erase(molgoAbility.begin()+temp2);
            molgoList.push_back(playerList[i].getId());
            molgoCount-=1;
        }else{
            int midAbilitySize=midAbility.size();
            temp2=rand()%midAbilitySize;
            playerList[i].setRole(midAbility[temp2]);
            midAbility.erase(midAbility.begin()+temp2);
            midList.push_back(playerList[i].getId());
            midCount-=1;
        }
        playercount-=1;
        i++;
    }
}

std::vector<int> Game::getPoolc(){
    return poolcList;
}
std::vector<int> Game::getMolgo(){
    return molgoList;
}
std::vector<int> Game::getMid(){
    return midList;
}

void Game::setMolgoCount(int molgo){
    this->molgoCount=molgo;
}
void Game::setMidCount(int mid){
    this->midCount=mid;
}