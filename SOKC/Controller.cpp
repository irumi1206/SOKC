#include <iostream>
#include <vector>
#include <algorithm>
#include "Controller.h"
#include <utility>
#include <map>

Controller::Controller(){
    this->game=Game();
};

Json::Value Controller::control1(std::string in, int clientId){
    Json::Value data=toJson(in);
    return control(data,clientId);
}
Json::Value Controller::control(Json::Value data, int clientId){
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

            //추가함
            if(game.hostId==-1) game.hostId=id;
            //

            //플레이어 입장 시 호스트가 누구인지 알려줌.
            Json::Value toOne1;
            toOne1["Header"]=8;
            toOne1["Content"]["id"]=game.getHost();
            out["toOne"].append(toOne1);

            //플레이어 입장 시 다른 플레이어들에게 입장한 플레이어의 정보 반환
            other["Header"]=3;
            other["Content"]["id"]=id;
            other["Content"]["name"]=name;
            other["Content"]["color"]=game.findPlayer(id).getColor();
            out["other"].append(other);

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
            toAll[Header]=6;
            int id=data[Content]["id"].asInt();
            
            game.deletePlayer(id);
            positionVector.erase(id);
            //호스트 나가면 호스트 배정
            if(game.hostId==id && game.playerList.size()){
                game.hostId=game.playerList[0].getId();
                Json::Value toAll1;
                toAll1["Header"]=8;
                toAll1["Content"]["id"]=game.getHost();
                out["toAll"].append(toAll1);
            }
            if(game.playerList.size()==0){
                ///추가함
                game.hostId=-1;
                ///
                enterAllow=true;
            }
            toAll[Content]["id"]=id;
            out["toAll"].append(toAll);
            return out;
        }
        //플레이어 레디
        case 7:
        {
            out["toAll"].append(data);
            return out;
        }
        //호스트 넘겨주기
        case 8:
        {
            game.hostId=data["Content"]["id"].asInt();
            toAll["Header"]=8;
            toAll["Content"]["id"]=data["Content"]["id"];
            out["toAll"].append(toAll);
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
            
            toOne[Content]["coolTime"]["killCool"]=game.getKillCoolTime();
            toOne[Content]["coolTime"]["conferenceCool"]=game.getConferenceCoolTime();
            toOne[Content]["coolTime"]["discussion"]=game.getDiscussionTime();
            toOne[Content]["coolTime"]["voting"]=game.getVotingTime();

            toOne[Content]["roleIn"]=roleSetting();
            out["toOne"].append(toOne);
            return out;
        }
        // //방 나가기
        case 14:
        {
            toAll[Header]=14;
            int id=data[Content]["id"].asInt();
            
            game.deletePlayer(id);
            positionVector.erase(id);
            //호스트 나가면 호스트 배정
            if(game.hostId==id && game.playerList.size()){
                game.hostId=game.playerList[0].getId();
                Json::Value toAll1;
                toAll1["Header"]=8;
                toAll1["Content"]["id"]=game.getHost();
                out["toAll"].append(toAll1);
            }
            toAll[Content]["id"]=id;
            out["toAll"].append(toAll);
            return out;
        }
        //게임 시작
        case 15:
        {
            enterAllow=false;
            game.gameStart();
            game.roundStart();
            std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
                Json::Value each;
                each["recver"]=player.getId();
                each["data"][Header]=15;
                each["data"][Content]["roleIndex"]=player.getRole();
                //자신의 팀원 알려주기
                if(player.roleflag.getTeam()==PoolC){
                    std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player player1){
                        if(player1.getId()!=player.getId()){
                            each["data"][Content]["teams"].append(player1.getId());
                        }
                    });
                }else if(player.roleflag.getTeam()==Morgo){
                    each["data"][Content]["teams"];
                    std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player player1){
                        if(player1.getTeam()==Morgo && player1.getId()!=player.getId()){
                            each["data"][Content]["teams"].append(player1.getId());
                        }
                    });
                };
                //=====================
                out["toEach"].append(each);
                if(player.getRole()==6){
                    toAll["Header"]=40;
                    toAll["Content"]["roleIndex"]=6;
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
                if(voteStart["roleIndex"]==22){
                    Json::Value each;
                    each["recver"]=voteStart["victim"];
                    each["data"]["Header"]=40;
                    each["data"]["Content"]["roleIndex"]=22;
                    out["toEach"].append(each);
                }
                game.voteStartQueue.pop();
            }
            game.voteFinishedByVote=false;
            
            startVote();
            
            int voteCallPlayerId=data[Content]["id"].asInt();
            int victomFlag=data[Content]["by"].asInt();
            toAll[Header]=20;
            toAll[Content]["id"]=voteCallPlayerId;
            toAll[Content]["by"]=victomFlag;
            Json::Value toAll1;
            toAll1["Header"]=13;
            toAll1["Content"]=survivors();
            out["toAll"].append(toAll);
            out["toAll"].append(toAll1);

            //타이머
            Json::Value timer;
            timer["time"]=game.gameSetting.discussionTime+game.gameSetting.votingTime+5;
            timer["data"]["Header"]=-100;
            timer["data"]["info"]="vote";
            out["timer"]=timer;
            return out;
        }
        //투표
        case 21:
        {
            int votingPlayerId=data[Content]["id"].asInt();
            int votedPlayerId=data[Content]["voted"].asInt();
            if(game.putVote(votingPlayerId,votedPlayerId)){
                if(game.findPlayer(votingPlayerId).roleflag.role==23){
                    Json::Value votingEnd;
                    votingEnd["roleIndex"]=23;
                    votingEnd["id"]=votingPlayerId;
                    votingEnd["victim"]=votedPlayerId;
                    game.voteEndingQueueAdd(votingEnd);
                }else if(game.findPlayer(votingPlayerId).roleflag.role==4){
                    Json::Value votingEnd;
                    votingEnd["roleIndex"]=4;
                    votingEnd["id"]=votingPlayerId;
                    votingEnd["victim"]=votedPlayerId;
                    game.voteEndingQueueAdd(votingEnd);
                }
                if(game.findPlayer(votingPlayerId).voteCount==0){
                    toAll[Header]=21;
                    toAll[Content]["id"]=votingPlayerId;
                    out["toAll"].append(toAll);
                }
                if(isVoteEnd()){
                    Json::Value temp=voteEnd();
                    for(int i=0;i<temp["toAll"].size();i++){
                        out["toAll"].append(temp["toAll"][i]);
                    }
                    for(int i=0;i<temp["toEach"].size();i++){
                        out["toEach"].append(temp["toEach"][i]);
                    }
                }
            }
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
            //보안관일 경우
            if(killerPlayer.roleflag.available){
                if(killerPlayer.roleflag.role==1){
                    toOne["Header"]=40;
                    if(victimPlayer.getTeam()==PoolC){
                        if(game.findPlayer(id).benefit<=0){
                            game.findPlayer(id).dead();
                            Json::Value toAll1;
                            toAll1["Header"]=33;
                            toAll1["Content"]["id"]=id;
                            out["toAll"].append(toAll1);

                        }else{
                            game.findPlayer(id).benefit-=1;
                        }
                        toOne["Content"]["intValue"]=-1;
                    }else{
                        toOne["Content"]["intValue"]=1;
                    }
                }
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
                //군인일 경우
                if(victimPlayer.roleflag.role==2 && victimPlayer.roleflag.available && (victimPlayer.benefit+victimPlayer.roleflag.abilityCount)>0){
                    if(victimPlayer.benefit>0){
                        victimPlayer.benefit-=1;
                    }else if(victimPlayer.roleflag.abilityCount>0){
                        victimPlayer.roleflag.abilityCount-=1;
                    };
                    //부활 토큰 쏨.
                    Json::Value toAll2;
                    toAll2["Header"]=40;
                    toAll2["Content"]["roleIndex"]=2;
                    toAll2["Content"]["id"]=victim;
                    out["toAll"].append(toAll2);
                //능력 사용이 가능한 군인이 아닐 경우
                }else{
                    victimPlayer.dead();
                    Json::Value toAll1;
                    toAll1[Header]=33;
                    toAll1[Content]["id"]=victim;
                    out["toAll"].append(toAll1);
                }
            }
            if(game.isGameEnd()){
                switch(game.isGameEnd()){
                    case 1:
                    {
                        out["toAll"].append(gameEnd(PoolC)["toAll"]);
                        out["toAll"].append(gameEnd(PoolC)["toAll1"]);
                        break;
                    }
                    case 2:
                    {
                        out["toAll"].append(gameEnd(Morgo)["toAll"]);
                        out["toAll"].append(gameEnd(Morgo)["toAll1"]);
                        break;
                    }
                    default:
                    break;
                }
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
                each["data"]["Content"]["roleIndex"]=24;
                each["data"]["Content"]["id"]=id;
                out["toEach"].append(each);
            }else{
                player.finishMission(missionId);
                if(game.isBenefit()){
                    player.benefit+=1;
                    player.score.benefitTaken+=1;
                    Json::Value toOne;
                    toOne["Header"]=35;
                    toOne["Content"]["id"]=id;
                    out["toOne"].append(toOne);
                }
            }
            int lank=0;
            std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player player){
                if(player.countMission()==0){
                    lank+=1;
                }
            });
            player.score.missionClearScore.push_back(lank);
            
            return out;
        }
    
        //능력 사용
        case 40:
        {
            if(data["Content"]["roleIndex"]==21 && game.findPlayer(data[Content]["id"].asInt()).roleflag.role!=21){
                game.codingTestStorage[data[Content]["id"].asInt()]=data["Content"]["intValue"].asInt();
                std::cout<<survivors().size()<<std::endl;
                if(isTestEnd()){
                    out=testEnd();
                }
                return out;
            }
            Json::Value temp=useAbility(data[Content]["roleIndex"].asInt(),data);
            return temp;
        }
        //플레이어 음소거
        case 90:
        {
            out["toAll"].append(data);
            return out;
        }
        //다음 게임 하기
        case 102:
        {
            int id = data[Content]["id"].asInt();
            if(game.readyRoom.size()==0){
                game.hostId=id;
                toAll["Header"]=8;
                toAll["Content"]["id"]=id;
                out["toAll"].append(toAll);
            }
            game.readyRoom.push_back(game.findPlayer(id));
            return out;
        }
        //타이머 종료 신호
        case -100:
        {
            if(game.voteFinishedByVote==false && data["info"]=="vote"){
                std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
                    if(!player.isDie() && player.voteCount>0){
                        for(int i=0;i<player.voteCount;i++){
                            game.putVote(player.getId(),-1);
                        }
                    }
                });
                return voteEnd();
            }else if(game.testFinishedByTest==false &&data["info"]=="test"){
                toAll["Header"]=40;
                toAll["Content"]["id"]=-3;
                toAll["Content"]["roleIndex"]=21;
                toAll["Content"]["boolValue"]=true;
                out["toAll"].append(toAll);
            }
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
        std::vector<int> missions=player.getMission();
        std::for_each(missions.begin(),missions.end(),[&](int missionId){
            each["data"]["Content"]["missions"].append(missionId);
        });
        out.append(each);
    });
    return out;
}
//Header 22
Json::Value Controller::voteEnd(){
    game.voteFinishedByVote=true;
    //결과 송출
    std::map<int,int> storage = game.voteInfo();
    Json::Value toAll;
    Json::Value out;
    toAll["Header"]=22;
    toAll[Content]["voteDatas"]=voteResult(storage);
    out["toAll"].append(toAll);
    int deadId=game.calculateVoteDead(storage);
    game.findPlayer(deadId).dead();
    //===========================================
    //게임 종료 및 생존자 송출
    if(game.findPlayer(deadId).roleflag.role==41 && game.findPlayer(deadId).roleflag.available){
        out["toAll"].append(gameEnd(Mid)["toAll"]);
        out["toAll"].append(gameEnd(Mid)["toAll1"]);
    }else if(game.isGameEnd()){
        switch(game.isGameEnd()){
            case 1:
            {
                out["toAll"].append(gameEnd(PoolC)["toAll"]);
                out["toAll"].append(gameEnd(PoolC)["toAll1"]);
                break;
            }
            case 2:
            {
                out["toAll"].append(gameEnd(Morgo)["toAll"]);
                out["toAll"].append(gameEnd(Morgo)["toAll1"]);
                break;
            }
            default:
            break;
        }
    }else{
        if(deadId!=-1){
            Json::Value toAll1;
            toAll1[Header]=23;
            toAll1[Content]["id"]= deadId;
            toAll1[Content]["role"]=game.findPlayer(deadId).getRole();
            out["toAll"].append(toAll1);
        }
        //voteEndingQueue 안에 있는것 빼서 처리해야 함.
        while(!game.voteEndingQueue.empty()){
            Json::Value data = game.voteEndingQueue.front();
            Json::Value each;
            if(storage[data["victim"].asInt()]==1 && game.findPlayer(data["id"].asInt()).roleflag.available){
                each["recver"]=data["id"];
                each["data"]["Header"]=40;
                each["data"]["Content"]["roleIndex"]=data["roleIndex"];
                each["data"]["Content"]["victim"]=data["victim"];
                each["data"]["Content"]["intValue"]=game.findPlayer(data["victim"].asInt()).roleflag.role;
                out["toEach"].append(each);
            }
            game.voteEndingQueue.pop();
        }
        Json::Value toAll2;
        toAll2["Header"]=13;
        toAll2["Content"]=survivors();
        out["toAll"].append(toAll2);
    }
    
    return out;
}

//Header 31
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
    enterAllow=true;
    Json::Value data;
    Json::Value toAll;
    Json::Value toAll1;
    toAll[Header]=100;
    if(team==PoolC){
        toAll[Content]["victory"]=0;
        toAll[Content]["players"]=teamPlayers(PoolC);
    }else if(team==Morgo){
        toAll[Content]["victory"]=1;
        toAll[Content]["players"]=teamPlayers(Morgo);
    }else{
        toAll[Content]["victory"]=2;
        toAll[Content]["players"]=teamPlayers(Mid);
    }
    toAll1["Header"]=101;
    toAll1["Content"]=game.MVP();

    data["toAll"]=toAll;
    data["toAll1"]=toAll1;
    return data;
}

bool Controller::isVoteEnd(){
    bool check= true;
    std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player player){
        if(!player.isDie() && player.voteCount!=0){
            check=false;
        }
    });
    return check;
}

bool Controller::isTestEnd(){
    bool check=true;
    std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player player){
        if(!player.isDie() && !game.codingTestStorage.contains(player.getId())&&player.roleflag.team!=Morgo){
            check=false;
        }
    });
    return check;
}

Json::Value Controller::testEnd(){
    game.testFinishedByTest=true;
    int id=-1;
    int count=1000;
    std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player player){
        if(player.roleflag.team!=Morgo && !game.codingTestStorage.contains(player.getId())){
            game.codingTestStorage[player.getId()]=0;
        }
    });
    for(auto current=game.codingTestStorage.begin();current!=game.codingTestStorage.end();current++){
        if(current->second==count){
            int temp = rand()%2;
            if(temp==0)id=current->first;
        }else if(current->second<count){
            id=current->first;
            count=current->second;
        }
    };
    game.findPlayer(id).dead();
    Json::Value out;
    Json::Value toAll;
    toAll["Header"]=33;
    toAll[Content]["id"]=id;
    out["toAll"].append(toAll);
    if(game.isGameEnd()){
        switch(game.isGameEnd()){
            case 1:
            {
                out["toAll"].append(gameEnd(PoolC)["toAll"]);
                out["toAll"].append(gameEnd(PoolC)["toAll1"]);
                break;
            }
            case 2:
            {
                out["toAll"].append(gameEnd(Morgo)["toAll"]);
                out["toAll"].append(gameEnd(Morgo)["toAll1"]);
                break;
            }
            default:
            break;
        }
    }
    return out;
}

void Controller::startVote(){
    std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
        if(!player.isDie()){
            if(player.roleflag.role==5 && player.roleflag.available){
                player.voteCount=2;
            }else{
                player.voteCount=1;
            }
        }
    });
    game.clearVoteStorage();
    game.voteFinishedByVote=false;
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

Json::Value Controller::voteResult(std::map<int,int> storage){
    Json::Value voteResult;
    for(auto current=storage.begin();current!=storage.end();current++){
        Json::Value result;
        result["id"]=current->first;
        result["voteNumber"]=current->second;
        voteResult.append(result);
    }
    return voteResult;
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

Json::Value Controller::survivors(){
    Json::Value survivors;
    std::for_each(game.playerList.begin(),game.playerList.end(),[&](Player player){
        Json::Value survivor;
        survivor["id"]=player.getId();
        survivor["alive"]=!player.isDie();
        survivors["survivors"].append(survivor);
    });
    return survivors;
}

Json::Value Controller::useAbility(int roleIndex, Json::Value data){
    Json::Value out;
    if(game.findPlayer(data["Content"]["id"].asInt()).roleflag.available){
        switch(roleIndex){
            case 1://보안관
            {}
            case 2://군인, 없음.
            {}
            case 3://탐정
            {
                Json::Value toOne;
                int id=data["Content"]["id"].asInt();
                if(game.findPlayer(id).roleflag.abilityCount+game.findPlayer(id).benefit){
                    if(game.findPlayer(id).benefit){
                        game.findPlayer(id).benefit-=1;
                    }else{
                        game.findPlayer(id).roleflag.abilityCount-=1;
                    }
                    int aliveCount=0;
                    for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
                        if(!player.isDie() && player.getTeam()==PoolC){
                            aliveCount+=1;
                        }
                    });
                    toOne["Header"]=40;
                    toOne["Content"]["roleIndex"]=3;
                    toOne["Content"]["intValue"]=aliveCount;
                    out["toOne"].append(toOne);
                }
                return out;
            }
            case 4://변덕쟁이, 투표 관련 직업
            {
                int id = data["Content"]["id"].asInt();
                if(game.findPlayer(id).benefit>=1){
                    game.findPlayer(id).voteCount+=1;
                    game.findPlayer(id).benefit-=1;
                }
                return out;
            }
            case 5://정치인, 투표 관련 직업
            {
                int id = data["Content"]["id"].asInt();
                if(game.findPlayer(id).benefit>=1){
                    game.findPlayer(id).voteCount+=1;
                    game.findPlayer(id).benefit-=1;
                }
                return out;
            }
            case 6://하리주니어
            {
                int id = data["Content"]["id"].asInt();
                if(game.findPlayer(id).benefit>=1){
                    out["toAll"].append(data);
                }
                return out;
            }
            case 7://회장
            {
                int id = data["Content"]["id"].asInt();
                if(game.findPlayer(id).benefit>0){
                    game.findPlayer(id).benefit-=1;
                    int victim=data["Content"]["victim"].asInt();
                    game.findPlayer(victim).roleflag.available=false;
                    Json::Value each;
                    each["recver"]=victim;
                    each["data"]["Header"]=40;
                    each["data"]["Content"]["roleIndex"]=7;
                    each["data"]["Content"]["id"]=id;
                    each["data"]["Content"]["victim"]=victim;
                    out["toEach"].append(each);
                }
                return out;
            }
            case 21://면접관
            {
                int id = data["Content"]["id"].asInt();
                if(game.findPlayer(id).roleflag.abilityCount && game.findPlayer(id).roleflag.role==21){
                    game.testFinishedByTest=false;
                    game.findPlayer(id).roleflag.abilityCount-=1;
                    game.codingTestStorage.clear();
                    Json::Value toAll;
                    toAll["Header"]=40;
                    toAll["Content"]["roleIndex"]=21;
                    toAll["Content"]["id"]=-3;
                    out["toAll"].append(toAll);
                    //타이머
                    Json::Value timer;
                    timer["time"]=60;
                    timer["data"]["Header"]=-100;
                    timer["data"]["info"]="test";
                    out["timer"]=timer;
                }
                return out;
            }
            case 22://군기반장
            {
                int id = data["Content"]["id"].asInt();
                if(game.findPlayer(id).roleflag.abilityCount){
                    game.findPlayer(id).roleflag.abilityCount-=1;
                    Json::Value voteStart;
                    voteStart["victim"]=data["Content"]["victim"].asInt();
                    voteStart["roleIndex"]=22;
                    game.voteStartQueue.push(voteStart);
                }
                return out;
            }
            case 23:{}//저격수, 자동발동
            case 24://해커
            {
                int id = data["Content"]["id"].asInt();
                if(game.findPlayer(id).roleflag.abilityCount){
                    game.findPlayer(id).roleflag.abilityCount-=1;
                    game.gameSetting.hackedMission=data["Content"]["intValue"].asInt();
                    game.gameSetting.hackerId=data["Content"]["id"].asInt();
                }
                return out;
            }
            case 41://도도새, 없음
            {}
            default:
            {
                return out;
            }
        }
    }
    return out;
}