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
    Mission(){
        missionVector.clear();
    }
    //미션벡터에 미션을 추가함
    void add(int missionId){
        missionVector.push_back(missionId);
    }
    //미션벡터를 반환하는 get함수
    std::vector<int> get(){
        return missionVector;
    }
    //자신에게 할당된 미션의 개수를 나타내는 함수
    int count(){
        return missionVector.size();
    }
    //미션 초기화 함수
    void reset(){
        missionVector.clear();
    }
    //미션이 끝나면 호출 할 함수
    void finish(int missionId){
        int index=0;
        for_each(missionVector.begin(), missionVector.end(), [&](int&mission){
            if(missionId==mission){
                missionVector.erase(missionVector.begin()+index);
            }
            index+=1;
        });
    }
    //미션을 할당하는 함수, 랜덤함수의 시드값을 넣어야 하기 때문에 (시간)+(자신의 id)를 시드로 갖는다
    void assign(int count, int id){
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
    }
};
std::vector<std::vector<int>> Mission::combination={{1,2,3},{4,5,6},{7,8,9},{10,11,12}};