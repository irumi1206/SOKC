#include <iostream>
#include <vector>
#include <algorithm>
#include "Controller.h"

Controller::Controller(){
    this->game=Game();
};
    Json::Value Controller::control(std::string in){
        Json::Value data=toJson(in);
        Json::Value out;
        Json::Value toOne;
        Json::Value other;
        Json::Value toAll;
        switch(data["Header"].asInt()){
            //룸 입장 가능 여부
            case 0:
            {
                toOne["Header"]=0;
                toOne["Content"]["serverConnect"]=roomCheck(data["Content"]["roomId"].asInt());
                out["toOne"]=toOne;
                return out;
            }
            //룸 입장
            case 1:
            {
                toOne["Header"]=1;
                std::string name=data["Content"]["name"].asString();
                int id=game.joinPlayer(name);
                toOne["Content"]["id"]=id;
                out["toOne"]=toOne;

                other["Header"]=2;
                other["Content"]["id"]=id;
                other["Content"]["name"]=name;
                out["other"]=other;

                Json::Value other2;
                other2["Header"]=3;
                other2["Content"]["id"]=id;
                other2["Content"]["colorId"]=game.findPlayer(id).getColor();
                out["other2"]=other2;

                return out;
            }
            //플레이어 색 변경
            case 3:
            {
                other["Header"]=3;
                int id=data["Content"]["id"].asInt();
                int colorId=data["Content"]["colorId"].asInt();
                game.findPlayer(id).setColor(colorId);
                other["Content"]["id"]=id;
                other["Content"]["colorId"]=colorId;
                out["other"]=other;
                return out;
            }
            //룸내 플레이어 리스트 받아오기
            case 4:
            {
                toOne["Header"]=4;
                toOne["Content"]["playerList"]=playerInfo();
                out["toOne"]=toOne;
                return out;
            }
            //플레이어 퇴장
            case 5:
            {
                other["Header"]=5;
                int id=data["Content"]["id"].asInt();
                game.deletePlayer(id);
                other["Content"]["id"]=id;
                out["other"]=other;
                return out;
            }
            //호스트가 게임 설정
            case 8:
            {
                if(data["Content"]["molgoCount"]!=null){
                    game.setMolgoCount(data["Content"]["molgoCount"].asInt());
                }
                if(data["Content"]["ysfbcCount"]!=null){
                    game.setMidCount(data["Content"]["ysfbcCount"].asInt());
                }
                if(data["Content"]["missionCount"]!=null){
                    game.setMissionCount(data["Content"]["missionCount"].asInt());
                }
                other["Header"]=8;
                other["Content"]["molgoCount"]=game.getMolgoCount();
                other["Content"]["ysfbcCount"]=game.getMidCount();
                other["Content"]["missionCount"]=game.getMissionCount();
                out["other"]=other;
                return out;
            }
            //게임 설정 가져오기
            case 9:
            {
                toOne["Header"]=9;
                toOne["Content"]["molgoCount"]=game.getMolgoCount();
                toOne["Content"]["ysfbcCount"]=game.getMidCount();
                toOne["Content"]["missionCount"]=game.getMissionCount();
                out["toOne"]=toOne;
                return out;
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
                game.findPlayer(data["Content"]["id"].asInt()).setPosition(data["Content"]["x"].asFloat(),data["Content"]["y"].asFloat());
                return out;
            }
            //킬
            case 32:
            {
                int id=data["Content"]["id"].asInt();
                int victim=data["Content"]["victim"].asInt();
                Player& victimPlayer=game.findPlayer(victim);
                Player& killerPlayer=game.findPlayer(id);
                victimPlayer.dead();
                if(victimPlayer.getTeam()==killerPlayer.getTeam()){
                    killerPlayer.addKillScore(-1);
                }else{
                    killerPlayer.addKillScore(1);
                }
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
                int id=data["Content"]["id"].asInt();
                int missionId=data["Content"]["missionId"].asInt();
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
        int i=0;
        int max=game.countPlayers()-1;
        std::string positions="[";
        std::for_each(game.playerList.begin(), game.playerList.end(), [&](Player& player){
            positions+="{";
            positions+="\"id\":"+std::to_string(player.getId());
            std::tuple<float,float> position=player.getPosition();
            positions+=",\"x\":"+std::to_string(std::get<0>(position));
            positions+=",\"y\":"+std::to_string(std::get<1>(position));
            if(i==max){
                positions+="}";
            }else{
                positions+="},";
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
            players+="{";
            players+="\"id\":"+std::to_string(player.getId());
            players+=",\"name\":\""+player.getName()+"\"";
            players+=",\"color\":"+std::to_string(player.getColor());
            if(i==max){
                players+="}";
            }else{
                players+="},";
            }
            i++;
        });
        players+="]";
        return players;
    }
    int Controller::roomCheck(int roomId){
        if(game.getId()==roomId && game.countPlayers()<16){
            return 1;
        }
        else{
            return -1;
        }
    }