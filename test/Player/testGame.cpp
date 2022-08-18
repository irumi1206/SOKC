#include <iostream>
#include "/home/ubuntu/GameProject/SOKC/Player/Game.h"
#include <gtest/gtest.h>

using namespace std;


TEST(room_test, join_player){
    Game game=Game();
    int id1 = game.joinPlayer("MY",1);
    EXPECT_EQ(game.countPlayers(),1);
    int id2=game.joinPlayer("YM",2);
    EXPECT_EQ(game.countPlayers(),2);
    EXPECT_EQ(game.deletePlayer(id1),1);
    EXPECT_EQ(game.deletePlayer(id2),1);
    EXPECT_EQ(game.deletePlayer(id2),0);
}

TEST(room_test, find_player){
    Game game=Game();
    int id1 = game.joinPlayer("MY",1);
    int id2=game.joinPlayer("YM",2);
    EXPECT_EQ(game.findPlayer(id1).getId(),id1);
    EXPECT_EQ(game.findPlayer(100).getId(),-1);
    EXPECT_EQ(game.deletePlayer(id1),1);
    EXPECT_EQ(game.deletePlayer(id2),1);
}

TEST(room_test, count_player){
    Game game=Game();
    int id1 = game.joinPlayer("MY",1);
    int id2=game.joinPlayer("YM",2);
    EXPECT_EQ(game.countPlayers(),2);
    EXPECT_EQ(game.deletePlayer(id1),1);
    EXPECT_EQ(game.deletePlayer(id2),1);
}


TEST(role_test,assign_Role){
    Game game=Game();
    int id1=game.joinPlayer("player1",1);
    int id2=game.joinPlayer("player2",2);
    int id3=game.joinPlayer("player3",3);
    int id4=game.joinPlayer("player4",4);
    int id5=game.joinPlayer("player5",5);
    int id6=game.joinPlayer("player6",6);
    int id7=game.joinPlayer("player7",7);
    game.setMorgoCount(2);
    game.setMidCount(1);
    game.assignRole();
    vector<Player> list=game.getPlayers();
    int poolc=0;
    int morgo=0;
    int mid=0;
    for_each(list.begin(), list.end(),[&](Player& player){
        if(player.getTeam()==PoolC){
            poolc++;
        }else if(player.getTeam()==Morgo){
            morgo++;
        }else if(player.getTeam()==Mid){
            mid++;
        }
    });
    EXPECT_EQ(poolc, 4);
    EXPECT_EQ(morgo, 2);
    EXPECT_EQ(mid, 1);
}

TEST(settings,count){
    Game game = Game();
    game.setMorgoCount(2);
    game.setMidCount(1);
    EXPECT_EQ(game.getMorgoCount(),2);
    EXPECT_EQ(game.getMidCount(),1);
    EXPECT_EQ(game.getMissionCount(),1);
}

TEST(settings,cooltime){
    Game game = Game();
    game.setKillCoolTime(30);
    game.setConferenceCoolTime(20);
    game.setDiscussionTime(20);
    game.setVotingTime(40);
    EXPECT_EQ(game.getKillCoolTime(),30);
    EXPECT_EQ(game.getConferenceCoolTime(),20);
    EXPECT_EQ(game.getDiscussionTime(),20);
    EXPECT_EQ(game.getVotingTime(),40);
}

TEST(color_test,assign_color_auto){
    Game game=Game();
    int id1=game.joinPlayer("player1",1);
    int id2=game.joinPlayer("player2",2);
    int id3=game.joinPlayer("player3",3);
    int id4=game.joinPlayer("player4",4);
    int id5=game.joinPlayer("player5",5);
    int id6=game.joinPlayer("player6",6);
    int id7=game.joinPlayer("player7",7);
    EXPECT_EQ(game.findPlayer(id1).getColor(),2);
    EXPECT_EQ(game.findPlayer(id2).getColor(),3);
    EXPECT_EQ(game.findPlayer(id3).getColor(),4);
    EXPECT_EQ(game.findPlayer(id4).getColor(),5);
    EXPECT_EQ(game.findPlayer(id5).getColor(),6);
    EXPECT_EQ(game.findPlayer(id6).getColor(),7);
    EXPECT_EQ(game.findPlayer(id7).getColor(),8);
}

TEST(host_test,first_player_host){
    Game game=Game();
    int id1=game.joinPlayer("player1",1);
    int id2=game.joinPlayer("player2",2);
    int id3=game.joinPlayer("player3",3);
    EXPECT_EQ(game.hostId,id1);
    game.findPlayer(game.hostId).setColor(10);
    EXPECT_EQ(game.findPlayer(id1).getColor(),10);
}

TEST(start_game,game_start){
    Game game=Game();
    int id1=game.joinPlayer("player1",1);
    int id2=game.joinPlayer("player2",2);
    int id3=game.joinPlayer("player3",3);
    int id4=game.joinPlayer("player4",4);
    int id5=game.joinPlayer("player5",5);
    int id6=game.joinPlayer("player6",6);
    int id7=game.joinPlayer("player7",7);
    game.gameStart();
    vector<Player> list=game.getPlayers();
    int poolc=0;
    int morgo=0;
    int mid=0;
    for_each(list.begin(), list.end(),[&](Player& player){
        if(player.getTeam()==PoolC){
            poolc++;
        }else if(player.getTeam()==Morgo){
            morgo++;
        }else if(player.getTeam()==Mid){
            mid++;
        }
    });
    EXPECT_EQ(poolc, 4);
    EXPECT_EQ(morgo, 2);
    EXPECT_EQ(mid, 1);
    for_each(game.playerList.begin(),game.playerList.end(),[&](Player& player){
        EXPECT_EQ(player.getMission().size(),1);
    });
}

TEST(Vote,voting_all){
    Game game=Game();
    int id1=game.joinPlayer("player1",1);
    int id2=game.joinPlayer("player2",2);
    int id3=game.joinPlayer("player3",3);
    int id4=game.joinPlayer("player4",4);
    int id5=game.joinPlayer("player5",5);
    int id6=game.joinPlayer("player6",6);
    int id7=game.joinPlayer("player7",7);
    int id8=game.joinPlayer("player8",8);
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