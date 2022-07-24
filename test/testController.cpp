#include <iostream>
#include "/home/ubuntu/GameProject/SOKC/Controller.h"
#include <gtest/gtest.h>

using namespace std;

TEST(HEADER_0,room_check){
    Controller controller=Controller();
    Json::Value out;
    Json::Value toOne;
    toOne["Header"]=0;
    toOne["Content"];
    toOne["Content"]["serverConnect"]=1;
    out["toOne"]=toOne;
    EXPECT_EQ(controller.control("{\"Header\":0,\"Content\":{\"roomId\":100}}"),out);
}

TEST(test,1){

}

TEST(HEADER_1,room_check){
    Controller controller=Controller();
    Json::Value out;
    Json::Value toOne;
    Json::Value toAll;
    toOne["Header"]=1;
    toOne["Content"];
    toOne["Content"]["id"]=10003;
    toOne["Content"]["playerList"]="[]";//구현 필요
    toAll["Header"]=1;
    toAll["Content"];
    toAll["Content"]["id"]=10003;
    toAll["Content"]["name"]="YM";
    out["toOne"]=toOne;
    out["toAll"]=toAll;
    EXPECT_EQ(controller.control("{\"Header\":1,\"Content\":{\"roomId\":100,\"name\":\"YM\"}}"),out);
    for(int i=0;i<15;i++){
        controller.control("{\"Header\":1,\"Content\":{\"roomId\":100,\"name\":\"YM\"}}");
        EXPECT_EQ(controller.game.countPlayers(),i+2);
    }
    Json::Value out1;
    Json::Value toOne1;
    toOne1["Header"]=0;
    toOne1["Content"];
    toOne1["Content"]["serverConnect"]=-1;
    out1["toOne"]=toOne1;
    EXPECT_EQ(controller.control("{\"Header\":0,\"Content\":{\"roomId\":100}}"),out1);
}

TEST(HEADER_1,playerListTest){
    Controller controller=Controller();
    Json::Value out;
    Json::Value toOne;
    Json::Value toAll;
    toOne["Header"]=1;
    toOne["Content"];
    toOne["Content"]["id"]=10003;
    toOne["Content"]["playerList"]="[]";//구현 필요
    toAll["Header"]=1;
    toAll["Content"];
    toAll["Content"]["id"]=10003;
    toAll["Content"]["name"]="YM";
    out["toOne"]=toOne;
    out["toAll"]=toAll;
    EXPECT_EQ(controller.control("{\"Header\":1,\"Content\":{\"roomId\":100,\"name\":\"YM\"}}"),out);
    toOne["Header"]=1;
    toOne["Content"];
    toOne["Content"]["id"]=10003;
    toOne["Content"]["playerList"]="[(\"id\":10026,\"name\":\"YM\",\"color\":0)]";//"[(10003,YM,0)]", 구현 필요
    toAll["Header"]=1;
    toAll["Content"];
    toAll["Content"]["id"]=10003;
    toAll["Content"]["name"]="YMK";
    out["toOne"]=toOne;
    out["toAll"]=toAll;
    EXPECT_EQ(controller.control("{\"Header\":1,\"Content\":{\"roomId\":100,\"name\":\"YMK\"}}"),out);
}

TEST(HEADER_2,color_change_check){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM");
    Json::Value out;
    Json::Value toAll;
    toAll["Header"]=2;
    toAll["Content"];
    toAll["Content"]["id"]=id;
    toAll["Content"]["colorId"]=4;
    out["toAll"]=toAll;
    string temp="{\"Header\":2,\"Content\":{\"id\":"+to_string(id)+",\"colorId\":4}}";
    EXPECT_EQ(controller.control(temp),out);
}

TEST(HEADER_5,exit_check){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM");
    Json::Value out;
    Json::Value toAll;
    toAll["Header"]=5;
    toAll["Content"];
    toAll["Content"]["id"]=id;
    out["toAll"]=toAll;
    string temp="{\"Header\":5,\"Content\":{\"id\":"+to_string(id)+"}}";
    EXPECT_EQ(controller.game.countPlayers(),1);
    EXPECT_EQ(controller.control(temp),out);
    EXPECT_EQ(controller.game.countPlayers(),0);
}

TEST(HEADER_30,moving_check){
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

TEST(HEADER_30,get_position_check){
    Controller controller=Controller();
    int id1=controller.game.joinPlayer("YM");
    int id2=controller.game.joinPlayer("SH");
    int id3=controller.game.joinPlayer("SJ");
    controller.control("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id1)+",\"x\":3.140000,\"y\":6.20000}}");
    controller.control("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id2)+",\"x\":3.530000,\"y\":0.700000}}");
    controller.control("{\"Header\":30,\"Content\":{\"id\":"+std::to_string(id3)+",\"x\":6.310000,\"y\":10.300000}}");
    Json::Value out;
    Json::Value toAll;
    toAll["Header"]=30;
    toAll["Content"];
    toAll["Content"]["playerPositions"]="[(\"id\":"+to_string(id1)+",\"x\":3.140000,\"y\":6.200000),(\"id\":"+to_string(id2)+",\"x\":3.530000,\"y\":0.700000),(\"id\":"+to_string(id3)+",\"x\":6.310000,\"y\":10.300000)]";
    out["toAll"]=toAll;
    EXPECT_EQ(controller.positions(),out);
}

TEST(HEADER_31,kill_check){
    Controller controller=Controller();
    int id1=controller.game.joinPlayer("YM");
    int id2=controller.game.joinPlayer("SH");
    int id3=controller.game.joinPlayer("SJ");
    EXPECT_EQ(controller.game.findPlayer(id1).isDie(),false);
    EXPECT_EQ(controller.game.findPlayer(id2).isDie(),false);
    EXPECT_EQ(controller.game.findPlayer(id3).isDie(),false);
    Json::Value out;
    Json::Value toAll;
    Json::Value toOne;
    toAll["Header"]=31;
    toOne["Header"]=31;
    toAll["Content"];
    toOne["Content"];
    toAll["Content"]["id"]=id2;
    toOne["Content"]["id"]=id1;
    out["toOne"]=toOne;
    out["toAll"]=toAll;
    EXPECT_EQ(controller.control("{\"Header\":31,\"Content\":{\"id\":"+to_string(id1)+",\"victim\":"+to_string(id2)+"}}"),out);
    EXPECT_EQ(controller.game.findPlayer(id2).isDie(),true);
    EXPECT_EQ(controller.game.findPlayer(id1).getKillScore(),1);
}

TEST(HEADER_32,mission_check){
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
    controller.control("{\"Header\":32,\"Content\":{\"id\":"+to_string(id1)+",\"missionId\":1}}");
    EXPECT_EQ(controller.game.findPlayer(id1).countMission(),2);
    EXPECT_EQ(controller.game.findPlayer(id1).getMissionScore(),1);
    controller.game.findPlayer(id3).assignMission(3);
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),3);
    vector<int> missions=controller.game.findPlayer(id3).getMission();
    controller.control("{\"Header\":32,\"Content\":{\"id\":"+to_string(id3)+",\"missionId\":"+to_string(missions[0])+"}}");
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),2);
    EXPECT_EQ(controller.game.findPlayer(id3).getMissionScore(),1);
    controller.control("{\"Header\":32,\"Content\":{\"id\":"+to_string(id3)+",\"missionId\":"+to_string(missions[1])+"}}");
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),1);
    EXPECT_EQ(controller.game.findPlayer(id3).getMissionScore(),2);
    controller.control("{\"Header\":32,\"Content\":{\"id\":"+to_string(id3)+",\"missionId\":"+to_string(missions[2])+"}}");
    EXPECT_EQ(controller.game.findPlayer(id3).countMission(),0);
    EXPECT_EQ(controller.game.findPlayer(id3).getMissionScore(),3);
}




int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}