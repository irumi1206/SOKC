#include <iostream>
#include "playerImplements/scorePlayer.cpp"
#include "playerImplements/positionPlayer.cpp"
#include "playerImplements/missionPlayer.cpp"
#include "playerImplements/rolePlayer.cpp"



class Player
{
private:
    std::string name;
    int id;
    CharacterRoleFlag roleflag;
    bool Die=false;
    SerializableVector3 position;
    PlayerScore score;
    Mission mission;
    bool isHost;
    int color;
public://initializer
    Player(int id, std::string name){
        this->id=id;
        this->name=name;
        this->roleflag=CharacterRoleFlag();
    }
    Player(){
        this->id=-1;
    }
public:
    bool isDie(){
        return this->Die;
    }
    void dead(){
        this->Die=true;
    }
    void live(){
        this->Die=false;
    }
public: //getter & setter
    std::string getName(){
        return name;
    }
    int getId(){
        return id;
    }
    int getColor(){
        return color;
    }
    void setColor(int color){
        this->color=color;
    }
public: //Mission
    void addMission(int missionId){
        this->mission.add(missionId);
    }
    std::vector<int> getMission(){
        return this->mission.get();
    }
    int countMission(){
        return this->mission.count();
    }
    void clearMission(){
        this->mission.clear();
    }
    void finishMission(int missionId){
        this->mission.finish(missionId);
    }
    void assignMission(int count){
        this->mission.assign(count,this->id);
    }
public: //position
    void setPosition(float x,float y){
        this->position.setPosition(x,y);
    }
    std::tuple<float,float> getPosition(){
        return std::make_tuple(position.x,position.y);
    }
public: //score
    void addKillScore(int scores){
        this->score.addKill(scores);
    }
    void addMissionScore(int scores){
        this->score.addMission(scores);
    }
    void addVotingAc(int scores){
        this->score.addVotingAc(scores);
    }
    void addVotingMi(int scores){
        this->score.addVotingMi(scores);
    }
    void addPOTGScore(int scores){
        this->score.addPOTG(scores);
    }
    void addSOTGScore(int scores){
        this->score.addSOTG(scores);
    }
    void clearScore(){
        this->score.reset();
    }
    int getMissionScore(){
        return this->score.getMission();
    }
    int getKillScore(){
        return this->score.getKill();
    }
    int getPOTGScore(){
        return this->score.getPOTG();
    }
    int getSOTGScore(){
        return this->score.getSOTG();
    }
    float votingAccuracy(){
        return this->score.votingAccuracy();
    }
};