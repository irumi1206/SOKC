#include <iostream>
#include "gameObject.cpp"
#include <gtest/gtest.h>

using namespace std;

Game game=Game();
Player player=Player(3, "YM");

TEST(room_test, join_player){
    EXPECT_EQ(game.joinPlayer(5,"MY"),1);
    EXPECT_EQ(game.joinPlayer(5,"MY"),0);
    EXPECT_EQ(game.countPlayers(),1);
    EXPECT_EQ(game.joinPlayer(player),1);
    EXPECT_EQ(game.countPlayers(),2);
    EXPECT_EQ(game.deletePlayer(5),1);
    EXPECT_EQ(game.deletePlayer(3),1);
    EXPECT_EQ(game.deletePlayer(3),0);
}

TEST(room_test, find_player){
    EXPECT_EQ(game.joinPlayer(player),1);
    EXPECT_EQ(game.joinPlayer(5,"MY"),1);
    EXPECT_EQ(game.findPlayer(3).getId(),3);
    EXPECT_EQ(game.findPlayer(4).getId(),-1);
    EXPECT_EQ(game.deletePlayer(5),1);
    EXPECT_EQ(game.deletePlayer(3),1);
}

TEST(room_test, count_player){
    EXPECT_EQ(game.joinPlayer(player),1);
    EXPECT_EQ(game.joinPlayer(5,"MY"),1);
    EXPECT_EQ(game.countPlayers(),2);
    EXPECT_EQ(game.deletePlayer(5),1);
    EXPECT_EQ(game.deletePlayer(3),1);
}


// int main(void){
//     cout<<"-----roomTest-----"<<endl;
//     cout<<"-"<<endl;
//     cout<<room.findPlayer(3).getId()<<endl;
//     cout<<room.findPlayer(4).getId()<<endl;
//     cout<<get<0>(room.findPlayer(3).getPosition())<<endl;
//     room.findPlayer(3).setPosition(3.2,2.4);
//     tuple<float,float> temp3=room.findPlayer(3).getPosition();
//     cout<<get<0>(temp3)<<endl;
// }

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}