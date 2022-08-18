#ifndef GAMESETTING_H
#define GAMESETTING_H
#include <vector>

class GameSetting{
public:
    std::vector<int> poolcAbility={1,2,3,4,5,6,7};
    std::vector<int> morgoAbility={21,22,23,24};
    std::vector<int> midAbility={41};
    int morgoCount=2;
    int midCount=1;
    int missionCount=1;
public://getter, setter
    std::vector<int> getPoolc();
    std::vector<int> getMorgo();
    std::vector<int> getMid();
    int getMorgoCount();
    int getMidCount();
    void setMorgoCount(int count);
    void setMidCount(int count);
};
#endif