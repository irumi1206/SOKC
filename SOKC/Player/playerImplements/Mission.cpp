#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "Mission.h"


Mission::Mission(){
    missionVector.clear();
};
//미션벡터에 미션을 추가함
void Mission::add(int missionId){
    missionVector.push_back(missionId);
};
//미션벡터를 반환하는 get함수
std::vector<int> Mission::get(){
    return missionVector;
};
//자신에게 할당된 미션의 개수를 나타내는 함수
int Mission::count(){
    return missionVector.size();
};
//미션 초기화 함수
void Mission::reset(){
    missionVector.clear();
};
//미션이 끝나면 호출 할 함수
void Mission::finish(int missionId){
    int index=0;
    for_each(missionVector.begin(), missionVector.end(), [&](int&mission){
        if(missionId==mission){
            missionVector.erase(missionVector.begin()+index);
        }
        index+=1;
    });
};