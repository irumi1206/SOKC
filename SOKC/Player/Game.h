#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "Player.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "VotingStatus.h"
#include <map>

class Game{
public: 
    int id;//방 id
    std::vector<Player> playerList;//방에 참여해 있는 플레이어들을 담는 구조체
    int hostId;
    int molgoCount=2;
    int midCount=2;
    int missionCount=3;

    //투표 추가
    std::vector<VotingStatus> voteStorage;
    void clearVoteStorage();
    void putVote(int votingPlayerId,int votedPlayerId);
    int calculateVoteDead();
    //

public:
    //게임 시작 함수
    void gameStart();
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
    void setMolgoCount(int molgo);
    void setMidCount(int mid);
    void setMissionCount(int missionCount);
    int getMolgoCount();
    int getMidCount();
    int getMissionCount();
    void assignRole();
    // std::vector<int> getPoolc();
    // std::vector<int> getMolgo();
    // std::vector<int> getMid();
    int emptyColor();
    bool checkEnd();
    std::map<int,int> voteInfo();
};
#endif