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
            //룸 입장 가능 여부
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
            //룸 입장
            case 1:
            {
                Json::Value toOne;
                toOne["Content"];
                toOne["Header"]=1;
                std::string name=data["name"].asString();
                int id=game.joinPlayer(name);
                toOne["Content"]["id"]=id;//id로 바꿔야 함
                out["toOne"]=toOne;

                Json::Value other;
                other["Header"]=2;
                other["Content"];
                other["Content"]["id"]=id;
                other["Content"]["name"]=name;
                out["other"]=other;

                Json::Value other2;
                other2["Header"]=3;
                other2["Content"];
                other2["Content"]["id"]=id;
                other2["Content"]["colorId"]=game.findPlayer(id).getColor();
                out["other2"]=other2;

                return out;
            }
            //플레이어 색 변경
            case 3:
            {
                Json::Value other;
                other["Header"]=3;
                other["Content"];
                int id=data["id"].asInt();
                int colorId=data["colorId"].asInt();
                game.findPlayer(id).setColor(colorId);
                other["Content"]["id"]=id;
                other["Content"]["colorId"]=colorId;
                out["other"]=other;
                return out;
            }
            //룸내 플레이어 리스트 받아오기
            case 4:
            {
                Json::Value toOne;
                toOne["Header"]=4;
                toOne["Content"];
                toOne["Content"]["playerList"]=playerInfo();
                out["toOne"]=toOne;
                return out;
            }
            //플레이어 퇴장
            case 5:
            {
                Json::Value other;
                other["Header"]=5;
                other["Content"];
                int id=data["id"].asInt();
                game.deletePlayer(id);
                other["Content"]["id"]=id;
                out["other"]=other;
                return out;
            }
            //호스트가 게임 설정
            case 8:
            {

            }
            //게임 설정 가져오기
            case 9:
            {

            }
            //게임 시작
            case 10:
            {

            }
            //투표 소집
            case 20:
            {

            }
            //투표
            case 21:
            {

            }
            //플레이어 이동
            case 30:
            {
                game.findPlayer(data["id"].asInt()).setPosition(data["x"].asFloat(),data["y"].asFloat());
                return out;
            }
            //킬
            case 32:
            {
                int id=data["id"].asInt();
                int victim=data["victim"].asInt();
                Player& victimPlayer=game.findPlayer(victim);
                Player& killerPlayer=game.findPlayer(id);
                victimPlayer.dead();
                if(victimPlayer.getTeam()==killerPlayer.getTeam()){
                    killerPlayer.addKillScore(-1);
                }else{
                    killerPlayer.addKillScore(1);
                }
                Json::Value toOne;
                Json::Value other;
                toOne["Content"];
                other["Content"];
                toOne["Header"]=32;
                other["Header"]=32;
                toOne["Content"]["id"]=id;
                other["Content"]["id"]=0;//다른 사람들에게는 더미데이터 전달
                toOne["Content"]["victim"]=victim;
                other["Content"]["victim"]=victim;
                out["toOne"]=toOne;
                out["other"]=other;
                return out;
            }
            //미션 클리어
            case 33:
            {
                int id=data["id"].asInt();
                int missionId=data["missionId"].asInt();
                game.findPlayer(id).finishMission(missionId);
                game.findPlayer(id).addMissionScore(1);
                return out;
            }
            //능력 사용
            case 34:
            {

            }
            //게임 종료
            case 100:
            {
                Json::Value toAll;
                toAll["Header"]=100;
                out["toAll"]=toAll;
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