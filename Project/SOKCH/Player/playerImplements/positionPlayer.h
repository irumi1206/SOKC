#ifndef POSITIONPLAYER_H
#define POSITIONPLAYER_H
#include <iostream>
#include <tuple>

//플레이어의 위치 정보를 저장하는 클래스
class SerializableVector3
{
public:
    float x;
    float y;
    SerializableVector3();
    SerializableVector3(float x, float y);
    void setPosition(float x,float y);
    std::tuple<float,float> getPosition();
};
#endif