#include <iostream>
#include "roomObject.cpp"

using namespace std;

int main(void){
    cout<<"-----score test-----"<<endl;
    Player player=Player(3,"YM");
    cout<<player.getKillScore()<<endl;
    player.addKillScore(1);
    cout<<player.getKillScore()<<endl;
    cout<<player.getName()<<endl;
    player.addVotingAc(1);
    cout<<player.votingAccuracy()<<endl;
    player.addVotingAc(1);
    player.addVotingMi(2);
    cout<<player.votingAccuracy()<<endl;
    cout<<"-----position test-----"<<endl;
    player.setPosition(3.5,6.2);
    tuple<float,float> temp=player.getPosition();
    cout<<get<0>(temp)<<endl;
    cout<<get<1>(temp)<<endl;
    cout<<"-----mission test-----"<<endl;
    player.addMission(3);
    player.addMission(4);
    cout<<"count\t"<<player.countMission()<<endl;
    vector<int> temp1=player.getMission();
    for_each(temp1.begin(),temp1.end(),[&](int& n){
        cout<<n<<endl;
    });
    player.finishMission(3);
    cout<<"count\t"<<player.countMission()<<endl;
    player.addMission(5);
    cout<<"count\t"<<player.countMission()<<endl;
    player.clearMission();
    cout<<"count\t"<<player.countMission()<<endl;
    player.assignMission(3);
    vector<int> temp2=player.getMission();
    for_each(temp2.begin(),temp2.end(),[&](int& n){
        cout<<n<<" ";
    });
    cout<<endl;
    cout<<"-----player test-----"<<endl;
    cout<<"isDie: "<<player.isDie()<<endl;
    player.dead();
    cout<<"isDie: "<<player.isDie()<<endl;
    player.live();
    cout<<"isDie: "<<player.isDie()<<endl;
    cout<<"-----roomTest-----"<<endl;
    Room room=Room();
    cout<<room.joinPlayer(5,"MY")<<" ";
    cout<<room.joinPlayer(5,"MY")<<" ";
    cout<<room.countPlayers()<<endl;
    cout<<"-"<<endl;
    cout<<room.joinPlayer(player)<<" ";
    cout<<room.countPlayers()<<endl;
    cout<<"-"<<endl;
    cout<<room.joinPlayer(player)<<" ";
    cout<<room.countPlayers()<<endl;
    cout<<"-"<<endl;
    cout<<room.findPlayer(3).getId()<<endl;
    cout<<room.findPlayer(4).getId()<<endl;
    cout<<get<0>(room.findPlayer(3).getPosition())<<endl;
    room.findPlayer(3).setPosition(3.2,2.4);
    tuple<float,float> temp3=room.findPlayer(3).getPosition();
    cout<<get<0>(temp3)<<endl;
}