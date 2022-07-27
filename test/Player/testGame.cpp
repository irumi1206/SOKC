#include <iostream>
#include "/home/ubuntu/GameProject/SOKC/Player/Game.h"
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


TEST(role_test,assign_Role){
    Game game=Game();
    int id1=game.joinPlayer("player1");
    int id2=game.joinPlayer("player2");
    int id3=game.joinPlayer("player3");
    int id4=game.joinPlayer("player4");
    int id5=game.joinPlayer("player5");
    int id6=game.joinPlayer("player6");
    int id7=game.joinPlayer("player7");
    int id8=game.joinPlayer("player8");
    game.setMolgoCount(2);
    game.setMidCount(2);
    game.assignRole();
    vector<Player> list=game.getPlayers();
    for_each(list.begin(),list.end(),[&](Player& player){
        cout<<player.getName()<<"("<<player.getId()<<") : "<<player.getRole()<<endl;
    });
    vector<int> poolcList=game.getPoolc();
    vector<int> molgoList=game.getMolgo();
    vector<int> midList=game.getMid();
    EXPECT_EQ(poolcList.size(),4);
    EXPECT_EQ(molgoList.size(),2);
    EXPECT_EQ(midList.size(),2);
    for_each(poolcList.begin(),poolcList.end(),[&](int player){
        cout<<"PoolC : "<<player<<endl;
    });
    for_each(molgoList.begin(),molgoList.end(),[&](int player){
        cout<<"Molgo : "<<player<<endl;
    });
    for_each(midList.begin(),midList.end(),[&](int player){
        cout<<"Mid : "<<player<<endl;
    });

}


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}