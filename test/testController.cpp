#include <iostream>
#include "/home/ubuntu/GameProject/SOKC/Controller.h"
#include <gtest/gtest.h>
#include <thread>
#include <unistd.h>

using namespace std;

TEST(HEADER,0_room_check){
    Controller controller=Controller();
    Json::Value out;
    Json::Value toOne;
    toOne["Header"]=0;
    toOne["Content"]["serverConnect"]=1;
    out["toOne"].append(toOne);
    EXPECT_EQ(controller.control("{\"Header\":0,\"Content\":{\"roomId\":100}}",0),out);
}
//룸 입장, 다른 사람들에게 입장한 플레이어 정보(2), 입장한 플레이어 색(3)
TEST(HEADER,1_room_enter){
    Controller controller=Controller();
    Json::Value expect1=controller.control("{\"Header\":1,\"Content\":{\"roomId\":100,\"name\":\"YM\"}}",0);
    Json::Value out;
    Json::Value toOne;
    Json::Value toOne1;
    Json::Value other;
    Json::Value other2;
    toOne["Header"]=1;
    toOne["Content"]["id"]=expect1["toOne"][0]["Content"]["id"];
    toOne1["Header"]=7;
    toOne1["Content"]["id"]=expect1["toOne"][0]["Content"]["id"];
    other["Header"]=2;
    other["Content"]["id"]=expect1["toOne"][0]["Content"]["id"];
    other["Content"]["name"]="YM";
    other2["Header"]=3;
    other2["Content"]["id"]=expect1["toOne"][0]["Content"]["id"];
    other2["Content"]["color"]=2;
    out["toOne"].append(toOne);
    out["toOne"].append(toOne1);
    out["other"].append(other);
    out["other"].append(other2);
    EXPECT_EQ(expect1,out);
    for(int i=0;i<15;i++){
        controller.control("{\"Header\":1,\"Content\":{\"roomId\":100,\"name\":\"YM\"}}",0);
        EXPECT_EQ(controller.game.countPlayers(),i+2);
    }
    Json::Value out1;
    Json::Value toOne2;
    toOne2["Header"]=0;
    toOne2["Content"]["serverConnect"]=-1;
    out1["toOne"].append(toOne2);
    EXPECT_EQ(controller.control("{\"Header\":0,\"Content\":{\"roomId\":100}}",0),out1);
}

TEST(HEADER,3_color_change_info){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM",1);
    Json::Value out;
    Json::Value toAll;
    toAll["Header"]=3;
    toAll["Content"]["id"]=id;
    toAll["Content"]["color"]=4;
    out["toAll"].append(toAll);
    string temp="{\"Header\":3,\"Content\":{\"id\":"+to_string(id)+",\"color\":4}}";
    EXPECT_EQ(controller.control(temp,0),out);
}

TEST(HEADER,4_room_list_get){
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
    toOne["Header"]=4;
    toOne["Content"]["playerList"]=playerList;
    out["toOne"].append(toOne);
    EXPECT_EQ(controller.control("{\"Header\":4}",0),out);
    int id1=controller.game.joinPlayer("KSH",2);
    controller.game.findPlayer(id1).setColor(5);
    playerinfo1["id"]=id1;
    playerinfo1["name"]="KSH";
    playerinfo1["color"]=5;
    playerList.append(playerinfo1);
    toOne["Content"]["playerList"]=playerList;
    out["toOne"][0]=toOne;
    EXPECT_EQ(controller.control("{\"Header\":4}",0),out);
}


TEST(HEADER,5_exit_info){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM",1);
    Json::Value out;
    Json::Value other;
    other["Header"]=5;
    other["Content"]["id"]=id;
    out["other"].append(other);
    string temp="{\"Header\":5,\"Content\":{\"id\":"+to_string(id)+"}}";
    EXPECT_EQ(controller.game.countPlayers(),1);
    EXPECT_EQ(controller.control(temp,0),out);
    EXPECT_EQ(controller.game.countPlayers(),0);
}

TEST(HEADER,6_ready){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM",1);
    Json::Value out;
    Json::Value toAll;
    Json::Value toAll1;
    toAll["Header"]=6;
    toAll["Content"]["id"]=id;
    toAll["Content"]["readyOn"]=true;
    out["toAll"].append(toAll);
    EXPECT_EQ(controller.control("{\"Header\":6,\"Content\":{\"id\":"+to_string(id)+",\"readyOn\":true}}",0),out);
    toAll1["Header"]=6;
    toAll1["Content"]["id"]=id;
    toAll1["Content"]["readyOn"]=false;
    out["toAll"][0]=toAll1;
    EXPECT_EQ(controller.control("{\"Header\":6,\"Content\":{\"id\":"+to_string(id)+",\"readyOn\":false}}",0),out);
}

TEST(HEADER,8_host_game_setting){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM",1);
    int id1=controller.game.joinPlayer("1",2);
    int id2=controller.game.joinPlayer("2",3);
    int id3=controller.game.joinPlayer("3",4);
    Json::Value out;
    Json::Value other;
    other["Header"]=8;
    other["Content"]["molgoCount"]=1;
    other["Content"]["ysfbcCount"]=1;
    other["Content"]["missionCount"]=1;
    out["other"].append(other);
    EXPECT_EQ(controller.control("{\"Header\":8,\"Content\":{\"molgoCount\":1,\"ysfbcCount\":1,\"missionCount\":1}}",0),out);
}

TEST(HEADER,9_get_game_setting){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM",1);
    int id1=controller.game.joinPlayer("1",2);
    int id2=controller.game.joinPlayer("2",3);
    int id3=controller.game.joinPlayer("3",4);
    Json::Value out;
    Json::Value toOne;
    Json::Value toOne1;
    toOne["Header"]=9;
    toOne["Content"]["molgoCount"]=1;
    toOne["Content"]["ysfbcCount"]=1;
    toOne["Content"]["missionCount"]=1;
    out["toOne"].append(toOne);
    controller.control("{\"Header\":8,\"Content\":{\"molgoCount\":1,\"ysfbcCount\":1,\"missionCount\":1}}",0);
    EXPECT_EQ(controller.control("{\"Header\":9}",0),out);
    toOne1["Header"]=9;
    toOne1["Content"]["molgoCount"]=2;
    toOne1["Content"]["ysfbcCount"]=2;
    toOne1["Content"]["missionCount"]=2;
    out["toOne"][0]=toOne1;
    controller.control("{\"Header\":8,\"Content\":{\"molgoCount\":2,\"ysfbcCount\":2,\"missionCount\":2}}",0);
    EXPECT_EQ(controller.control("{\"Header\":9}",0),out);

}

TEST(HEADER,10_game_start){
    Controller controller=Controller();
    controller.control("{\"Header\":8,\"Content\":{\"molgoCount\":1,\"ysfbcCount\":1,\"missionCount\":1}}",0);
    int id1=controller.game.joinPlayer("YM",1);
    int id2=controller.game.joinPlayer("SH",2);
    int id3=controller.game.joinPlayer("SJ",3);
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
    EXPECT_EQ(controller.control("{\"Header\":20,\"Content\":{\"id\":"+std::to_string(id)+",\"by\":-2}}",0),out);
    toAll1["Header"]=20;
    toAll1["Content"]["id"]=id;
    toAll1["Content"]["by"]=id1;
    out["toAll"][0]=toAll1;
    EXPECT_EQ(controller.control("{\"Header\":20,\"Content\":{\"id\":"+std::to_string(id)+",\"by\":"+std::to_string(id1)+"}}",0),out);
}

TEST(HEADER,21_voting_success){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("PLAYER1",1);
    int id2=controller.game.joinPlayer("PLAYER2",2);
    int id3=controller.game.joinPlayer("PLAYER3",3);
    int id4=controller.game.joinPlayer("PLAYER4",4);
    controller.control("{\"Header\":20,\"Content\":{\"id\":"+std::to_string(id1)+",\"by\":"+std::to_string(id2)+"}}",0);
    Json::Value out;
    Json::Value other;
    other["Header"]=21;
    other["Content"]["id"]=id1;
    out["other"].append(other);
    EXPECT_EQ(controller.control("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id1)+",\"voted\":"+std::to_string(id2)+"}}",0),out);
    other["Content"]["id"]=id2;
    out["other"][0]=other;
    EXPECT_EQ(controller.control("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id2)+",\"voted\":"+std::to_string(id2)+"}}",0),out);
    other["Content"]["id"]=id3;
    out["other"][0]=other;
    EXPECT_EQ(controller.control("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id3)+",\"voted\":"+std::to_string(id3)+"}}",0),out);
    other["Content"]["id"]=id4;
    out["other"][0]=other;
    EXPECT_EQ(controller.control("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id4)+",\"voted\":"+std::to_string(id4)+"}}",0),out);
    EXPECT_EQ(controller.game.calculateVoteDead(),id2);
}

TEST(HEADER,21_voting_fail){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("PLAYER1",1);
    int id2=controller.game.joinPlayer("PLAYER2",2);
    int id3=controller.game.joinPlayer("PLAYER3",3);
    int id4=controller.game.joinPlayer("PLAYER4",4);
    controller.control("{\"Header\":20,\"Content\":{\"id\":"+std::to_string(id1)+",\"by\":"+std::to_string(id2)+"}}",0);
    Json::Value out;
    Json::Value other;
    other["Header"]=21;
    other["Content"]["id"]=id1;
    out["other"].append(other);
    EXPECT_EQ(controller.control("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id1)+",\"voted\":"+std::to_string(id2)+"}}",0),out);
    other["Content"]["id"]=id2;
    out["other"][0]=other;
    EXPECT_EQ(controller.control("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id2)+",\"voted\":"+std::to_string(id2)+"}}",0),out);
    other["Content"]["id"]=id3;
    out["other"][0]=other;
    EXPECT_EQ(controller.control("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id3)+",\"voted\":"+std::to_string(id3)+"}}",0),out);
    other["Content"]["id"]=id4;
    out["other"][0]=other;
    EXPECT_EQ(controller.control("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id4)+",\"voted\":"+std::to_string(id3)+"}}",0),out);
    EXPECT_EQ(controller.game.calculateVoteDead(),-1);
}

TEST(HEADER,21_voting_score){
    Controller controller = Controller();
    int id1=controller.game.joinPlayer("PLAYER1",1);
    int id2=controller.game.joinPlayer("PLAYER2",2);
    int id3=controller.game.joinPlayer("PLAYER3",3);
    int id4=controller.game.joinPlayer("PLAYER4",4);
    controller.game.findPlayer(id1).setRole(1);
    controller.game.findPlayer(id2).setRole(2);
    controller.game.findPlayer(id3).setRole(20);
    controller.game.findPlayer(id4).setRole(21);
    controller.control("{\"Header\":20,\"Content\":{\"id\":"+std::to_string(id1)+",\"by\":"+std::to_string(id2)+"}}",0);
    Json::Value out;
    Json::Value other;
    other["Header"]=21;
    other["Content"]["id"]=id1;
    out["other"].append(other);
    EXPECT_EQ(controller.control("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id1)+",\"voted\":"+std::to_string(id2)+"}}",0),out);
    other["Content"]["id"]=id2;
    out["other"][0]=other;
    EXPECT_EQ(controller.control("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id2)+",\"voted\":"+std::to_string(id3)+"}}",0),out);
    other["Content"]["id"]=id3;
    out["other"][0]=other;
    EXPECT_EQ(controller.control("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id3)+",\"voted\":"+std::to_string(id3)+"}}",0),out);
    other["Content"]["id"]=id4;
    out["other"][0]=other;
    EXPECT_EQ(controller.control("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id4)+",\"voted\":"+std::to_string(id1)+"}}",0),out);
    EXPECT_EQ(controller.game.findPlayer(id1).votingAccuracy(),0);
    EXPECT_EQ(controller.game.findPlayer(id2).votingAccuracy(),1);
    EXPECT_EQ(controller.game.findPlayer(id3).votingAccuracy(),0);
    EXPECT_EQ(controller.game.findPlayer(id4).votingAccuracy(),1);
    controller.control("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id1)+",\"voted\":"+std::to_string(id3)+"}}",0);
    controller.control("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id2)+",\"voted\":"+std::to_string(id3)+"}}",0);
    controller.control("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id3)+",\"voted\":"+std::to_string(id1)+"}}",0);
    controller.control("{\"Header\":21,\"Content\":{\"id\":"+std::to_string(id4)+",\"voted\":"+std::to_string(id3)+"}}",0);
    EXPECT_EQ(controller.game.findPlayer(id1).votingAccuracy(),0.5);
    EXPECT_EQ(controller.game.findPlayer(id2).votingAccuracy(),1);
    EXPECT_EQ(controller.game.findPlayer(id3).votingAccuracy(),0.5);
    EXPECT_EQ(controller.game.findPlayer(id4).votingAccuracy(),0.5);
}


TEST(HEADER,30_moving_check){
    Controller controller=Controller();
    int id1=controller.game.joinPlayer("YM",1);
    int id2=controller.game.joinPlayer("SH",2);
    int id3=controller.game.joinPlayer("SJ",3);
    controller.control("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id1)+",\"x\":3.140000,\"y\":6.20000}}",0);
    controller.control("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id2)+",\"x\":3.530000,\"y\":0.700000}}",0);
    controller.control("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id3)+",\"x\":6.310000,\"y\":10.300000}}",0);
    tuple<float,float> temp1=make_tuple<float,float>(3.14,6.2);
    EXPECT_EQ(controller.game.findPlayer(id1).getPosition(), temp1);
    tuple<float,float> temp2=make_tuple<float,float>(3.53,0.7);
    EXPECT_EQ(controller.game.findPlayer(id2).getPosition(), temp2);
    tuple<float,float> temp3=make_tuple<float,float>(6.31,10.3);
    EXPECT_EQ(controller.game.findPlayer(id3).getPosition(), temp3);
}

TEST(HEADER,31_get_position_check){
    Controller controller=Controller();
    int id1=controller.game.joinPlayer("YM",1);
    int id2=controller.game.joinPlayer("SH",2);
    int id3=controller.game.joinPlayer("SJ",3);
    controller.control("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id1)+",\"x\":3.140000,\"y\":6.20000}}",0);
    controller.control("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id2)+",\"x\":3.530000,\"y\":0.700000}}",0);
    controller.control("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id3)+",\"x\":6.310000,\"y\":10.300000}}",0);
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
    out["toAll"].append(toAll);
    EXPECT_EQ(controller.positions(),out);
}

TEST(HEADER,32_kill_check){
    Controller controller=Controller();
    int id1=controller.game.joinPlayer("YM",1);
    int id2=controller.game.joinPlayer("SH",2);
    int id3=controller.game.joinPlayer("SJ",3);
    EXPECT_EQ(controller.game.findPlayer(id1).isDie(),false);
    EXPECT_EQ(controller.game.findPlayer(id2).isDie(),false);
    EXPECT_EQ(controller.game.findPlayer(id3).isDie(),false);
    //different team(molgo kill poolc)
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
    controller.game.findPlayer(id1).setRole(25);
    controller.game.findPlayer(id2).setRole(2);
    controller.game.findPlayer(id3).setRole(25);
    EXPECT_EQ(controller.control("{\"Header\":32,\"Content\":{\"id\":"+to_string(id1)+",\"victim\":"+to_string(id2)+"}}",0),out);
    EXPECT_EQ(controller.game.findPlayer(id2).isDie(),true);
    EXPECT_EQ(controller.game.findPlayer(id1).getKillScore(),1);
    //different team(poolc kill molgo)
    toAll["Header"]=32;
    toAll["Content"]["id"]=id2;
    toAll["Content"]["victim"]=id3;
    out["toAll"][0]=toAll;
    toAll1["Header"]=33;
    toAll1["Content"]["id"]=id3;
    out["toAll"][1]=toAll1;
    controller.game.findPlayer(id2).live();
    EXPECT_EQ(controller.control("{\"Header\":32,\"Content\":{\"id\":"+to_string(id2)+",\"victim\":"+to_string(id3)+"}}",0),out);
    EXPECT_EQ(controller.game.findPlayer(id3).isDie(),true);
    EXPECT_EQ(controller.game.findPlayer(id2).getKillScore(),1);
    //same team(molgo kill molgo)
    toAll["Header"]=32;
    toAll["Content"]["id"]=id3;
    toAll["Content"]["victim"]=id1;
    out["toAll"][0]=toAll;
    toAll1["Header"]=33;
    toAll1["Content"]["id"]=id1;
    out["toAll"][1]=toAll1;
    controller.game.findPlayer(id3).live();
    EXPECT_EQ(controller.control("{\"Header\":32,\"Content\":{\"id\":"+to_string(id3)+",\"victim\":"+to_string(id1)+"}}",0),out);
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
    controller.control("{\"Header\":34,\"Content\":{\"id\":"+to_string(id1)+",\"missionId\":1}}",0);
    EXPECT_EQ(controller.game.findPlayer(id1).countMission(),2);
    EXPECT_EQ(controller.game.findPlayer(id1).getMissionScore(),1);
    controller.game.findPlayer(id3).assignMission(3);
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),3);
    vector<int> missions=controller.game.findPlayer(id3).getMission();
    controller.control("{\"Header\":34,\"Content\":{\"id\":"+to_string(id3)+",\"missionId\":"+to_string(missions[0])+"}}",0);
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),2);
    EXPECT_EQ(controller.game.findPlayer(id3).getMissionScore(),1);
    controller.control("{\"Header\":34,\"Content\":{\"id\":"+to_string(id3)+",\"missionId\":"+to_string(missions[1])+"}}",0);
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),1);
    EXPECT_EQ(controller.game.findPlayer(id3).getMissionScore(),2);
    controller.control("{\"Header\":34,\"Content\":{\"id\":"+to_string(id3)+",\"missionId\":"+to_string(missions[2])+"}}",0);
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),0);
    EXPECT_EQ(controller.game.findPlayer(id3).getMissionScore(),3);
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
    EXPECT_EQ(controller.control("{\"Header\":90,\"Content\":{\"id\":"+to_string(id1)+",\"muteOn\":true}}",0),out);
}

void thread1(){
    int count=10;
    Controller controller;
    int id1=controller.game.joinPlayer("YM",1);
    int id2=controller.game.joinPlayer("SH",2);
    int id3=controller.game.joinPlayer("SJ",3);
    controller.game.findPlayer(id1).setPosition(1.1,4.3);
    controller.game.findPlayer(id2).setPosition(1.3,6.3);
    controller.game.findPlayer(id3).setPosition(1.5,10.3);
    while(count){
        usleep(166666);
        controller.game.findPlayer(id1).setPosition(count+1,4.3);
        controller.game.findPlayer(id2).setPosition(count+2,6.3);
        controller.game.findPlayer(id3).setPosition(count+3,10.3);
        cout<<controller.positions().toStyledString()<<endl;
        count--;
    }
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    //thread t1(thread1);
    //t1.join();
    return RUN_ALL_TESTS();
}