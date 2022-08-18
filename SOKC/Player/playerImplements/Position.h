#ifndef POSITION_H
#define POSITION_H
#include <iostream>
#include <tuple>
#include <vector>

//플레이어의 위치 정보를 저장하는 클래스
class SerializableVector3
{
    public:
        static std::vector<std::vector<float>> startPosition;
        float x;
        float y;
        SerializableVector3();
        SerializableVector3(float x, float y);
        void setPosition(float x,float y);
        std::tuple<float,float> getPosition();
        void randomPosition(int id);
};
#endif