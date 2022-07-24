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
//미션을 할당하는 함수, 랜덤함수의 시드값을 넣어야 하기 때문에 (시간)+(자신의 id)를 시드로 갖는다
void Mission::assign(int count, int id){
    int groupLength=combination.size(); //3
    int selected[count];                // {0,0,0}
    int size=0;                         //0
    int isSame;                         //
    int tmp2;                           //
    int tmp;                            //
    srand(time(NULL)+id);
    while(size<count){
        tmp=rand()%groupLength+1;
        isSame=0;
        for(int i=0;i<size;i++){
            if(tmp==selected[i]){
                isSame=1;
                break;
            }
        }
        if(isSame==0){
            selected[size]=tmp;
            tmp2=combination[tmp-1].size();
            this->missionVector.push_back(combination[tmp-1][rand()%tmp2]);
            size++;
        }
    }
};
std::vector<std::vector<int>> Mission::combination={{1,2,3},{4,5,6},{7,8,9},{10,11,12}};