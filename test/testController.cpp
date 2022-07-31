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
    out["toOne"]=toOne;
    EXPECT_EQ(controller.control("{\"Header\":0,\"Content\":{\"roomId\":100}}"),out);
}
//룸 입장, 다른 사람들에게 입장한 플레이어 정보(2), 입장한 플레이어 색(3)
TEST(HEADER,1_room_enter){
    Controller controller=Controller();
    Json::Value expect1=controller.control("{\"Header\":1,\"Content\":{\"roomId\":100,\"name\":\"YM\"}}");
    Json::Value out;
    Json::Value toOne;
    Json::Value other;
    Json::Value other2;
    toOne["Header"]=1;
    toOne["Content"]["id"]=expect1["toOne"]["Content"]["id"];
    other["Header"]=2;
    other["Content"]["id"]=expect1["toOne"]["Content"]["id"];
    other["Content"]["name"]="YM";
    other2["Header"]=3;
    other2["Content"]["id"]=expect1["toOne"]["Content"]["id"];
    other2["Content"]["colorId"]=1;
    out["toOne"]=toOne;
    out["other"]=other;
    out["other2"]=other2;
    EXPECT_EQ(expect1,out);
    for(int i=0;i<15;i++){
        controller.control("{\"Header\":1,\"Content\":{\"roomId\":100,\"name\":\"YM\"}}");
        EXPECT_EQ(controller.game.countPlayers(),i+2);
    }
    Json::Value out1;
    Json::Value toOne1;
    toOne1["Header"]=0;
    toOne1["Content"]["serverConnect"]=-1;
    out1["toOne"]=toOne1;
    EXPECT_EQ(controller.control("{\"Header\":0,\"Content\":{\"roomId\":100}}"),out1);
}

TEST(HEADER,3_color_change_info){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM");
    Json::Value out;
    Json::Value other;
    other["Header"]=3;
    other["Content"]["id"]=id;
    other["Content"]["colorId"]=4;
    out["other"]=other;
    string temp="{\"Header\":3,\"Content\":{\"id\":"+to_string(id)+",\"colorId\":4}}";
    EXPECT_EQ(controller.control(temp),out);
}

TEST(HEADER,4_room_list_get){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM");
    controller.game.findPlayer(id).setColor(3);
    Json::Value out;
    Json::Value toOne;
    toOne["Header"]=4;
    toOne["Content"]["playerList"]="[{\"id\":"+to_string(id)+",\"name\":\"YM\",\"color\":3}]";
    out["toOne"]=toOne;
    EXPECT_EQ(controller.control("{\"Header\":4}"),out);
    int id1=controller.game.joinPlayer("KSH");
    controller.game.findPlayer(id1).setColor(5);
    toOne["Content"]["playerList"]="[{\"id\":"+to_string(id)+",\"name\":\"YM\",\"color\":3},{\"id\":"+to_string(id1)+",\"name\":\"KSH\",\"color\":5}]";
    out["toOne"]=toOne;
    EXPECT_EQ(controller.control("{\"Header\":4}"),out);
}


TEST(HEADER,5_exit_info){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM");
    Json::Value out;
    Json::Value other;
    other["Header"]=5;
    other["Content"]["id"]=id;
    out["other"]=other;
    string temp="{\"Header\":5,\"Content\":{\"id\":"+to_string(id)+"}}";
    EXPECT_EQ(controller.game.countPlayers(),1);
    EXPECT_EQ(controller.control(temp),out);
    EXPECT_EQ(controller.game.countPlayers(),0);
}

TEST(HEADER,8_host_game_setting){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM");
    int id1=controller.game.joinPlayer("1");
    int id2=controller.game.joinPlayer("2");
    int id3=controller.game.joinPlayer("3");
    Json::Value out;
    Json::Value other;
    other["Header"]=8;
    other["Content"]["molgoCount"]=1;
    other["Content"]["ysfbcCount"]=1;
    other["Content"]["missionCount"]=1;
    out["other"]=other;
    EXPECT_EQ(controller.control("{\"Header\":8,\"Content\":{\"molgoCount\":1,\"ysfbcCount\":1,\"missionCount\":1}}"),out);
}

TEST(HEADER,9_get_game_setting){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM");
    int id1=controller.game.joinPlayer("1");
    int id2=controller.game.joinPlayer("2");
    int id3=controller.game.joinPlayer("3");
    Json::Value out;
    Json::Value toOne;
    toOne["Header"]=9;
    toOne["Content"]["molgoCount"]=1;
    toOne["Content"]["ysfbcCount"]=1;
    toOne["Content"]["missionCount"]=1;
    out["toOne"]=toOne;
    controller.control("{\"Header\":8,\"Content\":{\"molgoCount\":1,\"ysfbcCount\":1,\"missionCount\":1}}");
    EXPECT_EQ(controller.control("{\"Header\":9}"),out);
    toOne["Header"]=9;
    toOne["Content"]["molgoCount"]=2;
    toOne["Content"]["ysfbcCount"]=2;
    toOne["Content"]["missionCount"]=2;
    out["toOne"]=toOne;
    controller.control("{\"Header\":8,\"Content\":{\"molgoCount\":2,\"ysfbcCount\":2,\"missionCount\":2}}");
    EXPECT_EQ(controller.control("{\"Header\":9}"),out);

}

TEST(HEADER,10_game_start){
    Controller controller=Controller();
    controller.control("{\"Header\":8,\"Content\":{\"molgoCount\":1,\"ysfbcCount\":1,\"missionCount\":1}}");
    int id1=controller.game.joinPlayer("YM");
    int id2=controller.game.joinPlayer("SH");
    int id3=controller.game.joinPlayer("SJ");
    cout<<controller.control("{\"Header\":10}")<<endl;
}


TEST(HEADER,30_moving_check){
    Controller controller=Controller();
    int id1=controller.game.joinPlayer("YM");
    int id2=controller.game.joinPlayer("SH");
    int id3=controller.game.joinPlayer("SJ");
    controller.control("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id1)+",\"x\":3.140000,\"y\":6.20000}}");
    controller.control("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id2)+",\"x\":3.530000,\"y\":0.700000}}");
    controller.control("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id3)+",\"x\":6.310000,\"y\":10.300000}}");
    tuple<float,float> temp1=make_tuple<float,float>(3.14,6.2);
    EXPECT_EQ(controller.game.findPlayer(id1).getPosition(), temp1);
    tuple<float,float> temp2=make_tuple<float,float>(3.53,0.7);
    EXPECT_EQ(controller.game.findPlayer(id2).getPosition(), temp2);
    tuple<float,float> temp3=make_tuple<float,float>(6.31,10.3);
    EXPECT_EQ(controller.game.findPlayer(id3).getPosition(), temp3);
}

TEST(HEADER_31,get_position_check){
    Controller controller=Controller();
    int id1=controller.game.joinPlayer("YM");
    int id2=controller.game.joinPlayer("SH");
    int id3=controller.game.joinPlayer("SJ");
    controller.control("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id1)+",\"x\":3.140000,\"y\":6.20000}}");
    controller.control("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id2)+",\"x\":3.530000,\"y\":0.700000}}");
    controller.control("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id3)+",\"x\":6.310000,\"y\":10.300000}}");
    Json::Value out;
    Json::Value toAll;
    toAll["Header"]=31;
    toAll["Content"]["playerPositions"]="[{\"id\":"+to_string(id1)+",\"x\":3.140000,\"y\":6.200000},{\"id\":"+to_string(id2)+",\"x\":3.530000,\"y\":0.700000},{\"id\":"+to_string(id3)+",\"x\":6.310000,\"y\":10.300000}]";
    out["toAll"]=toAll;
    EXPECT_EQ(controller.positions(),out);
}

TEST(HEADER,32_kill_check){
    Controller controller=Controller();
    int id1=controller.game.joinPlayer("YM");
    int id2=controller.game.joinPlayer("SH");
    int id3=controller.game.joinPlayer("SJ");
    EXPECT_EQ(controller.game.findPlayer(id1).isDie(),false);
    EXPECT_EQ(controller.game.findPlayer(id2).isDie(),false);
    EXPECT_EQ(controller.game.findPlayer(id3).isDie(),false);
    //different team(molgo kill poolc)
    Json::Value out;
    Json::Value other;
    Json::Value toOne;
    other["Header"]=32;
    toOne["Header"]=32;
    other["Content"]["id"]=0;
    other["Content"]["victim"]=id2;
    toOne["Content"]["id"]=id1;
    toOne["Content"]["victim"]=id2;
    out["toOne"]=toOne;
    out["other"]=other;
    controller.game.findPlayer(id1).setRole(25);
    controller.game.findPlayer(id2).setRole(2);
    controller.game.findPlayer(id3).setRole(25);
    EXPECT_EQ(controller.control("{\"Header\":32,\"Content\":{\"id\":"+to_string(id1)+",\"victim\":"+to_string(id2)+"}}"),out);
    EXPECT_EQ(controller.game.findPlayer(id2).isDie(),true);
    EXPECT_EQ(controller.game.findPlayer(id1).getKillScore(),1);
    //different team(poolc kill molgo)
    other["Header"]=32;
    toOne["Header"]=32;
    other["Content"]["id"]=0;
    other["Content"]["victim"]=id3;
    toOne["Content"]["id"]=id2;
    toOne["Content"]["victim"]=id3;
    out["toOne"]=toOne;
    out["other"]=other;
    controller.game.findPlayer(id2).live();
    EXPECT_EQ(controller.control("{\"Header\":32,\"Content\":{\"id\":"+to_string(id2)+",\"victim\":"+to_string(id3)+"}}"),out);
    EXPECT_EQ(controller.game.findPlayer(id3).isDie(),true);
    EXPECT_EQ(controller.game.findPlayer(id2).getKillScore(),1);
    //same team(molgo kill molgo)
    other["Header"]=32;
    toOne["Header"]=32;
    other["Content"]["id"]=0;
    other["Content"]["victim"]=id1;
    toOne["Content"]["id"]=id3;
    toOne["Content"]["victim"]=id1;
    out["toOne"]=toOne;
    out["other"]=other;
    controller.game.findPlayer(id3).live();
    EXPECT_EQ(controller.control("{\"Header\":32,\"Content\":{\"id\":"+to_string(id3)+",\"victim\":"+to_string(id1)+"}}"),out);
    EXPECT_EQ(controller.game.findPlayer(id1).isDie(),true);
    EXPECT_EQ(controller.game.findPlayer(id3).getKillScore(),-1);
}

TEST(HEADER,33_mission_check){
    Controller controller=Controller();
    int id1=controller.game.joinPlayer("YM");
    int id2=controller.game.joinPlayer("SH");
    int id3=controller.game.joinPlayer("SJ");
    controller.game.findPlayer(id1).addMission(1);
    controller.game.findPlayer(id1).addMission(2);
    controller.game.findPlayer(id1).addMission(3);
    controller.game.findPlayer(id2).addMission(4);
    controller.game.findPlayer(id2).addMission(5);
    controller.game.findPlayer(id2).addMission(6);
    EXPECT_EQ(controller.game.findPlayer(id1).countMission(),3);
    EXPECT_EQ(controller.game.findPlayer(id2).countMission(),3);
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),0);
    controller.control("{\"Header\":33,\"Content\":{\"id\":"+to_string(id1)+",\"missionId\":1}}");
    EXPECT_EQ(controller.game.findPlayer(id1).countMission(),2);
    EXPECT_EQ(controller.game.findPlayer(id1).getMissionScore(),1);
    controller.game.findPlayer(id3).assignMission(3);
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),3);
    vector<int> missions=controller.game.findPlayer(id3).getMission();
    controller.control("{\"Header\":33,\"Content\":{\"id\":"+to_string(id3)+",\"missionId\":"+to_string(missions[0])+"}}");
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),2);
    EXPECT_EQ(controller.game.findPlayer(id3).getMissionScore(),1);
    controller.control("{\"Header\":33,\"Content\":{\"id\":"+to_string(id3)+",\"missionId\":"+to_string(missions[1])+"}}");
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),1);
    EXPECT_EQ(controller.game.findPlayer(id3).getMissionScore(),2);
    controller.control("{\"Header\":33,\"Content\":{\"id\":"+to_string(id3)+",\"missionId\":"+to_string(missions[2])+"}}");
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),0);
    EXPECT_EQ(controller.game.findPlayer(id3).getMissionScore(),3);
}


void thread1(){
    int count=10;
    Controller controller;
    int id1=controller.game.joinPlayer("YM");
    int id2=controller.game.joinPlayer("SH");
    int id3=controller.game.joinPlayer("SJ");
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
    // thread t1(thread1);
    // t1.join();
    return RUN_ALL_TESTS();
}