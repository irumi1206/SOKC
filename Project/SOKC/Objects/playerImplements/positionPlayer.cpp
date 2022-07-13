#include <iostream>
#include <tuple>

class SerializableVector3
{
public:
    float x;
    float y;
    SerializableVector3(float x=0, float y=0)
    {
        std::cout<<"Making new position"<<std::endl;
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