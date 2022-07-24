#include <iostream>
#include <tuple>
#include "Position.h"

SerializableVector3::SerializableVector3(float x=0, float y=0)
{
    this->x=x;
    this->y=y;
};
SerializableVector3::SerializableVector3()
{
    this->x=0;
    this->y=0;
};
void SerializableVector3::setPosition(float x,float y){
    this->x=x;
    this->y=y;
};

std::tuple<float,float> SerializableVector3::getPosition(){
    return std::make_tuple(x,y);
};