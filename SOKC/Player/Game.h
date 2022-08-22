#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "Player.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "VotingStatus.h"
#include <map>
#include "/home/ubuntu/GameProject/SOKC/jsonParser/JsonParser.h"
#include "gameSetting/GameSetting.h"
#include <queue>

class Game{
public: 
    GameSetting gameSetting;
    int id;//방 id
    std::vector<Player> playerList;//방에 참여해 있는 플레이어들을 담는 구조체
    //std::vector<Player *> inGameList;
    int hostId;
    //투표 추가
    std::vector<VotingStatus> voteStorage;
    void clearVoteStorage();
    bool putVote(int votingPlayerId,int votedPlayerId);
    int calculateVoteDead(std::map<int,int> storage);
    std::vector<int> playerLiveList;
    std::vector<int> playerDeadList;
    //투표종료 queue
    std::queue<Json::Value> voteEndingQueue;//저격수, 변덕쟁이용
    std::queue<Json::Value> voteStartQueue;//군기반장용

public:
    //게임 시작 함수
    void gameStart();
    //라운드 시작
    void roundStart();
    //생성자, id는 임시적으로 100할당
    Game();

    //생성자, id를 받아 저장
    Game(int i);

    //방의 id값을 가져오는 getter
    int getId();

    //호스트 아이디 가져오기
    int getHost();
    void setHost(int id);

    //roop문으로 플레이어 찾은 후 레퍼런스로 가져오기
    Player& findPlayer(int playerId);

    //roop문으로 플레이어 찾은 후 제거
    int deletePlayer(int playerId);

    //플레이어 참가, 아이디는 랜덤으로 배정해줌
    int joinPlayer(std::string name, int clientIndex);

    //플레이어 참가, input을 player로 받을 경우(사용하지 않음)
    int joinPlayer(Player playerIn);

    //플레이어 수
    int countPlayers();
    
    //플레이어 리스트를 벡터로 받아오는 함수
    std::vector<Player> getPlayers();
    //게임 설정 (count)
    void setMorgoCount(int morgo);
    void setMidCount(int mid);
    void setPoolcCount(int count);
    int getPoolcCount();
    int getMorgoCount();
    int getMidCount();
    int getMissionCount();

    //게임 설정 (cooltime)
    void setKillCoolTime(int time);
    void setConferenceCoolTime(int time);
    void setVotingTime(int time);
    void setDiscussionTime(int time);
    
    int getKillCoolTime();
    int getConferenceCoolTime();
    int getVotingTime();
    int getDiscussionTime();

    //게임 설정(직업)
    void setRoleSettingChange(int id, bool set);
    std::vector<std::map<int,bool>> getRoleSettingChange();

    void assignRole();
    // std::vector<int> getPoolc();
    // std::vector<int> getMolgo();
    // std::vector<int> getMid();
    void assignMission();
    int emptyColor();
    std::map<int,int> voteInfo();

    //queue 
    void voteEndingQueueAdd(Json::Value data);

    //void inGameListAdder(int role, Player player);
    //void inGameListFlush();
    //게임 종료 여부 확인
    int isGameEnd();
    //베네핏 획득 여부 확인
    bool isBenefit();//1은 poolc, 2는 morgo, 3은 mid
    Json::Value MVP();
    int missionClearTOP();
    int votingAccTOP();
    int benefitTOP();
    int killScoreTOP();
    int talkingTOP();
};
#endif