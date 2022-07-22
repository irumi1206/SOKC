#ifndef MISSIONPLAYER_H
#define MISSIONPLAYER_H
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
//같은 방에 있는 미션을 구분하는 벡터, {{1,2,3},{4,5,6},{7,8,9},{10,11,12}}에서 1,2,3은 같은 방에 존재하여 같이 할당되면 안되는 미션임.
static std::vector<std::vector<int>> combination;
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
    //미션을 할당하는 함수, 랜덤함수의 시드값을 넣어야 하기 때문에 (시간)+(자신의 id)를 시드로 갖는다
    void assign(int count, int id);
};
#endif