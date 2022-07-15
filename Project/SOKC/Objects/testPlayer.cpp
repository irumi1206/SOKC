#include <iostream>
#include "playerObject.cpp"
#include <gtest/gtest.h>
#include <tuple>
#include <vector>

using namespace std;
TEST(score_test,add_kill_score){
    Player player=Player(3,"YM");
    EXPECT_EQ(player.getKillScore(),0);
    player.addKillScore(1);
    EXPECT_EQ(player.getKillScore(),1);
}

TEST(score_test,add_voting_score){
    Player player=Player(3,"YM");
    player.addVotingAc(1);
    EXPECT_EQ(player.votingAccuracy(),1);
    player.addVotingAc(1);
    player.addVotingMi(2);
    EXPECT_EQ(player.votingAccuracy(),0.5);
}

TEST(player_info_test,get_name){
    Player player=Player(3,"YM");
    EXPECT_EQ(player.getName(),"YM");
}
TEST(player_info_test,isDie){
    Player player=Player(3,"YM");
    EXPECT_EQ(player.isDie(),false);
    player.dead();
    EXPECT_EQ(player.isDie(),true);
    player.live();
    EXPECT_EQ(player.isDie(),false);
}

TEST(position_test,position){
    Player player=Player(3,"YM");
    player.setPosition(3.5,6.2);
    tuple<float,float> temp=make_tuple(3.5,6.2);
    EXPECT_EQ(player.getPosition(),temp);
}

TEST(mission_test,add_mission){
    Player player=Player(3,"YM");
    player.addMission(3);
    player.addMission(4);
    EXPECT_EQ(player.countMission(),2);
    vector<int> temp1={3,4};
    EXPECT_EQ(player.getMission(),temp1);
    player.finishMission(3);
    EXPECT_EQ(player.countMission(),1);
    vector<int> temp2={4};
    EXPECT_EQ(player.getMission(),temp2);
    player.addMission(5);
    EXPECT_EQ(player.countMission(),2);
    player.clearMission();
    player.assignMission(3);
    EXPECT_EQ(player.countMission(),3);
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}