#ifndef POLITICIAN_H
#define POLITICIAN_H
#include "/home/ubuntu/GameProject/SOKC-branch/Player/Player.h"
#include "/home/ubuntu/GameProject/SOKC-branch/jsonParser/JsonParser.h"

class Politician:public Player{
public:
    Politician(int id, std::string name);
    void benefit();
};


#endif