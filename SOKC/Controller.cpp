#include <iostream>
#include <vector>
#include <algorithm>
#include "Controller.h"

Controller::Controller(){
    this->game=Game();
};
    Json::Value Controller::control(std::string in){
        Json::Value datas=toJson(in);
        Json::Value out;
        Json::Value data=datas["Content"];
        switch(datas["Header"].asInt()){
            case 0:
            {
                Json::Value toOne;
                toOne["Header"]=0;
                toOne["Content"];
                if(game.getId()==data["roomId"].asInt() && game.countPlayers()<16){
                    toOne["Content"]["serverConnect"]=1;
                }else{
                    toOne["Content"]["serverConnect"]=-1;
                }
                out["toOne"]=toOne;
                return out;
            }
            case 1:
            {
                Json::Value toOne;
                Json::Value toAll;
                toOne["Content"];
                toAll["Content"];
                toOne["Header"]=1;
                toAll["Header"]=1;
                std::string name=data["name"].asString();
                toOne["Content"]["playerList"]=playerInfo();
                int id=game.joinPlayer(name);
                toOne["Content"]["id"]=10003;//id로 바꿔야 함
                toAll["Content"]["id"]=10003;//id로 바꿔야 함
                toAll["Content"]["name"]=name;
                out["toOne"]=toOne;
                out["toAll"]=toAll;
                return out;

            }
            case 2:
            {
                Json::Value toAll;
                toAll["Header"]=2;
                toAll["Content"];
                int id=data["id"].asInt();
                int colorId=data["colorId"].asInt();
                game.findPlayer(id).setColor(colorId);
                toAll["Content"]["id"]=id;
                toAll["Content"]["colorId"]=colorId;
                out["toAll"]=toAll;
                return out;
            }
            case 5:
            {
                Json::Value toAll;
                toAll["Header"]=5;
                toAll["Content"];
                int id=data["id"].asInt();
                game.deletePlayer(id);
                toAll["Content"]["id"]=id;
                out["toAll"]=toAll;
                return out;
            }
            case 30:
            {
                game.findPlayer(data["id"].asInt()).setPosition(data["x"].asFloat(),data["y"].asFloat());
                return out;
            }
            case 31:
            {
                int id=data["id"].asInt();
                int victim=data["victim"].asInt();
                game.findPlayer(victim).dead();
                game.findPlayer(id).addKillScore(1);
                Json::Value toOne;
                Json::Value toAll;
                toOne["Content"];
                toAll["Content"];
                toOne["Header"]=31;
                toAll["Header"]=31;
                toOne["Content"]["id"]=id;
                toAll["Content"]["id"]=victim;
                out["toOne"]=toOne;
                out["toAll"]=toAll;
                return out;
            }
            case 32:
            {
                int id=data["id"].asInt();
                int missionId=data["missionId"].asInt();
                game.findPlayer(id).finishMission(missionId);
                game.findPlayer(id).addMissionScore(1);
                return out;
            }
            default:
            {
                return out;
            }
        }
    };
    Json::Value Controller::positions(){
        Json::Value out;
        Json::Value toAll;
        toAll["Header"]=30;
        toAll["Content"];
        int i=0;
        int max=game.countPlayers()-1;
        std::string positions="[";
        std::for_each(game.playerList.begin(), game.playerList.end(), [&](Player& player){
            positions+="(";
            positions+="\"id\":"+std::to_string(player.getId());
            std::tuple<float,float> position=player.getPosition();
            positions+=",\"x\":"+std::to_string(std::get<0>(position));
            positions+=",\"y\":"+std::to_string(std::get<1>(position));
            if(i==max){
                positions+=")";
            }else{
                positions+="),";
            }
            i++;
        });
        positions+="]";
        toAll["Content"]["playerPositions"]=positions;
        out["toAll"]=toAll;
        return out;
    };
    std::string Controller::playerInfo(){
        std::string players="[";
        int i=0;
        int max=game.countPlayers()-1;
        std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
            players+="(";
            players+="\"id\":"+std::to_string(player.getId());
            players+=",\"name\":\""+player.getName()+"\"";
            players+=",\"color\":"+std::to_string(player.getColor());
            if(i==max){
                players+=")";
            }else{
                players+="),";
            }
            i++;
        });
        players+="]";
        return players;
    }