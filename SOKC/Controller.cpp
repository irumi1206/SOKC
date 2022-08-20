#include <iostream>
#include <vector>
#include <algorithm>
#include "Controller.h"
#include <utility>
#include <map>

Controller::Controller(){
    this->game=Game();
};
Json::Value Controller::control(std::string in, int clientId){
    Json::Value data=toJson(in);
    Json::Value out;
    Json::Value toOne;
    Json::Value other;
    Json::Value toAll;
    switch(data[Header].asInt()){
        //룸 입장 가능 여부
        // case 0:
        // {
        //     //플레이어 입장 시, 입장 가능한지 여부 확인
        //     toOne[Header]=0;
        //     toOne[Content]["serverConnect"]=roomCheck(data[Content]["roomId"].asInt());
        //     out["toOne"].append(toOne);
        //     return out;
        // }
        //룸 입장
        case 2:
        {
            //플레이어 입장 시 해당 플레이어의 아이디를 반환함.
            toOne["Header"]=2;
            std::string name=data["Content"]["name"].asString();
            int id=game.joinPlayer(name,clientId);
            positionVector.insert({id,std::make_tuple(0.0,0.0)});
            toOne["Content"]["id"]=id;
            out["toOne"].append(toOne);

            //플레이어 입장 시 호스트가 누구인지 알려줌.
            Json::Value toOne1;
            toOne1["Header"]=8;
            toOne1["Content"]["id"]=game.getHost();
            out["toOne"].append(toOne1);

            //플레이어 입장 시 다른 플레이어들에게 입장한 플레이어의 정보 반환
            other["Header"]=3;
            other["Content"]["id"]=id;
            other["Content"]["name"]=name;
            out["other"].append(other);

            //플레이어 입장 시 입장한 플레이어가 색을 바꾸면서 색 설정
            Json::Value other2;
            other2["Header"]=4;
            other2["Content"]["id"]=id;
            other2["Content"]["color"]=game.findPlayer(id).getColor();
            out["other"].append(other2);

            return out;
        }
        //플레이어 색 변경
        case 4:
        {
            toAll[Header]=4;
            int id=data[Content]["id"].asInt();
            int color=data[Content]["color"].asInt();
            game.findPlayer(id).setColor(color);
            toAll[Content]["id"]=id;
            toAll[Content]["color"]=color;
            out["toAll"].append(toAll);
            return out;
        }
        //룸내 플레이어 리스트 받아오기
        case 5:
        {
            toOne[Header]=5;
            toOne[Content]["playerList"]=playerInfo();
            out["toOne"].append(toOne);
            return out;
        }
        //플레이어 퇴장
        case 6:
        {
            other[Header]=6;
            int id=data[Content]["id"].asInt();
            game.deletePlayer(id);
            positionVector.erase(id);
            other[Content]["id"]=id;
            out["other"].append(other);
            return out;
        }
        //플레이어 레디
        case 7:
        {
            out["toAll"].append(data);
            return out;
        }
        //count 게임 설정값 변경
        case 9:
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
            other[Header]=9;
            other[Content]["poolCCount"]=game.getPoolcCount();
            other[Content]["morgoCount"]=game.getMorgoCount();
            other[Content]["ysfbcCount"]=game.getMidCount();
            out["other"].append(other);
            return out;
        }
        //cooltime 게임 설정값 변경
        case 10:
        {
            game.setKillCoolTime(data[Content]["killCool"].asInt());
            game.setConferenceCoolTime(data[Content]["conferenceCool"].asInt());
            game.setDiscussionTime(data[Content]["discussion"].asInt());
            game.setVotingTime(data[Content]["voting"].asInt());
            
            other[Header]=10;
            other[Content]["killCool"]=game.getKillCoolTime();
            other[Content]["conferenceCool"]=game.getConferenceCoolTime();
            other[Content]["discussion"]=game.getDiscussionTime();
            other[Content]["voting"]=game.getVotingTime();
            out["other"].append(other);
            return out;
        }
        //직업 설정값 변경
        case 11:
        {
            game.setRoleSettingChange(data[Content]["roleFlag"].asInt(),data[Content]["state"].asBool());
            out["other"].append(data);
            return out;
        }
        //게임 설정 가져오기
        case 12:
        {
            toOne[Header]=12;
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
            game.roundStart();
            std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
                Json::Value each;
                each["recver"]=player.getId();
                each["data"][Header]=15;
                each["data"][Content]["roleFlag"]=player.getRole();
                out["toEach"].append(each);
                if(player.getRole()==6){
                    toAll["Header"]=40;
                    toAll["Content"]["roleFlag"]=6;
                    toAll["Content"]["id"]=player.getId();
                    out["toAll"].append(toAll);
                }
            });
            Json::Value round=roundStartData();
            for(int i=0;i<round.size();i++){
                out["toEach"].append(round[i]);
            }
            return out;
        }
        //투표 소집
        case 20:
        {
            while(!game.voteStartQueue.empty()){
                Json::Value voteStart = game.voteStartQueue.front();
                if(voteStart["roleFlag"]==22){
                    Json::Value each;
                    each["recver"]=voteStart["victim"];
                    each["data"]["Header"]=40;
                    each["data"]["Content"]["roleFlag"]=22;
                    out["toEach"].append(each);
                }
                game.voteStartQueue.pop();
            }
            game.clearVoteStorage();
            int voteCallPlayerId=data[Content]["id"].asInt();
            int victomFlag=data[Content]["by"].asInt();
            toAll[Header]=20;
            toAll[Content]["id"]=voteCallPlayerId;
            toAll[Content]["by"]=victomFlag;
            // toAll[Content]["deadsList"]=deadList();
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
            game.findPlayer(deadId).die=true;
            toAll1[Header]=23;
            toAll1[Content]["id"]= game.calculateVoteDead();
            toAll1[Content]["role"]=game.findPlayer(deadId).getRole();
            out["toAll"].append(toAll1);
            return out;
        }
        //플레이어 이동
        case 30:
        {
            get<0>(positionVector[data[Content]["id"].asInt()])=data[Content]["x"].asFloat();
            get<1>(positionVector[data[Content]["id"].asInt()])=data[Content]["y"].asFloat();
            //game.findPlayer(data[Content]["id"].asInt()).setPosition(data[Content]["x"].asFloat(),data[Content]["y"].asFloat());
            return out;
        }
        //킬
        case 32:
        {
            int id=data[Content]["id"].asInt();
            int victim=data[Content]["victim"].asInt();
            Player& victimPlayer=game.findPlayer(victim);
            Player& killerPlayer=game.findPlayer(id);
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
            Player& player=game.findPlayer(id);
            player.addMissionScore(1);
            if(missionId == game.gameSetting.hackedMission){
                Json::Value each;
                each["recver"]=game.gameSetting.hackerId;
                each["data"]["Header"]=40;
                each["data"]["Content"]["roleFlag"]=24;
                each["data"]["Content"]["id"]=id;
                out["toEach"].append(each);
            }else{
                player.finishMission(missionId);
                if(game.isBenefit()){
                    player.benefit+=1;
                    Json::Value toOne;
                    toOne["Header"]=35;
                    toOne["Content"]["id"]=id;
                    out["toOne"].append(toOne);
                }
            }
            
            return out;
        }
    
        //능력 사용
        case 40:
        {
            return useAbility(data[Content]["roleFlag"].asInt(),data);
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
        default:
        {
            return out;
        }
    }
};
//Header 8
Json::Value Controller::setHost(int id){
    Json::Value toAll;
    toAll[Header]=8;
    toAll[Content]["id"]=id;
    return toAll;
}
//Header 16 라운드 시작, 미션 할당
Json::Value Controller::roundStartData(){
    Json::Value out;
    std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
        Json::Value each;
        each["recver"]=player.getId();
        each["data"]["Header"]=16;
        each["data"]["Content"]["missions"]=getMission(player);
        out.append(each);
    });
    return out;
}
//Header 22
//Header 31
// Json::Value Controller::positions(){
//     Json::Value toAll;
//     toAll[Header]=31;
//     Json::Value playerPositions;
//     std::for_each(game.playerList.begin(), game.playerList.end(), [&](Player& player){
//         Json::Value positions;
//         positions["id"]=player.getId();
//         std::tuple<float,float> position=player.getPosition();
//         positions["x"]=std::get<0>(position);
//         positions["y"]=std::get<1>(position);
//         playerPositions.append(positions);
//     });
//     toAll[Content]["playerPositions"]=playerPositions;
//     return toAll;
// };

Json::Value Controller::positions(){
    Json::Value toAll;
    toAll[Header]=31;
    for(auto [key,value]:positionVector){
        Json::Value position;
        position["id"]=key;
        position["x"]=std::get<0>(value);
        position["y"]=std::get<1>(value);
        toAll[Content]["playerPositions"].append(position);
    };
    return toAll;
}

//Header 100 게임 종료 조건 달성 여부 확인 및 종료 진행
Json::Value Controller::gameEnd(Team team){

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
        toAll[Content]["players"].append(Mid);
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
// int Controller::roomCheck(int roomId){
//     if(game.getId()==roomId && game.countPlayers()<16){
//         return 1;
//     }
//     else{
//         return -1;
//     }
// }
// Json::Value Controller::getMission(Player& player){
//     Json::Value out;
//     std::vector<int> missions=player.getMission();
//     std::for_each(missions.begin(),missions.end(),[&](int mission){
//         out.append(mission);
//     });
//     return out;
// }
int Controller::getMission(Player& player){
    return player.getMission()[0];
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

Json::Value Controller::useAbility(int roleFlag, Json::Value data){
    Json::Value out;
    switch(roleFlag){
        case 1://보안관
        {
            Json::Value toOne;
            Json::Value toAll;
            int id = data["Content"]["id"].asInt();
            Player& sheriff = game.findPlayer(id);
            Player& victim = game.findPlayer(data["Content"]["victim"].asInt());
            victim.dead();
            toAll["Header"]=32;
            toAll["Content"]["id"]=id;
            toAll["Content"]["victim"]=data["Content"]["victim"].asInt();
            toOne["Header"]=40;
            if(victim.getTeam()==PoolC){
                sheriff.addKillScore(-1);
                if(sheriff.benefit<=0){
                    sheriff.dead();
                }else{
                    sheriff.benefit-=1;
                }
                toOne["Content"]["intValue"]=-1;
            }else{
                sheriff.addKillScore(1);
                toOne["Content"]["intValue"]=1;
            }
            out["toOne"].append(toOne);
            out["toAll"].append(toAll);
            return out;
        }
        case 2://군인, 없음.
        {}
        case 3://탐정, 사용 횟수 제한 구현해야 함.
        {
            Json::Value toOne;
            int id=data["Content"]["id"].asInt();
            int aliveCount=0;
            for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
                if(!player.isDie() && player.getTeam()==PoolC){
                    aliveCount+=1;
                }
            });
            toOne["Header"]=40;
            toOne["Content"]["roleFlag"]=3;
            toOne["Content"]["intValue"]=aliveCount;
            out["toOne"].append(toOne);
            return out;
        }
        case 4://변덕쟁이, 투표 관련 직업
        {

        }
        case 5://정치인, 투표 관련 직업
        {

        }
        case 6://하리주니어
        {
            int id = data["Content"]["id"].asInt();
            if(game.findPlayer(id).benefit>=1){
                out["toAll"].append(data);
            }
            return out;
        }
        case 7://회장, 당하는 것 구현해야 함.
        {
            int id = data["Content"]["id"].asInt();
            if(game.findPlayer(id).benefit>=1){

            }
            return out;
        }
        case 21://면접관
        {
            Json::Value toAll;
            int id = data["Content"]["id"].asInt();
            //사용 횟수 감소 수현 필요
            toAll["Header"]=40;
            toAll["Content"]["roleFlag"]=21;
            toAll["Content"]["intValue"]=3;//랜덤 코테 필요함
            out["toAll"].append(toAll);
            return out;
        }
        case 22://군기반장
        {
            Json::Value voteStart;
            voteStart["victim"]=data["Content"]["victim"].asInt();
            voteStart["roleFlag"]=22;
            game.voteStartQueue.push(voteStart);
        }
        case 23://저격수
        {

        }
        case 24://해커
        {
            game.gameSetting.hackedMission=data["Content"]["intValue"].asInt();
            game.gameSetting.hackerId=data["Content"]["id"].asInt();
        }
        case 41://도도새, 없음
        {}
        default:
        {
            return out;
        }
    }
}