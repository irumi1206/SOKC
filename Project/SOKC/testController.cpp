#include <iostream>
#include "gameController.cpp"
#include <gtest/gtest.h>

using namespace std;

TEST(HEADER_0,room_check){
    Controller controller=Controller();
    Json::Value out;
    Json::Value toOne;
    toOne["Header"]=0;
    toOne["serverConnect"]=1;
    out["toOne"]=toOne;
    EXPECT_EQ(controller.control("{\"Header\":0,\"roomId\":100}"),out);
}

TEST(HEADER_1,room_check){
    Controller controller=Controller();
    Json::Value out;
    Json::Value toOne;
    Json::Value toAll;
    toOne["Header"]=1;
    toOne["id"]=10003;
    toOne["playerList"]=true;
    toAll["Header"]=1;
    toAll["id"]=10003;
    toAll["name"]="YM";
    out["toOne"]=toOne;
    out["toAll"]=toAll;
    EXPECT_EQ(controller.control("{\"Header\":1,\"roomId\":100,\"name\":\"YM\"}"),out);
    for(int i=0;i<15;i++){
        controller.control("{\"Header\":1,\"roomId\":100,\"name\":\"YM\"}");
        EXPECT_EQ(controller.game.countPlayers(),i+2);
    }
    Json::Value out1;
    Json::Value toOne1;
    toOne1["Header"]=0;
    toOne1["serverConnect"]=-1;
    out1["toOne"]=toOne1;
    EXPECT_EQ(controller.control("{\"Header\":0,\"roomId\":100}"),out1);
}

TEST(HEADER_2,color_change_check){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM");
    Json::Value out;
    Json::Value toAll;
    toAll["Header"]=2;
    toAll["id"]=id;
    toAll["colorId"]=4;
    out["toAll"]=toAll;
    string temp="{\"Header\":2,\"id\":"+to_string(id)+",\"colorId\":4}";
    EXPECT_EQ(controller.control(temp),out);
}

TEST(HEADER_5,exit_check){
    Controller controller=Controller();
    int id=controller.game.joinPlayer("YM");
    Json::Value out;
    Json::Value toAll;
    toAll["Header"]=5;
    toAll["id"]=id;
    out["toAll"]=toAll;
    string temp="{\"Header\":5,\"id\":"+to_string(id)+"}";
    EXPECT_EQ(controller.control(temp),out);
}




int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}