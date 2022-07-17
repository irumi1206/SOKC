#include <iostream>
#include <tuple>

//플레이어의 위치 정보를 저장하는 클래스
class SerializableVector3
{
public:
    float x;
    float y;
    SerializableVector3(float x=0, float y=0)
    {
        this->x=x;
        this->y=y;
    }
    void setPosition(float x,float y){
        this->x=x;
        this->y=y;
    }
    
    std::tuple<float,float> getPosition(){
        return std::make_tuple(x,y);
    }
};