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
            //다른 플레이어 입장 -->제거
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
            //플레이어 색 변경
            case 3:
            {

            }
            //룸내 플레이어 리스트 받아오기
            case 4:
            {

            }
            //플레이어 퇴장
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
            //유저 위치 동기화 -->제거
            case 31:
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
            //킬
            case 32:
            {
                int id=data["id"].asInt();
                int missionId=data["missionId"].asInt();
                game.findPlayer(id).finishMission(missionId);
                game.findPlayer(id).addMissionScore(1);
                return out;
            }
            //미션 클리어
            case 33:
            {

            }
            //능력 사용
            case 34:
            {

            }
            //게임 종료
            case 100:
            {

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