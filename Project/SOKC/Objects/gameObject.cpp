#include <iostream>
#include "playerObject.cpp"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "jsonparser/jsonparser.cpp"

class Game{
public: 
    int id;
    std::vector<Player> playerList;
    Player host;
    int aliveCount;
    int deadCount;
public:
    Game(){
        this->id=100;
    }
    Game(int i){
        this->id=i;
    }
    int getId(){
        return this->id;
    }
    int playerCount(){
        return playerList.size();
    }
    Player& findPlayer(int playerId){
        for(int i=0; i<playerList.size();i++){
            if(playerList[i].getId()==playerId){
                return playerList[i];
            }
        }
        Player temp=Player();
        Player& resultTemp=temp;
        return resultTemp;
    }
    int deletePlayer(int playerId){
        for(int i=0; i<playerList.size();i++){
            if(playerList[i].getId()==playerId){
                playerList.erase(playerList.begin()+i);
                return 1;
            }
        }
        return 0;
    }
    int joinPlayer(std::string name){
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
    int joinPlayer(Player playerIn){
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
    int countPlayers(){
        return playerList.size();
    }
    std::vector<Player> getPlayers(){
        return playerList;
    }
};