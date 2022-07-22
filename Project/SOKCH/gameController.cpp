#include <iostream>
#include <vector>
#include <algorithm>
#include "gameController.h"

Controller::Controller(){
    this->game=Game();
};
    Json::Value Controller::control(std::string in){
        Json::Value data=toJson(in);
        Json::Value out;
        switch(data["Header"].asInt()){
            case 0:
            {
                Json::Value toOne;
                toOne["Header"]=0;
                if(game.getId()==data["roomId"].asInt() && game.countPlayers()<16){
                    toOne["serverConnect"]=1;
                }else{
                    toOne["serverConnect"]=-1;
                }
                out["toOne"]=toOne;
                return out;
            }
            case 1:
            {
                Json::Value toOne;
                Json::Value toAll;
                toOne["Header"]=1;
                toAll["Header"]=1;
                std::string name=data["name"].asString();
                int id=game.joinPlayer(name);
                toOne["id"]=10003;//id로 바꿔야 함
                toOne["playerList"]=true;//만들어야 함.
                toAll["id"]=10003;//id로 바꿔야 함
                toAll["name"]=name;
                out["toOne"]=toOne;
                out["toAll"]=toAll;
                return out;

            }
            case 2:
            {
                Json::Value toAll;
                toAll["Header"]=2;
                int id=data["id"].asInt();
                int colorId=data["colorId"].asInt();
                game.findPlayer(id).setColor(colorId);
                toAll["id"]=id;
                toAll["colorId"]=colorId;
                out["toAll"]=toAll;
                return out;
            }
            case 5:
            {
                Json::Value toAll;
                toAll["Header"]=5;
                int id=data["id"].asInt();
                game.deletePlayer(id);
                toAll["id"]=id;
                out["toAll"]=toAll;
                return out;
            }
            case 30:
            {
                game.findPlayer(data["id"].asInt()).setPosition(data["x"].asFloat(),data["y"].asFloat());
                out["Header"]=1;
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
                toOne["Header"]=31;
                toAll["Header"]=31;
                toOne["id"]=id;
                toAll["id"]=victim;
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
        int i=0;
        std::string positions="[";
        std::for_each(game.playerList.begin(), game.playerList.end(), [&](Player& player){
            positions+="(";
            positions+="\"id\":"+std::to_string(player.getId());
            std::tuple<float,float> position=player.getPosition();
            positions+=",\"x\":"+std::to_string(std::get<0>(position));
            positions+=",\"y\":"+std::to_string(std::get<1>(position));
            if(i==game.countPlayers()-1){
                positions+=")";
            }else{
                positions+="),";
            }
            i++;
        });
        positions+="]";
        toAll["playerPositions"]=positions;
        out["toAll"]=toAll;
        return out;
    };