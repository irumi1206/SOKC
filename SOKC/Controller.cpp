#include <iostream>
#include <vector>
#include <algorithm>
#include "Controller.h"
#include <utility>

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
            //플레이어 입장 시, 입장 가능한지 여부 확인
            toOne["Header"]=0;
            toOne["Content"]["serverConnect"]=roomCheck(data["Content"]["roomId"].asInt());
            out["toOne"]=toOne;
            return out;
        }
        //룸 입장
        case 1:
        {
            //플레이어 입장 시 해당 플레이어의 아이디를 반환함.
            toOne["Header"]=1;
            std::string name=data["Content"]["name"].asString();
            int id=game.joinPlayer(name);
            toOne["Content"]["id"]=id;
            out["toOne"]=toOne;

            //플레이어 입장 시 다른 플레이어들에게 입장한 플레이어의 정보 반환
            other["Header"]=2;
            other["Content"]["id"]=id;
            other["Content"]["name"]=name;
            out["other"]=other;

            //플레이어 입장 시 입장한 플레이어가 색을 바꾸면서 색 설정
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
            game.gameStart();
            std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
                Json::Value each;
                each["Header"]=10;
                each["Content"]["roleFlag"]=player.getRole();
                each["Content"]["missions"]=getMission(player);
                toAll[std::to_string(player.getId())]=each;
            });
            out["toAll"]=toAll;
            return out;
        }
        //투표 소집
        case 20:
        {
            game.clearVoteStorage();
            int voteCallPlayerId=data["Content"]["id"].asInt();
            int victomFlag=data["Content"]["by"].asInt();
            toAll["Header"]=20;
            toAll["Content"]["id"]=voteCallPlayerId;
            toAll["Content"]["by"]=victomFlag;
            //toAll["Content"]["by"=function();
            out["toAll"]=toAll;
            return out;
        }
        //투표
        case 21:
        {
            int votingPlayerId=data["Content"]["id"].asInt();
            int votedPlayerId=data["Content"]["voted"].asInt();
            game.putVote(votingPlayerId,votedPlayerId);
            other["Header"]=21;
            other["Content"]["id"]=votingPlayerId;
            out["other"]=other;
            return out;
        }
        //투표 결과
        case 22:
        {
            toAll["Content"]["voteDatas"]=voteInfo();
            out["toAll"]=toAll;
            return out;
        }
        //투표 사망
        case 23:
        {
            int deadId=game.calculateVoteDead();
            toAll["Content"]["id"]= deadId;
            toAll["Content"]["role"]=game.findPlayer(deadId).getRole();
            out["toAll"]=toAll;
            return out;
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
            toAll["Header"]=32;
            toAll["Content"]["id"]=id;
            toAll["Content"]["victim"]=victim;
            out["toAll"]=toAll;
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
        default:
        {
            return out;
        }
    }
};
Json::Value Controller::positions(){
    Json::Value out;
    Json::Value toAll;
    toAll["Header"]=31;
    std::string positions="[";
    std::for_each(game.playerList.begin(), game.playerList.end(), [&](Player& player){
        positions+="{";
        positions+="\"id\":"+std::to_string(player.getId());
        std::tuple<float,float> position=player.getPosition();
        positions+=",\"x\":"+std::to_string(std::get<0>(position));
        positions+=",\"y\":"+std::to_string(std::get<1>(position));
        positions+="},";
    });
    positions=positions.substr(0, positions.length()-1);
    positions+="]";
    toAll["Content"]["playerPositions"]=positions;
    out["toAll"]=toAll;
    return out;
};
std::string Controller::playerInfo(){
    std::string players="[";
    std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
        players+="{";
        players+="\"id\":"+std::to_string(player.getId());
        players+=",\"name\":\""+player.getName()+"\"";
        players+=",\"color\":"+std::to_string(player.getColor());
        players+="},";
    });
    players=players.substr(0, players.length()-1);
    players+="]";
    return players;
}
std::string Controller::voteInfo(){
    std::string voteInfo="[";
    for(int i=0;i<game.voteStorage.size();++i){
        int votingPlayerId=game.voteStorage[i].votingPlayerId;
        int votedPlayerId=game.voteStorage[i].votedPlayerId;
        voteInfo+="{";
        voteInfo+=std::to_string(votingPlayerId);
        voteInfo+=",";
        voteInfo+=std::to_string(votedPlayerId);
        voteInfo+="}";
        if(i!=game.voteStorage.size()-1) voteInfo+=",";
    }
    voteInfo+="]";
    return voteInfo;
}
int Controller::roomCheck(int roomId){
    if(game.getId()==roomId && game.countPlayers()<16){
        return 1;
    }
    else{
        return -1;
    }
}
std::string Controller::getMission(Player& player){
    std::string out="[";
    std::vector<int> missions=player.getMission();
    std::for_each(missions.begin(),missions.end(),[&](int mission){
        out+=std::to_string(mission);
        out+=", ";
    });
    out=out.substr(0, out.length()-1);
    out+="]";
    return out;
}
Json::Value Controller::gameEnd(Team team,int id){
    Json::Value toAll;
    toAll["Header"]=100;
    if(team==PoolC){
        toAll["Content"]["victory"]=0;
        toAll["Content"]["players"]=teamPlayers(PoolC);
    }else if(team==Morgo){
        toAll["Content"]["victory"]=1;
        toAll["Content"]["players"]=teamPlayers(Morgo);
    }else{
        toAll["Content"]["victory"]=2;
        toAll["Content"]["players"]="["+std::to_string(id)+"]";
    }
    return toAll;
}
std::string Controller::teamPlayers(Team team){
    std::string out="[";
    std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
        if(player.getTeam()==team){
            out+=player.getId();
            out+=",";
        }
    });
    out=out.substr(0, out.length()-1);
    out+="]";
    return out;
}
std::string Controller::deadList(){
    std::string out="[";
    std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
        if(player.getPlayStatus()==Gaming && !player.isDie()){
            out+=player.getId();
            out+=",";
        }
    });
    out=out.substr(0, out.length()-1);
    out+="]";
    return out;
}