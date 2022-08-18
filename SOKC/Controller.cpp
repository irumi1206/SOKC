#include <iostream>
#include <vector>
#include <algorithm>
#include "Controller.h"
#include <utility>
#include <map>

Controller::Controller(){
    this->game=Game();
};
Json::Value Controller::control(std::string in, int clientIndex){
    Json::Value data=toJson(in);
    Json::Value out;
    Json::Value toOne;
    Json::Value other;
    Json::Value toAll;
    switch(data[Header].asInt()){
        //룸 입장 가능 여부
        case 0:
        {
            //플레이어 입장 시, 입장 가능한지 여부 확인
            toOne[Header]=0;
            toOne[Content]["serverConnect"]=roomCheck(data[Content]["roomId"].asInt());
            out["toOne"].append(toOne);
            return out;
        }
        //룸 입장
        case 1:
        {
            //플레이어 입장 시 해당 플레이어의 아이디를 반환함.
            toOne[Header]=1;
            std::string name=data[Content]["name"].asString();
            int id=game.joinPlayer(name,clientIndex);
            toOne[Content]["id"]=id;
            out["toOne"].append(toOne);

            //플레이어 입장 시 호스트가 누구인지 알려줌.
            Json::Value toOne1;
            toOne1[Header]=7;
            toOne1[Content]["id"]=game.getHost();
            out["toOne"].append(toOne1);

            //플레이어 입장 시 다른 플레이어들에게 입장한 플레이어의 정보 반환
            other[Header]=2;
            other[Content]["id"]=id;
            other[Content]["name"]=name;
            out["other"].append(other);

            //플레이어 입장 시 입장한 플레이어가 색을 바꾸면서 색 설정
            Json::Value other2;
            other2[Header]=3;
            other2[Content]["id"]=id;
            other2[Content]["color"]=game.findPlayer(id).getColor();
            out["other"].append(other2);

            return out;
        }
        //플레이어 색 변경
        case 3:
        {
            toAll[Header]=3;
            int id=data[Content]["id"].asInt();
            int color=data[Content]["color"].asInt();
            game.findPlayer(id).setColor(color);
            toAll[Content]["id"]=id;
            toAll[Content]["color"]=color;
            out["toAll"].append(toAll);
            return out;
        }
        //룸내 플레이어 리스트 받아오기
        case 4:
        {
            toOne[Header]=4;
            toOne[Content]["playerList"]=playerInfo();
            out["toOne"].append(toOne);
            return out;
        }
        //플레이어 퇴장
        case 5:
        {
            other[Header]=5;
            int id=data[Content]["id"].asInt();
            game.deletePlayer(id);
            other[Content]["id"]=id;
            out["other"].append(other);
            return out;
        }
        //플레이어 레디
        case 6:
        {
            out["toAll"].append(data);
            return out;
        }
        //count 게임 설정값 변경
        case 8:
        {
            if(data[Content]["poolCCount"]!=null){
                game.setPoolcCount(data[Content]["poolCCount"].asInt());
            }
            if(data[Content]["morgoCount"]!=null){
                game.setMorgoCount(data[Content]["morgoCount"].asInt());
            }
            if(data[Content]["ysfbcCount"]!=null){
                game.setMidCount(data[Content]["ysfbcCount"].asInt());
            }
            other[Header]=8;
            other[Content]["poolCCount"]=game.getPoolcCount();
            other[Content]["morgoCount"]=game.getMorgoCount();
            other[Content]["ysfbcCount"]=game.getMidCount();
            out["other"].append(other);
            return out;
        }
        //cooltime 게임 설정값 변경
        case 9:
        {
            game.setKillCoolTime(data[Content]["killCool"].asInt());
            game.setConferenceCoolTime(data[Content]["conferenceCool"].asInt());
            game.setDiscussionTime(data[Content]["discussion"].asInt());
            game.setVotingTime(data[Content]["voting"].asInt());
            
            other[Header]=9;
            other[Content]["killCool"]=game.getKillCoolTime();
            other[Content]["conferenceCool"]=game.getConferenceCoolTime();
            other[Content]["discussion"]=game.getDiscussionTime();
            other[Content]["voting"]=game.getVotingTime();
            out["other"].append(other);
            return out;
        }
        //직업 설정값 변경
        case 10:
        {
            game.setRoleSettingChange(data[Content]["roleFlag"].asInt(),data[Content]["state"].asBool());
            out["other"].append(data);
            return out;
        }
        //게임 설정 가져오기
        case 11:
        {
            toOne[Header]=11;
            toOne[Content]["sideCount"]["poolCCount"]=game.getPoolcCount();
            toOne[Content]["sideCount"]["morgoCount"]=game.getMorgoCount();
            toOne[Content]["sideCount"]["ysfbcCount"]=game.getMidCount();
            
            toOne[Content]["coolTime"]["killCoolTime"]=game.getKillCoolTime();
            toOne[Content]["coolTime"]["conferenceCoolTime"]=game.getConferenceCoolTime();
            toOne[Content]["coolTime"]["discussionTime"]=game.getDiscussionTime();
            toOne[Content]["coolTime"]["votingTime"]=game.getVotingTime();

            toOne[Content]["roleIn"]=roleSetting();
            out["toOne"].append(toOne);
            return out;
        }
        //게임 시작
        case 15:
        {
            game.gameStart();
            Json::Value each;
            std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
                each["recver"]=player.getId();
                each["data"][Header]=15;
                each["data"][Content]["roleFlag"]=player.getRole();
            });
            out["toEach"].append(each);
            return out;
        }
        //투표 소집
        case 20:
        {
            game.clearVoteStorage();
            int voteCallPlayerId=data[Content]["id"].asInt();
            int victomFlag=data[Content]["by"].asInt();
            toAll[Header]=20;
            toAll[Content]["id"]=voteCallPlayerId;
            toAll[Content]["by"]=victomFlag;
            //toAll[Content]["deadsList"]=function();
            out["toAll"].append(toAll);
            return out;
        }
        //투표
        case 21:
        {
            int votingPlayerId=data[Content]["id"].asInt();
            int votedPlayerId=data[Content]["voted"].asInt();
            game.putVote(votingPlayerId,votedPlayerId);
            other[Header]=21;
            other[Content]["id"]=votingPlayerId;
            out["other"].append(other);
            return out;
        }
        //투표 결과 ->자동으로 실행되게 해야 함.
        case 22:
        {
            toAll[Content]["voteDatas"]=voteResult();
            out["toAll"].append(toAll);
            Json::Value toAll1;
            int deadId=game.calculateVoteDead();
            game.findPlayer(deadId).dead();
            toAll1[Header]=23;
            toAll1[Content]["id"]= game.calculateVoteDead();
            toAll1[Content]["role"]=game.findPlayer(deadId).getRole();
            out["toAll"].append(toAll1);
            return out;
        }
        //플레이어 이동 ->스레드로 일정 시간마다 실행되게 해야 함.
        case 30:
        {
            game.findPlayer(data[Content]["id"].asInt()).setPosition(data[Content]["x"].asFloat(),data[Content]["y"].asFloat());
            return out;
        }
        //킬
        case 32:
        {
            int id=data[Content]["id"].asInt();
            int victim=data[Content]["victim"].asInt();
            Player& victimPlayer=game.findPlayer(victim);
            Player& killerPlayer=game.findPlayer(id);
            victimPlayer.dead();
            if(victimPlayer.getTeam()==killerPlayer.getTeam()){
                killerPlayer.addKillScore(-1);
            }else{
                killerPlayer.addKillScore(1);
            }
            toAll[Header]=32;
            toAll[Content]["id"]=id;
            toAll[Content]["victim"]=victim;
            out["toAll"].append(toAll);
            //Header 33
            if(victimPlayer.dead()){
                Json::Value toAll1;
                toAll1[Header]=33;
                toAll1[Content]["id"]=victim;
                out["toAll"].append(toAll1);
            }
            return out;
        }
        //미션 클리어
        case 34:
        {
            int id=data[Content]["id"].asInt();
            int missionId=data[Content]["missionId"].asInt();
            game.findPlayer(id).finishMission(missionId);
            game.findPlayer(id).addMissionScore(1);
            return out;
        }
    
        //능력 사용
        case 40:
        {
            
        }
        //베네핏 사용
        case 60:
        {

        }
        //플레이어 음소거
        case 90:
        {
            out["toAll"].append(data);
            return out;
        }
        //게임 종료
        default:
        {
            return out;
        }
    }
};
//Header 7
Json::Value Controller::setHost(int id){
    Json::Value toAll;
    toAll[Header]=7;
    toAll[Content]["id"]=id;
    return toAll;
}
//Header 16 라운드 시작, 구현 필요, 미션 할당
Json::Value Controller::roundStart(){
    Json::Value each;
    //each["data"][Content]["missions"]=getMission(player);
    return each;
}
//Header 31
Json::Value Controller::positions(){
    Json::Value out;
    Json::Value toAll;
    toAll[Header]=31;
    Json::Value playerPositions;
    std::for_each(game.playerList.begin(), game.playerList.end(), [&](Player& player){
        Json::Value positions;
        positions["id"]=player.getId();
        std::tuple<float,float> position=player.getPosition();
        positions["x"]=std::get<0>(position);
        positions["y"]=std::get<1>(position);
        playerPositions.append(positions);
    });
    toAll[Content]["playerPositions"]=playerPositions;
    out["toAll"].append(toAll);
    return out;
};
//Header 35
Json::Value Controller::benefitTaken(int id){
    Json::Value out;
    return out;
}
//Header 100
Json::Value Controller::gameEnd(Team team,int id){
    Json::Value toAll;
    toAll[Header]=100;
    if(team==PoolC){
        toAll[Content]["victory"]=0;
        toAll[Content]["players"]=teamPlayers(PoolC);
    }else if(team==Morgo){
        toAll[Content]["victory"]=1;
        toAll[Content]["players"]=teamPlayers(Morgo);
    }else{
        toAll[Content]["victory"]=2;
        toAll[Content]["players"].append(id);
    }
    return toAll;
}
Json::Value Controller::teamPlayers(Team team){
    Json::Value out;
    std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
        if(player.getTeam()==team){
            out.append(player.getId());
        }
    });
    return out;
}
Json::Value Controller::deadList(){
    Json::Value list;
    std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
        if(player.getPlayStatus()==Gaming && !player.isDie()){
            list.append(player.getId());
        }
    });
    return list;
}
Json::Value Controller::playerInfo(){
    Json::Value players;
    std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
        Json::Value infomation;
        infomation["id"]=player.getId();
        infomation["name"]=player.getName();
        infomation["color"]=player.getColor();
        players.append(infomation);
    });
    return players;
}
Json::Value Controller::voteResult(){
    std::map<int,int> storage=game.voteInfo();

    Json::Value voteResult;
    for(auto current=storage.begin();current!=storage.end();current++){
        Json::Value result;
        result["id"]=current->first;
        result["voteNumber"]=current->second;
        voteResult.append(result);
    }
    return voteResult;
}
int Controller::roomCheck(int roomId){
    if(game.getId()==roomId && game.countPlayers()<16){
        return 1;
    }
    else{
        return -1;
    }
}
Json::Value Controller::getMission(Player& player){
    Json::Value out;
    std::vector<int> missions=player.getMission();
    std::for_each(missions.begin(),missions.end(),[&](int mission){
        out.append(mission);
    });
    return out;
}
Json::Value Controller::votingCheck(){
    Json::Value out;
    return out;
}

Json::Value Controller::roleSetting(){
    Json::Value out;
    std::vector<std::map<int,bool>> settings= game.gameSetting.getRoleSetting();
    for(int i=0;i<3;i++){
        std::map<int,bool> setting=settings[i];
        for (const auto & [key, value] : setting) {
            Json::Value role;
            role["roleFlag"]=key;
            role["state"]=value;
            out.append(role);
        }
    }
    
    return out;
}