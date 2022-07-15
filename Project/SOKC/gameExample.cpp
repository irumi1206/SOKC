#include <iostream>
#include "jsonparser/jsonparser.cpp"
#include <vector>
#include <algorithm>

class GameController
{
public:
    void example(std::string in){
        Json::Value data=toJson(in);
        Json::Value toOne;
        Json::Value toAll;
        switch(data["Header"].asInt()){
            case 0:
            {
                toOne["Header"]=0;
                toOne["serverConnect"]=1;
                outOne(toOne);
                break;
            }
            case 1:
            {
                toOne["Header"]=1;
                toAll["Header"]=1;
                toOne["id"]=10039;
                toOne["playerList"]="[(10032,\"YM\",3),(10053,\"SH\",4)]";
                toAll["id"]=10039;
                toAll["name"]=data["name"].asString();
                outOne(toOne);
                outAll(toAll);
                break;
            }
            case 2:
            {
                toAll["Header"]=2;
                toAll["id"]=data["id"];
                toAll["colorId"]=data["colorId"].asInt();
                outAll(toAll);
                break;
            }
            case 5:
            {
                toAll["Header"]=5;
                toAll["id"]=data["id"];
                toAll["name"]="YM!";
                outAll(toAll);
                break;
            }
        }
    }

    void outOne(Json::Value out){
        std::cout<<"To One : "<<out.toStyledString()<<std::endl;
    }
    void outAll(Json::Value out){
        std::cout<<"To All : "<<out.toStyledString()<<std::endl;
    }
};