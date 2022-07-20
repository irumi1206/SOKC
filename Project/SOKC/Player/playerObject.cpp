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
    CharacterRoleFlag roleflag;//직업(역할)
    bool die=false;//살았는지 죽었는지
    SerializableVector3 position;//위치
    PlayerScore score;//점수 object
    Mission mission;//미션 object
    bool isHost;//해당 플레이어가 호스트인지
    int color;//색 확인
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
        return this->die;
    }
    void dead(){
        this->die=true;
    }
    void live(){
        this->die=false;
    }
public: //getter & setter
    std::string getName(){
        return name;
    }
    void setName(std::string name){
        this->name=name;
    }
    int getId(){
        return id;
    }
    //id는 바꿀 수 없으므로 setId는 만들어놓지 않음.
    int getColor(){
        return color;
    }
    void setColor(int color){
        this->color=color;
    }
public://role
    Team getTeam(){
        return roleflag.getTeam();
    }
    int getRole(){
        return roleflag.getRole();
    }
    void setRole(int role){
        this->roleflag.setRole(role);
    }
    
public: //Mission
    //강제로 미션 한개 추가
    void addMission(int missionId){
        this->mission.add(missionId);
    }
    //할당된 미션 가져오기
    std::vector<int> getMission(){
        return this->mission.get();
    }
    //남은 미션 개수
    int countMission(){
        return this->mission.count();
    }
    //할당된 미션 없얘기 (flush)
    void resetMission(){
        this->mission.reset();
    }
    //미션 클리어
    void finishMission(int missionId){
        this->mission.finish(missionId);
    }
    //미션 할당, 개수를 넣으면 할당해줌.
    void assignMission(int count){
        this->mission.assign(count,this->id);
    }
public: //position
    //위치 지정
    void setPosition(float x,float y){
        this->position.setPosition(x,y);
    }
    //위치값을 tuple로 받기
    std::tuple<float,float> getPosition(){
        return std::make_tuple(position.x,position.y);
    }
public: //score
    //killscore추가
    void addKillScore(int scores){
        this->score.addKill(scores);
    }
    //missionscore추가
    void addMissionScore(int scores){
        this->score.addMission(scores);
    }
    //정확히 투표 했을 경우(accurate)
    void addVotingAc(int scores){
        this->score.addVotingAc(scores);
    }
    //잘못 투표했을 경우(miss)
    void addVotingMi(int scores){
        this->score.addVotingMi(scores);
    }
    //POTG점수 추가
    void addPOTGScore(int scores){
        this->score.addPOTG(scores);
    }
    //SOTG점수 추가
    void addSOTGScore(int scores){
        this->score.addSOTG(scores);
    }
    //점수 초기화
    void clearScore(){
        this->score.reset();
    }
    //미션점수 가져오기
    int getMissionScore(){
        return this->score.getMission();
    }
    //킬점수 가져오기
    int getKillScore(){
        return this->score.getKill();
    }
    int getPOTGScore(){
        return this->score.getPOTG();
    }
    int getSOTGScore(){
        return this->score.getSOTG();
    }
    //투표정확도 가져오기(float으로 출력)
    float votingAccuracy(){
        return this->score.votingAccuracy();
    }
};