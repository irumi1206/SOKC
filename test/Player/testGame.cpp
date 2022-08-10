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
    // vector<int> poolcList=game.getPoolc();
    // vector<int> molgoList=game.getMolgo();
    // vector<int> midList=game.getMid();
    // EXPECT_EQ(poolcList.size(),4);
    // EXPECT_EQ(molgoList.size(),2);
    // EXPECT_EQ(midList.size(),2);
}

TEST(color_test,assign_color_auto){
    Game game=Game();
    int id1=game.joinPlayer("player1");
    int id2=game.joinPlayer("player2");
    int id3=game.joinPlayer("player3");
    int id4=game.joinPlayer("player4");
    int id5=game.joinPlayer("player5");
    int id6=game.joinPlayer("player6");
    int id7=game.joinPlayer("player7");
    int id8=game.joinPlayer("player8");
    EXPECT_EQ(game.findPlayer(id1).getColor(),2);
    EXPECT_EQ(game.findPlayer(id2).getColor(),3);
    EXPECT_EQ(game.findPlayer(id3).getColor(),4);
    EXPECT_EQ(game.findPlayer(id4).getColor(),5);
    EXPECT_EQ(game.findPlayer(id5).getColor(),6);
    EXPECT_EQ(game.findPlayer(id6).getColor(),7);
    EXPECT_EQ(game.findPlayer(id7).getColor(),8);
    EXPECT_EQ(game.findPlayer(id8).getColor(),9);
}

TEST(host_test,first_player_host){
    Game game=Game();
    int id1=game.joinPlayer("player1");
    int id2=game.joinPlayer("player2");
    int id3=game.joinPlayer("player3");
    EXPECT_EQ(game.hostId,id1);
    game.findPlayer(game.hostId).setColor(10);
    EXPECT_EQ(game.findPlayer(id1).getColor(),10);
}

TEST(start_game,game_start){
    Game game=Game();
    int id1=game.joinPlayer("player1");
    int id2=game.joinPlayer("player2");
    int id3=game.joinPlayer("player3");
    int id4=game.joinPlayer("player4");
    int id5=game.joinPlayer("player5");
    int id6=game.joinPlayer("player6");
    int id7=game.joinPlayer("player7");
    int id8=game.joinPlayer("player8");
    game.gameStart();
    // EXPECT_EQ(game.getMolgo().size(),2);
    // EXPECT_EQ(game.getPoolc().size(),4);
    // EXPECT_EQ(game.getMid().size(),2);
    for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
        EXPECT_EQ(player.getMission().size(),3);
    });
}

TEST(Vote,voting_all){
    Game game=Game();
    int id1=game.joinPlayer("player1");
    int id2=game.joinPlayer("player2");
    int id3=game.joinPlayer("player3");
    int id4=game.joinPlayer("player4");
    int id5=game.joinPlayer("player5");
    int id6=game.joinPlayer("player6");
    int id7=game.joinPlayer("player7");
    int id8=game.joinPlayer("player8");
    game.putVote(id1,id2);
    game.putVote(id2,id2);
    game.putVote(id3,id2);
    game.putVote(id4,id1);
    game.putVote(id5,id1);
    game.putVote(id6,id4);
    game.putVote(id7,id5);
    game.putVote(id8,id6);
    EXPECT_EQ(game.calculateVoteDead(),id2);
    game.clearVoteStorage();
    game.putVote(id1,id2);
    game.putVote(id2,id2);
    game.putVote(id3,id2);
    game.putVote(id4,id1);
    game.putVote(id5,id1);
    game.putVote(id6,id1);
    game.putVote(id7,id5);
    game.putVote(id8,id6);
    EXPECT_EQ(game.calculateVoteDead(),-1);
}


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}