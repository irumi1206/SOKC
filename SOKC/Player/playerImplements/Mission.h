#ifndef MISSION_H
#define MISSION_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

//mission class for playerObject
class Mission{
    
    private:
    //미션을 담아두는 vector
        std::vector<int> missionVector;
        
    public:
        //생성자, 미션벡터를 초가회 함.
        Mission();
        //미션벡터에 미션을 추가함
        void add(int missionId);
        //미션벡터를 반환하는 get함수
        std::vector<int> get();
        //자신에게 할당된 미션의 개수를 나타내는 함수
        int count();
        //미션 초기화 함수
        void reset();
        //미션이 끝나면 호출 할 함수
        void finish(int missionId);
};
#endif