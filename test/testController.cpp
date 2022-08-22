#include <iostream>
#include "/home/ubuntu/GameProject/SOKC/Controller.h"
#include <gtest/gtest.h>

using namespace std;

//룸 입장, 다른 사람들에게 입장한 플레이어 정보(2), 입장한 플레이어 색(3)
TEST(HEADER,2_room_enter){
    Controller controller=Controller();
    Json::Value expect1=controller.control1("{\"Header\":2,\"Content\":{\"roomId\":100,\"name\":\"YM\"}}",0);
    Json::Value out;
    Json::Value toOne;
    Json::Value toOne1;
    Json::Value other;
    Json::Value other2;
    toOne["Header"]=2;
    toOne["Content"]["id"]=expect1["toOne"][0]["Content"]["id"];
    toOne1["Header"]=8;
    toOne1["Content"]["id"]=expect1["toOne"][0]["Content"]["id"];
    other["Header"]=3;
    other["Content"]["id"]=expect1["toOne"][0]["Content"]["id"];
    other["Content"]["name"]="YM";
    other["Content"]["color"]=2;
    out["toOne"].append(toOne);
    out["toOne"].append(toOne1);
    out["other"].append(other);
    EXPECT_EQ(expect1,out);
    for(int i=0;i<15;i++){
        controller.control1("{\"Header\":2,\"Content\":{\"roomId\":100,\"name\":\"YM\"}}",0);
        EXPECT_EQ(controller.game.countPlayers(),i+2);
    }
}

TEST(HEADER,4_color_change_info){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM",1);
    Json::Value out;
    Json::Value toAll;
    toAll["Header"]=4;
    toAll["Content"]["id"]=id;
    toAll["Content"]["color"]=4;
    out["toAll"].append(toAll);
    string temp="{\"Header\":4,\"Content\":{\"id\":"+to_string(id)+",\"color\":4}}";
    EXPECT_EQ(controller.control1(temp,0),out);
}

TEST(HEADER,5_room_list_get){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM",1);
    controller.game.findPlayer(id).setColor(3);
    Json::Value out;
    Json::Value toOne;
    Json::Value playerList;
    Json::Value playerinfo;
    Json::Value playerinfo1;
    playerinfo["id"]=id;
    playerinfo["name"]="YM";
    playerinfo["color"]=3;
    playerList.append(playerinfo);
    toOne["Header"]=5;
    toOne["Content"]["playerList"]=playerList;
    out["toOne"].append(toOne);
    EXPECT_EQ(controller.control1("{\"Header\":5}",0),out);
    int id1=controller.game.joinPlayer("KSH",2);
    controller.game.findPlayer(id1).setColor(5);
    playerinfo1["id"]=id1;
    playerinfo1["name"]="KSH";
    playerinfo1["color"]=5;
    playerList.append(playerinfo1);
    toOne["Content"]["playerList"]=playerList;
    out["toOne"][0]=toOne;
    EXPECT_EQ(controller.control1("{\"Header\":5}",0),out);
}


TEST(HEADER,6_exit_info){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM",1);
    Json::Value out;
    Json::Value toAll;
    toAll["Header"]=6;
    toAll["Content"]["id"]=id;
    out["toAll"].append(toAll);
    string temp="{\"Header\":6,\"Content\":{\"id\":"+to_string(id)+"}}";
    EXPECT_EQ(controller.game.countPlayers(),1);
    EXPECT_EQ(controller.control1(temp,0),out);
    EXPECT_EQ(controller.game.countPlayers(),0);
}

TEST(HEADER,7_ready){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM",1);
    Json::Value out;
    Json::Value toAll;
    Json::Value toAll1;
    toAll["Header"]=7;
    toAll["Content"]["id"]=id;
    toAll["Content"]["readyOn"]=true;
    out["toAll"].append(toAll);
    EXPECT_EQ(controller.control1("{\"Header\":7,\"Content\":{\"id\":"+to_string(id)+",\"readyOn\":true}}",0),out);
    toAll1["Header"]=7;
    toAll1["Content"]["id"]=id;
    toAll1["Content"]["readyOn"]=false;
    out["toAll"][0]=toAll1;
    EXPECT_EQ(controller.control1("{\"Header\":7,\"Content\":{\"id\":"+to_string(id)+",\"readyOn\":false}}",0),out);
}

TEST(HEADER,9_host_count_game_setting){
    Controller controller=Controller();
    Json::Value other;
    Json::Value out;
    other["Header"]=9;
    other["Content"]["poolCCount"]=3;
    other["Content"]["morgoCount"]=2;
    other["Content"]["ysfbcCount"]=1;
    out["other"].append(other);
    EXPECT_EQ(controller.control1("{\"Header\":9,\"Content\":{\"poolCCount\":3,\"morgoCount\":2,\"ysfbcCount\":1}}",0),out);
}

TEST(HEADER,10_host_cooltime_setting){
    Controller controller=Controller();
    Json::Value other;
    Json::Value out;
    other["Header"]=10;
    other["Content"]["killCool"]=20;
    other["Content"]["conferenceCool"]=30;
    other["Content"]["discussion"]=20;
    other["Content"]["voting"]=40;
    out["other"].append(other);
    EXPECT_EQ(controller.control1("{\"Header\":10,\"Content\":{\"killCool\":20,\"conferenceCool\":30,\"discussion\":20,\"voting\":40}}",0),out);
}

TEST(HEADER,11_role_setting){
    Controller controller=Controller();
    Json::Value other;
    Json::Value out;
    other["Header"]=11;
    other["Content"]["roleFlag"]=3;
    other["Content"]["state"]=false;
    out["other"].append(other);
    EXPECT_EQ(controller.control1("{\"Header\":11,\"Content\":{\"roleFlag\":3,\"state\":false}}",0),out);
    vector<int> temp = controller.game.gameSetting.getPoolc();
    vector<int> temp2 = {1,2,4,5,6,7};
    EXPECT_EQ(temp,temp2);
}

TEST(HEADER,12_get_game_setting){
    Controller controller=Controller();
    Json::Value toOne;
    Json::Value out;
    toOne["Header"]=12;
    toOne["Content"]["sideCount"]["poolCCount"]=5;
    toOne["Content"]["sideCount"]["morgoCount"]=1;
    toOne["Content"]["sideCount"]["ysfbcCount"]=0;

    toOne["Content"]["coolTime"]["killCoolTime"]=20;
    toOne["Content"]["coolTime"]["conferenceCoolTime"]=30;
    toOne["Content"]["coolTime"]["discussionTime"]=20;
    toOne["Content"]["coolTime"]["votingTime"]=40;
    Json::Value role;
    role["roleFlag"]=1;
    role["state"]=true;
    toOne["Content"]["roleIn"].append(role);
    role["roleFlag"]=2;
    role["state"]=true;
    toOne["Content"]["roleIn"].append(role);
    role["roleFlag"]=3;
    role["state"]=false;
    toOne["Content"]["roleIn"].append(role);
    role["roleFlag"]=4;
    role["state"]=true;
    toOne["Content"]["roleIn"].append(role);
    role["roleFlag"]=5;
    role["state"]=true;
    toOne["Content"]["roleIn"].append(role);
    role["roleFlag"]=6;
    role["state"]=false;
    toOne["Content"]["roleIn"].append(role);
    role["roleFlag"]=7;
    role["state"]=true;
    toOne["Content"]["roleIn"].append(role);

    role["roleFlag"]=21;
    role["state"]=true;
    toOne["Content"]["roleIn"].append(role);
    role["roleFlag"]=22;
    role["state"]=true;
    toOne["Content"]["roleIn"].append(role);
    role["roleFlag"]=23;
    role["state"]=true;
    toOne["Content"]["roleIn"].append(role);
    role["roleFlag"]=24;
    role["state"]=false;
    toOne["Content"]["roleIn"].append(role);

    role["roleFlag"]=41;
    role["state"]=false;
    toOne["Content"]["roleIn"].append(role);

    controller.control1("{\"Header\":11,\"Content\":{\"roleFlag\":1,\"state\":true}}",0);
    controller.control1("{\"Header\":11,\"Content\":{\"roleFlag\":2,\"state\":true}}",0);
    controller.control1("{\"Header\":11,\"Content\":{\"roleFlag\":3,\"state\":false}}",0);
    controller.control1("{\"Header\":11,\"Content\":{\"roleFlag\":4,\"state\":true}}",0);
    controller.control1("{\"Header\":11,\"Content\":{\"roleFlag\":5,\"state\":true}}",0);
    controller.control1("{\"Header\":11,\"Content\":{\"roleFlag\":6,\"state\":false}}",0);
    controller.control1("{\"Header\":11,\"Content\":{\"roleFlag\":7,\"state\":true}}",0);

    controller.control1("{\"Header\":11,\"Content\":{\"roleFlag\":21,\"state\":true}}",0);
    controller.control1("{\"Header\":11,\"Content\":{\"roleFlag\":22,\"state\":true}}",0);
    controller.control1("{\"Header\":11,\"Content\":{\"roleFlag\":23,\"state\":true}}",0);
    controller.control1("{\"Header\":11,\"Content\":{\"roleFlag\":24,\"state\":false}}",0);

    controller.control1("{\"Header\":11,\"Content\":{\"roleFlag\":41,\"state\":false}}",0);

    controller.control1("{\"Header\":9,\"Content\":{\"poolCCount\":5,\"morgoCount\":1,\"ysfbcCount\":0}}",0);
    controller.control1("{\"Header\":10,\"Content\":{\"killCool\":20,\"conferenceCool\":30,\"discussion\":20,\"voting\":40}}",0);

    out["toOne"].append(toOne);
    EXPECT_EQ(controller.control1("{\"Header\":12}",0),out);
}

TEST(HEADER,15_game_start){
    Controller controller=Controller();
    int id1=controller.game.joinPlayer("PLAYER1",1);
    int id2=controller.game.joinPlayer("PLAYER2",2);
    int id3=controller.game.joinPlayer("PLAYER3",3);
    int id4=controller.game.joinPlayer("PLAYER4",4);
    controller.game.gameSetting.setRoleSetting(7,false);
    controller.control1("{\"Header\":9,\"Content\":{\"poolCCount\":3,\"morgoCount\":1,\"ysfbcCount\":0}}",0);
    controller.control1("{\"Header\":15}",0);
    vector<Player> players = controller.game.getPlayers();
    int poolCount=0;
    int morCount=0;
    for_each(players.begin(),players.end(),[&](Player& player){
        if(player.getTeam()==PoolC){
            poolCount+=1;
        }else if(player.getTeam()==Morgo){
            morCount+=1;
        }else{
            cout<<"error"<<"\n";
        }
        EXPECT_EQ(player.countMission(),1);
    });
    EXPECT_EQ(poolCount,3);
    EXPECT_EQ(morCount,1);
}

TEST(HEADER,16_round_start){
    Controller controller=Controller();
    int id1=controller.game.joinPlayer("PLAYER1",1);
    int id2=controller.game.joinPlayer("PLAYER2",2);
    int id3=controller.game.joinPlayer("PLAYER3",3);
    int id4=controller.game.joinPlayer("PLAYER4",4);
    controller.game.roundStart();
    vector<Player> players = controller.game.getPlayers();
    for_each(players.begin(),players.end(),[&](Player& player){
        EXPECT_EQ(player.countMission(),1);
    });
}

TEST(HEADER,20_voting_call){
    Controller controller = Controller();
    int id=controller.game.joinPlayer("YM",1);
    int id1=controller.game.joinPlayer("1",2);
    int id2=controller.game.joinPlayer("2",3);
    int id3=controller.game.joinPlayer("3",4);
    Json::Value out;
    Json::Value toAll;
    Json::Value toAll1;
    toAll["Header"]=20;
    toAll["Content"]["id"]=id;
    toAll["Content"]["by"]=-2;
    out["toAll"].append(toAll);
    Json::Value toAll2;
    Json::Value survivor;
    toAll2["Header"]=13;
    survivor["id"]=id;
    survivor["alive"]=true;
    toAll2["Content"]["survivors"].append(survivor);
    survivor["id"]=id1;
    survivor["alive"]=true;
    toAll2["Content"]["survivors"].append(survivor);
    survivor["id"]=id2;
    survivor["alive"]=true;
    toAll2["Content"]["survivors"].append(survivor);
    survivor["id"]=id3;
    survivor["alive"]=true;
    toAll2["Content"]["survivors"].append(survivor);
    out["toAll"].append(toAll2);
    EXPECT_EQ(controller.control1("{\"Header\":20,\"Content\":{\"id\":"+std::to_string(id)+",\"by\":-2}}",0),out);
    toAll1["Header"]=20;
    toAll1["Content"]["id"]=id;
    toAll1["Content"]["by"]=id1;
    out["toAll"][0]=toAll1;
    EXPECT_EQ(controller.control1("{\"Header\":20,\"Content\":{\"id\":"+std::to_string(id)+",\"by\":"+std::to_string(id1)+"}}",0),out);
}

TEST(HEADER,21_voting_success){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("PLAYER1",1);
    int id2=controller.game.joinPlayer("PLAYER2",2);
    int id3=controller.game.joinPlayer("PLAYER3",3);
    int id4=controller.game.joinPlayer("PLAYER4",4);
    int id5=controller.game.joinPlayer("PLAYER4",5);

    controller.control1("{\"Header\":20,\"Content\":{\"id\":"+std::to_string(id1)+",\"by\":"+std::to_string(id2)+"}}",0);
    Json::Value out;
    Json::Value other;
    other["Header"]=21;
    other["Content"]["id"]=id1;
    out["other"].append(other);
    
    EXPECT_EQ(controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id1)+",\"voted\":"+std::to_string(id2)+"}}",0),out);
    other["Content"]["id"]=id2;
    out["other"][0]=other;
    EXPECT_EQ(controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id2)+",\"voted\":"+std::to_string(id2)+"}}",0),out);
    other["Content"]["id"]=id3;
    out["other"][0]=other;
    EXPECT_EQ(controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id3)+",\"voted\":"+std::to_string(id3)+"}}",0),out);
    other["Content"]["id"]=id4;
    out["other"][0]=other;
    EXPECT_EQ(controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id4)+",\"voted\":"+std::to_string(id4)+"}}",0),out);
    //EXPECT_EQ(controller.game.calculateVoteDead(),id2);
}

TEST(HEADER,21_voting_fail){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("PLAYER1",1);
    int id2=controller.game.joinPlayer("PLAYER2",2);
    int id3=controller.game.joinPlayer("PLAYER3",3);
    int id4=controller.game.joinPlayer("PLAYER4",4);
    int id5=controller.game.joinPlayer("PLAYER4",5);
    controller.control1("{\"Header\":20,\"Content\":{\"id\":"+std::to_string(id1)+",\"by\":"+std::to_string(id2)+"}}",0);
    Json::Value out;
    Json::Value other;
    other["Header"]=21;
    other["Content"]["id"]=id1;
    out["other"].append(other);
    EXPECT_EQ(controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id1)+",\"voted\":"+std::to_string(id2)+"}}",0),out);
    other["Content"]["id"]=id2;
    out["other"][0]=other;
    EXPECT_EQ(controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id2)+",\"voted\":"+std::to_string(id2)+"}}",0),out);
    other["Content"]["id"]=id3;
    out["other"][0]=other;
    EXPECT_EQ(controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id3)+",\"voted\":"+std::to_string(id3)+"}}",0),out);
    other["Content"]["id"]=id4;
    out["other"][0]=other;
    EXPECT_EQ(controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id4)+",\"voted\":"+std::to_string(id3)+"}}",0),out);
    //EXPECT_EQ(controller.game.calculateVoteDead(),-1);
}

TEST(HEADER,21_voting_score){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("PLAYER1",1);
    int id2=controller.game.joinPlayer("PLAYER2",2);
    int id3=controller.game.joinPlayer("PLAYER3",3);
    int id4=controller.game.joinPlayer("PLAYER4",4);
    int id5=controller.game.joinPlayer("PLAYER4",5);
    controller.game.findPlayer(id1).setRole(1);
    controller.game.findPlayer(id2).setRole(2);
    controller.game.findPlayer(id3).setRole(21);
    controller.game.findPlayer(id4).setRole(22);
    controller.game.findPlayer(id5).setRole(3);
    controller.control1("{\"Header\":20,\"Content\":{\"id\":"+std::to_string(id1)+",\"by\":"+std::to_string(id2)+"}}",0);
    Json::Value out;
    Json::Value other;
    other["Header"]=21;
    other["Content"]["id"]=id1;
    out["other"].append(other);
    EXPECT_EQ(controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id1)+",\"voted\":"+std::to_string(id2)+"}}",0),out);
    other["Content"]["id"]=id2;
    out["other"][0]=other;
    EXPECT_EQ(controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id2)+",\"voted\":"+std::to_string(id3)+"}}",0),out);
    other["Content"]["id"]=id3;
    out["other"][0]=other;
    EXPECT_EQ(controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id3)+",\"voted\":"+std::to_string(id3)+"}}",0),out);
    other["Content"]["id"]=id4;
    out["other"][0]=other;
    EXPECT_EQ(controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id4)+",\"voted\":"+std::to_string(id1)+"}}",0),out);
    EXPECT_EQ(controller.game.findPlayer(id1).votingAccuracy(),0);
    EXPECT_EQ(controller.game.findPlayer(id2).votingAccuracy(),1);
    EXPECT_EQ(controller.game.findPlayer(id3).votingAccuracy(),0);
    EXPECT_EQ(controller.game.findPlayer(id4).votingAccuracy(),1);
    controller.control1("{\"Header\":20,\"Content\":{\"id\":"+std::to_string(id1)+",\"by\":"+std::to_string(id2)+"}}",0);
    controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id1)+",\"voted\":"+std::to_string(id3)+"}}",0);
    controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id2)+",\"voted\":"+std::to_string(id3)+"}}",0);
    controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id3)+",\"voted\":"+std::to_string(id1)+"}}",0);
    controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id4)+",\"voted\":"+std::to_string(id3)+"}}",0);
    EXPECT_EQ(controller.game.findPlayer(id1).votingAccuracy(),0.5);
    EXPECT_EQ(controller.game.findPlayer(id2).votingAccuracy(),1);
    EXPECT_EQ(controller.game.findPlayer(id3).votingAccuracy(),0.5);
    EXPECT_EQ(controller.game.findPlayer(id4).votingAccuracy(),0.5);
}

TEST(HEADER,20_21_22_voting_check_all1){
    Controller controller=Controller();
    int id1=controller.game.joinPlayer("YM",1);
    int id2=controller.game.joinPlayer("YM",2);
    int id3=controller.game.joinPlayer("YM",3);
    int id4=controller.game.joinPlayer("YM",4);
    int id5=controller.game.joinPlayer("YM",5);
    int id6=controller.game.joinPlayer("YM",6);
    controller.game.findPlayer(id1).setRole(4);//변덕쟁이
    controller.game.findPlayer(id2).setRole(5);//정치인
    controller.game.findPlayer(id3).setRole(7);//회장
    controller.game.findPlayer(id4).setRole(22);//군기반장
    controller.game.findPlayer(id5).setRole(23);//저격수
    controller.game.findPlayer(id6).setRole(41);//도도새
    controller.control1("{\"Header\":20,\"Content\":{\"id\":"+std::to_string(id1)+",\"by\":-2}}",0);
    controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id1)+",\"voted\":"+std::to_string(id3)+"}}",0);
    controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id2)+",\"voted\":"+std::to_string(id6)+"}}",0);
    controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id2)+",\"voted\":"+std::to_string(id6)+"}}",0);
    controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id3)+",\"voted\":"+std::to_string(id6)+"}}",0);
    controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id4)+",\"voted\":"+std::to_string(id6)+"}}",0);
    controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id5)+",\"voted\":"+std::to_string(id6)+"}}",0);
    cout<<controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id6)+",\"voted\":"+std::to_string(id6)+"}}",0).toStyledString()<<endl;
}

TEST(HEADER,20_21_22_voting_check_all2){
    Controller controller=Controller();
    int id1=controller.game.joinPlayer("YM",1);
    int id2=controller.game.joinPlayer("YM",2);
    int id3=controller.game.joinPlayer("YM",3);
    int id4=controller.game.joinPlayer("YM",4);
    int id5=controller.game.joinPlayer("YM",5);
    int id6=controller.game.joinPlayer("YM",6);
    controller.game.findPlayer(id1).setRole(4);//변덕쟁이
    controller.game.findPlayer(id2).setRole(5);//정치인
    controller.game.findPlayer(id3).setRole(7);//회장
    controller.game.findPlayer(id4).setRole(22);//군기반장
    controller.game.findPlayer(id5).setRole(23);//저격수
    controller.game.findPlayer(id6).setRole(41);//도도새
    controller.control1("{\"Header\":20,\"Content\":{\"id\":"+std::to_string(id1)+",\"by\":-2}}",0);
    controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id1)+",\"voted\":"+std::to_string(id3)+"}}",0);
    controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id2)+",\"voted\":"+std::to_string(id6)+"}}",0);
    controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id2)+",\"voted\":"+std::to_string(id6)+"}}",0);
    controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id3)+",\"voted\":"+std::to_string(id6)+"}}",0);
    controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id4)+",\"voted\":"+std::to_string(id6)+"}}",0);
    controller.control1("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id5)+",\"voted\":"+std::to_string(id6)+"}}",0);
    cout<<controller.control1("{\"Header\":-100}",0)<<endl;
}

TEST(HEADER,31_get_position_check){
    Controller controller=Controller();
    int id1=controller.game.joinPlayer("YM",1);
    int id2=controller.game.joinPlayer("SH",2);
    int id3=controller.game.joinPlayer("SJ",3);
    controller.control1("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id1)+",\"x\":3.140000,\"y\":6.20000}}",0);
    controller.control1("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id2)+",\"x\":3.530000,\"y\":0.700000}}",0);
    controller.control1("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id3)+",\"x\":6.310000,\"y\":10.300000}}",0);
    Json::Value out;
    Json::Value toAll;
    Json::Value playerPositions;
    Json::Value position;
    position["id"]=id1;
    position["x"]=3.1400001049041748;
    position["y"]=6.1999998092651367;
    playerPositions.append(position);
    position["id"]=id2;
    position["x"]=3.5299999713897705;
    position["y"]=0.69999998807907104;
    playerPositions.append(position);
    position["id"]=id3;
    position["x"]=6.309999942779541;
    position["y"]=10.300000190734863;
    playerPositions.append(position);
    toAll["Header"]=31;
    toAll["Content"]["playerPositions"]=playerPositions;
    EXPECT_EQ(controller.positions(),toAll);
}

TEST(HEADER,32_kill_check){
    Controller controller=Controller();
    int id1=controller.game.joinPlayer("YM",1);
    int id2=controller.game.joinPlayer("SH",2);
    int id3=controller.game.joinPlayer("SJ",3);
    int id4=controller.game.joinPlayer("SJ",4);
    int id5=controller.game.joinPlayer("SJ",5);
    int id6=controller.game.joinPlayer("SJ",6);
    EXPECT_EQ(controller.game.findPlayer(id1).isDie(),false);
    EXPECT_EQ(controller.game.findPlayer(id2).isDie(),false);
    EXPECT_EQ(controller.game.findPlayer(id3).isDie(),false);
    //different team(morgo kill poolc)
    Json::Value out;
    Json::Value toAll;
    Json::Value toAll1;
    toAll["Header"]=32;
    toAll["Content"]["id"]=id1;
    toAll["Content"]["victim"]=id2;
    toAll1["Header"]=33;
    toAll1["Content"]["id"]=id2;
    out["toAll"].append(toAll);
    out["toAll"].append(toAll1);
    controller.game.findPlayer(id1).setRole(21);
    controller.game.findPlayer(id2).setRole(1);
    controller.game.findPlayer(id3).setRole(22);
    controller.game.findPlayer(id4).setRole(5);
    controller.game.findPlayer(id5).setRole(3);
    controller.game.findPlayer(id6).setRole(4);
    EXPECT_EQ(controller.control1("{\"Header\":32,\"Content\":{\"id\":"+to_string(id1)+",\"victim\":"+to_string(id2)+"}}",0),out);
    EXPECT_EQ(controller.game.findPlayer(id2).isDie(),true);
    EXPECT_EQ(controller.game.findPlayer(id1).getKillScore(),1);
    //different team(poolc kill morgo)
    toAll["Header"]=32;
    toAll["Content"]["id"]=id2;
    toAll["Content"]["victim"]=id3;
    out["toAll"][0]=toAll;
    toAll1["Header"]=33;
    toAll1["Content"]["id"]=id3;
    out["toAll"][1]=toAll1;
    controller.game.findPlayer(id2).live();
    EXPECT_EQ(controller.control1("{\"Header\":32,\"Content\":{\"id\":"+to_string(id2)+",\"victim\":"+to_string(id3)+"}}",0),out);
    EXPECT_EQ(controller.game.findPlayer(id3).isDie(),true);
    EXPECT_EQ(controller.game.findPlayer(id2).getKillScore(),1);
    //same team(morgo kill morgo)
    toAll["Header"]=32;
    toAll["Content"]["id"]=id3;
    toAll["Content"]["victim"]=id1;
    out["toAll"][0]=toAll;
    toAll1["Header"]=33;
    toAll1["Content"]["id"]=id1;
    out["toAll"][1]=toAll1;
    controller.game.findPlayer(id3).live();
    EXPECT_EQ(controller.control1("{\"Header\":32,\"Content\":{\"id\":"+to_string(id3)+",\"victim\":"+to_string(id1)+"}}",0),out);
    EXPECT_EQ(controller.game.findPlayer(id1).isDie(),true);
    EXPECT_EQ(controller.game.findPlayer(id3).getKillScore(),-1);
}

TEST(HEADER,34_mission_check){
    Controller controller=Controller();
    int id1=controller.game.joinPlayer("YM",1);
    int id2=controller.game.joinPlayer("SH",2);
    int id3=controller.game.joinPlayer("SJ",3);
    controller.game.findPlayer(id1).addMission(1);
    controller.game.findPlayer(id1).addMission(2);
    controller.game.findPlayer(id1).addMission(3);
    controller.game.findPlayer(id2).addMission(4);
    controller.game.findPlayer(id2).addMission(5);
    controller.game.findPlayer(id2).addMission(6);
    EXPECT_EQ(controller.game.findPlayer(id1).countMission(),3);
    EXPECT_EQ(controller.game.findPlayer(id2).countMission(),3);
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),0);
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id1)+",\"missionId\":1}}",0);
    EXPECT_EQ(controller.game.findPlayer(id1).countMission(),2);
    EXPECT_EQ(controller.game.findPlayer(id1).getMissionScore(),1);
    controller.game.findPlayer(id3).addMission(3);
    controller.game.findPlayer(id3).addMission(4);
    controller.game.findPlayer(id3).addMission(5);
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),3);
    vector<int> missions=controller.game.findPlayer(id3).getMission();
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id3)+",\"missionId\":"+to_string(missions[0])+"}}",0);
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),2);
    EXPECT_EQ(controller.game.findPlayer(id3).getMissionScore(),1);
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id3)+",\"missionId\":"+to_string(missions[1])+"}}",0);
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),1);
    EXPECT_EQ(controller.game.findPlayer(id3).getMissionScore(),2);
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id3)+",\"missionId\":"+to_string(missions[2])+"}}",0);
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),0);
    EXPECT_EQ(controller.game.findPlayer(id3).getMissionScore(),3);
}

TEST(HEADER,35_benefit_get_check){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("YM",10001); 
    int id2=controller.game.joinPlayer("SH",10002);
    int id3=controller.game.joinPlayer("SJ",10003);
    controller.game.gameSetting.setRoleSetting(7,false);
    controller.control1("{\"Header\":9,\"Content\":{\"poolCCount\":2,\"morgoCount\":1,\"ysfbcCount\":0}}",0);
    controller.control1("{\"Header\":15}",0);
    controller.game.findPlayer(id1).setRole(1);
    controller.game.findPlayer(id2).setRole(2);
    controller.game.findPlayer(id3).setRole(21);
    int id1Mission = controller.game.findPlayer(id1).getMission()[0];
    int id2Mission = controller.game.findPlayer(id2).getMission()[0];
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id1)+",\"missionId\":"+to_string(id1Mission)+"}}",0);
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id2)+",\"missionId\":"+to_string(id2Mission)+"}}",0);
    EXPECT_EQ(controller.game.findPlayer(id1).benefit,0);
    EXPECT_EQ(controller.game.findPlayer(id2).benefit,1);
}

TEST(HEADER,35_benefit_get_check_dead_person){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("YM",10001); 
    int id2=controller.game.joinPlayer("SH",10002);
    int id3=controller.game.joinPlayer("SJ",10003);
    int id4=controller.game.joinPlayer("ymym",10004);
    controller.game.gameSetting.setRoleSetting(7,false);
    controller.control1("{\"Header\":9,\"Content\":{\"poolCCount\":3,\"morgoCount\":1,\"ysfbcCount\":0}}",0);
    controller.control1("{\"Header\":15}",0);
    controller.game.findPlayer(id1).setRole(1);
    controller.game.findPlayer(id2).setRole(2);
    controller.game.findPlayer(id3).setRole(21);
    controller.game.findPlayer(id4).setRole(3);
    int id1Mission = controller.game.findPlayer(id1).getMission()[0];
    int id2Mission = controller.game.findPlayer(id2).getMission()[0];
    int id4Mission = controller.game.findPlayer(id4).getMission()[0];
    controller.game.findPlayer(id4).dead();
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id1)+",\"missionId\":"+to_string(id1Mission)+"}}",0);
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id2)+",\"missionId\":"+to_string(id2Mission)+"}}",0);
    EXPECT_EQ(controller.game.findPlayer(id1).benefit,0);
    EXPECT_EQ(controller.game.findPlayer(id2).benefit,1);
}

TEST(HEADER,40_1_ability_sheriff_bad_kill){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("YM",10001); 
    int id2=controller.game.joinPlayer("SH",10002);
    int id3=controller.game.joinPlayer("SJ",10003);
    int id4=controller.game.joinPlayer("SJ",10004);
    int id5=controller.game.joinPlayer("SJ",10005);
    int id6=controller.game.joinPlayer("SJ",10006);
    controller.game.findPlayer(id1).setRole(1);
    controller.game.findPlayer(id2).setRole(3);
    controller.game.findPlayer(id3).setRole(21);
    controller.game.findPlayer(id4).setRole(4);
    controller.game.findPlayer(id5).setRole(5);
    controller.game.findPlayer(id6).setRole(6);
    Json::Value out;
    Json::Value toOne;
    Json::Value toAll;
    toOne["Header"]=40;
    toOne["Content"]["intValue"]=-1;
    toAll["Header"]=32;
    toAll["Content"]["id"]=id1;
    toAll["Content"]["victim"]=id2;
    out["toOne"].append(toOne);
    out["toAll"].append(toAll);
    EXPECT_EQ(controller.control1("{\"Header\":40,\"Content\":{\"roleFlag\":1,\"id\":"+to_string(id1)+",\"victim\":"+to_string(id2)+"}}",0),out);
    EXPECT_EQ(controller.game.findPlayer(id1).isDie(),true);
    EXPECT_EQ(controller.game.findPlayer(id2).isDie(),true);
}

TEST(HEADER,40_1_ability_sheriff_bad_kill_benefit){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("YM",10001); 
    int id2=controller.game.joinPlayer("SH",10002);
    int id3=controller.game.joinPlayer("SJ",10003);
    int id4=controller.game.joinPlayer("SJ",10004);
    int id5=controller.game.joinPlayer("SJ",10005);
    int id6=controller.game.joinPlayer("SJ",10006);
    controller.game.findPlayer(id1).setRole(1);
    controller.game.findPlayer(id2).setRole(3);
    controller.game.findPlayer(id3).setRole(21);
    controller.game.findPlayer(id4).setRole(4);
    controller.game.findPlayer(id5).setRole(5);
    controller.game.findPlayer(id6).setRole(6);
    controller.game.roundStart();
    controller.game.findPlayer(id4).resetMission();
    controller.game.findPlayer(id5).resetMission();
    controller.game.findPlayer(id6).resetMission();
    int id1Mission = controller.game.findPlayer(id1).getMission()[0];
    int id2Mission = controller.game.findPlayer(id2).getMission()[0];
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id2)+",\"missionId\":"+to_string(id2Mission)+"}}",0);
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id1)+",\"missionId\":"+to_string(id1Mission)+"}}",0);
    Json::Value out;
    Json::Value toOne;
    Json::Value toAll;
    toOne["Header"]=40;
    toOne["Content"]["intValue"]=-1;
    toAll["Header"]=32;
    toAll["Content"]["id"]=id1;
    toAll["Content"]["victim"]=id2;
    out["toOne"].append(toOne);
    out["toAll"].append(toAll);
    EXPECT_EQ(controller.game.findPlayer(id1).benefit,1);
    EXPECT_EQ(controller.control1("{\"Header\":40,\"Content\":{\"roleFlag\":1,\"id\":"+to_string(id1)+",\"victim\":"+to_string(id2)+"}}",0),out);
    EXPECT_EQ(controller.game.findPlayer(id1).isDie(),false);
    EXPECT_EQ(controller.game.findPlayer(id2).isDie(),true);
    EXPECT_EQ(controller.game.findPlayer(id1).benefit,0);
}

TEST(HEADER,40_1_ability_sheriff_good_kill){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("YM",10001); 
    int id2=controller.game.joinPlayer("SH",10002);
    int id3=controller.game.joinPlayer("SJ",10003);
    int id4=controller.game.joinPlayer("SJ",10004);
    int id5=controller.game.joinPlayer("SJ",10005);
    int id6=controller.game.joinPlayer("SJ",10006);
    controller.game.findPlayer(id1).setRole(1);
    controller.game.findPlayer(id2).setRole(3);
    controller.game.findPlayer(id3).setRole(21);
    controller.game.findPlayer(id4).setRole(22);
    controller.game.findPlayer(id5).setRole(5);
    controller.game.findPlayer(id6).setRole(6);
    Json::Value out;
    Json::Value toOne;
    Json::Value toAll;
    toOne["Header"]=40;
    toOne["Content"]["intValue"]=1;
    toAll["Header"]=32;
    toAll["Content"]["id"]=id1;
    toAll["Content"]["victim"]=id3;
    out["toOne"].append(toOne);
    out["toAll"].append(toAll);
    EXPECT_EQ(controller.control1("{\"Header\":40,\"Content\":{\"roleFlag\":1,\"id\":"+to_string(id1)+",\"victim\":"+to_string(id3)+"}}",0),out);
    EXPECT_EQ(controller.game.findPlayer(id1).isDie(),false);
    EXPECT_EQ(controller.game.findPlayer(id3).isDie(),true);
}

TEST(HEADER,40_2_ability_soldier_nobenefit){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("YM",10001); 
    int id2=controller.game.joinPlayer("SH",10002);
    int id3=controller.game.joinPlayer("SJ",10003);
    int id4=controller.game.joinPlayer("SJ",10004);
    int id5=controller.game.joinPlayer("SJ",10005);
    int id6=controller.game.joinPlayer("SJ",10006);
    controller.game.findPlayer(id1).setRole(1);
    controller.game.findPlayer(id2).setRole(2);
    controller.game.findPlayer(id3).setRole(21);
    controller.game.findPlayer(id4).setRole(3);
    controller.game.findPlayer(id5).setRole(4);
    controller.game.findPlayer(id6).setRole(5);
    controller.game.findPlayer(id2).roleflag.abilityCount=1;
    controller.game.roundStart();
    Json::Value out;
    Json::Value toAll;
    toAll["Header"]=32;
    toAll["Content"]["id"]=id3;
    toAll["Content"]["victim"]=id2;
    out["toAll"].append(toAll);
    EXPECT_EQ(controller.control1("{\"Header\":32,\"Content\":{\"id\":"+to_string(id3)+",\"victim\":"+to_string(id2)+"}}",0),out);
    Json::Value toAll1;
    toAll1["Header"]=33;
    toAll1["Content"]["id"]=id2;
    out["toAll"].append(toAll1);
    EXPECT_EQ(controller.control1("{\"Header\":32,\"Content\":{\"id\":"+to_string(id3)+",\"victim\":"+to_string(id2)+"}}",0),out);
}

TEST(HEADER,40_2_ability_soldier_benefit){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("YM",10001); 
    int id2=controller.game.joinPlayer("SH",10002);
    int id3=controller.game.joinPlayer("SJ",10003);
    int id4=controller.game.joinPlayer("SJ",10004);
    int id5=controller.game.joinPlayer("SJ",10005);
    int id6=controller.game.joinPlayer("SJ",10006);
    controller.game.findPlayer(id1).setRole(1);
    controller.game.findPlayer(id2).setRole(2);
    controller.game.findPlayer(id3).setRole(21);
    controller.game.findPlayer(id4).setRole(4);
    controller.game.findPlayer(id5).setRole(5);
    controller.game.findPlayer(id6).setRole(6);
    controller.game.findPlayer(id2).roleflag.abilityCount=1;
    controller.game.roundStart();
    controller.game.findPlayer(id4).resetMission();
    controller.game.findPlayer(id5).resetMission();
    controller.game.findPlayer(id6).resetMission();
    int id1Mission = controller.game.findPlayer(id1).getMission()[0];
    int id2Mission = controller.game.findPlayer(id2).getMission()[0];
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id1)+",\"missionId\":"+to_string(id1Mission)+"}}",0);
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id2)+",\"missionId\":"+to_string(id2Mission)+"}}",0);
    Json::Value out;
    Json::Value toAll;
    toAll["Header"]=32;
    toAll["Content"]["id"]=id3;
    toAll["Content"]["victim"]=id2;
    out["toAll"].append(toAll);
    EXPECT_EQ(controller.game.findPlayer(id2).benefit,1);
    EXPECT_EQ(controller.control1("{\"Header\":32,\"Content\":{\"id\":"+to_string(id3)+",\"victim\":"+to_string(id2)+"}}",0),out);
    EXPECT_EQ(controller.game.findPlayer(id2).benefit,0);
    EXPECT_EQ(controller.game.findPlayer(id2).roleflag.abilityCount,1);
    EXPECT_EQ(controller.control1("{\"Header\":32,\"Content\":{\"id\":"+to_string(id3)+",\"victim\":"+to_string(id2)+"}}",0),out);
    EXPECT_EQ(controller.game.findPlayer(id2).roleflag.abilityCount,0);
    Json::Value toAll1;
    toAll1["Header"]=33;
    toAll1["Content"]["id"]=id2;
    out["toAll"].append(toAll1);
    EXPECT_EQ(controller.control1("{\"Header\":32,\"Content\":{\"id\":"+to_string(id3)+",\"victim\":"+to_string(id2)+"}}",0),out);
}

TEST(HEADER,40_3_ability_detective){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("YM",10001); 
    int id2=controller.game.joinPlayer("SH",10002);
    int id3=controller.game.joinPlayer("SJ",10003);
    int id4=controller.game.joinPlayer("SJ",10004);
    int id5=controller.game.joinPlayer("SJ",10005);
    int id6=controller.game.joinPlayer("SJ",10006);
    controller.game.findPlayer(id1).setRole(1);
    controller.game.findPlayer(id2).setRole(3);
    controller.game.findPlayer(id3).setRole(21);
    controller.game.findPlayer(id4).setRole(4);
    controller.game.findPlayer(id5).setRole(5);
    controller.game.findPlayer(id6).setRole(6);
    controller.game.findPlayer(id2).roleflag.abilityCount=2;
    Json::Value out;
    Json::Value toOne;
    toOne["Header"]=40;
    toOne["Content"]["roleFlag"]=3;
    toOne["Content"]["intValue"]=5;
    out["toOne"].append(toOne);
    EXPECT_EQ(controller.control1("{\"Header\":40,\"Content\":{\"roleFlag\":3,\"id\":"+to_string(id2)+"}}",0),out);
    controller.control1("{\"Header\":32,\"Content\":{\"id\":"+to_string(id3)+",\"victim\":"+to_string(id2)+"}}",0);
    out["toOne"][0]["Content"]["intValue"]=4;
    EXPECT_EQ(controller.control1("{\"Header\":40,\"Content\":{\"roleFlag\":3,\"id\":"+to_string(id2)+"}}",0),out);
    Json::Value null;
    EXPECT_EQ(controller.control1("{\"Header\":40,\"Content\":{\"roleFlag\":3,\"id\":"+to_string(id2)+"}}",0),null);
}

TEST(HEADER,40_6_ability_harijunior){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("YM",10001); 
    int id2=controller.game.joinPlayer("SH",10002);
    int id3=controller.game.joinPlayer("SJ",10003);
    controller.game.roundStart();
    controller.game.findPlayer(id1).setRole(1);
    controller.game.findPlayer(id2).setRole(6);
    controller.game.findPlayer(id3).setRole(21);
    int id1Mission = controller.game.findPlayer(id1).getMission()[0];
    int id2Mission = controller.game.findPlayer(id2).getMission()[0];
    Json::Value out;
    EXPECT_EQ(controller.control1("{\"Header\":40, \"Content\":{\"roleFlag\":6,\"id\":"+to_string(id2)+",\"boolValue\":true}}",0),out);
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id1)+",\"missionId\":"+to_string(id1Mission)+"}}",0);
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id2)+",\"missionId\":"+to_string(id2Mission)+"}}",0);
    Json::Value toAll;
    toAll["Header"]=40;
    toAll["Content"]["roleFlag"]=6;
    toAll["Content"]["id"]=id2;
    toAll["Content"]["boolValue"]=true;
    out["toAll"].append(toAll);
    EXPECT_EQ(controller.control1("{\"Header\":40, \"Content\":{\"roleFlag\":6,\"id\":"+to_string(id2)+",\"boolValue\":true}}",0),out);
}

TEST(HEADER,40_7_ability_president){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("YM",10001); 
    int id2=controller.game.joinPlayer("SH",10002);
    int id3=controller.game.joinPlayer("SJ",10003);
    controller.game.roundStart();
    controller.game.findPlayer(id1).setRole(1);
    controller.game.findPlayer(id2).setRole(7);
    controller.game.findPlayer(id3).setRole(21);
    Json::Value out;
    EXPECT_EQ(controller.control1("{\"Header\":40,\"Content\":{\"roleFlag\":7,\"id\":"+to_string(id2)+",\"victim\":"+to_string(id3)+"}}",0),out);
    int id1Mission = controller.game.findPlayer(id1).getMission()[0];
    int id2Mission = controller.game.findPlayer(id2).getMission()[0];
    EXPECT_EQ(controller.game.findPlayer(id2).benefit,0);
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id1)+",\"missionId\":"+to_string(id1Mission)+"}}",0);
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id2)+",\"missionId\":"+to_string(id2Mission)+"}}",0);
    EXPECT_EQ(controller.game.findPlayer(id2).benefit,1);
    Json::Value each;
    Json::Value null;
    each["recver"]=id1;
    each["data"]["Header"]=40;
    each["data"]["Content"]["roleFlag"]=7;
    each["data"]["Content"]["id"]=id2;
    each["data"]["Content"]["victim"]=id1;
    out["toEach"].append(each);
    EXPECT_EQ(controller.control1("{\"Header\":40,\"Content\":{\"roleFlag\":7,\"id\":"+to_string(id2)+",\"victim\":"+to_string(id1)+"}}",0),out);
    EXPECT_EQ(controller.control1("{\"Header\":40,\"Content\":{\"roleFlag\":1,\"id\":"+to_string(id1)+",\"victim\":"+to_string(id2)+"}}",0),null);
    EXPECT_EQ(controller.control1("{\"Header\":32,\"Content\":{\"id\":"+to_string(id1)+",\"victim\":"+to_string(id3)+"}}",0),null);
}

TEST(HEADER,40_21_ability_interviewer){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("YM",10001); 
    int id2=controller.game.joinPlayer("SH",10002);
    int id3=controller.game.joinPlayer("SJ",10003);
    controller.game.findPlayer(id1).setRole(1);
    controller.game.findPlayer(id2).setRole(6);
    controller.game.findPlayer(id3).setRole(21);
    controller.game.findPlayer(id3).roleflag.abilityCount=1;
    Json::Value out;
    Json::Value toAll;
    toAll["Header"]=40;
    toAll["Content"]["roleFlag"]=21;
    toAll["Content"]["intValue"]=3;
    out["toAll"].append(toAll);
    EXPECT_EQ(controller.control1("{\"Header\":40,\"Content\":{\"roleFlag\":21,\"id\":"+to_string(id3)+"}}",0),out);
}

TEST(HEADER,40_22_ability_silencer){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("YM",10001); 
    int id2=controller.game.joinPlayer("SH",10002);
    int id3=controller.game.joinPlayer("SJ",10003);
    controller.game.findPlayer(id1).setRole(1);
    controller.game.findPlayer(id2).setRole(6);
    controller.game.findPlayer(id3).setRole(22);
    controller.game.findPlayer(id3).roleflag.abilityCount=1;
    Json::Value null;
    EXPECT_EQ(controller.control1("{\"Header\":40,\"Content\":{\"roleFlag\":22,\"id\":"+to_string(id3)+",\"victim\":"+to_string(id1)+"}}",0),null);
    Json::Value out;
    Json::Value each;
    Json::Value toAll;
    each["recver"]=id1;
    each["data"]["Header"]=40;
    each["data"]["Content"]["roleFlag"]=22;
    toAll["Header"]=20;
    toAll["Content"]["id"]=id1;
    toAll["Content"]["by"]=-2;
    out["toAll"].append(toAll);
    out["toEach"].append(each);
    Json::Value toAll2;
    Json::Value survivor;
    toAll2["Header"]=13;
    survivor["id"]=id1;
    survivor["alive"]=true;
    toAll2["Content"]["survivors"].append(survivor);
    survivor["id"]=id2;
    survivor["alive"]=true;
    toAll2["Content"]["survivors"].append(survivor);
    survivor["id"]=id3;
    survivor["alive"]=true;
    toAll2["Content"]["survivors"].append(survivor);
    out["toAll"].append(toAll2);
    EXPECT_EQ(controller.control1("{\"Header\":20,\"Content\":{\"id\":"+to_string(id1)+",\"by\":-2}}",0),out);
}

TEST(HEADER,40_24_ability_hacker){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("YM",10001); 
    int id2=controller.game.joinPlayer("SH",10002);
    int id3=controller.game.joinPlayer("SJ",10003);
    controller.game.findPlayer(id1).setRole(1);
    controller.game.findPlayer(id2).setRole(6);
    controller.game.findPlayer(id3).setRole(24);
    controller.game.roundStart();
    int id1Mission = controller.game.findPlayer(id1).getMission()[0];
    int id2Mission = controller.game.findPlayer(id2).getMission()[0];
    controller.game.findPlayer(id3).roleflag.abilityCount=1;
    Json::Value out;
    Json::Value each;
    each["recver"]=id3;
    each["data"]["Header"]=40;
    each["data"]["Content"]["roleFlag"]=24;
    each["data"]["Content"]["id"]=id1;
    out["toEach"].append(each);
    controller.control1("{\"Header\":40,\"Content\":{\"roleFlag\":24,\"id\":"+to_string(id3)+",\"intValue\":"+to_string(id1Mission)+"}}",0);
    controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id2)+",\"missionId\":"+to_string(id2Mission)+"}}",0);
    EXPECT_EQ(controller.control1("{\"Header\":34,\"Content\":{\"id\":"+to_string(id1)+",\"missionId\":"+to_string(id1Mission)+"}}",0),out);
    EXPECT_EQ(controller.game.findPlayer(id1).benefit,0);
}

TEST(HEADER,90_player_mute){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("YM",1);
    int id2=controller.game.joinPlayer("SH",2);
    int id3=controller.game.joinPlayer("SJ",3);
    Json::Value out;
    Json::Value toAll;
    toAll["Header"]=90;
    toAll["Content"]["id"]=id1;
    toAll["Content"]["muteOn"]=true;
    out["toAll"].append(toAll);
    EXPECT_EQ(controller.control1("{\"Header\":90,\"Content\":{\"id\":"+to_string(id1)+",\"muteOn\":true}}",0),out);
}

TEST(HEADER,100_game_end_poolc_win){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("YM",10001); 
    int id2=controller.game.joinPlayer("SH",10002);
    int id3=controller.game.joinPlayer("SJ",10003);
    int id4=controller.game.joinPlayer("SJ",10004);
    int id5=controller.game.joinPlayer("SJ",10005);
    int id6=controller.game.joinPlayer("SJ",10006);
    controller.game.findPlayer(id1).roleflag.setRole(1);
    controller.game.findPlayer(id2).roleflag.setRole(2);
    controller.game.findPlayer(id3).roleflag.setRole(3);
    controller.game.findPlayer(id4).roleflag.setRole(21);
    controller.game.findPlayer(id5).roleflag.setRole(22);
    controller.game.findPlayer(id6).roleflag.setRole(41);
    controller.game.roundStart();
    Json::Value out;
    Json::Value toAll;
    Json::Value toOne;
    Json::Value toAll1;
    toOne["Header"]=40;
    toOne["Content"]["intValue"]=1;
    toAll["Header"]=32;
    toAll["Content"]["id"]=id1;
    toAll["Content"]["victim"]=id5;
    toAll1["Header"]=100;
    toAll1["Content"]["victory"]=0;
    toAll1["Content"]["players"].append(id1);
    toAll1["Content"]["players"].append(id2);
    toAll1["Content"]["players"].append(id3);
    out["toOne"].append(toOne);
    out["toAll"].append(toAll);
    out["toAll"].append(toAll1);
    controller.control1("{\"Header\":40,\"Content\":{\"roleFlag\":1,\"id\":"+to_string(id1)+",\"victim\":"+to_string(id4)+"}}",0);
    cout<<controller.control1("{\"Header\":40,\"Content\":{\"roleFlag\":1,\"id\":"+to_string(id1)+",\"victim\":"+to_string(id5)+"}}",0).toStyledString()<<endl;
}

TEST(HEADER,100_game_end_morgo_win){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("YM",10001); 
    int id2=controller.game.joinPlayer("SH",10002);
    int id3=controller.game.joinPlayer("SJ",10003);
    int id4=controller.game.joinPlayer("SJ",10004);
    int id5=controller.game.joinPlayer("SJ",10005);
    int id6=controller.game.joinPlayer("SJ",10006);
    controller.game.findPlayer(id1).roleflag.setRole(1);
    controller.game.findPlayer(id2).roleflag.setRole(2);
    controller.game.findPlayer(id3).roleflag.setRole(3);
    controller.game.findPlayer(id4).roleflag.setRole(21);
    controller.game.findPlayer(id5).roleflag.setRole(22);
    controller.game.findPlayer(id6).roleflag.setRole(41);
    controller.game.roundStart();
    controller.game.findPlayer(id2).roleflag.abilityCount=1;
    Json::Value out;
    Json::Value toAll;
    Json::Value toAll1;
    Json::Value toAll2;
    toAll["Header"]=32;
    toAll["Content"]["id"]=id4;
    toAll["Content"]["victim"]=id2;
    toAll1["Header"]=33;
    toAll1["Content"]["id"]=id2;
    toAll2["Header"]=100;
    toAll2["Content"]["victory"]=1;
    toAll2["Content"]["players"].append(id4);
    toAll2["Content"]["players"].append(id5);
    out["toAll"].append(toAll);
    controller.control1("{\"Header\":32,\"Content\":{\"id\":"+to_string(id4)+",\"victim\":"+to_string(id1)+"}}",0);
    EXPECT_EQ(controller.control1("{\"Header\":32,\"Content\":{\"id\":"+to_string(id4)+",\"victim\":"+to_string(id2)+"}}",0),out);
    out["toAll"].append(toAll1);
    out["toAll"].append(toAll2);
    cout<<controller.control1("{\"Header\":32,\"Content\":{\"id\":"+to_string(id4)+",\"victim\":"+to_string(id2)+"}}",0).toStyledString()<<endl;
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}