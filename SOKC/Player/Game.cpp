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
    for(int i=0;i<readyRoom.size();i++){
        if(readyRoom[i].getId()==playerId){
            readyRoom.erase(readyRoom.begin()+i);
            return 1;
        }
    }
    return 0;
}
//플레이어 참가, 아이디는 tcp의 index로 지정해줌
int Game::joinPlayer(std::string name,int clientId){
    int result=1;
    // std::for_each(playerList.begin(), playerList.end(), [&](Player& player){
    //     if(player.getId()==id){
    //         result=0;
    //     }
    // });
    Player tempPlayer=Player(clientId,name);
    tempPlayer.setColor(emptyColor());
    if(readyRoom.size()==0){
        hostId=clientId;
    }
    playerList.push_back(tempPlayer);
    readyRoom.push_back(tempPlayer);
    return clientId;
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
void Game::assignMission(){
    srand(time(NULL));
    std::vector<int> missions = gameSetting.missionVector;
    int size=missions.size();
    std::for_each(playerList.begin(),playerList.end(),[&](Player& player){
        if(player.roleflag.role==7){
            int temp=rand()%missions.size();
            player.addMission(missions[temp]);
        }
        int temp=rand()%missions.size();
        player.addMission(missions[temp]);
    });
}
void Game::assignRole(){

    int playercount=countPlayers();
    int morgoCount = getMorgoCount();
    int midCount = getMidCount();
    int poolcCount=playercount-morgoCount-midCount;
    if(poolcCount<0){
        poolcCount=0;
    }

    std::vector<int> poolcAbility=gameSetting.getPoolc();
    std::vector<int> morgoAbility=gameSetting.getMorgo();
    std::vector<int> midAbility=gameSetting.getMid();
    while(poolcCount>poolcAbility.size()){
        poolcAbility.push_back(0);
    }
    while(morgoCount>morgoAbility.size()){
        morgoAbility.push_back(20);
    }
    
    srand(time(NULL));
    int i=0;
    while(playercount){
        int temp=rand()%playercount;
        int temp2;
        if(temp<poolcCount){
            temp2=rand()%poolcAbility.size();
            playerList[i].setRole(poolcAbility[temp2]);
            poolcAbility.erase(poolcAbility.begin()+temp2);
            poolcCount-=1;
        }else if(temp<poolcCount+morgoCount){
            temp2=rand()%morgoAbility.size();
            playerList[i].setRole(morgoAbility[temp2]);
            morgoAbility.erase(morgoAbility.begin()+temp2);
            morgoCount-=1;
        }else{
            temp2=rand()%midAbility.size();
            playerList[i].setRole(midAbility[temp2]);
            midAbility.erase(midAbility.begin()+temp2);
            midCount-=1;
        }
        playercount-=1;
        i++;
    }
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



void Game::gameStart(){
    assignRole();
    readyRoom.clear();
    std::for_each(playerList.begin(),playerList.end(),[&](Player& player){
        playerLiveList.push_back(player.getId());
        player.live();
        player.setStatus(Gaming);
    });
}
void Game::roundStart(){
    assignMission();
    std::for_each(playerList.begin(),playerList.end(),[&](Player& player){
        if(player.roleflag.role==22){
            player.roleflag.abilityCount=1;
        }else if(player.roleflag.role==24){
            player.roleflag.abilityCount=1;
        }
    });
    gameSetting.hackedMission=-1;
    gameSetting.hackerId=-1;
}
//투표
void Game::clearVoteStorage(){
    this->voteStorage.clear();
}

bool Game::putVote(int votingPlayerId,int votedPlayerId){
    Player& votingPlayer=findPlayer(votingPlayerId);
    Player& votedPlayer=findPlayer(votedPlayerId);
    if(votingPlayer.voteCount>0){
        votingPlayer.voteCount-=1;
        this->voteStorage.push_back(VotingStatus(votingPlayerId,votedPlayerId));
        if(votingPlayer.getTeam()!=votedPlayer.getTeam()){
            votingPlayer.addVotingAc(1);
        }else{
            votingPlayer.addVotingMi(1);
        }
        return true;
    }
    return false;
}

std::map<int,int> Game::voteInfo(){
    std::map<int,int> storage;
    for(VotingStatus currentVote:voteStorage){
        storage[currentVote.votedPlayerId]++;
    };
    return storage;
}

int Game::calculateVoteDead(std::map<int,int> storage){
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


//게임 설정 (count)
void Game::setMorgoCount(int morgo){
    this->gameSetting.setMorgoCount(morgo);
}
void Game::setMidCount(int mid){
    this->gameSetting.setMidCount(mid);
}
void Game::setPoolcCount(int count){
    this->gameSetting.setPoolcCount(count);
}

int Game::getPoolcCount(){
    return this->gameSetting.getPoolcCount();
}

int Game::getMorgoCount(){
    return this->gameSetting.getMorgoCount();
}

int Game::getMidCount(){
    return this->gameSetting.getMidCount();
}

int Game::getMissionCount(){
    return this->gameSetting.getMissionCount();
}
//게임 설정 (cooltime)
void Game::setKillCoolTime(int time){
    this->gameSetting.setKillCoolTime(time);
}
void Game::setConferenceCoolTime(int time){
    this->gameSetting.setConferenceCoolTime(time);
}
void Game::setVotingTime(int time){
    this->gameSetting.setVotingTime(time);
}
void Game::setDiscussionTime(int time){
    this->gameSetting.setDiscussionTime(time);
}

int Game::getKillCoolTime(){
    return this->gameSetting.getKillCoolTime();
}
int Game::getConferenceCoolTime(){
    return this->gameSetting.getConferenceCoolTime();
}
int Game::getVotingTime(){
    return this->gameSetting.getVotingTime();
}
int Game::getDiscussionTime(){
    return this->gameSetting.getDiscussionTime();
}

//게임 설정 (직업)
void Game::setRoleSettingChange(int id, bool set){
    this->gameSetting.setRoleSetting(id,set);
}
std::vector<std::map<int,bool>> Game::getRoleSettingChange(){
    return this->gameSetting.getRoleSetting();
}

void Game::voteEndingQueueAdd(Json::Value data){
    this->voteEndingQueue.push(data);
}

//void Game::inGameListAdder(int role, Player player){
//
//}

//void Game::inGameListFlush(){
//    this->inGameList.clear;
//}

int Game::isGameEnd(){//게임이 끝났는지 체크, 1은 poolc, 2는 morgo, 3은 중립
    int alivePoolC=0;
    int aliveMorgo=0;
    int aliveMid=0;
    std::for_each(playerList.begin(),playerList.end(),[&](Player& player){
        if(!player.isDie()){
            if(player.getTeam()==PoolC){
                alivePoolC+=1;
            }else if(player.getTeam()==Morgo){
                aliveMorgo+=1;
            }else{
                aliveMid+=1;
            }
        }
    });
    if(aliveMorgo==0){
        return 1;
    }else if((alivePoolC+aliveMid)<=aliveMorgo){
        return 2;
    }else{
        return 0;
    }
}

bool Game::isBenefit(){
    bool check=true;
    std::for_each(playerList.begin(),playerList.end(),[&](Player& player){
        if(player.getTeam()==PoolC && player.countMission() && !player.isDie()){
            check=false;
        }
    });
    return check;
}

Json::Value Game::MVP(){
    std::vector<int> mvps={1,2,3,4,5};
    Json::Value out;
    Json::Value MVPS;
    srand(time(NULL));
    for(int i=0;i<3;i++){
        Json::Value mvp;
        int index=rand()%mvps.size();
        switch(mvps[index]){
            case 1://평균 미션 완료 순위
            {
                int id = missionClearTOP();
                mvp["type"]=1;
                mvp["id"]=id;
                mvp["score"]=findPlayer(id).score.averageMissionClear();
                MVPS["MVP"].append(mvp);
                break;
            }
            case 2://투표 정확도
            {
                int id = votingAccTOP();
                mvp["type"]=2;
                mvp["id"]=id;
                mvp["score"]=(int)(findPlayer(id).score.votingAccuracy()*100.0);
                MVPS["MVP"].append(mvp);
                break;
            }
            case 3://베네핏 최다 획득
            {
                int id = benefitTOP();
                mvp["type"]=3;
                mvp["id"]=id;
                mvp["score"]=findPlayer(id).score.benefitTaken;
                MVPS["MVP"].append(mvp);
                break;
            }
            case 4://최대 킬
            {
                int id = killScoreTOP();
                mvp["type"]=4;
                mvp["id"]=id;
                mvp["score"]=findPlayer(id).score.killScore;
                MVPS["MVP"].append(mvp);
                break;
            }
            case 5://수다왕
            {
                int id = talkingTOP();
                mvp["type"]=5;
                mvp["id"]=id;
                mvp["score"]=0;
                MVPS["MVP"].append(mvp);
                break;
            }
            default:
            break;
        }
        mvps.erase(mvps.begin()+index);
    }
    return MVPS;
}

int Game::missionClearTOP(){
    int id=0;
    int score=1000;
    std::for_each(playerList.begin(),playerList.end(),[&](Player player){
        if(player.score.averageMissionClear()<score){
            id=player.getId();
            score=player.score.averageMissionClear();
        }
    });
    return id;
}

int Game::votingAccTOP(){
    int id=0;
    float score=0;
    std::for_each(playerList.begin(),playerList.end(),[&](Player player){
        if(player.votingAccuracy()>score){
            id=player.getId();
            score=player.votingAccuracy();
        }
    });
    return id;
}

int Game::benefitTOP(){
    int id=0;
    int score=0;
    std::for_each(playerList.begin(),playerList.end(),[&](Player player){
        if(player.score.benefitTaken>score){
            id=player.getId();
            score=player.score.benefitTaken;
        }
    });
    return id;
}

int Game::killScoreTOP(){
    int id=0;
    int score=0;
    std::for_each(playerList.begin(),playerList.end(),[&](Player player){
        if(player.getTeam()==Morgo && player.getKillScore()>score){
            id=player.getId();
            score=player.getKillScore();
        }
    });
    return id;
}

int Game::talkingTOP(){
    int id=0;
    int score=0;
    //투표 통화쪽 구현 필요
    return 1;
}
