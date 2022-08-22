#include <iostream>
#include <tuple>
#include "Position.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

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

void SerializableVector3::randomPosition(int id){
    srand(time(NULL)+id);
    int startPositionLength = startPosition.size();
    int temp;
    temp=rand()%startPositionLength+1;
    this->x = startPosition[temp][0];
    this->y = startPosition[temp][1];
}

std::vector<std::vector<float>> SerializableVector3::startPosition={{0.0,0.0},{30.1,40.2}};