#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class Mission{
    
private:
    std::vector<int> missionVector;
    
public:
static std::vector<std::vector<int>> combination;
    Mission(){
        missionVector.clear();
        srand((unsigned int)time(NULL));
    }
    void add(int MissionId){
        missionVector.push_back(MissionId);
    }
    std::vector<int> get(){
        return missionVector;
    }
    int count(){
        return missionVector.size();
    }
    void clear(){
        missionVector.clear();
    }
    void finish(int missionId){
        int index=0;
        for_each(missionVector.begin(), missionVector.end(), [&](int&mission){
            if(missionId==mission){
                missionVector.erase(missionVector.begin()+index);
            }
            index+=1;
        });
    }
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
        std::cout<<"assigned successfully"<<std::endl;
    }
};

std::vector<std::vector<int>> Mission::combination={{1,2,3},{4,5,6},{7,8,9},{10,11,12}};