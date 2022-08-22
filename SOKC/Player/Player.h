#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "playerImplements/Score.h"
#include "playerImplements/Mission.h"
#include "playerImplements/Role.h"

enum PlayStatus{
    Ready,
    Gaming
};

class Player
{
public:
    PlayStatus status;
    std::string name;
    int id;
    CharacterRoleFlag roleflag;//직업(역할)
    bool die=false;//살았는지 죽었는지
    PlayerScore score;//점수 object
    Mission mission;//미션 object
    int color;//색 확인
    int benefit=0;
    int voteCount=0;
public://initializer
    Player(int id, std::string name);
    Player();
public:
    bool isDie();
    int dead();
    void live();
public: //getter & setter
    int getVoteCount();
    std::string getName();
    void setName(std::string name);
    int getId();
    //id는 바꿀 수 없으므로 setId는 만들어놓지 않음.
    int getColor();
    void setColor(int color);
    void setStatus(PlayStatus status);
    PlayStatus getPlayStatus();
public://role
    Team getTeam();
    int getRole();
    void setRole(int role);
    
public: //Mission
    //강제로 미션 한개 추가
    void addMission(int missionId);
    //할당된 미션 가져오기
    std::vector<int> getMission();
    //남은 미션 개수
    int countMission();
    //할당된 미션 없얘기 (flush)
    void resetMission();
    //미션 클리어
    void finishMission(int missionId);
public: //score
    //killscore추가
    void addKillScore(int scores);
    //missionscore추가
    void addMissionScore(int scores);
    //정확히 투표 했을 경우(accurate)
    void addVotingAc(int scores);
    //잘못 투표했을 경우(miss)
    void addVotingMi(int scores);
    //POTG점수 추가
    void addPOTGScore(int scores);
    //SOTG점수 추가
    void addSOTGScore(int scores);
    //점수 초기화
    void clearScore();
    //미션점수 가져오기
    int getMissionScore();
    //킬점수 가져오기
    int getKillScore();
    int getPOTGScore();
    int getSOTGScore();
    //투표정확도 가져오기(float으로 출력)
    float votingAccuracy();
};

#endif