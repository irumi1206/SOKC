#include <jsoncpp/json/json.h>
#include <iostream>

using namespace std;

enum Team{
    PoolC,
    Morgo
};
class Side{
public:
    Team team;
    void setTeam(Team team){
        this->team=team;
    }
    Team getTeam(){
        return this->team;
    }
};

int main(void){
    Side team;
    Side team1;
    Side team2;
    team.setTeam(PoolC);
    team1.setTeam(PoolC);
    team2.setTeam(Morgo);
    cout<<(team.getTeam()==team2.getTeam())<<endl;
    cout<<(team.getTeam()==team1.getTeam())<<endl;
    cout<<team.getTeam()<<endl;
    cout<<team2.getTeam()<<endl;
    
}