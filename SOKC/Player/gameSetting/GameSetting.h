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
    int poolcCount=4;
    int morgoCount=2;
    int midCount=1;
    int missionCount=1;
    int discussionTime;//
    int votingTime;//
    int conferenceCoolTime;//
    int killCoolTime;//
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

    int roleToInt(std::string role);
};
#endif