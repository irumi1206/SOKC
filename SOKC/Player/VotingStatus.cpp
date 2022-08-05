#include "VotingStatus.h"
VotingStatus::VotingStatus(){
    this->votingPlayerId=-1;
    this->votedPlayerId=-1;
};
        
VotingStatus::VotingStatus(int votingPlayerId,int votedPlayerId){
    this->votingPlayerId=votingPlayerId;
    this->votedPlayerId=votedPlayerId;
};

void VotingStatus::setValue(int votingPlayerId,int votedPlayerId){
    this->votingPlayerId=votingPlayerId;
    this->votedPlayerId=votedPlayerId;
}