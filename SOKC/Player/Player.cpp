#include <iostream>
#include "Player.h"

Player::Player(int id, std::string name){
    this->id=id;
    this->name=name;
    this->roleflag=CharacterRoleFlag();
    this->color=0;
};
Player::Player(){
    this->id=-3;
};
bool Player::isDie(){
    return this->die;
};
int Player::dead(){
    this->die=true;
    return 1;
};
void Player::live(){
    this->die=false;
};
int Player::getVoteCount(){
    return this->voteCount;
};
std::string Player::getName(){
    return name;
};
void Player::setName(std::string name){
    this->name=name;
};
int Player::getId(){
    return id;
};
//id는 바꿀 수 없으므로 setId는 만들어놓지 않음.
int Player::getColor(){
    return color;
};
void Player::setColor(int color){
    this->color=color;
};
Team Player::getTeam(){
    return roleflag.getTeam();
};
int Player::getRole(){
    return roleflag.getRole();
};
void Player::setRole(int role){
    this->roleflag.setRole(role);
};

//강제로 미션 한개 추가
void Player::addMission(int missionId){
    this->mission.add(missionId);
};
//할당된 미션 가져오기
std::vector<int> Player::getMission(){
    return this->mission.get();
};
//남은 미션 개수
int Player::countMission(){
    return this->mission.count();
};
//할당된 미션 없얘기 (flush)
void Player::resetMission(){
    this->mission.reset();
};
//미션 클리어
void Player::finishMission(int missionId){
    this->mission.finish(missionId);
};
//killscore추가
void Player::addKillScore(int scores){
    this->score.addKill(scores);
};
//missionscore추가
void Player::addMissionScore(int scores){
    this->score.addMission(scores);
};
//정확히 투표 했을 경우(accurate)
void Player::addVotingAc(int scores){
    this->score.addVotingAc(scores);
};
//잘못 투표했을 경우(miss)
void Player::addVotingMi(int scores){
    this->score.addVotingMi(scores);
};
//POTG점수 추가
void Player::addPOTGScore(int scores){
    this->score.addPOTG(scores);
};
//SOTG점수 추가
void Player::addSOTGScore(int scores){
    this->score.addSOTG(scores);
};
//점수 초기화
void Player::clearScore(){
    this->score.reset();
};
//미션점수 가져오기
int Player::getMissionScore(){
    return this->score.getMission();
};
//킬점수 가져오기
int Player::getKillScore(){
    return this->score.getKill();
};
int Player::getPOTGScore(){
    return this->score.getPOTG();
};
int Player::getSOTGScore(){
    return this->score.getSOTG();
};
//투표정확도 가져오기(float으로 출력)
float Player::votingAccuracy(){
    return this->score.votingAccuracy();
};

void Player::setStatus(PlayStatus status){
    this->status=status;
}

PlayStatus Player::getPlayStatus(){
    return this->status;
}