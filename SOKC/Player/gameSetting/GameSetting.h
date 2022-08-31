#ifndef GAMESETTING_H
#define GAMESETTING_H
#include <vector>
#include <tuple>
#include <map>
#include <string>

class GameSetting{
public:
    std::map<int,bool> poolcAbility;
    std::map<int,bool> morgoAbility;
    std::map<int,bool> midAbility;
    std::vector<int> missionVector={2,6,10,11,12,13,15};
    int poolcCount=4; //4~7
    int morgoCount=1; //1~4
    int midCount=0;   //0~1
    int missionCount=1;
    int discussionTime=30;//최소 10, 최대 60
    int votingTime=30;//최소 10, 최대 60
    int conferenceCoolTime=25;//최소 10, 최대 60
    int killCoolTime=30;//최소 10, 최대 60
    int hackedMission=-1;
    int hackerId=-1;
    GameSetting();
public://getter, setter
    std::vector<int> getPoolc();
    std::vector<int> getMorgo();
    std::vector<int> getMid();
    int getMorgoCount();
    int getMidCount();
    int getPoolcCount();
    int getMissionCount();
    void setMorgoCount(int count);
    void setMidCount(int count);
    void setPoolcCount(int count);

    void setKillCoolTime(int time);
    void setConferenceCoolTime(int time);
    void setVotingTime(int time);
    void setDiscussionTime(int time);
    
    int getKillCoolTime();
    int getConferenceCoolTime();
    int getVotingTime();
    int getDiscussionTime();

    void setRoleSetting(int id, bool setting);
    std::vector<std::map<int,bool>> getRoleSetting();

};
#endif